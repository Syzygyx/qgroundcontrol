#include <QDebug>
#include <QMessageBox>

#include "ExternalAppLauncher.h"

//-----------------------------------------------------------------------------

ExternalAppLauncher::ExternalAppLauncher(QObject *pParent) :
	QObject(pParent)
{
	m_pProcess = new QProcess(this);
	// make sure that error at startup is reported
	connect(
				m_pProcess,
				SIGNAL(error(QProcess::ProcessError)),
				this,
				SLOT(HandleError(QProcess::ProcessError))
				);

	// magic string checking
	connect(
				m_pProcess,
				SIGNAL(readyReadStandardOutput()),
				this,
				SLOT(ReadStandardOutput())
				);
	connect(
				m_pProcess,
				SIGNAL(readyReadStandardError()),
				this,
				SLOT(ReadStandardOutput())
				);

	// make sure SignalFinished is emitted when process is finished
	connect(
				m_pProcess,
				SIGNAL(finished(int)),
				this,
				SIGNAL(SignalFinished())
				);
}

//-----------------------------------------------------------------------------

ExternalAppLauncher::~ExternalAppLauncher()
{
	delete m_pProcess;
}

//-----------------------------------------------------------------------------

void ExternalAppLauncher::Launch(QString qsApp, QString qsPar, QString qsUrl)
{
	m_qsApp = qsApp;
	m_qsPar = qsPar;
	m_qsUrl = qsUrl;
	QString qsCommand = m_qsApp + " " + m_qsPar;
	m_pProcess->start(qsCommand);
}

//-----------------------------------------------------------------------------

void ExternalAppLauncher::HandleError(QProcess::ProcessError ePE)
{
	if (ePE == QProcess::FailedToStart) {
		QString qsMsg = tr("Looks like %1 is not installed on this computer. ").arg(m_qsApp);
		if (m_qsUrl.length() > 0)
			qsMsg += tr("You can download %1 from %2 and install it.").arg(m_qsApp).arg(m_qsUrl);

		QMessageBox::warning(
					0,
					tr("Failed to launch %1").arg(m_qsApp),
					qsMsg
					);
	}
}

//-----------------------------------------------------------------------------

void ExternalAppLauncher::ReadStandardOutput()
{
	QString qsText = m_pProcess->readAllStandardOutput();
	QString qsErr = m_pProcess->readAllStandardError();
	if (m_qsMagic.length() > 0) {
		if (qsText.indexOf(m_qsMagic) >= 0 || qsErr.indexOf(m_qsMagic) >= 0) {
			emit SignalReady();
		}
	}
}

//-----------------------------------------------------------------------------

