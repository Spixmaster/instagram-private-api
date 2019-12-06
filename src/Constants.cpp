#include "ig/Constants.h"
#include <string>
#include <iostream>

namespace ig
{
	const std::string Constants::version = "0.0.11";
	const std::string Constants::release = "06.Dec.2019";
	const std::string Constants::ig_url = "https://i.instagram.com/api/v1/";
	const std::string Constants::device_manufacturer = "Xiaomi";
	const std::string Constants::device_model = "HM 1SW";
	const std::string Constants::device_android_version = "18";
	const std::string Constants::device_android_release = "4.3";
	const std::string Constants::ig_user_agent = "Instagram 10.26.0 Android (" + Constants::device_android_version +
			"/" + Constants::device_android_release + "; 320dpi; 720x1280; " + Constants::device_manufacturer + "; " + Constants::device_model + "; armani; qcom; en_US)";
	const std::string Constants::ig_sig_key = "c36436a942ea1dbb40d7f2d7d45280a620d991ce8c62fb4ce600f0a048c32c11";
	const std::string Constants::ig_sig_key_version = "4";
}
