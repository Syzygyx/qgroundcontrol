#ifndef VERTICALSPEEDINDICATOR_H
#define VERTICALSPEEDINDICATOR_H

#include "gauge/qcgaugewidget.h"

//! This indicator shows the vertical speed
class VerticalSpeedIndicator : public QcGaugeWidget
{
	Q_OBJECT

public:
	//! Constructor
	VerticalSpeedIndicator(double dMaxVS, QWidget* pParent = 0);
	//! Destructor
	~VerticalSpeedIndicator();

	/** Initializes the indicator. Call it after constructor! Reimplement to
	 *  obtain different look
	 */
	virtual void Init();

public slots:
	//! Sets the current vertical speed in 100 feet per minute
	void SetVerticalSpeed(double dVerticalSpeed);

protected:
	//! Pointer to the needle
	QcNeedleItem* m_pNeedle;
	//! Indicates the maximal vertical speed (minimal is -maximal)
	double m_dMaxVS;
};

#endif // VERTICALSPEEDINDICATOR_H
