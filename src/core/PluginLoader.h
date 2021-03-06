#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QString>

#include "interfaces/BrandingInterface.h"
#include "interfaces/GaugeInterface.h"

//! This singleton class is used to load dynamic plugins
class PluginLoader
{
private:
	//! This is singleton, thus private constructor
	PluginLoader();
public:
	//! Destructor
	~PluginLoader();

	//! Returns pointer to the instance
	static PluginLoader* GetInstance();
	//! Sets the plugins folder
	static void SetFolder(QString qsDir)
	{	s_qsPath = qsDir; }

	//! Returns pointer to the branding interface
	const BrandingInterface* GetPlugin() const
	{	return m_pBI; }
	//! Returns pointer to the gauge interface
	const GaugeInterface* GetGauges() const
	{	return m_pGI; }

private:
	//! Pointer to the instance
	static PluginLoader* s_pInstance;
	//! Should be set to folder where plugins are located before calling GetInstance!
	static QString s_qsPath;
	//! Pointer to the implementation of BrandingInterface
	BrandingInterface* m_pBI;
	//! Pointer to the implementation of GaugeInterface
	GaugeInterface* m_pGI;
};

#endif // PLUGINLOADER_H
