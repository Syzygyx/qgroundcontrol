#include <QPainter>

#include "QcRotatedGaugeWidget.h"

//-----------------------------------------------------------------------------

QcRotatedGaugeWidget::QcRotatedGaugeWidget(QWidget *pParent) :
	QcGaugeWidget(pParent)
{
	m_dAngle = 0.0f;
}

//-----------------------------------------------------------------------------

QcRotatedGaugeWidget::~QcRotatedGaugeWidget()
{	}

//-----------------------------------------------------------------------------

void QcRotatedGaugeWidget::setRotation(double dAng)
{
	m_dAngle = dAng;
	update();
}

//-----------------------------------------------------------------------------

void QcRotatedGaugeWidget::paintEvent(QPaintEvent*)
{
	QPainter P(this);
	P.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	// now draw all the items
	for (int i = 0; i < mItems.count(); i++) {
		if (mItems[i]->canRotate() == true) {
			// save the current state for easier retrieval
			P.save();
			// rotate around center:
			// move painter origin from (0, 0) to center
			P.translate(width()/2.0f, height()/2.0f);
			// perform rotation
			P.rotate(m_dAngle);
			// painter origin from center back to (0, 0)
			P.translate(-width()/2.0f, -height()/2.0f);
		}
		// draw the item
		mItems[i]->draw(&P);
		if (mItems[i]->canRotate() == true) {
			// retrieve the current state
			P.restore();
		}
	}
}

//-----------------------------------------------------------------------------

