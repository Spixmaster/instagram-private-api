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
	ig::Api api("the_username", "the_password");
	
	std::string all_comments = api.get_media_comments_all(ig::Api::get_media_id("https://www.instagram.com/p/B6WuipPF2H-/"));
	std::string likers = api.get_media_likers(ig::Api::get_media_id("https://www.instagram.com/p/B6bV0_ygLQe/"));
	
	return EXIT_SUCCESS;
}
```

## FAQ
* Q: Is it safe to use this library?
* A: I use it personally very extensively and can relate from my experience that you do not need to worry about your account too much. After months of use of the common python Instagram libraries I never experienced any restrictions or even deletions. My library is just a port from them and should thus not cause any complications. Nevertheless, the use of an Instagram account whose loss you could bear is not stupid. You can send to many requests in which case the servers will respond with an error message but after a cooldown everything will work as expected.
***
* Q: Did not you forget to make some post login request during the login process?
* A: I am aware of them but do not deem them to be necessary. It works fine without them.
***
* Q: The API requests me to solve a challenge manually. What do I need to do?
* A: Just follow the instructions sent with the message. There is no reason to worry. Your session is still valid but Instagram blocks requests from it as long as you have not solved the challenge. The challenge is nothing remarkable. It is a simple captcha. You will encounter it when you log in to Instagram in your browser.

## Safe usage
Everything you read here in this section is not required but I would recommend you follow suit these advices.
* Do not keep too many open sessions which happens if you only log in to Instagram with your account but do not log out and instead just delete the cookies and uuids. Thus, call the logout member function if you no longer want to use that specific session. This will also delete the proper files from your machine for you. It is a security risk and should make Instagram suspicous if there are to many open sessions for one account. Go to [this page](https://www.instagram.com/session/login_activity/) when logged in in your browser and manage your open sessions if your forgot to log out and just deleted your cookies.
* After the login go to [this page](https://www.instagram.com/session/login_activity/) in your browser again and approve your login. You will encouter the information that a device logged in. Just tell Instagram that that was you by clicking the proper button.
* Go [here](https://www.instagram.com/session/login_activity/) regularly to check your sessions.

## Technical
An [MITM attack](https://www.youtube.com/watch?v=rub_uNFwTF8) on a mobile device is needed to get all Instagram's endpoints. As Instagram has some additional security measures it is needed to [break certificate pinning](https://www.youtube.com/watch?v=yJRlMmJjrhY).

## Thanks to
As I could not root my phone due to is unpopularity as there are mainly roots available for popular phones I was reliant on other people's work. These repos helped me a lot and I want to thank them. Without the help of the existing source code I would not have been able to write my code for this project.
* https://github.com/mgp25/Instagram-API
* https://github.com/instagrambot/instabot
* https://github.com/ping/instagram_private_api
* https://github.com/LevPasha/Instagram-API-python
