#ifndef PIXMAPGENERATOR_H
#define PIXMAPGENERATOR_H

#include <QPixmap>
#include <QPixmapCache>

//! This class is used to generate some pixmaps
class PixmapGenerator
{
public:
	//! Generates teardrop
	static QPixmap GetTearDrop();
};

#endif // PIXMAPGENERATOR_H
