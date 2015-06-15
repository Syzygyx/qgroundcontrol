#include <QFile>
#include "GeoFenceContainer.h"

//-----------------------------------------------------------------------------

GeoFenceContainer::GeoFenceContainer()
{	}

//-----------------------------------------------------------------------------

GeoFenceContainer::~GeoFenceContainer()
{	}

//-----------------------------------------------------------------------------

bool GeoFenceContainer::Load(QString qsName)
{
	m_qsFile = qsName;
	QFile f(m_qsFile);
	if (f.open(QFile::ReadOnly) == true) {
		QTextStream ts(&f);
		GeoFenceZone zone;
		// read from text stream. The zone load method will return false
		// when it cannot parse a zone anymore
		while (zone.Load(ts) == true)
			Append(zone);

		f.close();
		emit SignalRefresh();
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------

bool GeoFenceContainer::Save(QString qsName)
{
	if (qsName.length() == 0)
		qsName = m_qsFile;

	if (qsName.length() == 0)
		return false;

	QFile f(qsName);
	if (f.open(QFile::WriteOnly) == true) {
		QTextStream ts(&f);
		// write all the zones
		for (int i = 0; i < GetCount(); i++)
			GetZone(i).Save(ts, GeoFenceZone::gffDMS);
		f.close();
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------

void GeoFenceContainer::SetLongitude(int iInd, int iP, double dLon)
{
	GetZone(iInd).SetLongitude(iP, dLon);
	emit SignalUpdate(iInd);
}

//-----------------------------------------------------------------------------

void GeoFenceContainer::SetLatitude(int iInd, int iP, double dLat)
{
	GetZone(iInd).SetLatitude(iP, dLat);
	emit SignalUpdate(iInd);
}

//-----------------------------------------------------------------------------

void GeoFenceContainer::SetLocation(int iInd, int iP, double dLon, double dLat)
{
	GetZone(iInd).SetLongitude(iP, dLon);
	GetZone(iInd).SetLatitude(iP, dLat);
	emit SignalUpdate(iInd);
}

//-----------------------------------------------------------------------------

