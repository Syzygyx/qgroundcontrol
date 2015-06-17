#ifndef GAUGEINTERFACE_H
#define GAUGEINTERFACE_H

#include <QWidget>
#include "ui/flightindicators/AirspeedIndicator.h"

//! This is the interface to gauge providing classes
class GaugeInterface
{
public:
	//! This enum denotes each gauge individually
	enum GaugeType {
		gtAirspeedIndicator			= 1,
		gtAltitudeIndicator			= 2,
		gtDurationGauge				= 4,
		gtFuelGauge						= 8,
		gtHeadingIndicator			= 16,
		gtVerticalSpeedIndicator	= 32,
		gtWeightGauge					= 64,
		gtFlightInstruments			= 128
	};

public:
	//! Default destructor
	virtual ~GaugeInterface()
	{	}

	//! Creates and returns Airspeed indicator
	virtual AirspeedIndicator* CreateAirspeedIndicator(
			double dMin,
			double dMax,
			AirspeedIndicator::AirspeedUnit eAU = AirspeedIndicator::auKnots,
			QWidget* pParent = 0
			) const = 0;
};

Q_DECLARE_INTERFACE(GaugeInterface, "org.qt-project.Qt.QGroundControl.GaugeInterface")

#endif // GAUGEINTERFACE_H
