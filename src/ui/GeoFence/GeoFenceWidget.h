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
	//! Sets the current edit widget
	void SetCurrent(int iInd);
	//! Sets the minimal altitude for given zone
	void SetMinAlt(int iInd, double dAlt);
	//! Sets the maximal altitude for given zone
	void SetMaxAlt(int iInd, double dAlt);

protected:
	//! Paints the background
	void paintEvent(QPaintEvent* pPE);
	//! Handles mouse press events
	void mousePressEvent(QMouseEvent* pME);
	//! Reports that this widget is active
	void showEvent(QShowEvent* pSE);
	//! Reports that this widget is not active
	void hideEvent(QHideEvent* pHE);

protected slots:
	//! Updates the values in given lon/lat spin boxes without triggering signals
	void MoveVertex(int iInd, int iP, double dLon, double dLat);
	/** Adds a point to a current zone or (if no zone is current) creates a zone
	 *  with given point
	 */
	void AddPoint(double dLon, double dLat);
	//! Removes the iInd-th zone
	void RemoveZone(int iInd);

private:
	//! Creates GeoFenceZone edit widget for i-th zone and appends it to list
	void CreateEditwidget(int i);
	//! Sets the minimum size
	void UpdateMinSize();


private:
	//! Pointer to the GeoFenceZones container
	GeoFenceContainer& m_rGFC;
	//! List of zone editing widgets
	QList<GeoFenceEdit*> m_lipEdit;
	//! Main widget layout
	QVBoxLayout* m_pLayout;
	//! Index of current zone
	int m_iCurrent;
};

#endif // GEOFENCEWIDGET_H
