#pragma once

#include <zeek/plugin/Plugin.h>

namespace plugin {
namespace Corelight_CommunityID {

class Plugin : public zeek::plugin::Plugin
{
protected:
	// Overridden from plugin::Plugin.
	zeek::plugin::Configuration Configure() override;
};

extern Plugin plugin;

}
}
