#ifndef IG_CONSTANTS_CONSTANTS_H
#define IG_CONSTANTS_CONSTANTS_H

#include <string>
#include <memory>

/*
 * @brief container of all constants in the programme
 * @brief it is a monostate
 */

namespace ig
{
	struct Constants
	{
		//pointer of itself
		typedef std::shared_ptr<Constants> ptr;

		//member variables
		static const std::string version;
		static const std::string release;
			//Instagram Api
		static const std::string ig_api_url;
		static const std::string ig_version;
		static const std::string ig_sig_key_version;
		static const std::string ig_sig_key;
		static const std::string bloks_version_id;
		static const std::string x_ig_capabilities;
		static const std::string x_ig_app_id;
		static const int app_refresh_interval;
		static const int log_lns;
				//http body
		static const std::string qe_sync_experiments;
		static const std::string qe_sync_experiments2;
		static const std::string supported_capabilities_new;
		static const std::string surfaces_to_queries;
			//folders
		static const std::string folder;
			//files
		static const std::string file_log;
	};
}

#endif
