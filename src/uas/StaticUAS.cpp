#include "StaticUAS.h"

//-----------------------------------------------------------------------------

StaticUAS::StaticUAS(MAVLinkProtocol *protocol, int id) :
	UAS(protocol, id)
{	}

//-----------------------------------------------------------------------------

StaticUAS::~StaticUAS()
{	}

//-----------------------------------------------------------------------------

QString StaticUAS::getUASName() const
{	return "staticUAS"; }

//-----------------------------------------------------------------------------

int StaticUAS::getAutopilotType()
{	return MAV_AUTOPILOT_ARDUPILOTMEGA; }

//-----------------------------------------------------------------------------

