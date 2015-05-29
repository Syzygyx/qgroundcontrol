#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#include "gauge/QcPixmapItem.h"

//! This class is used to show the fuel gauge
class FuelGauge : public QcGaugeWidget
{
	Q_OBJECT

public:
	//! Constructor. Set dCapacity in gallons
	FuelGauge(double dCapacity, QWidget* pParent = 0);
	//! Destructor
	~FuelGauge();

public slots:
	//! Sets the fuel quantity
	void SetFuel(double dFuel);

private:
	//! Holds the engine fuel capacity
	double m_dCapacity;
	//! Pointer to the needle item
	QcNeedleItem* m_pNeedle;
};

#endif // FUELGAUGE_H
