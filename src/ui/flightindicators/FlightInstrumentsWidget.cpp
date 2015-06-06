#include <QGridLayout>

#include "core/MessageDispatcher.h"
#include "FlightInstrumentsWidget.h"

//-----------------------------------------------------------------------------

FlightInstrumentsWidget::FlightInstrumentsWidget(QWidget* pParent) :
	QWidget(pParent)
{
	// main widget layout
	QGridLayout* pLayout = new QGridLayout(this);

	m_pAltitude = new AltitudeIndicator;
	m_pAltitude->Init();
	m_pVariometer = new VerticalSpeedIndicator(20.0);
	m_pVariometer->Init();
	m_pAirspeed = new AirspeedIndicator(0, 50, AirspeedIndicator::auKnots);
	m_pAirspeed->Init();
	m_pHeading = new HeadingIndicator;
	m_pHeading->Init();
	m_pFuel = new FuelGauge(6.0);
	m_pWeight = new WeightGauge(200);

	pLayout->addWidget(m_pAltitude, 0, 0);
	pLayout->addWidget(m_pVariometer, 0, 1);
	pLayout->addWidget(m_pAirspeed, 1, 0);
	pLayout->addWidget(m_pHeading, 1, 1);
	pLayout->addWidget(m_pFuel, 2, 0);
	pLayout->addWidget(m_pWeight, 2, 1);

	connect(
				MessageDispatcher::GetInstance(),
				SIGNAL(SignalAirSpeed(double)),
				this,
				SLOT(SetAirspeed(double))
				);
	connect(
				MessageDispatcher::GetInstance(),
				SIGNAL(SignalAltitude(double)),
				this,
				SLOT(SetAltitude(double))
				);
	connect(
				MessageDispatcher::GetInstance(),
				SIGNAL(SignalHeading(double)),
				this,
				SLOT(SetHeading(double))
				);

	connect(
				MessageDispatcher::GetInstance(),
				SIGNAL(SignalVario(double)),
				this,
				SLOT(SetVerticalSpeed(double))
				);
}

//-----------------------------------------------------------------------------

FlightInstrumentsWidget::~FlightInstrumentsWidget()
{	}

//-----------------------------------------------------------------------------

void FlightInstrumentsWidget::SetAltitude(double dAlt)
{
	m_pAltitude->SetAltitude(dAlt);
	m_pAltitude->update();
}

//-----------------------------------------------------------------------------

void FlightInstrumentsWidget::SetVerticalSpeed(double dVSpeed)
{
	m_pVariometer->SetVerticalSpeed(dVSpeed);
	m_pVariometer->update();
}

//-----------------------------------------------------------------------------

void FlightInstrumentsWidget::SetAirspeed(double dSpeed)
{
	m_pAirspeed->SetSpeed(dSpeed);
	m_pAirspeed->update();
}

//-----------------------------------------------------------------------------

void FlightInstrumentsWidget::SetHeading(double dAngle)
{
	m_pHeading->SetHeading(dAngle);
	m_pHeading->update();
}

//-----------------------------------------------------------------------------

void FlightInstrumentsWidget::SetFuel(double dFuel)
{
	m_pFuel->SetFuel(dFuel);
	m_pFuel->update();
}

//-----------------------------------------------------------------------------

void FlightInstrumentsWidget::SetWeight(double dWeight)
{
	m_pWeight->SetWeight(dWeight);
	m_pWeight->update();
}

//-----------------------------------------------------------------------------

