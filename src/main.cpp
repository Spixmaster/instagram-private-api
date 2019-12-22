#include <iostream>
#include "ig/Api.h"

int main()
{
	ig::Api api("hija_look", "generic_password");
	api.login();

//	std::cout << api.get_media_comments("2198175238655007495_20782778") << std::endl; //todo view all
//	std::cout << api.get_media_comments("2198175238655007495_20782778", "0") << std::endl; //todo view all
	std::cout << api.get_media_comments("2198175238655007495_20782778", "150") << std::endl; //todo view all

	return 0;
}
