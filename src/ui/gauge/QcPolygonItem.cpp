#include <QDebug>

#include <gauge/QcPolygonItem.h>

//-----------------------------------------------------------------------------

QcPolygonItem::QcPolygonItem(QObject* pParent) :
	QcItem(pParent)
{	}

//-----------------------------------------------------------------------------

QcPolygonItem::~QcPolygonItem()
{	}

//-----------------------------------------------------------------------------

void QcPolygonItem::AddPoint(float fX, float fY)
{
	m_liPts << QPointF(fX, fY);
}

//-----------------------------------------------------------------------------

void QcPolygonItem::AddMirrorY()
{
	QPointF pt;

	// i = m_liPts.count() is executed only at start of the loop, so no
	// worries about changing number of elements in the list
	for (int i = m_liPts.count() - 1; i >= 0; i--) {
		AddPoint(-m_liPts[i].x(), m_liPts[i].y());
	}
}

//-----------------------------------------------------------------------------

void QcPolygonItem::draw(QPainter* pP)
{
	QRectF tmpRect = resetRect();
	float r = getRadius(adjustRect(position()));

	int iX = tmpRect.center().x();
	int iY = tmpRect.center().y();
	QPolygon poly;
	for (int i = 0; i < m_liPts.count(); i++) {
		poly << QPoint(
					  iX + (int)roundf(r*m_liPts[i].x()),
					  iY + (int)roundf(r*m_liPts[i].y())
					  );
	}

	pP->save();
	pP->setPen(QPen(m_color, 2.0));
	pP->drawPolygon(poly);
	pP->restore();
}

//-----------------------------------------------------------------------------

