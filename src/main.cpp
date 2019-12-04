#include <iostream>
#include "ig/Endpoints.h"

int main()
{
	ig::Endpoints temp("nutzername", "pw");
	temp.login();

	return 0;
}
