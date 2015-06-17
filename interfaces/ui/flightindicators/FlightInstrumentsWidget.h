#ifndef FLIGHTINSTRUMENTSWIDGET_H
#define FLIGHTINSTRUMENTSWIDGET_H

#include <QWidget>
#include "AltitudeIndicator.h"
#include "VerticalSpeedIndicator.h"
#include "AirspeedIndicator.h"
#include "HeadingIndicator.h"
#include "FuelGauge.h"
#include "WeightGauge.h"

/** This widget shows six gauges/indicators
 *  altimeter                 variometer
 *  airspeed indicator        heading indicator
 *  fuel indicator            weight indicator
 */
class FlightInstrumentsWidget : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	FlightInstrumentsWidget(QWidget* pParent = 0);
	//! Destructor
	~FlightInstrumentsWidget();

public slots:
	//! Sets the altitude [feet]
	void SetAltitude(double dAlt);
	//! Sets the vertical speed [feet/min]
	void SetVerticalSpeed(double dVSpeed);
	//! Sets the airspeed [knots]
	void SetAirspeed(double dSpeed);
	//! Sets the heading angle
	void SetHeading(double dAngle);
	//! Sets the amount of fuel [gallons]
	void SetFuel(double dFuel);
	//! Sets the total vehicle weight
	void SetWeight(double dWeight);

protected:
	//! Pointer to the altitude indicator
	AltitudeIndicator* m_pAltitude;
	//! Pointer to the vertical speed indicator
	VerticalSpeedIndicator* m_pVariometer;
	//! Pointer to the airspeed indicator
	AirspeedIndicator* m_pAirspeed;
	//! Pointer to the heading indicator
	HeadingIndicator* m_pHeading;
	//! Pointer to the fuel gauge
	FuelGauge* m_pFuel;
	//! Pointer to the weight gauge
	WeightGauge* m_pWeight;
};

#endif // FLIGHTINSTRUMENTSWIDGET_H
