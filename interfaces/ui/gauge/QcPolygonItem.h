#ifndef QCPOLYGONITEM_H
#define QCPOLYGONITEM_H

#include <gauge/qcgaugewidget.h>

/** This class represents an item which is drawn as a polygon, centered and widget center.
 *  Points of this polygon should be given as a fraction (-1.0..1.0).
 */
class QcPolygonItem : public QcItem
{
public:
	//! Constructor
	QcPolygonItem(QObject* pParent = 0);
	//! Destructor
	~QcPolygonItem();

	//! Add given point
	void AddPoint(float fX, float fY);
	//! Adds the mirror image of polygon over y axis
	void AddMirrorY();
	//! Sets the color of the line
	void SetColor(QColor clr)
	{	m_color = clr; }
	//! Draws the item
	void draw(QPainter* pP);

private:
	//! List of points
	QList<QPointF> m_liPts;
	//! Color of the line
	QColor m_color;
};

#endif // QCPOLYGONITEM_H
