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
		gtFirst							= 1,
		gtAirspeedIndicator			= 1,
		gtAltitudeIndicator			= 2,
		gtFuelGauge						= 4,
		gtHeadingIndicator			= 8,
		gtVerticalSpeedIndicator	= 16,
		gtWeightGauge					= 32,
		gtFlightInstruments			= 64,
		gtLast							= 128,
	};

public:
	//! Default destructor
	virtual ~GaugeInterface()
	{	}

	//! Returns the XML key for given gauge
	const char* GetGaugeKey(GaugeType eGT) const
	{
		switch(eGT) {
		case gtAirspeedIndicator:
			return "AIRSPEED_INDICATOR_DOCKWIDGET";
		case gtAltitudeIndicator:
			return "ALTITDE_INDICATOR_DOCKWIDGET";
		case gtFuelGauge:
			return "FUEL_GAUGE_DOCKWIDGET";
		case gtHeadingIndicator:
			return "HEADING_INDICATOR_DOCKWIDGET";
		case gtVerticalSpeedIndicator:
			return "VERTICAL_SPEED_INDICATOR_DOCKWIDGET";
		case gtWeightGauge:
			return "WEIGHT_GAUGE_DOCKWIDGET";
		case gtFlightInstruments:
			return "FLIGHT_INSTRUMENTS_DOCKWIDGET";
		default:
			return "";
		}
	}

	//! Returns the title for given gauge
	const char* GetGaugeTitle(GaugeType eGT) const
	{
		switch (eGT) {
		case gtAirspeedIndicator:
			return "Airspeed Indicator";
		case gtAltitudeIndicator:
			return "Altitude Indicator";
		case gtFuelGauge:
			return "Fuel Indicator";
		case gtHeadingIndicator:
			return "Heading Indicator";
		case gtVerticalSpeedIndicator:
			return "Vertical Speed Indicator";
		case gtWeightGauge:
			return "Total Weight Indicator";
		case gtFlightInstruments:
			return "Flight Instruments";
		default:
			return "";
		}
	}

	//! Returns true, if given gauge is available
	virtual bool HasGauge(GaugeType eGT) const
	{	return (GetAvailable() & eGT) > 0; }

	//! Returns the GaugeTypes 'or'ed together, indicating which gauges are available
	virtual int GetAvailable() const = 0;

	//! Creates and returns Airspeed indicator
	virtual AirspeedIndicator* CreateAirspeedIndicator(QWidget* pParent = 0) const = 0;
};

Q_DECLARE_INTERFACE(GaugeInterface, "org.qt-project.Qt.QGroundControl.GaugeInterface")

#endif // GAUGEINTERFACE_H
