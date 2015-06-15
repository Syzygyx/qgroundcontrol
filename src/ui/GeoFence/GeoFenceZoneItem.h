#ifndef GEOFENCEZONEITEM_H
#define GEOFENCEZONEITEM_H

#include <QObject>
#include <QGraphicsItem>

#include "../../mapwidget/mapgraphicitem.h"

#include "GeoFence/GeoFenceZone.h"

//! This class is a graphical reprezentation of the entire GeoFenceZone
class GeoFenceZoneItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	//
	enum { Type = UserType + 213 };
	//! Constructor
	GeoFenceZoneItem(mapcontrol::MapGraphicItem* pMap, int i);
	//! Destructor
	~GeoFenceZoneItem();
	//! Returns the bounding rect
	QRectF boundingRect() const;
	//! Paints the item
	void paint(QPainter* pP, const QStyleOptionGraphicsItem* option, QWidget* widget);

	//! Calculates the item parameters
	void RefreshPos();

protected:
	//! Handles mouse press event. Emits signal SignalCurrent with the index
	void mousePressEvent(QGraphicsSceneMouseEvent* pGSME);
	//! Handles dragging vertex around the map
	void mouseMoveEvent(QGraphicsSceneMouseEvent* pGSME);
	//! Handles mouse release event
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* pGSME);

signals:
	//! Emitted when user clicked on this item
	void SignalCurrent(int iInd);
	//! Emitted when iP-th vertex has been moved to (dLon, dLat)
	void SignalMoved(int iInd, int iP, double dLon, double dLat);

protected:
	//! Pointer to the map object
	mapcontrol::MapGraphicItem* m_pMap;
	//! Holds the bounding rectangle
	QRectF m_rect;
	//! Holds the polygon of points on the screen
	QPolygon m_poly;
	//! Zone index
	int m_iIndex;
	//! Index of clicked vertex
	int m_iVertex;
};

#endif // GEOFENCEZONEITEM_H
