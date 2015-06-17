#ifndef BRANDINGINTERFACE_H
#define BRANDINGINTERFACE_H

#include <QPixmap>
#include "ui/flightindicators/AirspeedIndicator.h"

//! This is interface to pixmap providing classes
class BrandingInterface
{
public:
	//! Default destructor
	virtual ~BrandingInterface()
	{	}

	//! Should load and return the splash pixmap
	virtual QPixmap GetSplashPixmap() const = 0;
};

//! This is the interface to gauge providing classes
class GaugeInterace
{
public:
	//! Default destructor
	virtual ~GaugeInterace()
	{	}

	//! Creates and returns Airspeed indicator
	AirspeedIndicator* CreateAirspeedIndicator() const = 0;
};

Q_DECLARE_INTERFACE(BrandingInterface, "org.qt-project.Qt.QGroundControl.BrandingInterface")

Q_DECLARE_INTERFACE(GaugeInterface, "org.qt-project.Qt.QGroundControl.GaugeInterface")

#endif // BRANDINGINTERFACE_H
