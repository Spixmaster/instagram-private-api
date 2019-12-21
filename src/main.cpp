#include <iostream>
#include "ig/Api.h"
#include "tools/Tools.h"

int main()
{
	ig::Api api("hija_look", "generic_password");
	api.login();

//	std::cout << api.get_media_likers("2200835617808968768_1992029340") << std::endl;
	std::cout << api.get_media_comments("2200835617808968768_1992029340") << std::endl;

	return 0;
}
