#ifndef VEHICLEWIDGETFALCON_H
#define VEHICLEWIDGETFALCON_H

#include "VehicleWidget.h"

//! This class is derived from VehicleWidget and uses Falcon.png as underlying image
class VehicleWidgetFalcon : public VehicleWidget
{
	Q_OBJECT

public:
	//! Constructor
	VehicleWidgetFalcon(QWidget* pParent = 0);
	//! Destructor
	~VehicleWidgetFalcon();

	//! Returns the center position of the i-th engine
	QPoint GetCenter(int i) const;
	//! Returns the size of the i-th engine
	int GetSize(int i) const;

	//! Creates the internal vehicle pixmap
	void CreateVehiclePixmap();
};

#endif // VEHICLEWIDGETFALCON_H
