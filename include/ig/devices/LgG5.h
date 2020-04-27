#ifndef IG_DEVICES_LG_G5_h
#define IG_DEVICES_LG_G5_h

#include <string>
#include <memory>
#include "ig/devices/Device.h"

namespace ig
{
	/**
	 * @class LgG5
	 * @brief This class represents the LG G5.
	 */
	class LgG5: public Device
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<LgG5> ptr;

	private:
		//Member variables
		/**
		 * @var m_ig_version
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_ig_version;
		/**
		 * @var m_android_api_version
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_android_api_version;
		/**
		 * @var m_android_version
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_android_version;
		/**
		 * @var m_dpi
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_dpi;
		/**
		 * @var m_resolution
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_resolution;
		/**
		 * @var m_manufacturer
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_manufacturer;
		/**
		 * @var m_device
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_device;
		/**
		 * @var m_model
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_model;
		/**
		 * @var m_cpu
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_cpu;
		/**
		 * @var m_useragent
		 * @brief See the super class for documentation on this member variable.
		 */
		std::string m_useragent;

	public:
		//Constructors
		LgG5();

		//Destructors
		virtual ~LgG5();

		//Member functions
		/**
		 * @brief Getter.
		 * @return m_ig_version
		 */
		std::string get_ig_version() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_android_api_version
		 */
		std::string get_android_api_version() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_android_version
		 */
		std::string get_android_version() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_dpi
		 */
		std::string get_dpi() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_resolution
		 */
		std::string get_resolution() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_manufacturer
		 */
		std::string get_manufacturer() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_device
		 */
		std::string get_device() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_model
		 */
		std::string get_model() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_cpu
		 */
		std::string get_cpu() const noexcept;

		/**
		 * @brief Getter.
		 * @return m_useragent
		 */
		std::string get_useragent() const noexcept;
	};
}

#endif
