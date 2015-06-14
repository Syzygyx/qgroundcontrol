#include <math.h>

#include <QDebug>

#include "GeoFenceZone.h"

//-----------------------------------------------------------------------------

GeoFenceZone::GeoFenceZone() :
	m_poly()
{
	m_dMinAlt = 0.0;
	m_dMaxAlt = 1000.0;
}

//-----------------------------------------------------------------------------

GeoFenceZone::~GeoFenceZone()
{	}

//-----------------------------------------------------------------------------

GeoFenceZone::GeoFenceZone(const GeoFenceZone& rZone)
{	Copy(rZone); }

//-----------------------------------------------------------------------------

GeoFenceZone& GeoFenceZone::operator=(const GeoFenceZone& rZone)
{
	Copy(rZone);
	return *this;
}

//-----------------------------------------------------------------------------

void GeoFenceZone::SetLatitude(int i, double dLat)
{
	m_poly[i].setY(dLat);
}

//-----------------------------------------------------------------------------

void GeoFenceZone::SetLongitude(int i, double dLon)
{
	m_poly[i].setX(dLon);
}

//-----------------------------------------------------------------------------

bool GeoFenceZone::Load(QTextStream& ts)
{
	if (ReadAltitudes(ts) == false)
		return false;

	ReadPoints(ts);

	qDebug() << "Read zone" << m_dMinAlt << m_dMaxAlt << m_poly;

	// there have to be at least three points in the polygon!
	return (GetCount() >= 3);
}

//-----------------------------------------------------------------------------

bool GeoFenceZone::Save(QTextStream& ts, GeoFenceFormat eGFF) const
{
	ts.setRealNumberNotation(QTextStream::FixedNotation);
	ts.setRealNumberPrecision(2);
	ts << m_dMinAlt << " " << m_dMaxAlt << endl;
	QPointF pt;

	for (int i = 0; i < GetCount(); i++) {
		pt = GetPoint(i);
		if (eGFF == gffDecimal) {
			ts.setRealNumberPrecision(17);
			ts << pt.y() << " " << pt.x() << endl;
		}	else {
			ts.setRealNumberPrecision(5);
			ts << "DMS ";
			WriteDMS(ts, pt.y());
			ts << " ";
			WriteDMS(ts, pt.x());
			ts << endl;
		}

	}
	ts << endl;
	return true;
}

//-----------------------------------------------------------------------------

bool GeoFenceZone::ReadAltitudes(QTextStream& ts)
{
	QString qsAlt;
	// read the line and remove all the unnecessary spaces
	qsAlt = ts.readLine().simplified();
	// check if we are at the end of file
	if (qsAlt.isNull() == true)
		return false;

	// split the string to obtain two altitudes
	QStringList qsl = qsAlt.split(" ");
	if (qsl.count() != 2)
		return false;

	bool bOK;
	m_dMinAlt = qsl[0].toDouble(&bOK);
	if (bOK == false)
		return false;
	m_dMaxAlt = qsl[1].toDouble(&bOK);
	return bOK;
}

//-----------------------------------------------------------------------------

void GeoFenceZone::ReadPoints(QTextStream& ts)
{
	QString qsPts;
	QPointF pt;
	bool bOK;

	Clear();
	qsPts = ts.readLine().simplified();
	pt = ParsePoint(qsPts, &bOK);
	while (bOK == true) {
		Append(pt);
		qsPts = ts.readLine().simplified();
		pt = ParsePoint(qsPts, &bOK);
	}
}

//-----------------------------------------------------------------------------

QPointF GeoFenceZone::ParsePoint(QString qsText, bool* pbOK)
{
	QStringList qsl = qsText.split(" ");
	QPointF pt;
	bool bCheck[6];

	// assume error
	if (pbOK != 0)
		*pbOK = false;

	// first check DMS format
	if (qsl[0].compare("DMS", Qt::CaseInsensitive) == 0) {
		// DMS format, there have to be 6 numbers after DMS string
		if (qsl.count() == 7) {
			// first try reading latitude
			pt.setY(
					qsl[1].toDouble(&bCheck[0]) +
					qsl[2].toDouble(&bCheck[1])/60.0 +
					qsl[3].toDouble(&bCheck[2])/3600.0
					);

			// then longitude
			pt.setX(
					qsl[4].toDouble(&bCheck[3]) +
					qsl[5].toDouble(&bCheck[4])/60.0 +
					qsl[6].toDouble(&bCheck[5])/3600.0
					);

			// check if any conversion failed
			for (int i = 0; i < 6; i++)
				if (bCheck[i] == false) {
					pt.setX(0.0);
					pt.setY(0.0);
					return pt;
				}
		}	else {
			// if there are not 6 numbers after DMS, parsing must fail
			return pt;
		}
	}	else {
		// decimal format, there have to be 2 numbers total
		if (qsl.count() == 2) {
			pt.setY(qsl[0].toDouble(&bCheck[0]));
			pt.setX(qsl[1].toDouble(&bCheck[1]));

			// check if any conversion failed
			if ((bCheck[0] == false) || (bCheck[1] == false)) {
				pt.setX(0.0);
				pt.setY(0.0);
				return pt;
			}
		}	else {
			// if there are not 2 numbers in decimal format, parsing must fail
			return pt;
		}
	}

	// if we got here, parsing was successful
	if (pbOK != 0)
		*pbOK = true;
	return pt;
}

//-----------------------------------------------------------------------------

void GeoFenceZone::WriteDMS(QTextStream& ts, double dVal) const
{
	int iD;
	int iM;
	double dSec;
	double dAbsVal;
	int iSign;

	if (dVal < 0.0)
		iSign = -1;
	else
		iSign = 1;
	dAbsVal = fabs(dVal);

	iD = (int)floor(dAbsVal);
	iM = (int)floor(60*(dAbsVal - iD));
	dSec = 3600.0*(dAbsVal - iD - iM/60.0);
	ts << iSign*iD << " " << iSign*iM << " " << iSign*dSec;
}

//-----------------------------------------------------------------------------

void GeoFenceZone::Copy(const GeoFenceZone& rZone)
{
	m_dMinAlt = rZone.GetMinAltitude();
	m_dMaxAlt = rZone.GetMaxAltitude();
	m_poly.clear();
	for (int i = 0; i < rZone.GetCount(); i++)
		Append(rZone.GetPoint(i));
}

//-----------------------------------------------------------------------------

