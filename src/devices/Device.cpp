#include "ig/devices/Device.h"
#include "ig/Constants.h"

namespace ig
{
	Device::~Device()
	{};

	std::string Device::get_ig_version() const
	{
		return m_ig_version;
	}

	std::string Device::get_android_version() const
	{
		return m_android_version;
	}

	std::string Device::get_android_release() const
	{
		return m_android_release;
	}

	std::string Device::get_dpi() const
	{
		return m_dpi;
	}

	std::string Device::get_resolution() const
	{
		return m_resolution;
	}

	std::string Device::get_manufacturer() const
	{
		return m_manufacturer;
	}

	std::string Device::get_device() const
	{
		return m_device;
	}

	std::string Device::get_model() const
	{
		return m_model;
	}

	std::string Device::get_cpu() const
	{
		return m_cpu;
	}

	std::string Device::get_useragent() const
	{
		return m_useragent;
	}
}
