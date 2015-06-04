#include "MAVLinkProtocol.h"
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
}

//-----------------------------------------------------------------------------

MessageDispatcher::~MessageDispatcher()
{
	//delete m_pMAVLink;
}

//-----------------------------------------------------------------------------

MessageDispatcher* MessageDispatcher::GetInstance()
{
	if (s_pInstance == 0)
		s_pInstance = new MessageDispatcher;
	return s_pInstance;
}

//-----------------------------------------------------------------------------

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

	bool bOK;
	double dVal = vValue.toDouble(&bOK);
	QMetaType::Type eMT = static_cast<QMetaType::Type>(vValue.type());

	// ignore messages which do not carry numerical value
	if (bOK == false || eMT == QMetaType::QString || eMT == QMetaType::QByteArray)
		return;

	if (qsName == "groundSpeed")
		emit SignalGroundSpeed(dVal);
}

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
}

//-----------------------------------------------------------------------------

void MessageDispatcher::InitUAS(UASInterface* pUAS)
{
	if (m_pUAS == 0)
		SetActiveUAS(pUAS);
}

//-----------------------------------------------------------------------------

MessageDispatcher* MessageDispatcher::s_pInstance = 0;

//-----------------------------------------------------------------------------

