#ifndef SIGNALTRANSMITTER_H
#define SIGNALTRANSMITTER_H

#include <QObject>

//! This singleton class receives and emits some signals
class SignalTransmitter : public QObject
{
	Q_OBJECT

private:
	//! Singleton, thus private constructor
	SignalTransmitter();

public:
	//! Destructor
	virtual ~SignalTransmitter();

	//! Returns pointer to the instance
	static SignalTransmitter* GetInstance();

signals:
	//! Should be emitted when GeoFence file is loaded
	void SignalLoadGF(QString qsName);

private:
	//! Pointer to the instance
	static SignalTransmitter* s_pInstance;
};


#endif // SIGNALTRANSMITTER_H
