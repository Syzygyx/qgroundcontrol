#ifndef STATICUAS_H
#define STATICUAS_H

#include "UAS.h"

/** This class doesn't really represent UAS. It is a fake UAS,
 *  used solely for the purpose of being used in default UASWaypointManager
 */
class StaticUAS : public UAS
{
public:
	//! Constructor
	StaticUAS(MAVLinkProtocol* protocol, int id = 0);
	//! Destructor
	~StaticUAS();

	//! Returns the name
	QString getUASName() const;

	//! Returns the autopilot type
	int getAutopilotType();
};

#endif // STATICUAS_H
