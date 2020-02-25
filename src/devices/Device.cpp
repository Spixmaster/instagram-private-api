#include "ig/constants/Constants.h"
#include "ig/devices/Device.h"

namespace ig
{
	Device::~Device()
	{};

	std::string Device::get_ig_version() const noexcept
	{
		return m_ig_version;
	}

	std::string Device::get_android_version() const noexcept
	{
		return m_android_version;
	}

	std::string Device::get_android_release() const noexcept
	{
		return m_android_release;
	}

	std::string Device::get_dpi() const noexcept
	{
		return m_dpi;
	}

	std::string Device::get_resolution() const noexcept
	{
		return m_resolution;
	}

	std::string Device::get_manufacturer() const noexcept
	{
		return m_manufacturer;
	}

	std::string Device::get_device() const noexcept
	{
		return m_device;
	}

	std::string Device::get_model() const noexcept
	{
		return m_model;
	}

	std::string Device::get_cpu() const noexcept
	{
		return m_cpu;
	}

	std::string Device::get_useragent() const noexcept
	{
		return m_useragent;
	}
}
