#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QTimer>

#include "ExternalAppLauncher.h"

#if defined(Q_OS_WIN32)
    #define PARENTHESIS             "\""
#else
    #define PARENTHESIS             ""
#endif

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
		QStringList qslDirs,
		QString qsName
		)
{
	m_iPath = 0;
	m_qslDirs = qslDirs;
	m_qsApp = qsApp;
	m_qsPar = qsPar;
	m_qsUrl = qsUrl;
	if (qsName.length() == 0)
		m_qsName = m_qsApp;
	else
		m_qsName = qsName;

	if (m_qslDirs[m_iPath].length() > 0)
        m_pProcess->setWorkingDirectory(m_qslDirs[m_iPath]);
    QString qsCommand = m_qsApp;
    if (m_qslDirs[m_iPath].length() > 0)
        qsCommand = PARENTHESIS + m_qslDirs[m_iPath] + "/" + m_qsApp + PARENTHESIS;

	m_bSignalled = false;
    m_pProcess->start(qsCommand + " " + m_qsPar);

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
            QString qsCommand = m_qsApp;
            if (m_qslDirs[m_iPath].length() > 0)
                qsCommand = PARENTHESIS + m_qslDirs[m_iPath] + "/" + m_qsApp + PARENTHESIS;
            m_pProcess->start(qsCommand + " " + m_qsPar);
			return;
		}

		QString qsMsg = tr("Looks like %1 is not installed on this computer. ").arg(m_qsName);
		if (m_qsUrl.length() > 0)
			qsMsg += tr("You can download %1 from %2 and install it.").arg(m_qsName).arg(m_qsUrl);

		qsMsg += tr("\n\nIs %1 already installed on your computer and you would like to find it yourself?").arg(m_qsName);

		QMessageBox::StandardButton sb = (QMessageBox::StandardButton)QMessageBox::warning(
					0,
					tr("Failed to launch %1").arg(m_qsApp),
					qsMsg,
					QMessageBox::Yes,
					QMessageBox::No
					);

		if (sb == QMessageBox::Yes)
			emit SignalFailed();
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
