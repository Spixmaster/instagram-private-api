#include <iostream>
#include "ig/Endpoints.h"
#include "tools/Tools.h"
#include <Poco/UTF8String.h>

int main()
{
	ig::Endpoints temp("hija_look", "161861joanf");
	temp.login();

	return 0;
}
