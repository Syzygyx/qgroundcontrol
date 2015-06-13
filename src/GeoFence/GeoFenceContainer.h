#ifndef GEOFENCECONTAINER_H
#define GEOFENCECONTAINER_H

#include "GeoFence/GeoFenceZone.h"

//! This class contains a list of GeoFence zones
class GeoFenceContainer
{
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

	/** Loads the zones from given file and remembers the filename. Returns true
	 *  on success
	 */
	bool Load(QString qsName);
	/** Saves the zones into given file. If file is not set, it saves them into
	 *  previously loaded file
	 */
	bool Save(QString qsName = "");

protected:
	//! List of GeoFence zones
	QList<GeoFenceZone> m_liZones;
	//! Filename
	QString m_qsFile;
};

#endif // GEOFENCECONTAINER_H
