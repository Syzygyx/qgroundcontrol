#ifndef GAUGEINTERFACE_H
#define GAUGEINTERFACE_H

#include <QObject>
#include "ui/flightindicators/AirspeedIndicator.h"

//! This is the interface to gauge providing classes
class GaugeInterface
{
public:
	//! Default destructor
	virtual ~GaugeInterface()
	{	}

	//! Creates and returns Airspeed indicator
	virtual AirspeedIndicator* CreateAirspeedIndicator() const = 0;
};

Q_DECLARE_INTERFACE(GaugeInterface, "org.qt-project.Qt.QGroundControl.GaugeInterface")

#endif // GAUGEINTERFACE_H
