#include "ig/devices/SamsungGalaxyS7.h"

namespace ig
{
	const std::string SamsungGalaxyS7::ig_version = "105.0.0.18.119";
	const std::string SamsungGalaxyS7::android_version = "24";
	const std::string SamsungGalaxyS7::android_release = "7.0";
	const std::string SamsungGalaxyS7::dpi = "640dpi";
	const std::string SamsungGalaxyS7::resolution = "1440x2560";
	const std::string SamsungGalaxyS7::manufacturer = "samsung";
	const std::string SamsungGalaxyS7::device = "SM-G930F";
	const std::string SamsungGalaxyS7::model = "herolte";
	const std::string SamsungGalaxyS7::cpu = "samsungexynos8890";
	const std::string SamsungGalaxyS7::user_agent = "Instagram " + SamsungGalaxyS7::ig_version + " Android (" +
			SamsungGalaxyS7::android_version + "/" + SamsungGalaxyS7::android_release + "; " + SamsungGalaxyS7::dpi + "; " +
			SamsungGalaxyS7::resolution + "; " + SamsungGalaxyS7::manufacturer + "; " + SamsungGalaxyS7::device +
			"; " + SamsungGalaxyS7::model + "; " + SamsungGalaxyS7::cpu + "; en_US)";
}
