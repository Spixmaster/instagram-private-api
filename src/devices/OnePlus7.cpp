#include "ig/constants/Constants.h"
#include "ig/devices/OnePlus7.h"
#include <boost/format.hpp>

namespace ig
{
	OnePlus7::OnePlus7()
	{
		m_ig_version = Constants::ig_version;
		m_android_api_version = "28";
		m_android_version = "9.0";
		m_dpi = "420dpi";
		m_resolution = "1080x2260";
		m_manufacturer = "OnePlus";
		m_device = "GM1903";
		m_model = "OnePlus7";
		m_cpu = "qcom";
		boost::str(boost::format("Instagram %1% Android (%2%/%3%; %4%; %5%; %6%; %7%; %8%; %9%; en_US") % m_ig_version % m_android_api_version % m_android_version %
				m_dpi % m_resolution % m_manufacturer % m_device % m_model % m_cpu);
	}

	OnePlus7::~OnePlus7()
	{}

	std::string OnePlus7::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string OnePlus7::get_android_api_version() const noexcept
	{
		return m_android_api_version;
	}

	std::string OnePlus7::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string OnePlus7::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string OnePlus7::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string OnePlus7::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string OnePlus7::get_device() const noexcept
	{
		return m_device;
	}

	std::string OnePlus7::get_model() const noexcept
	{
		return m_model;
	}

	std::string OnePlus7::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string OnePlus7::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
