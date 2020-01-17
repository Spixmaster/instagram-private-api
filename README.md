# instagram-private-api
A C++ library for the Instagram API. As Instagram does not provide a public API for developers this library pretends to be an Instagram account logging in from a mobile device.

## Usage
You can only use this project in your own ones. Thus, no main is included.

### As a submodule
```sh
cd to/your/project
git submodule add *link to this repo*
```

### As a contributor
#### eclipse
* clone the project to anywhere
* create a new eclipse project
* right click on the project > Import > General > File System
* select all content from the cloned project

### Compiler
You need to use a C++17 compiler.

### Dependencies
The following packages need to be installed:

#### Poco
```sh
sudo apt install libpoco-dev
```

#### rapidjson
Moreover, [rapdijson](https://github.com/Tencent/rapidjson) needs to be installed.

For this, do the following steps:
```sh
git clone https://github.com/Tencent/rapidjson
cd rapidjson
cmake .
make -j4
sudo make install
```

#### boost
```sh
sudo apt install libboost-all-dev
```

#### Submodules
```sh
git submodule init
git submodule update
```

#### Libraries that need to be linked (option -l)
* PocoFoundation
* PocoNetSSL
* PocoNet
* PocoCrypto
* boost_iostreams

### Example
```cpp
#include "ig/Api.h"

int main()
{
	ig::Api::ptr api = std::make_shared<ig::Api>("the_username", "the_password");

	std::string all_comments = api->get_media_comments_all(ig::Api::get_media_id("https://www.instagram.com/p/B6WuipPF2H-/"));
	std::string likers = api->get_media_likers(ig::Api::get_media_id("https://www.instagram.com/p/B6bV0_ygLQe/"));

	return EXIT_SUCCESS;
}
```

## FAQ
* Q: Is it safe to use this library?
* A: This question cannot be answered with yes or no. If you really depend on logging in on the Instagram servers you can be happy that you have found this repository. In the other case, that you just want to test it I cannot really recommend you to do so. Do not understand me wrong. This software is more likely to work than not but things can go wrong. It may happen to you that you cannot log in which is caused by your account. If you try to log in with a different account it should work. This situation occurs frequently. In one case I was not able to log in ever again with this project after trying to log in to this date but with the official Android app everything works fine. In worse cases, my accounts were banned temporarily, not deleted. The account was still visible from third accounts but I was not able to log in with them for like 9 hours after that time they worked like before. The ban's duration varies.

Whenever unexpected errors occur, the software will inform you via the stderr output.

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

## Thanks to
Sniffing Instagram's http requests is not easy as I described in the wiki. Thus, I copied the endpoints from already existing projects. These repos helped me a lot and I want to thank them. Without the help of the existing source code I would not have been able to write my code for this project.
* https://github.com/mgp25/Instagram-API
* https://github.com/instagrambot/instabot
* https://github.com/ping/instagram_private_api
* https://github.com/LevPasha/Instagram-API-python
