#ifndef EXTERNALAPPLAUNCHER_H
#define EXTERNALAPPLAUNCHER_H

#include <QObject>
#include <QProcess>

//! This class is used to launch external applications
class ExternalAppLauncher : public QObject
{
	Q_OBJECT

public:
	//! Constructor
	ExternalAppLauncher(QObject* pParent = 0);
	//! Destructor
	~ExternalAppLauncher();

	//! Launches the application with the given parameters.
	void Launch(
			QString qsApp,
			QString qsPar,
			QString qsUrl,
			QStringList qslDirs,
			QString qsName = ""
			);
	//! Sets the magic string
	void SetMagicString(QString qsMagic)
	{	m_qsMagic = qsMagic; }

protected slots:
	//! Called when error occured when launching application or during its execution
	void HandleError(QProcess::ProcessError ePE);
	//! Reads from standard output and emits SignalReady, if necessary
	void ReadStandardOutput();
	//! Emits SignalReady if it hasn't been emitted yet
	void CheckReady();

signals:
	//! Emitted when magic string is read from the application output
	void SignalReady();
	//! Emitted when process has finished
	void SignalFinished();
	//! Emitted when process failed to launch
	void SignalFailed();

private:
	//! Index of currently used working path
	int m_iPath;
	//! List of possible application paths
	QStringList m_qslDirs;
	//! Name of external application executable
	QString m_qsApp;
	//! External application parameters
	QString m_qsPar;
	//! External application download page
	QString m_qsUrl;
	//! Application real name
	QString m_qsName;
	//! When this string is read from app output, SignalReady is emitted
	QString m_qsMagic;
	//! Pointer to the process object
	QProcess* m_pProcess;
	//! Timeout after which the process will emit SignalReady [ms]
	int m_iTimeout;
	//! Indicates whether SignalReady has been emitted after launch
	bool m_bSignalled;
};

#endif // EXTERNALAPPLAUNCHER_H
