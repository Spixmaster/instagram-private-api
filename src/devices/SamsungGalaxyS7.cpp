#include "ig/devices/SamsungGalaxyS7.h"
#include "ig/Constants.h"

namespace ig
{
	SamsungGalaxyS7::SamsungGalaxyS7()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "24";
		m_android_release = "7.0";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "samsung";
		m_device = "SM-G930F";
		m_model = "herolte";
		m_cpu = "samsungexynos8890";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	SamsungGalaxyS7::~SamsungGalaxyS7()
	{}

	std::string SamsungGalaxyS7::get_ig_version() const
	{
		return m_ig_version;
	}

	std::string SamsungGalaxyS7::get_android_version() const
	{
		return m_android_version;
	}

	std::string SamsungGalaxyS7::get_android_release() const
	{
		return m_android_release;
	}

	std::string SamsungGalaxyS7::get_dpi() const
	{
		return m_dpi;
	}

	std::string SamsungGalaxyS7::get_resolution() const
	{
		return m_resolution;
	}

	std::string SamsungGalaxyS7::get_manufacturer() const
	{
		return m_manufacturer;
	}

	std::string SamsungGalaxyS7::get_device() const
	{
		return m_device;
	}

	std::string SamsungGalaxyS7::get_model() const
	{
		return m_model;
	}

	std::string SamsungGalaxyS7::get_cpu() const
	{
		return m_cpu;
	}

	std::string SamsungGalaxyS7::get_useragent() const
	{
		return m_useragent;
	}
}
