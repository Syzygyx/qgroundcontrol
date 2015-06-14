#ifndef MODELDATA_H
#define MODELDATA_H

#include <QObject>

#include "GeoFence/GeoFenceContainer.h"

//! This singleton class receives and emits some signals
class ModelData : public QObject
{
	Q_OBJECT

private:
	//! Singleton, thus private constructor
	ModelData();

public:
	//! Destructor
	virtual ~ModelData();

	//! Returns pointer to the instance
	static ModelData* GetInstance();

	//! Returns full access to GeoFence container
	GeoFenceContainer& GetGFC()
	{	return m_conGF; }

signals:
	//! Should be emitted when GeoFence file needs to be loaded
	void SignalLoadGF(QString qsName);
	//! Should be emitted when GeoFence file needs to be saved
	void SignalSaveGF(QString qsName);

private:
	//! Pointer to the instance
	static ModelData* s_pInstance;
	//! Object containing GeoFence zones
	GeoFenceContainer m_conGF;
};


#endif // MODELDATA_H
