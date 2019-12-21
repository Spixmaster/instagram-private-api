#include <iostream>
#include "ig/Api.h"

int main()
{
	ig::Api api("hija_look", "generic_password");
	api.login();

	api.get_media_likers("2200835617808968768_1992029340");
//	std::cout << api.get_media_comments("2200835617808968768_1992029340") << std::endl;

	return 0;
}
