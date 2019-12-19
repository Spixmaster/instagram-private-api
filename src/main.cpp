#include <iostream>
#include "ig/Endpoints.h"
#include "tools/Tools.h"

int main()
{
	ig::Endpoints api("hija_look", "generic_password");

	std::cout << tools::Tools::gzip_decompress(api.get_media_likers("2200835617808968768_1992029340")) << std::endl;

	return 0;
}
