#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <QObject>
#include <QTimer>
#include "ui/MAVLinkDecoder.h"
#include "uas/UASInterface.h"

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

private slots:
	/*
	//! Used to decode MAVLink messages
	void DecodeMessage(
			int uasID,
			QString qsName,
			QString qsUnit,
			QVariant vValue,
			quint64 uiTime
			);
			*/
	//! Sets the active UAS
	void SetActiveUAS(UASInterface* pUAS);
	//! Sets the active UAS only if it is not set already
	void InitUAS(UASInterface* pUAS);
	//! Emits certain signals (heading)
	void Report();
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

signals:
	//! Emitted when ground speed has changed
	void SignalAirSpeed(double);
	//! Emitted when motor temperature has changed
	void SignalTemperature(double);
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

private:
	//! Pointer to the instance
	static MessageDispatcher* s_pInstance;
	//! Pointer to the MAVLinkDecoder object
	MAVLinkDecoder* m_pMAVLink;
	//! Pointer to the current UAS object
	UASInterface* m_pUAS;
	//! Internal timer used to emit some signals at regular intervals
	QTimer* m_pTimer;
};

#endif // MESSAGEDISPATCHER_H
