#ifndef GEOFENCEZONE_H
#define GEOFENCEZONE_H

#include <QString>
#include <QPolygonF>
#include <QTextStream>

//! This class holds one GeoFence zone with the ability to load and save it
class GeoFenceZone
{
public:
	//! Defines file format
	enum GeoFenceFormat {
		gffDecimal,				//!< decimal format of points (47.5)
		gffDMS,					//!< degrees, minutes, seconds (47 30 0)
	};

public:
	//! Constructor
	GeoFenceZone();
	//! Destructor
	virtual ~GeoFenceZone();
	//! Copy constructor
	GeoFenceZone(const GeoFenceZone& rZone);
	//! Assignment operator
	GeoFenceZone& operator=(const GeoFenceZone& rZone);

	//! Returns the minimal altitude AMSL
	double GetMinAltitude() const
	{	return m_dMinAlt; }
	//! Sets the minimal altitude AMSL
	void SetMinAltitude(double dAlt)
	{	m_dMinAlt = dAlt; }
	//! Returns the maximal altitude AMSL
	double GetMaxAltitude() const
	{	return m_dMaxAlt; }
	//! Sets the maximal altitude AMSL
	void SetMaxAltitude(double dAlt)
	{	m_dMaxAlt = dAlt; }
	//! Returns the number of zone points
	int GetCount() const
	{	return m_poly.count(); }
	//! Returns i-th zone point
	QPointF GetPoint(int i) const
	{	return m_poly[i]; }
	//! Appends given point to the zone
	void Append(const QPointF& pt)
	{	m_poly << pt; }
	//! Inserts given point to i-th position in the zone
	void Insert(int i, const QPointF& pt)
	{	m_poly.insert(i, pt); }
	//! Removes i-th point from the zone
	void Remove(int i)
	{	m_poly.remove(i); }
	//! Removes all points from the zone
	void Clear()
	{	m_poly.clear(); }
	//! Returns const reference to polygon
	const QPolygonF& GetPoints() const
	{	return m_poly; }

	//! Sets the latitude of the i-th point
	void SetLatitude(int i, double dLat);

	//! Sets the longitude of the i-th point
	void SetLongitude(int i, double dLon);

	//! Loads zone from a given text stream. Returns true on success
	virtual bool Load(QTextStream& ts);

	//! Writes zone into a given text stream in given format
	virtual bool Save(QTextStream& ts, GeoFenceFormat eGFF = gffDecimal) const;

protected:
	//! Reads the altitudes from the text stream, returns true on success
	virtual bool ReadAltitudes(QTextStream& ts);
	/** Reads the points from the text stream until end of file or line containing
	 *  no point is read
	 */
	virtual void ReadPoints(QTextStream& ts);
	/** Parses point data from given string. If pbOK is not 0, it writes true into
	 *  it, if parsing succeded and false otherwise
	 */
	virtual QPointF ParsePoint(QString qsText, bool* pbOK = 0);
	//! Writes number in DMS format into text string
	virtual void WriteDMS(QTextStream& ts, double dVal) const;

private:
	//! Copies the info from rZone
	void Copy(const GeoFenceZone& rZone);

private:
	//! Minimal altitude AMSL [m]
	double m_dMinAlt;
	//! Maximal altitude AMSL [m]
	double m_dMaxAlt;
	//! Polygon of points, defining the zone
	QPolygonF m_poly;
};

#endif // GEOFENCEZONE_H
