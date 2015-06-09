#include "gauge/QcColorLabelItem.h"

//-----------------------------------------------------------------------------

QcColorLabelItem::QcColorLabelItem(QObject* pParent) : QcLabelItem(pParent)
{
	m_clrBG = Qt::white;
	m_iPer = 20;
}

//-----------------------------------------------------------------------------

void QcColorLabelItem::SetValue(QString qsVal)
{
	m_qsValue = qsVal;
	update();
}

//-----------------------------------------------------------------------------

void QcColorLabelItem::draw(QPainter* pP)
{
	resetRect();
	QRectF tmpRect = adjustRect(position());
	float fR = getRadius(rect());
	QFont font("Meiryo UI", fR/10.0 + miFont, meWeight);
	pP->setFont(font);

	QPointF txtCenter = getPoint(mAngle,tmpRect);
	QFontMetrics fm = pP->fontMetrics();
	//QSize sz = fMetrics.size( Qt::TextSingleLine, mText );
	QSize sz((int)round(m_iPer*fR/100), fm.height());
	QRectF txtRect(QPointF(-sz.width()/2.0, -sz.height()/2.0), sz );

	//txtRect.moveCenter(txtCenter);

	pP->save();
	pP->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	pP->translate(txtCenter);
	//pP->rotate(mrRotation);
	//pP->drawText( txtRect, Qt::TextSingleLine,mText );
	pP->fillRect(txtRect, m_clrBG);

	// leave a little bit of space
	txtRect.setWidth(txtRect.width()*0.95);
	// finally draw the value
	pP->setPen(mColor);
	pP->drawText(txtRect, Qt::AlignVCenter | Qt::AlignRight, m_qsValue);

	pP->restore();

}

//-----------------------------------------------------------------------------


