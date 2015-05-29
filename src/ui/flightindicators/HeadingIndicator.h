#ifndef HEADINGINDICATOR_H
#define HEADINGINDICATOR_H

#include "gauge/QcRotatedGaugeWidget.h"

class HeadingIndicator : public QcRotatedGaugeWidget
{
	Q_OBJECT

public:
	//! Constructor
	HeadingIndicator(QWidget* pParent = 0);
	//! Destructor
	virtual ~HeadingIndicator();

	/** Initializes the indicator. Call it after constructor! Reimplement to
	 *  obtain different look
	 */
	void Init();

public slots:
	//! Sets the current heading to fAng [deg]
	void SetHeading(float fAng);
	//! Testing only
	void IncreaseHeading();
};

#endif // HEADINGINDICATOR_H
