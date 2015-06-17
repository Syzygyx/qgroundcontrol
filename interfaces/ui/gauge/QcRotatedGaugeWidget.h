#ifndef QCROTATEDGAUGEWIDGET_H
#define QCROTATEDGAUGEWIDGET_H

#include "qcgaugewidget.h"

class QcRotatedGaugeWidget : public QcGaugeWidget
{
	Q_OBJECT

public:
	//! Constructor
	QcRotatedGaugeWidget(QWidget* pParent = 0);
	//! Destructor
	virtual ~QcRotatedGaugeWidget();

	//! Sets the angle of rotation
	void setRotation(double dAng);
	//! Returns the current angle of rotation
	float rotation() const
	{	return m_dAngle; }

protected:
	//! Paints the widget
	void paintEvent(QPaintEvent*);

private:
	//! Angle of rotation
	double m_dAngle;
};

#endif // QCROTATEDGAUGEWIDGET_H
