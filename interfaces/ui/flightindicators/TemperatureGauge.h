#ifndef TEMPERATUREGAUGE_H
#define TEMPERATUREGAUGE_H

#include "qcgaugewidget.h"
#include "QcColorLabelItem.h"

//! This gauge is used to show the temperature
class TemperatureGauge : public QcGaugeWidget
{
	Q_OBJECT

public:
	//! Constructor
	TemperatureGauge(double dMinT, double dMaxT, QWidget* pParent = 0);
	//! Destructor
	~TemperatureGauge();

	//! Call this method after construction. Can be reimplemented in derived classes
	virtual void Init();

public slots:
	//! Sets the current temperature
	void SetTemperature(double dTemp);
	//! Just in case an integer value setter is needed
	void SetTemperature(int iTemp);
	//! Sets the RPM value
	void SetRPM(int iRPM);

protected:
	//! Minimal temperature
	double m_dMin;
	//! Maximal temperature
	double m_dMax;
	//! Pointer to the needle
	QcNeedleItem* m_pNeedle;
	//! Pointer to the RPM item
	QcColorLabelItem* m_pCLI;
};

#endif // TEMPERATUREGAUGE_H
