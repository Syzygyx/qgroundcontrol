#ifndef AIRSPEEDINDICATOR_H
#define AIRSPEEDINDICATOR_H

#include "qcgaugewidget.h"

//! This indicator shows the airspeed
class AirspeedIndicator : public QcGaugeWidget
{
	Q_OBJECT

public:
	//! Denotes the units shown by the airspeed indicator
	enum AirspeedUnit {
		auKmh,				//!< km/h
		auKnots,				//!< knots
		auMph,				//!< mph
	};

public:
	//! Constructor
	AirspeedIndicator(
			double dMinSpeed,
			double dMaxSpeed,
			AirspeedUnit eAU = auKnots,
			QWidget* pParent = 0
			);
	//! Destructor
	~AirspeedIndicator();

	/** Initializes the indicator. Call it after constructor! Reimplement to use
	 *  different coloring and enumeration.
	 */
	virtual void Init();

public slots:
	//! Sets the current speed in units given at constructor
	void SetSpeed(double dSpeed);

protected:
	//! Pointer to the needle
	QcNeedleItem* m_pNeedle;
	//! Indicates the units displayed
	AirspeedUnit m_eAU;
	//! Minimal shown air speed
	double m_dMinSpeed;
	//! Maximal indicated air speed
	double m_dMaxSpeed;
};

#endif // AIRSPEEDINDICATOR_H
