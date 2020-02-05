#ifndef IG_DEVICES_DEVICE_H
#define IG_DEVICES_DEVICE_H

#include <memory>

/*
 * @brief this class is only there for inheritance reasons
 * @brief all devices inherent from it
 */

namespace ig
{
	class Device
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<Device> ptr;

	private:
		//member variables
		std::string m_ig_version;
		std::string m_android_version;
		std::string m_android_release;
		std::string m_dpi;
		std::string m_resolution;
		std::string m_manufacturer;
		std::string m_device;
		std::string m_model;
		std::string m_cpu;
		std::string m_useragent;

	public:
		//destructors
		virtual ~Device();

		//member functions
		/*
		 * @brief getter for m_ig_version
		 * @return m_ig_version
		 */
		virtual std::string get_ig_version() const noexcept;

		/*
		 * @brief getter for m_android_version
		 * @return m_android_version
		 */
		virtual std::string get_android_version() const noexcept;

		/*
		 * @brief getter for m_android_release
		 * @return m_android_release
		 */
		virtual std::string get_android_release() const noexcept;

		/*
		 * @brief getter for m_dpi
		 * @return m_dpi
		 */
		virtual std::string get_dpi() const noexcept;

		/*
		 * @brief getter for m_resolution
		 * @return m_resolution
		 */
		virtual std::string get_resolution() const noexcept;

		/*
		 * @brief getter for m_manufacturer
		 * @return m_manufacturer
		 */
		virtual std::string get_manufacturer() const noexcept;

		/*
		 * @brief getter for m_device
		 * @return m_device
		 */
		virtual std::string get_device() const noexcept;

		/*
		 * @brief getter for m_model
		 * @return m_model
		 */
		virtual std::string get_model() const noexcept;

		/*
		 * @brief getter for m_cpu
		 * @return m_cpu
		 */
		virtual std::string get_cpu() const noexcept;

		/*
		 * @brief getter for m_useragent
		 * @return m_useragent
		 */
		virtual std::string get_useragent() const noexcept;
	};
}

#endif
