#include <iostream>
#include "ig/Api.h"

int main()
{
	ig::Api api("hija_look", "generic_password");

	api.get_media_comments_all(ig::Api::get_media_id("https://www.instagram.com/p/B6WuipPF2H-/"));

	return 0;
}
