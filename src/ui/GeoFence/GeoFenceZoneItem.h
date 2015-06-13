#ifndef GEOFENCEZONEITEM_H
#define GEOFENCEZONEITEM_H

#include <QGraphicsItem>

#include "../../mapwidget/mapgraphicitem.h"

#include "GeoFence/GeoFenceZone.h"

//! This class is a graphical reprezentation of the entire GeoFenceZone
class GeoFenceZoneItem : public QGraphicsItem
{
public:
	//! Constructor
	GeoFenceZoneItem(mapcontrol::MapGraphicItem* pMap, const GeoFenceZone& rZone);
	//! Destructor
	~GeoFenceZoneItem();
	//! Returns the bounding rect
	QRectF boundingRect() const;
	//! Paints the item
	void paint(QPainter* pP, const QStyleOptionGraphicsItem* option, QWidget* widget);

	//! Calculates the item parameters
	void RefreshPos();

protected:
	//! Pointer to the map object
	mapcontrol::MapGraphicItem* m_pMap;
	//! Reference to the zone
	GeoFenceZone m_zone;
	//! Holds the bounding rectangle
	QRectF m_rect;
	//! Holds the polygon of points on the screen
	QPolygon m_poly;
};

#endif // GEOFENCEZONEITEM_H
