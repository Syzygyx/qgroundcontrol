#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QTimer>

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

    m_iTimeout = 45000;
}

//-----------------------------------------------------------------------------

ExternalAppLauncher::~ExternalAppLauncher()
{
	delete m_pProcess;
}

//-----------------------------------------------------------------------------

void ExternalAppLauncher::Launch(
		QString qsApp,
		QString qsPar,
		QString qsUrl,
		QStringList qslDirs
		)
{
	m_iPath = 0;
	m_qslDirs = qslDirs;
	m_qsApp = qsApp;
	m_qsPar = qsPar;
	m_qsUrl = qsUrl;

	if (m_qslDirs[m_iPath].length() > 0)
		m_pProcess->setWorkingDirectory(QDir::toNativeSeparators(m_qslDirs[m_iPath]));
	QString qsCommand = m_qsApp + " " + m_qsPar;

	m_bSignalled = false;
	m_pProcess->start(qsCommand);

	// emit SignalReady after 20s
	QTimer::singleShot(m_iTimeout, this, SLOT(CheckReady()));
}

//-----------------------------------------------------------------------------

void ExternalAppLauncher::HandleError(QProcess::ProcessError ePE)
{
	if (ePE == QProcess::FailedToStart) {
		// look if there are more candidates
		m_iPath++;
		if (m_iPath < m_qslDirs.count()) {
			// try next working dir
			if (m_qslDirs[m_iPath].length() > 0)
				m_pProcess->setWorkingDirectory(m_qslDirs[m_iPath]);
			QString qsCommand = m_qsApp + " " + m_qsPar;
			m_pProcess->start(qsCommand);
			return;
		}

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
			CheckReady();
		}
	}
}

//-----------------------------------------------------------------------------

void ExternalAppLauncher::CheckReady()
{
	qDebug() << "Checking ready" << m_bSignalled;
	if (m_bSignalled == false) {
		emit SignalReady();
		m_bSignalled = true;
		qDebug() << "Application launched!";
	}
}

//-----------------------------------------------------------------------------

