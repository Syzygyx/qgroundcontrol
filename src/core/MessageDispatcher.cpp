#include <time.h>

#include <QDebug>

#include "comm/MAVLinkProtocol.h"
#include "uas/UASManager.h"

#include "MessageDispatcher.h"

//-----------------------------------------------------------------------------

MessageDispatcher::MessageDispatcher() : QObject()
{
	// reset the structure
	memset(&m_netFDM, 0, sizeof(m_netFDM));
	// save the correct version
	m_netFDM.version = ToNetwork(FG_NET_FDM_VERSION);

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

    // create a timer, which will trigger Report call 100 times per second
//	m_pTimer = new QTimer(this);
//    m_pTimer->setInterval(20);
//	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(ReadUAS()));
//	m_pTimer->start();

	m_bSendUDP = false;
    // create a timer, which will send information over UDP port 0 times per second
	m_pTimerUDP = new QTimer(this);
    m_pTimerUDP->setInterval(25);
	connect(m_pTimerUDP, SIGNAL(timeout()), this, SLOT(SendUDP()));
	m_pTimerUDP->start();

	// create an UDP socket object
	m_pSocketUDP = new QUdpSocket(this);
}

//-----------------------------------------------------------------------------

MessageDispatcher::~MessageDispatcher()
{
	//delete m_pMAVLink;
	delete m_pTimer;
	delete m_pTimerUDP;
	delete m_pSocketUDP;
}

//-----------------------------------------------------------------------------

MessageDispatcher* MessageDispatcher::GetInstance()
{
	if (s_pInstance == 0)
		s_pInstance = new MessageDispatcher;
	return s_pInstance;
}

//-----------------------------------------------------------------------------

void MessageDispatcher::EnableUDP()
{	m_bSendUDP = true; }

//-----------------------------------------------------------------------------

void MessageDispatcher::DisableUDP()
{	m_bSendUDP = false; }

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

void MessageDispatcher::DecodeMessage(
		int uasID,
		QString qsName,
		QString qsUnit,
		QVariant vValue,
		quint64 uiTime
		)
{
	// this is testing only
	for (int i = 0; i < 7; i++)
		emit SignalTempRPM(i, 200 + 20*i, 100000 + 10000*i);
}

//-----------------------------------------------------------------------------

void MessageDispatcher::SetActiveUAS(UASInterface* pUAS)
{
	if (pUAS == 0)
		return;

	m_pUAS = pUAS;
	/*
	connect(
				m_pUAS,
				SIGNAL(valueChanged(int,QString,QString,QVariant,quint64)),
				this,
				SLOT(DecodeMessage(int,QString,QString,QVariant,quint64))
				);
				*/

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

void MessageDispatcher::ReadUAS()
{
	if (m_pUAS != 0) {
		// read UAS info and save it into m_netFDM in correct format for sending to UDP port
		m_netFDM.longitude = ToNetwork(double(M_PI*m_pUAS->getLongitude()/180.0));
        m_netFDM.latitude = ToNetwork(double(M_PI*m_pUAS->getLatitude()/180.0));

        m_netFDM.altitude = ToNetwork(double(m_pUAS->getAltitudeAMSL()+2));
        m_netFDM.agl = ToNetwork(float(fmax(1,m_pUAS->getAltitudeRelative())));

		m_netFDM.phi = ToNetwork(float(m_pUAS->getRoll()));
		m_netFDM.theta = ToNetwork(float(m_pUAS->getPitch()));
		m_netFDM.psi = ToNetwork(float(m_pUAS->getYaw()));

		//qDebug() << "Position" << m_pUAS->getLongitude() << m_pUAS->getLatitude();
		/*qDebug() << "Angles" << 180.0*m_pUAS->getRoll()/M_PI
						<< 180.0*m_pUAS->getPitch()/M_PI
							<< 180.0*m_pUAS->getYaw()/M_PI;*/
		/*qDebug() << "Altitude" << m_pUAS->getAltitudeAMSL() << "m  " <<
						3.28084*m_pUAS->getAltitudeAMSL() << "ft" <<
						m_pUAS->getAltitudeAMSL()/3.28084;*/
		// convert from radians to degrees
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
    emit SignalAltitude(3.28084f*dAltRel);
    emit SignalVario(dVario);

    // also update the object to send to UDP port
    //m_netFDM.altitude = ToNetwork(double(1000.0));
    //m_netFDM.agl = ToNetwork(float(500));
}

//-----------------------------------------------------------------------------

void MessageDispatcher::SendUDP()
{
    ReadUAS();
	/*
	m_netFDM.version = ToNetwork(FG_NET_FDM_VERSION);
	m_netFDM.longitude = ToNetwork(double(M_PI*14.54/180.0));
	m_netFDM.latitude = ToNetwork(double(M_PI*45.56/180.0));
	m_netFDM.altitude = ToNetwork(1200.0);

	m_netFDM.phi = ToNetwork(0.0f);
	m_netFDM.theta = ToNetwork(0.0f);
	m_netFDM.psi = ToNetwork(0.0f);

	m_netFDM.num_engines = ToNetwork(uint32_t(1));
	m_netFDM.num_tanks = ToNetwork(uint32_t(1));
	m_netFDM.fuel_quantity[0] = ToNetwork(6.0f);
	m_netFDM.num_wheels = ToNetwork(uint32_t(3));

	m_netFDM.cur_time = ToNetwork(uint32_t(time(0)));
	m_netFDM.warp = ToNetwork(uint32_t(1));
	m_netFDM.visibility = ToNetwork(5000.0f);
	*/

	if (m_bSendUDP == true) {
		m_netFDM.cur_time = ToNetwork(uint32_t(time(0)));
		m_netFDM.visibility = ToNetwork(20000.0f);
		char* pch = (char*)&m_netFDM;
		m_pSocketUDP->writeDatagram(pch, sizeof(m_netFDM), QHostAddress::LocalHost, 5600);
	}
}

//-----------------------------------------------------------------------------

void MessageDispatcher::GetData()
{
	while (m_pSocketUDP->hasPendingDatagrams() == true) {
		// let's capture the FG output and save it into file for analysis
		QByteArray ba;
		ba.resize(m_pSocketUDP->pendingDatagramSize());
		QHostAddress ha;
		quint16 uiPort;
		m_pSocketUDP->readDatagram(ba.data(), ba.size(), &ha, &uiPort);
		QFile f("fg_out.bin");
		if (f.exists() == false) {
			qDebug() << "Data received" << ba.size() << sizeof(FGNetFDM);
			if (f.open(QFile::WriteOnly) == true) {
				f.write(ba);
				f.close();
			}
		}
	}
}

//-----------------------------------------------------------------------------

uint32_t MessageDispatcher::ToNetwork(uint32_t uiVal) const
{
	qint32* pi = (qint32*)&uiVal;
	qint32 iNew = qToBigEndian(*pi);
	uiVal = *(uint32_t*)&iNew;
	return uiVal;
}

//-----------------------------------------------------------------------------

float MessageDispatcher::ToNetwork(float fVal) const
{
	qint32* pi = (qint32*)&fVal;
	qint32 iNew = qToBigEndian(*pi);
	fVal = *(float*)&iNew;
	return fVal;
}

//-----------------------------------------------------------------------------

double MessageDispatcher::ToNetwork(double dVal) const
{
	qint64* pi =(qint64*)&dVal;
	qint64 iNew = qToBigEndian(*pi);
	dVal = *(double*)&iNew;
	return dVal;
}

//-----------------------------------------------------------------------------

MessageDispatcher* MessageDispatcher::s_pInstance = 0;

//-----------------------------------------------------------------------------

