#ifndef GAUGEINTERFACE_H
#define GAUGEINTERFACE_H

#include <QWidget>
#include "ui/flightindicators/AirspeedIndicator.h"
#include "ui/flightindicators/AltitudeIndicator.h"
#include "ui/flightindicators/FuelGauge.h"
#include "ui/flightindicators/HeadingIndicator.h"
#include "ui/flightindicators/VerticalSpeedIndicator.h"
#include "ui/flightindicators/WeightGauge.h"
#include "ui/flightindicators/FlightInstrumentsWidget.h"
#include "ui/video/FlightGearGrabWidget.h"


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
		gtFlightGearGrab				= 128,
		gtLast							= 256,
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
		case gtFlightGearGrab:
			return "FLIGHT_GEAR_VIDEO_DOCKWIDGET";
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
		case gtFlightGearGrab:
			return "FlightGear Live Video";
		default:
			return "";
		}
	}

	//! Returns the preferred dock widget area
	Qt::DockWidgetArea GetGaugePos(GaugeType eGT) const
	{
		switch (eGT) {
		case gtFuelGauge:
		case gtFlightInstruments:
		case gtWeightGauge:
			return Qt::LeftDockWidgetArea;

		default:
			return Qt::RightDockWidgetArea;
		}
	}

	//! Returns the gauge indicator for given key
	GaugeInterface::GaugeType GetType(QString qsKey) const
	{
		for (GaugeType eGT = gtFirst; eGT != gtLast; eGT = GaugeType(eGT << 1))
			if (qsKey == GetGaugeKey(eGT))
				return eGT;

		return gtLast;
	}

	//! Returns true, if given gauge is available
	virtual bool HasGauge(GaugeType eGT) const
	{	return (GetAvailable() & eGT) > 0; }

	//! Returns the GaugeTypes 'or'ed together, indicating which gauges are available
	virtual int GetAvailable() const = 0;

	//! Creates and returns airspeed indicator
	virtual AirspeedIndicator* CreateAirspeedIndicator(QWidget* pParent = 0) const = 0;

	//! Creates and returns altitude indicator
	virtual AltitudeIndicator* CreateAltitudeIndicator(QWidget* pParent = 0) const = 0;

	//! Creates and returns fuel gauge
	virtual FuelGauge* CreateFuelGauge(QWidget* pParent = 0) const = 0;

	//! Creates and returns heading indicator
	virtual HeadingIndicator* CreateHeadingIndicator(QWidget* pParent = 0) const = 0;

	//! Creates and returns vertical speed indicator
	virtual VerticalSpeedIndicator* CreateVerticalSpeedIndicator(QWidget* pParent = 0) const = 0;

	//! Creates and returns weight gauge
	virtual WeightGauge* CreateWeightGauge(QWidget* pParent = 0) const = 0;

	//! Creates and returns flight instruments widget
	virtual FlightInstrumentsWidget* CreateFlightInstruments(QWidget* pParent = 0) const = 0;

	//! Creates and returns FlightGear Live Video widget
	virtual FlightGearGrabWidget* CreateFlightGearLiveVideo(QWidget* pParent = 0) const = 0;

};

Q_DECLARE_INTERFACE(GaugeInterface, "org.qt-project.Qt.QGroundControl.GaugeInterface")

#endif // GAUGEINTERFACE_H
