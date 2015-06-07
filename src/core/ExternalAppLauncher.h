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
	void Launch(QString qsApp, QString qsPar = "", QString qsUrl = "");
	//! Sets the magic string
	void SetMagicString(QString qsMagic)
	{	m_qsMagic = qsMagic; }

protected slots:
	//! Called when error occured when launching application or during its execution
	void HandleError(QProcess::ProcessError ePE);
	//! Reads from standard output and emits SignalReady, if necessary
	void ReadStandardOutput();

signals:
	//! Emitted when magic string is read from the application output
	void SignalReady();
	//! Emitted when process has finished
	void SignalFinished();

private:
	//! External application name
	QString m_qsApp;
	//! External application parameters
	QString m_qsPar;
	//! External application download page
	QString m_qsUrl;
	//! When this string is read from app output, SignalReady is emitted
	QString m_qsMagic;
	//! Pointer to the process object
	QProcess* m_pProcess;
};

#endif // EXTERNALAPPLAUNCHER_H
