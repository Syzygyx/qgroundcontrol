#ifndef REFERENCETECHNOLOGIESPLUGIN_H
#define REFERENCETECHNOLOGIESPLUGIN_H

#include <QGenericPlugin>

#include "BrandingInterface.h"

class ReferenceTechnologiesPlugin :
		public QGenericPlugin,
		public BrandingInterface
{
	Q_OBJECT
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.ReferenceTechnologiesInterface" FILE "ReferenceTechnologies.json")
#endif // QT_VERSION >= 0x050000
	Q_INTERFACES(BrandingInterface)

public:
	//! Constructor
	ReferenceTechnologiesPlugin(QObject *parent = 0);
	//! Destructor
	~ReferenceTechnologiesPlugin();
	//! Loads and returns the main splash screen logo
	QPixmap GetSplashPixmap() const Q_DECL_OVERRIDE;
	//! Creates some object
	QObject* create(const QString& name, const QString& spec);
};

#endif // REFERENCETECHNOLOGIESPLUGIN_H
