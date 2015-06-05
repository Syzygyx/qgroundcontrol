#include <QDebug>

#include "comm/MAVLinkProtocol.h"
#include "uas/UASManager.h"

#include "MessageDispatcher.h"

//-----------------------------------------------------------------------------

MessageDispatcher::MessageDispatcher() : QObject()
{
	m_pUAS = 0;
	//m_pMAVLink = new MAVLinkDecoder(MAVLinkProtocol::instance(), this);

	// update current UAS on manager change
	connect(
				UASManager::instance(),
				SIGNAL(activeUASSet(UASInterface*)),
				this,
				SLOT(SetActiveUAS(UASInterface*))
				);
	// update current UAS on manager create, if it is not set yet
	connect(
				UASManager::instance(),
				SIGNAL(UASCreated(UASInterface*)),
				this,
				SLOT(InitUAS(UASInterface*))
				);

	InitUAS(UASManager::instance()->getActiveUAS());
	m_pTimer = new QTimer(this);
	m_pTimer->setInterval(100);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(Report()));
	m_pTimer->start();
}

//-----------------------------------------------------------------------------

MessageDispatcher::~MessageDispatcher()
{
	//delete m_pMAVLink;
	delete m_pTimer;
}

//-----------------------------------------------------------------------------

MessageDispatcher* MessageDispatcher::GetInstance()
{
	if (s_pInstance == 0)
		s_pInstance = new MessageDispatcher;
	return s_pInstance;
}

//-----------------------------------------------------------------------------

/*
void MessageDispatcher::DecodeMessage(
		int uasID,
		QString qsName,
		QString qsUnit,
		QVariant vValue,
		quint64 uiTime
		)
{
	Q_UNUSED(uasID);
	Q_UNUSED(qsUnit);
	Q_UNUSED(uiTime);

	//qDebug() << "MessageDispatcher::DecodeMessage" << uasID << qsName << qsUnit;
	bool bOK;
	double dVal = vValue.toDouble(&bOK);
	QMetaType::Type eMT = static_cast<QMetaType::Type>(vValue.type());

	// ignore messages which do not carry numerical value
	if (bOK == false || eMT == QMetaType::QString || eMT == QMetaType::QByteArray)
		return;

	if (qsName == "airSpeed") {
		//qDebug() << "air speed" << dVal << qsUnit;
		// conversion m/s -> knots (multiplier 1.94384)
		emit SignalAirSpeed(1.94384f*dVal);
	}
}
*/

//-----------------------------------------------------------------------------

void MessageDispatcher::SetActiveUAS(UASInterface* pUAS)
{
	if (pUAS == 0)
		return;

	m_pUAS = pUAS;
	connect(
				m_pUAS,
				SIGNAL(valueChanged(int,QString,QString,QVariant,quint64)),
				this,
				SLOT(DecodeMessage(int,QString,QString,QVariant,quint64))
				);

	connect(
				m_pUAS,
				SIGNAL(speedChanged(UASInterface*,double,double,quint64)),
				this,
				SLOT(ReportSpeed(UASInterface*,double,double,quint64))
				);

	connect(
				m_pUAS,
				SIGNAL(altitudeChanged(UASInterface*,double,double,double,double,quint64)),
				this,
				SLOT(ReportAltitude(UASInterface*,double,double,double,double,quint64))
				);
}

//-----------------------------------------------------------------------------

void MessageDispatcher::InitUAS(UASInterface* pUAS)
{
	if (m_pUAS == 0)
		SetActiveUAS(pUAS);
}

//-----------------------------------------------------------------------------

void MessageDispatcher::Report()
{
	if (m_pUAS != 0) {
		emit SignalHeading(180.0*m_pUAS->getYaw()/M_PI);
	}
}

//-----------------------------------------------------------------------------

void MessageDispatcher::ReportSpeed(
		UASInterface *,
		double dGroundSpeed,
		double dAirSpeed,
		quint64 uiTime
		)
{
	Q_UNUSED(dGroundSpeed);
	Q_UNUSED(uiTime);

	// convert from [m/s] into [knots]
	emit SignalAirSpeed(1.94384*dAirSpeed);
}

//-----------------------------------------------------------------------------

void MessageDispatcher::ReportAltitude(
		UASInterface *,
		double dAltAMSL,
		double dAltWGS84,
		double dAltRel,
		double dVario,
		quint64 uiTime
		)
{
	Q_UNUSED(dAltWGS84);
	Q_UNUSED(dAltRel);
	Q_UNUSED(uiTime);
	// convert altitude from [m] to [ft]
	emit SignalAltitude(3.28084f*dAltAMSL);
	emit SignalVario(dVario);
}

//-----------------------------------------------------------------------------

MessageDispatcher* MessageDispatcher::s_pInstance = 0;

//-----------------------------------------------------------------------------

