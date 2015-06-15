#ifndef GEOFENCEEDIT_H
#define GEOFENCEEDIT_H

#include <QWidget>
#include <QLabel>
#include <QSignalMapper>
#include <QGridLayout>

#include "QGCDoubleSpinBox.h"
#include "GeoFence/GeoFenceZone.h"

/** This class is used to show GeoFence parameters and allows user
 *  to edit it
 */
class GeoFenceEdit : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	GeoFenceEdit(int iInd, GeoFenceZone* pZone, QWidget* pParent = 0);
	//! Destructor
	~GeoFenceEdit();

	//! Returns true, if this is current edited GeoFenceZone
	bool IsCurrent() const
	{	return m_bCurrent; }

public slots:
	//! Sets the current flag
	void SetCurrent(bool bCur = true);
	//! Updates the edit boxes with zone data
	void Update();
	//! Updates the location of i-th point without triggering signals
	void UpdateLocation(int i, double dLon, double dLat);
	//! Adds lon/lat fields for last point (should only be called after point was added!)
	void AddLatestFields();

private:
	//! Builds the widget GUI
	void BuildGUI();
	//! Adds lon/lat fields for i-th vertex
	void AddFields(int i);

private slots:
	//! Emits SignalCurrent signal with the m_iIndex parameter
	void ReportCurrent();
	//! Emits SignalMinAlt signal with index and minimal altitude
	void ReportMinAlt();
	//! Emits SignalMaxAlt signal with index and minimal altitude
	void ReportMaxAlt();
	//! Reports latitude or longitude changes
	void ReportPosition(int iInd);

signals:
	//! Emitted when one of the subwidgets receives focus or is clicked on or both
	void SignalCurrent(int iIndex);
	//! Emitted when min altitude has changed
	void SignalMinAlt(int iIndex, double dAlt);
	//! Emitted when max altitude has changed
	void SignalMaxAlt(int iIndex, double dAlt);
	//! Emitted when latitude on iP-th point has changed
	void SignalLat(int iIndex, int iP, double dLat);
	//! Emitted when longitude on iP-th point has changed
	void SignalLon(int iIndex, int iP, double dLon);

private:
	//! Main widget layout
	QGridLayout* m_pLayout;
	//! Pointer to GeoFenceZone object
	GeoFenceZone* m_pZone;
	//! Min altitude line edit
	QGCDoubleSpinBox* m_psbMinAlt;
	//! Max altitude line edit
	QGCDoubleSpinBox* m_psbMaxAlt;
	//! List of longitude line edits
	QList<QGCDoubleSpinBox*> m_liLongitudes;
	//! List of latitude line edits
	QList<QGCDoubleSpinBox*> m_liLatitudes;
	//! Label showing index
	QLabel* m_plbIndex;
	//! GeoFenceZone index
	int m_iIndex;
	//! Index of the leftmost lon/lat line edits
	int m_iLeftMost;
	//! List of top vertex labels
	QList<QLabel*> m_liplbVert;
	//! Indicates that this is the current GeoFenceWidget
	bool m_bCurrent;
	//! Signal mapper for obtaining lat/lon field index when reporting a change
	QSignalMapper* m_pMapper;
};

#endif // GEOFENCEEDIT_H
