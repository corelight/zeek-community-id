
#include "Plugin.h"

namespace plugin { namespace Corelight_CommunityID { Plugin plugin; } }

using namespace plugin::Corelight_CommunityID;

zeek::plugin::Configuration Plugin::Configure()
	{
	zeek::plugin::Configuration config;
	config.name = "Corelight::CommunityID";
	config.description = "\"Community ID\" flow hash support in the connection log";
	config.version.major = 1;
	config.version.minor = 5;
	return config;
	}
