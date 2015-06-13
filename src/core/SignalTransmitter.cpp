#include "SignalTransmitter.h"

//-----------------------------------------------------------------------------

SignalTransmitter::SignalTransmitter() : QObject()
{	}

//-----------------------------------------------------------------------------

SignalTransmitter::~SignalTransmitter()
{	}

//-----------------------------------------------------------------------------

SignalTransmitter* SignalTransmitter::GetInstance()
{
	if (s_pInstance == 0)
		s_pInstance = new SignalTransmitter;
	return s_pInstance;
}

//-----------------------------------------------------------------------------

SignalTransmitter* SignalTransmitter::s_pInstance = 0;

//-----------------------------------------------------------------------------

