#include "ig/constants/Constants.h"
#include "ig/devices/HuaweiMate9Pro.h"
#include <boost/format.hpp>

namespace ig
{
	HuaweiMate9Pro::HuaweiMate9Pro()
	{
		m_ig_version = Constants::ig_version;
		m_android_api_version = "24";
		m_android_version = "7.0";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "HUAWEI";
		m_device = "LON-L29";
		m_model = "HWLON";
		m_cpu = "hi3660";
		boost::str(boost::format("Instagram %1% Android (%2%/%3%; %4%; %5%; %6%; %7%; %8%; %9%; en_US") % m_ig_version % m_android_api_version % m_android_version %
				m_dpi % m_resolution % m_manufacturer % m_device % m_model % m_cpu);
	}

	HuaweiMate9Pro::~HuaweiMate9Pro()
	{}

	std::string HuaweiMate9Pro::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string HuaweiMate9Pro::get_android_api_version() const noexcept
	{
		return m_android_api_version;
	}

	std::string HuaweiMate9Pro::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string HuaweiMate9Pro::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string HuaweiMate9Pro::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string HuaweiMate9Pro::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string HuaweiMate9Pro::get_device() const noexcept
	{
		return m_device;
	}

	std::string HuaweiMate9Pro::get_model() const noexcept
	{
		return m_model;
	}

	std::string HuaweiMate9Pro::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string HuaweiMate9Pro::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
