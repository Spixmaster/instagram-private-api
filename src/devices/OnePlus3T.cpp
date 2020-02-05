#include "ig/devices/OnePlus3T.h"
#include "ig/Constants.h"

namespace ig
{
	OnePlus3T::OnePlus3T()
	{
		m_ig_version = Constants::ig_version;
		m_android_version = "24";
		m_android_release = "7.0";
		m_dpi = "380dpi";
		m_resolution = "1080x1920";
		m_manufacturer = "OnePlus";
		m_device = "ONEPLUS A3010";
		m_model = "OnePlus3T";
		m_cpu = "qcom";
		m_useragent = "Instagram " + m_ig_version + " Android (" +
				m_android_version + "/" + m_android_release + "; " + m_dpi + "; " +
				m_resolution + "; " + m_manufacturer + "; " + m_device +
				"; " + m_model + "; " + m_cpu + "; en_US)";
	}

	OnePlus3T::~OnePlus3T()
	{}

	std::string OnePlus3T::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string OnePlus3T::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string OnePlus3T::get_android_release() const noexcept
	{
		return m_android_release;
	}

	std::string OnePlus3T::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string OnePlus3T::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string OnePlus3T::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string OnePlus3T::get_device() const noexcept
	{
		return m_device;
	}

	std::string OnePlus3T::get_model() const noexcept
	{
		return m_model;
	}

	std::string OnePlus3T::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string OnePlus3T::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
