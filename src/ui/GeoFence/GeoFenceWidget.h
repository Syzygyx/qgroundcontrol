#ifndef GEOFENCEWIDGET_H
#define GEOFENCEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

#include "GeoFence/GeoFenceContainer.h"
#include "GeoFence/GeoFenceEdit.h"


//! This class is used to show all the GeoFence zones
class GeoFenceWidget : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	GeoFenceWidget(QWidget* pParent = 0);
	//! Destructor
	~GeoFenceWidget();

public slots:
	//! Updates the entire widget
	void Update();

protected:
	//! Paints the background
	void paintEvent(QPaintEvent* pPE);
	//! Handles mouse press events
	void mousePressEvent(QMouseEvent* pME);

private:
	//! Pointer to the GeoFenceZones container
	GeoFenceContainer& m_rGFC;
	//! List of zone editing widgets
	QList<GeoFenceEdit*> m_lipEdit;
	//! Main widget layout
	QVBoxLayout* m_pLayout;
};

#endif // GEOFENCEWIDGET_H
