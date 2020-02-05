#include "ig/devices/SamsungGalaxyS9Plus.h"
#include "ig/Constants.h"

namespace ig
{
	SamsungGalaxyS9Plus::SamsungGalaxyS9Plus()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "24";
		m_android_release = "7.0";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "samsung";
		m_device = "SM_G965F";
		m_model = "star2qltecs";
		m_cpu = "samsungexynos9810";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	SamsungGalaxyS9Plus::~SamsungGalaxyS9Plus()
	{}

	std::string SamsungGalaxyS9Plus::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string SamsungGalaxyS9Plus::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string SamsungGalaxyS9Plus::get_android_release() const noexcept
	{
		return m_android_release;
	}

	std::string SamsungGalaxyS9Plus::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string SamsungGalaxyS9Plus::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string SamsungGalaxyS9Plus::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string SamsungGalaxyS9Plus::get_device() const noexcept
	{
		return m_device;
	}

	std::string SamsungGalaxyS9Plus::get_model() const noexcept
	{
		return m_model;
	}

	std::string SamsungGalaxyS9Plus::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string SamsungGalaxyS9Plus::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
