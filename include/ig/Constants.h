#ifndef IG_CONSTANTS_H
#define IG_CONSTANTS_H

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
		static const std::string ig_url;
		static const std::string ig_sig_key_version;
		static const std::string ig_sig_key;
		static const std::string launcher_configs;
		static const std::string login_experiments;
		static const std::string experiments;
			//files
		static const std::string files_folder;
	};
}

#endif
