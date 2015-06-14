#ifndef GEOFENCEEDIT_H
#define GEOFENCEEDIT_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>

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

private:
	//! Builds the widget GUI
	void BuildGUI();

private:
	//! Pointer to GeoFenceZone object
	GeoFenceZone* m_pZone;
	//! Min altitude line edit
	QDoubleSpinBox* m_psbMinAlt;
	//! Max altitude line edit
	QDoubleSpinBox* m_psbMaxAlt;
	//! List of longitude line edits
	QList<QDoubleSpinBox*> m_liLongitudes;
	//! List of latitude line edits
	QList<QDoubleSpinBox*> m_liLatitudes;
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
};

#endif // GEOFENCEEDIT_H
