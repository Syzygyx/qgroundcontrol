#include "PixmapGenerator.h"

//-----------------------------------------------------------------------------

QPixmap PixmapGenerator::GetTearDrop()
{
	QString qsName = ":/markers/images/marker1.png";

	QPixmap* pPixSaved = QPixmapCache::find(qsName);
	if (pPixSaved != 0)
		return *pPixSaved;

	QPixmap pix;
	pix.load(qsName);

	QPixmapCache::insert(qsName, pix);
	return pix;
}

//-----------------------------------------------------------------------------

