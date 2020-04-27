#ifndef IG_CONSTANTS_CONSTANTS_H
#define IG_CONSTANTS_CONSTANTS_H

#include <string>
#include <memory>

namespace ig
{
	/**
	 * @struct Constants
	 * @brief A container of all constants in the programme.
	 * @details it is a monostate.
	 */
	struct Constants
	{
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<Constants> ptr;

		//Member variables
		/**
		 * @var version
		 * @brief The version of the software.
		 */
		static const std::string version;
		/**
		 * @var release
		 * @brief The release date of the version.
		 */
		static const std::string release;
		//Instagram API
		/**
		 * @var ig_api_url
		 * @brief The url to the Instagram server.
		 */
		static const std::string ig_api_url;
		/**
		 * @var ig_version
		 * @brief The Instagram app version.
		 */
		static const std::string ig_version;
		/**
		 * @var ig_sig_key_version
		 * @brief The signature key version.
		 */
		static const std::string ig_sig_key_version;
		/**
		 * @var ig_sig_key
		 * @brief The signature key which is used to sign most of the HTTP bodies.
		 */
		static const std::string ig_sig_key;
		/**
		 * @var bloks_version_id
		 * @brief The value is used but the meaning is not sure.
		 */
		static const std::string bloks_version_id;
		/**
		 * @var x_ig_capabilities
		 * @brief Some arbitrary value which is sent.
		 */
		static const std::string x_ig_capabilities;
		/**
		 * @var x_ig_app_id
		 * @brief Some arbitrary value which is sent.
		 */
		static const std::string x_ig_app_id;
		/**
		 * @var app_refresh_interval
		 * @brief The value is stated in seconds and defines when a new app opening shall happen.
		 * @details Every app opening is recorded and when the interval is due the app opening process happens again.
		 */
		static const int app_refresh_interval;
		/**
		 * @var log_lns
		 * @brief All requests are logged an this number states how many of them shall be logged.
		 */
		static const int log_lns;
		//HTTP body
		/**
		 * @var qe_sync_experiments
		 * @brief This is an arbitrary value that is sent in the HTTP body.
		 */
		static const std::string qe_sync_experiments;
		/**
		 * @var qe_sync_experiments2
		 * @brief This is an arbitrary value that is sent in the HTTP body.
		 */
		static const std::string qe_sync_experiments2;
		/**
		 * @var supported_capabilities_new
		 * @brief This is an arbitrary value that is sent in the HTTP body.
		 */
		static const std::string supported_capabilities_new;
		/**
		 * @var surfaces_to_queries
		 * @brief This is an arbitrary value that is sent in the HTTP body.
		 */
		static const std::string surfaces_to_queries;
		//Folders
		/**
		 * @var folder
		 * @brief The base folder where all files are stored.
		 */
		static const std::string folder;
		//Files
		/**
		 * @var file_log
		 * @brief The file in which the logs are stored.
		 */
		static const std::string file_log;
	};
}

#endif
