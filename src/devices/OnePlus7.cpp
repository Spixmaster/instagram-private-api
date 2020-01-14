#include "ig/devices/OnePlus7.h"
#include "ig/Constants.h"

namespace ig
{
	OnePlus7::OnePlus7()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "28";
		m_android_release = "9.0";
		m_dpi = "420dpi";
		m_resolution = "1080x2260";
		m_manufacturer = "OnePlus";
		m_device = "GM1903";
		m_model = "OnePlus7";
		m_cpu = "qcom";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	OnePlus7::~OnePlus7()
	{}

	std::string OnePlus7::get_ig_version() const
	{
		return m_ig_version;
	}

	std::string OnePlus7::get_android_version() const
	{
		return m_android_version;
	}

	std::string OnePlus7::get_android_release() const
	{
		return m_android_release;
	}

	std::string OnePlus7::get_dpi() const
	{
		return m_dpi;
	}

	std::string OnePlus7::get_resolution() const
	{
		return m_resolution;
	}

	std::string OnePlus7::get_manufacturer() const
	{
		return m_manufacturer;
	}

	std::string OnePlus7::get_device() const
	{
		return m_device;
	}

	std::string OnePlus7::get_model() const
	{
		return m_model;
	}

	std::string OnePlus7::get_cpu() const
	{
		return m_cpu;
	}

	std::string OnePlus7::get_useragent() const
	{
		return m_useragent;
	}
}
