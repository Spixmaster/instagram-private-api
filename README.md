# instagram-private-api
A C++ library for the Instagram API. As Instagram does not provide a public API for developers this library pretends to be an Instagram account logging in from a mobile device.

## Installation
### As a submodule
```sh
cd to/your/project
git submodule add *link-to-this-repo*
```

### As a contributor
The project needs to be set up properly in your IDE to be able to compile it.

#### Example eclipse
These instructions show how to set up the project right in eclipse.
1. Clone the project to anywhere.
2. Create a new eclipse project.
3. Right click on the project > "Import" > "General" > "File System".
4. Select all content from the cloned project.

### Compiler
You need to use a C++20 compiler for compilation.

### Dependencies
This software is built with the help of third party libraries. It is shown below how to install them.

#### Poco
```sh
sudo apt install libpoco-dev
```

#### rapidjson
```sh
sudo apt install rapidjson-dev
```

#### boost
```sh
sudo apt install libboost-all-dev
```

#### Submodules
```sh
cd folder/to/this/project/
git submodule init
git submodule update
```

#### Libraries that need to be linked (option -l)
* PocoFoundation
* PocoNetSSL
* PocoNet
* PocoCrypto
* boost_system
* boost_filesystem
* boost_iostreams
* boost_locale

## Usage
The source code cannot be compiled by itself as there is no main function included. It is thought to be used in other software as a library.

### Documentation
The documentation was generated with the help of Doxygen. It is an HTML document and can be found in *./doc/html/index.html*. Open that file with your favourite browser.

### Example
```cpp
#include "ig/constants/Constants.h"
#include "ig/Api.h"
#include <memory>

int main(int argc, const char *argv[])
{
	ig::Api::ptr api = std::make_shared<ig::Api>("the_username", "the_password", ig::Constants::folder);

	std::string all_comments = api->get_media_comments_all(ig::Api::get_media_id("https://www.instagram.com/p/B6WuipPF2H-/"));
	std::string likers = api->get_media_likers(ig::Api::get_media_id("https://www.instagram.com/p/B6bV0_ygLQe/"));

	return EXIT_SUCCESS;
}
```

## Changelog
The changelog can be seen on the documentation's main page.

## FAQ
* Q: Is it safe to use this library?
* A: This question cannot be answered with yes or no. If you really depend on logging in on the Instagram servers you can be happy that you have found this repository. In the other case, that you just want to test it I cannot really recommend you to do so. Do not understand me wrong. This software is more likely to work than not but things can go wrong. It may happen to you that you cannot log in which is caused by your account. If you try to log in with a different account it should work. This situation occurs frequently. In one case I was not able to log in a long time with this project after trying to log but with the official Android app everything worked fine. In worse cases, my accounts were banned temporarily, not deleted. The account was still visible from third accounts but I was not able to log in with them for like 9 hours after that time they worked like before. The ban's duration may vary.\
Whenever unexpected errors occur, the software will inform you via the error log.\
The good part is that as soon as you logged in and got the proper cookies. You are safe for as long as the cookies are valid. I have never experienced problems after the login process despite one time when one of my account was deleted due to massive liking and commenting. Do not do that! I turned away from this kind of abuse and so should you.
***
* Q: Are the cookies saved or is it necessary to login again every time?
* A: Of course they are. Just log in once and use the cookies for approximately quarter a year.
***
* Q: The API requests me to solve a challenge manually. What do I need to do?
* A: Just follow the instructions sent with the message. There is no reason to worry. Your session is still valid but Instagram blocks requests from it as long as you have not solved the challenge. The challenge is nothing remarkable. It is a simple captcha. You will encounter it when you log in to Instagram in your browser.

## Safe usage
Everything you read here in this section is not required but I would recommend you follow suit these advices.
* Do not keep too many open sessions which happens if you only log in to Instagram with your account but do not log out and instead just delete the cookies and additional app information. Thus, call the logout member function if you no longer want to use that specific session. This will also delete the proper files from your machine for you. It is a security risk and should make Instagram suspicous if there are to many open sessions for one account. Go to [this page](https://www.instagram.com/session/login_activity/) when logged in in your browser and manage your open sessions if your forgot to log out and just deleted your cookies.
* After the login go to [this page](https://www.instagram.com/session/login_activity/) in your browser again and approve your login. You will encouter the information that a device logged in. Just tell Instagram that that was you by clicking the proper button.
* Go [here](https://www.instagram.com/session/login_activity/) regularly to check your sessions.
* You should use an account with a verified mobile number. You do not even need a SIM card for this. Consider [this service](https://sms-activate.ru/en/).
* Make the account look trustworthy. Set up a profile picture, follow some accounts, like and comment on some posts.

## Thanks to
These repos helped me a lot and I want to thank them. Without the help of the existing source code I would not have been able to write my first code for this project.
* https://github.com/instagrambot/instabot
* https://github.com/LevPasha/Instagram-API-python
* https://github.com/ping/instagram_private_api
* https://github.com/itsMoji/Instagram_SSL_Pinning
