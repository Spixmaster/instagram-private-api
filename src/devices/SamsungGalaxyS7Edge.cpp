#include "ig/devices/SamsungGalaxyS7Edge.h"
#include "ig/Constants.h"

namespace ig
{
	SamsungGalaxyS7Edge::SamsungGalaxyS7Edge()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "23";
		m_android_release = "6.0.1";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "samsung";
		m_device = "SM-G935";
		m_model = "hero2lte";
		m_cpu = "samsungexynos8890";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	SamsungGalaxyS7Edge::~SamsungGalaxyS7Edge()
	{}

	std::string SamsungGalaxyS7Edge::get_ig_version() const
	{
		return m_ig_version;
	}

	std::string SamsungGalaxyS7Edge::get_android_version() const
	{
		return m_android_version;
	}

	std::string SamsungGalaxyS7Edge::get_android_release() const
	{
		return m_android_release;
	}

	std::string SamsungGalaxyS7Edge::get_dpi() const
	{
		return m_dpi;
	}

	std::string SamsungGalaxyS7Edge::get_resolution() const
	{
		return m_resolution;
	}

	std::string SamsungGalaxyS7Edge::get_manufacturer() const
	{
		return m_manufacturer;
	}

	std::string SamsungGalaxyS7Edge::get_device() const
	{
		return m_device;
	}

	std::string SamsungGalaxyS7Edge::get_model() const
	{
		return m_model;
	}

	std::string SamsungGalaxyS7Edge::get_cpu() const
	{
		return m_cpu;
	}

	std::string SamsungGalaxyS7Edge::get_useragent() const
	{
		return m_useragent;
	}
}
