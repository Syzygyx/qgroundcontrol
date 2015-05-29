#ifndef ALTITUDEINDICATOR_H
#define ALTITUDEINDICATOR_H

#include "gauge/qcgaugewidget.h"

//! This class is used to show altitude in classic altimeter style
class AltitudeIndicator : public QcGaugeWidget
{
	Q_OBJECT

public:
	//! Constructor
	AltitudeIndicator(QWidget* pParent = 0);
	//! Destructor
	~AltitudeIndicator();
	/** Initializes the indicator. Call it after constructor! Reimplement to
	 *  obtain different look
	 */
	virtual void Init();

public slots:
	//! Sets the current altitude
	void SetAltitude(double dAlt);
	//! Testing only
	void IncreaseAltitude();

protected:
	//! Pointer to the feet needle
	QcNeedleItem* m_pNeedle1;
	//! Pointer to the 100 feet needle
	QcNeedleItem* m_pNeedle100;
	//! Testing only
	double m_dAlt;
};

#endif // ALTITUDEINDICATOR_H
