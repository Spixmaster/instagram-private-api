#include "ig/constants/Constants.h"
#include "ig/devices/LgG5.h"

namespace ig
{
	LgG5::LgG5()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "23";
		m_android_release = "6.0.1";
		m_dpi = "640dpi";
		m_resolution = "1440x2392";
		m_manufacturer = "LGE/lge";
		m_device = "RS988";
		m_model = "h1";
		m_cpu = "h1";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	LgG5::~LgG5()
	{}

	std::string LgG5::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string LgG5::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string LgG5::get_android_release() const noexcept
	{
		return m_android_release;
	}

	std::string LgG5::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string LgG5::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string LgG5::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string LgG5::get_device() const noexcept
	{
		return m_device;
	}

	std::string LgG5::get_model() const noexcept
	{
		return m_model;
	}

	std::string LgG5::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string LgG5::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
