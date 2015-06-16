#ifndef BRANDINGINTERFACE_H
#define BRANDINGINTERFACE_H

#include <QPixmap>

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

Q_DECLARE_INTERFACE(BrandingInterface, "org.qt-project.Qt.QGroundControl.BrandingInterface")

#endif // BRANDINGINTERFACE_H
