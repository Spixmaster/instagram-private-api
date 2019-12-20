#include <iostream>
#include "ig/Api.h"
#include "tools/Tools.h"
#include <variant>

void hi(std::variant<std::string, int> hi)
{
	std::cout << "juten tag" << std::endl;
}

int main()
{
	ig::Api api("hija_look", "generic_password");

	hi(5);
	hi("isjfsdofj");

//	std::cout << api.get_media_likers("2200835617808968768_1992029340") << std::endl;
//	std::cout << api.get_media_comments("2200835617808968768_1992029340") << std::endl;

	return 0;
}
