#include "GeoFenceZoneItem.h"

//-----------------------------------------------------------------------------

GeoFenceZoneItem::GeoFenceZoneItem(
		mapcontrol::MapGraphicItem* pMap,
		const GeoFenceZone& rZone
		)
{
	m_pMap = pMap;
	m_zone = rZone;

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

	pP->setPen(Qt::red);
	pP->setBrush(QColor(255, 64, 32, 64));

	pP->drawPolygon(m_poly);
}

//-----------------------------------------------------------------------------

void GeoFenceZoneItem::RefreshPos()
{
	core::Point pt;

	m_poly.clear();
	// Convert all points from lat/lon to a polygon of widget
	// coordinates and obtain bounding box around it
	for (int i = 0; i < m_zone.GetCount(); i++) {
		using namespace internals;
		pt = m_pMap->FromLatLngToLocal(PointLatLng(
													 m_zone.GetPoint(i).x(),
													 m_zone.GetPoint(i).y()
													 )
												 );
		m_poly << QPoint(pt.X(), pt.Y());
	}

	m_rect = m_poly.boundingRect();
	// make it slightly bigger just in case
	m_rect.adjust(-2, -2, 2, 2);
	setPos(m_rect.center());
}

//-----------------------------------------------------------------------------

