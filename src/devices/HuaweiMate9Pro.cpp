#include "ig/devices/HuaweiMate9Pro.h"
#include "ig/Constants.h"

namespace ig
{
	HuaweiMate9Pro::HuaweiMate9Pro()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "24";
		m_android_release = "7.0";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "HUAWEI";
		m_device = "LON-L29";
		m_model = "HWLON";
		m_cpu = "hi3660";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	HuaweiMate9Pro::~HuaweiMate9Pro()
	{}

	std::string HuaweiMate9Pro::get_ig_version() const
	{
		return m_ig_version;
	}

	std::string HuaweiMate9Pro::get_android_version() const
	{
		return m_android_version;
	}

	std::string HuaweiMate9Pro::get_android_release() const
	{
		return m_android_release;
	}

	std::string HuaweiMate9Pro::get_dpi() const
	{
		return m_dpi;
	}

	std::string HuaweiMate9Pro::get_resolution() const
	{
		return m_resolution;
	}

	std::string HuaweiMate9Pro::get_manufacturer() const
	{
		return m_manufacturer;
	}

	std::string HuaweiMate9Pro::get_device() const
	{
		return m_device;
	}

	std::string HuaweiMate9Pro::get_model() const
	{
		return m_model;
	}

	std::string HuaweiMate9Pro::get_cpu() const
	{
		return m_cpu;
	}

	std::string HuaweiMate9Pro::get_useragent() const
	{
		return m_useragent;
	}
}
