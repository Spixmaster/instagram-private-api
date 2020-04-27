#include "ig/constants/Constants.h"
#include "ig/devices/ZteAxon7.h"
#include <boost/format.hpp>

namespace ig
{
	ZteAxon7::ZteAxon7()
	{
		m_ig_version = Constants::ig_version;
		m_android_api_version = "23";
		m_android_version = "6.0.1";
		m_dpi = "640dpi";
		m_resolution = "1440x2560";
		m_manufacturer = "ZTE";
		m_device = "ZTE A2017U";
		m_model = "ailsa_ii";
		m_cpu = "qcom";
		boost::str(boost::format("Instagram %1% Android (%2%/%3%; %4%; %5%; %6%; %7%; %8%; %9%; en_US") % m_ig_version % m_android_api_version % m_android_version %
				m_dpi % m_resolution % m_manufacturer % m_device % m_model % m_cpu);
	}

	ZteAxon7::~ZteAxon7()
	{}

	std::string ZteAxon7::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string ZteAxon7::get_android_api_version() const noexcept
	{
		return m_android_api_version;
	}

	std::string ZteAxon7::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string ZteAxon7::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string ZteAxon7::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string ZteAxon7::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string ZteAxon7::get_device() const noexcept
	{
		return m_device;
	}

	std::string ZteAxon7::get_model() const noexcept
	{
		return m_model;
	}

	std::string ZteAxon7::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string ZteAxon7::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
