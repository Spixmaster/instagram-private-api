#include "ig/constants/Constants.h"
#include "ig/devices/SamsungGalaxyS7Edge.h"
#include <boost/format.hpp>

namespace ig
{
	SamsungGalaxyS7Edge::SamsungGalaxyS7Edge()
	{
		m_ig_version = Constants::ig_version;
		m_android_api_version = "23";
		m_android_version = "6.0.1";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "samsung";
		m_device = "SM-G935";
		m_model = "hero2lte";
		m_cpu = "samsungexynos8890";
		boost::str(boost::format("Instagram %1% Android (%2%/%3%; %4%; %5%; %6%; %7%; %8%; %9%; en_US") % m_ig_version % m_android_api_version % m_android_version %
				m_dpi % m_resolution % m_manufacturer % m_device % m_model % m_cpu);
	}

	SamsungGalaxyS7Edge::~SamsungGalaxyS7Edge()
	{}

	std::string SamsungGalaxyS7Edge::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string SamsungGalaxyS7Edge::get_android_api_version() const noexcept
	{
		return m_android_api_version;
	}

	std::string SamsungGalaxyS7Edge::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string SamsungGalaxyS7Edge::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string SamsungGalaxyS7Edge::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string SamsungGalaxyS7Edge::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string SamsungGalaxyS7Edge::get_device() const noexcept
	{
		return m_device;
	}

	std::string SamsungGalaxyS7Edge::get_model() const noexcept
	{
		return m_model;
	}

	std::string SamsungGalaxyS7Edge::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string SamsungGalaxyS7Edge::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
