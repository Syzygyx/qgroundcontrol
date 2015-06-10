#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include <QtEndian>

#include "ui/MAVLinkDecoder.h"
#include "uas/UASInterface.h"
#include "core/net_fdm.hxx"

/** This class uses MAVLinkDecoder class and converts its messages into more user
 *  friendly ones
 */
class MessageDispatcher : public QObject
{
	Q_OBJECT

protected:
	//! This is singleton, thus protected constructor
	MessageDispatcher();
public:
	//! Destructor
	~MessageDispatcher();
	//! Returns the instance. Creates one, if it does not exist yet
	static MessageDispatcher* GetInstance();

public slots:
	//! Enables sending data over UDP port
	void EnableUDP();
	//! Disables sending data over UDP port
	void DisableUDP();
	//! Used to decode MAVLink messages
	void DecodeMessage(
			int uasID,
			QString qsName,
			QString qsUnit,
			QVariant vValue,
			quint64 uiTime
			);

private slots:
	//! Sets the active UAS
	void SetActiveUAS(UASInterface* pUAS);
	//! Sets the active UAS only if it is not set already
	void InitUAS(UASInterface* pUAS);
	//! Obtains position and attitude from UASInterface and also sends some signals (heading)
	void ReadUAS();

	//! Emits speed signal
	void ReportSpeed(
			UASInterface*,
			double dGroundSpeed,
			double dAirSpeed,
			quint64 uiTime
			);
	//! Emits altitude and vario signals
	void ReportAltitude(
			UASInterface*,
			double dAltAMSL,
			double dAltWGS84,
			double dAltRel,
			double dVario,
			quint64 uiTime
			);
	//! Sends information over UDP port
	void SendUDP();
	//! Testing only. Receive data from FG
	void GetData();

private:
	//! Converts uint32 to network order
	uint32_t ToNetwork(uint32_t uiVal) const;
	//! Converts float to network order
	float ToNetwork(float fVal) const;
	//! Converts double to network order
	double ToNetwork(double dVal) const;

	//! Returns the first integer it founds in the string, starting at i-th character
	int GetInt(QString qs, int i) const;

signals:
	//! Emitted when ground speed has changed
	void SignalAirSpeed(double);
	//! Emitted when altitude has changed
	void SignalAltitude(double);
	//! Emitted when vertical speed has changed
	void SignalVario(double);
	//! Emitted when heading has changed
	void SignalHeading(double);
	//! Emitted when fuel has changed
	void SignalFuel(double);
	//! Emitted when total weight has changed
	void SignalTotalWeight(double);
	//! Emitted when temperature and RPM of i-th servo have been read
	void SignalTempRPM(int, double, double);

private:
	//! Pointer to the instance
	static MessageDispatcher* s_pInstance;
	//! Pointer to the MAVLinkDecoder object
	MAVLinkDecoder* m_pMAVLink;
	//! Pointer to the current UAS object
	UASInterface* m_pUAS;
	//! Internal timer used to emit some signals at regular intervals
	QTimer* m_pTimer;
	//! Internal timer used to send information over UDP port
	QTimer* m_pTimerUDP;
	//! UDP socket for sending data
	QUdpSocket* m_pSocketUDP;
	//! Structure to be sent over UDP socket
	FGNetFDM m_netFDM;
	//! Indicates whether the sending data over UDP is allowed
	bool m_bSendUDP;
};

#endif // MESSAGEDISPATCHER_H
