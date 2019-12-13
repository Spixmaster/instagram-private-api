#include <iostream>
#include "ig/Endpoints.h"
#include "tools/Tools.h"
#include <Poco/UTF8String.h>

int main()
{
//	ig::Endpoints temp("hija_look", "generic_password");
//	temp.login();

	std::string temp = "pythön!";
	temp = Poco::UTF8::escape(temp);

	return 0;
}
