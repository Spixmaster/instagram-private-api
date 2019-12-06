#include "ig/Constants.h"
#include <string>
#include <iostream>

namespace ig
{
	const std::string Constants::version = "0.0.11";
	const std::string Constants::release = "05.Dec.2019";
	const std::string Constants::ig_url = "https://i.instagram.com/api/v1/";
	const std::string Constants::device_manufacturer = "Xiaomi";
	const std::string Constants::device_model = "HM 1SW";
	const std::string Constants::device_android_version = "18";
	const std::string Constants::device_android_release = "4.3";
	const std::string Constants::ig_user_agent = "Instagram 10.26.0 Android (" + Constants::device_android_version +
			"/" + Constants::device_android_release + "; 320dpi; 720x1280; " + Constants::device_manufacturer + "; " + Constants::device_model + "; armani; qcom; en_US)";
	const std::string Constants::ig_sig_key = "4f8732eb9ba7d1c8e8897a75d6474d4eb3f5279137431b2aafb71fafe2abe178";
	const std::string Constants::ig_sig_key_version = "4";
}
