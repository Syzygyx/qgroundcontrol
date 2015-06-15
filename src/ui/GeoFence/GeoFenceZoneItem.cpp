#include "core/ModelData.h"

#include "GeoFenceZoneItem.h"

//-----------------------------------------------------------------------------

GeoFenceZoneItem::GeoFenceZoneItem(
		mapcontrol::MapGraphicItem* pMap,
		int iInd
		) :
	QObject(),
	QGraphicsItem()
{
	m_pMap = pMap;
	m_iIndex = iInd;
	setZValue(100.0);

	RefreshPos();
}

//-----------------------------------------------------------------------------

GeoFenceZoneItem::~GeoFenceZoneItem()
{	}

//-----------------------------------------------------------------------------

QRectF GeoFenceZoneItem::boundingRect() const
{
	return m_rect;
}

//-----------------------------------------------------------------------------

void GeoFenceZoneItem::paint(
		QPainter* pP,
		const QStyleOptionGraphicsItem* option,
		QWidget* widget
		)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	pP->save();
	pP->setRenderHints(QPainter::Antialiasing);
	pP->setPen(Qt::red);
	pP->setBrush(QColor(255, 64, 32, 64));

	// first draw the polygon
	pP->drawPolygon(m_poly);

	// then draw each vertex individually
	for (int i = 0; i < m_poly.count(); i++) {
		pP->drawEllipse(m_poly[i], 3, 3);
	}

	pP->restore();
}

//-----------------------------------------------------------------------------

void GeoFenceZoneItem::RefreshPos()
{
	core::Point pt;

	m_poly.clear();

	const GeoFenceZone& rZone =
			ModelData::GetInstance()->GetGFC().GetZone(m_iIndex);
	// Convert all points from lat/lon to a polygon of widget
	// coordinates and obtain bounding box around it
	for (int i = 0; i < rZone.GetCount(); i++) {
		using namespace internals;
		pt = m_pMap->FromLatLngToLocal(PointLatLng(
													 rZone.GetPoint(i).y(),
													 rZone.GetPoint(i).x()
													 )
												 );
		m_poly << QPoint(pt.X(), pt.Y());
	}

	m_rect = m_poly.boundingRect();
	// make it slightly bigger just in case
	m_rect.adjust(-3, -3, 3, 3);
	QGraphicsItem::prepareGeometryChange();
}

//-----------------------------------------------------------------------------

void GeoFenceZoneItem::mousePressEvent(QGraphicsSceneMouseEvent *pGSME)
{
	QGraphicsItem::mousePressEvent(pGSME);
	emit SignalCurrent(m_iIndex);
}

//-----------------------------------------------------------------------------

