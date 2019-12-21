#include <iostream>
#include "ig/Api.h"
#include "tools/Tools.h"
#include <Poco/Net/HTTPCookie.h>
#include "tools/http/HttpCookie.h" //todo

int main()
{
	std::string cookie = "urlgen={\"2003:c4:5700:d800:c903:db81:fae2:ed2a\":3320}:ligUlu:acPgszMCKOmm2WEGFeqxLgQt5RY; Domain=.instagram.om;HttpOnly;Path=/; Secure";

	tools::HttpCookie http_cookie(cookie);

	std::cout << http_cookie.get_domain() << std::endl;
	std::cout << http_cookie.get_expires() << std::endl;
	std::cout << http_cookie.get_http_only() << std::endl;
	std::cout << http_cookie.get_max_age() << std::endl;
	std::cout << http_cookie.get_name() << std::endl;
	std::cout << http_cookie.get_path() << std::endl;
	std::cout << http_cookie.get_secure() << std::endl;
	std::cout << http_cookie.get_value() << std::endl;

//	ig::Api api("hija_look", "generic_password");
//	api.login();

//	std::cout << api.get_media_likers("2200835617808968768_1992029340") << std::endl;
//	std::cout << api.get_media_comments("2200835617808968768_1992029340") << std::endl;

	return 0;
}
