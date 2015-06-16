#include "ReferenceTechnologiesPlugin.h"

//-----------------------------------------------------------------------------

ReferenceTechnologiesPlugin::ReferenceTechnologiesPlugin(QObject *parent) :
	QGenericPlugin(parent)
{
}

//-----------------------------------------------------------------------------

ReferenceTechnologiesPlugin::~ReferenceTechnologiesPlugin()
{	}

//-----------------------------------------------------------------------------

QPixmap ReferenceTechnologiesPlugin::GetSplashPixmap() const
{
	QPixmap pix(":/files/full-logo.png");
	return pix;
}

//-----------------------------------------------------------------------------

QObject* ReferenceTechnologiesPlugin::create(const QString &name, const QString &spec)
{
	return 0;
}

//-----------------------------------------------------------------------------

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ReferenceTechnologies, ReferenceTechnologiesPlugin)
#endif // QT_VERSION < 0x050000
