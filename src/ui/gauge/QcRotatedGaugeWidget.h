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
	void setRotation(float fAng);
	//! Returns the current angle of rotation
	float rotation() const
	{	return m_fAngle; }

protected:
	//! Paints the widget
	void paintEvent(QPaintEvent*);

private:
	//! Angle of rotation
	float m_fAngle;
};

#endif // QCROTATEDGAUGEWIDGET_H
