#ifndef IG_DEVICES_DEVICE_H
#define IG_DEVICES_DEVICE_H

#include <memory>

namespace ig
{
	/**
	 * @class Device
	 * @brief This class is only there for inheritance reasons. It contains all information of a device which are needed for the Instagram app.
	 * @details All devices inherent from it.
	 */
	class Device
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<Device> ptr;

	private:
		//Member variables
		/**
		 * @var m_ig_version
		 * @brief The Instagram app version.
		 */
		std::string m_ig_version;
		/**
		 * @var m_android_version
		 * @brief The Android API version.
		 */
		std::string m_android_api_version;
		/**
		 * @var m_android_version
		 * @brief The Android version.
		 */
		std::string m_android_version;
		/**
		 * @var m_dpi
		 * @brief Dots per inch.
		 */
		std::string m_dpi;
		/**
		 * @var m_resolution
		 * @brief The resolution.
		 */
		std::string m_resolution;
		/**
		 * @var m_manufacturer
		 * @brief The manufacturer.
		 */
		std::string m_manufacturer;
		/**
		 * @var m_device
		 * @brief The device.
		 */
		std::string m_device;
		/**
		 * @var m_model
		 * @brief The model.
		 */
		std::string m_model;
		/**
		 * @var m_cpu
		 * @brief The CPU.
		 */
		std::string m_cpu;
		/**
		 * @var m_cpu
		 * @brief The useragent based on the device's settings.
		 */
		std::string m_useragent;

	public:
		//Destructors
		virtual ~Device();

		//Member functions
		/**
		 * @brief Getter.
		 * @return m_ig_version
		 */
		virtual std::string get_ig_version() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_android_api_version
		 */
		virtual std::string get_android_api_version() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_android_version
		 */
		virtual std::string get_android_version() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_dpi
		 */
		virtual std::string get_dpi() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_resolution
		 */
		virtual std::string get_resolution() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_manufacturer
		 */
		virtual std::string get_manufacturer() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_device
		 */
		virtual std::string get_device() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_model
		 */
		virtual std::string get_model() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_cpu
		 */
		virtual std::string get_cpu() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_useragent
		 */
		virtual std::string get_useragent() const noexcept;
	};
}

#endif
