#ifndef GEOFENCECONTAINER_H
#define GEOFENCECONTAINER_H

#include <QObject>
#include "GeoFence/GeoFenceZone.h"

//! This class contains a list of GeoFence zones
class GeoFenceContainer : public QObject
{
	Q_OBJECT

public:
	//! Constructor
	GeoFenceContainer();
	//! Destructor
	virtual ~GeoFenceContainer();

	//! Returns the number of zones
	int GetCount() const
	{	return m_liZones.count(); }
	//! Appends the zone to the list
	void Append(const GeoFenceZone& rZone)
	{	m_liZones << rZone; }
	//! Inserts the zone into i-th position
	void Insert(int i, const GeoFenceZone& rZone)
	{	m_liZones.insert(i, rZone); }
	//! Sets the zone into i-th position and overwrites the previous content
	void SetZone(int i, const GeoFenceZone& rZone)
	{	m_liZones[i] = rZone; }
	//! Deletes i-th zone
	void Remove(int i)
	{	m_liZones.removeAt(i); }
	//! Removes all the zones
	void Clear()
	{	m_liZones.clear(); }
	//! Const access to the i-th zone
	const GeoFenceZone& GetZone(int i) const
	{	return m_liZones[i]; }
	//! Full access to the i-th zone
	GeoFenceZone& GetZone(int i)
	{	return m_liZones[i]; }

	//! Returns true, if GeoFence mode is on
	bool IsGeoFenceMode() const
	{	return m_bGeoFenceMode; }
	//! Sets the GeoFenceMode flag
	void SetGeoFenceMode(bool bVal)
	{	m_bGeoFenceMode = bVal; }

	/** Loads the zones from given file and remembers the filename. Returns true
	 *  on success
	 */
	bool Load(QString qsName);
	/** Saves the zones into given file. If file is not set, it saves them into
	 *  previously loaded file
	 */
	bool Save(QString qsName = "");

public slots:
	//! Sets the longitude for iP-th point of iInd-th zone
	void SetLongitude(int iInd, int iP, double dLon);
	//! Sets the latitude for iP-th point of iInd-th zone
	void SetLatitude(int iInd, int iP, double dLat);

	//! Sets the longitude and latitude for iP-th point of iInd-th zone
	void SetLocation(int iInd, int iP, double dLon, double dLat);

signals:
	//! Should be emitted when GeoFence file needs to be loaded
	void SignalLoadGF(QString qsName);
	//! Should be emitted when GeoFence file needs to be saved
	void SignalSaveGF(QString qsName);
	//! Emitted, when new set of GeoFence zones are loaded and update is needed
	void SignalRefresh();
	//! Emitted when i-th GeoFence zone changed
	void SignalUpdate(int i);
	//! Should be emitted when new current GeoFence zone was selected on the map
	void SignalMapCurrent(int iInd);
	//! Should be emitted when iP-th vertex of iInd-th zone was moved to a new location
	void SignalMoved(int iInd, int iP, double dLon, double dLat);
	//! Emitted when there was a double click on the map with intent to add a point
	void SignalAddPoint(double dLon, double dLat);
	//! Emitted when new zone was added by  double click on the map
	void SignalAddZone();


protected:
	//! List of GeoFence zones
	QList<GeoFenceZone> m_liZones;
	//! Filename
	QString m_qsFile;
	//! Indicates the GeoFence mode
	bool m_bGeoFenceMode;
};

#endif // GEOFENCECONTAINER_H
