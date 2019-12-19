#ifndef IG_DEVICES_ONE_PLUS_7_H
#define IG_DEVICES_ONE_PLUS_7_H

#include <string>
#include <memory>

/*
 * @brief this struct simpy contains information about a mobile device
 * @brief the information is needed for Instagram
 */

namespace ig
{
	struct OnePlus7
	{
		//pointer of itself
		typedef std::shared_ptr<OnePlus7> ptr;

		//member variables
		std::string ig_version;
		std::string android_version;
		std::string android_release;
		std::string dpi;
		std::string resolution;
		std::string manufacturer;
		std::string device;
		std::string model;
		std::string cpu;
		std::string user_agent;
	};
}

#endif
