#ifndef IG_DEVICES_SAMSUNG_GALAXY_S7_H
#define IG_DEVICES_SAMSUNG_GALAXY_S7_H

#include <string>
#include <memory>

/*
 * @brief this struct simply contains information about a mobile device
 * @brief the information is needed for Instagram
 */

namespace ig
{
	struct SamsungGalaxyS7
	{
		//pointer of itself
		typedef std::shared_ptr<SamsungGalaxyS7> ptr;

		//member variables
		static const std::string ig_version;
		static const std::string android_version;
		static const std::string android_release;
		static const std::string dpi;
		static const std::string resolution;
		static const std::string manufacturer;
		static const std::string device;
		static const std::string model;
		static const std::string cpu;
		static const std::string user_agent;
	};
}

#endif
