#include "ig/Api.h"

int main()
{
	ig::Api api("hija_look", "generic_password");
	api.login();

	for(int j = 0; j < 25; ++j)
	{
		api.get_media_comments_all("2198175238655007495_20782778");
		api.get_media_comments_all("2204498368496146133_3854894733");
	}

	return EXIT_SUCCESS;
}
