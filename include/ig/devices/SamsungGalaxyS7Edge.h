#ifndef IG_DEVICES_SAMSUNG_GALAXY_S7_EDGE_H
#define IG_DEVICES_SAMSUNG_GALAXY_S7_EDGE_H

#include <string>
#include <memory>
#include "ig/devices/Device.h"

/*
 * @brief this class simply contains information about a mobile device
 * @brief the information is needed for Instagram
 */

namespace ig
{
	class SamsungGalaxyS7Edge: public Device
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<SamsungGalaxyS7Edge> ptr;

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
		//constructors
		SamsungGalaxyS7Edge();

		//destructors
		virtual ~SamsungGalaxyS7Edge();

		//member functions
		/*
		 * @brief getter for m_ig_version
		 * @return m_ig_version
		 */
		std::string get_ig_version() const noexcept;

		/*
		 * @brief getter for m_android_version
		 * @return m_android_version
		 */
		std::string get_android_version() const noexcept;

		/*
		 * @brief getter for m_android_release
		 * @return m_android_release
		 */
		std::string get_android_release() const noexcept;

		/*
		 * @brief getter for m_dpi
		 * @return m_dpi
		 */
		std::string get_dpi() const noexcept;

		/*
		 * @brief getter for m_resolution
		 * @return m_resolution
		 */
		std::string get_resolution() const noexcept;

		/*
		 * @brief getter for m_manufacturer
		 * @return m_manufacturer
		 */
		std::string get_manufacturer() const noexcept;

		/*
		 * @brief getter for m_device
		 * @return m_device
		 */
		std::string get_device() const noexcept;

		/*
		 * @brief getter for m_model
		 * @return m_model
		 */
		std::string get_model() const noexcept;

		/*
		 * @brief getter for m_cpu
		 * @return m_cpu
		 */
		std::string get_cpu() const noexcept;

		/*
		 * @brief getter for m_useragent
		 * @return m_useragent
		 */
		std::string get_useragent() const noexcept;
	};
}

#endif
