#include <QDir>
#include <QPluginLoader>
#include <QDebug>

#include "interfaces/BrandingInterface.h"
#include "PluginLoader.h"

//-----------------------------------------------------------------------------

PluginLoader::PluginLoader()
{
	m_pBI = 0;
	m_pGI = 0;
	QDir dir(s_qsPath);
	QStringList qslFiles = dir.entryList(QDir::Files);

	// go through all files and try to load a plugin
	for (int i = 0; i < qslFiles.count(); i++) {
		qDebug() << "Checking" << i << dir.absoluteFilePath(qslFiles[i]);
		QPluginLoader pl(dir.absoluteFilePath(qslFiles[i]));
		QObject* pPlugin = pl.instance();
		if (pPlugin != 0) {
			m_pBI = qobject_cast<BrandingInterface*>(pPlugin);
			m_pGI = qobject_cast<GaugeInterface*>(pPlugin);
		}
	}

	qDebug() << "Interface loaded" << m_pBI << m_pGI << s_qsPath;
}

//-----------------------------------------------------------------------------

PluginLoader::~PluginLoader()
{	}

//-----------------------------------------------------------------------------

PluginLoader* PluginLoader::GetInstance()
{
	if (s_pInstance == 0) {
		if (s_qsPath.length() == 0) {
			qWarning() << "Folder not set in PluginLoader! Call SetFolder before GetInstance";
			Q_ASSERT(s_qsPath.length() > 0);
		}

		s_pInstance = new PluginLoader;
	}

	return s_pInstance;
}

//-----------------------------------------------------------------------------

PluginLoader* PluginLoader::s_pInstance = 0;
QString PluginLoader::s_qsPath = "";

//-----------------------------------------------------------------------------

