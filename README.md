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

	if(api.login())
    {
        std::string all_comments = api.get_media_comments_all("2198175238655007495_20782778");
        std::string likers = api.get_media_likers("2204498368496146133_3854894733");
    }

	return EXIT_SUCCESS;
}
```

## FAQ
* Q: Is it safe to use this library?
* A: I use it personally very extensively and can relate from my experience that you do not need to worry about your account too much. After months of use of the common python Instagram libraries I never experienced any restrictions or even deletions. My library is just a port from them and should thus not cause any complications. Nevertheless, the use of an Instagram account whose loss you could bear is not stupid. You can send to many requests in which case the servers will respond with an error message but after a cooldown everything will work as expected.
***
* Q: Did not you forget to make some post login request during the login process?
* A: I am aware of them but do not deem them to be necessary. It works fine without them.

## Technical
An [MITM attack](https://www.youtube.com/watch?v=rub_uNFwTF8) on a mobile device is needed to get all Instagram's endpoints. As Instagram has some additional security measures it is needed to [break certificate pinning](https://www.youtube.com/watch?v=yJRlMmJjrhY).

## Thanks to
As I could not root my phone due to is unpopularity as there are mainly roots available for popular phones I was reliant on other people's work. These repos helped me a lot and I want to thank them. Without the help of the existing source code I would not have been able to write my code for this project.
* https://github.com/mgp25/Instagram-API
* https://github.com/instagrambot/instabot
* https://github.com/ping/instagram_private_api
* https://github.com/LevPasha/Instagram-API-python
