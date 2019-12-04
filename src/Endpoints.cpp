#include "ig/Endpoints.h"
#include "tools/http/HttpClient.h"
#include "tools/http/InputFile.h"
#include <iostream>
#include "tools/Tools.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "tools/http/HttpHeader.h"
#include "ig/Constants.h"
#include <boost/uuid/detail/md5.hpp>

namespace ig
{
	Endpoints::Endpoints(const std::string &username, const std::string &password) : m_username(username), m_password(password)
	{}

	bool Endpoints::login() const
	{
		//#####first request#####
		{
			std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());

			//http headers
			std::vector<tools::HttpHeader> http_headers;
			http_headers.push_back(tools::HttpHeader("Connection", "close"));
			http_headers.push_back(tools::HttpHeader("Accept", "*/*"));
			http_headers.push_back(tools::HttpHeader("Content-type", "application/x-www-form-urlencoded; charset=UTF-8"));
			http_headers.push_back(tools::HttpHeader("Cookie2", "$Version=1"));
			http_headers.push_back(tools::HttpHeader("Accept-Language", "en-US"));
			http_headers.push_back(tools::HttpHeader("User-Agent", Constants::ig_user_agent));

			tools::HttpClient http_client(Constants::ig_url + "si/fetch_headers/?challenge_type=signup&guid=" + uuid, http_headers);
			std::string json = http_client.send_post_req_urlencoded(true).txt;
		}

		//#####second request#####
		//todo
		{
			std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());

			//http headers
			std::vector<tools::HttpHeader> http_headers;
			http_headers.push_back(tools::HttpHeader("Connection", "close"));
			http_headers.push_back(tools::HttpHeader("Accept", "*/*"));
			http_headers.push_back(tools::HttpHeader("Content-type", "application/x-www-form-urlencoded; charset=UTF-8"));
			http_headers.push_back(tools::HttpHeader("Cookie2", "$Version=1"));
			http_headers.push_back(tools::HttpHeader("Accept-Language", "en-US"));
			http_headers.push_back(tools::HttpHeader("User-Agent", Constants::ig_user_agent));

			//http args
			std::vector<tools::HttpArg> http_args;
			http_args.push_back(tools::HttpArg("phone_id", "EERRRRRRRRRRRRRRRR"));
			http_args.push_back(tools::HttpArg("_csrftoken", "EERRRRRRRRRRRRRRRR"));
			http_args.push_back(tools::HttpArg("username", m_username));
			http_args.push_back(tools::HttpArg("guid", uuid));
			http_args.push_back(tools::HttpArg("device_id", "EERRRRRRRRRRRRRRRR"));
			http_args.push_back(tools::HttpArg("password", m_password));
			http_args.push_back(tools::HttpArg("login_attempt_count", 0));

//			data = {'phone_id': self.generateUUID(True),
//					'_csrftoken': self.LastResponse.cookies['csrftoken'],
//					'username': self.username,
//					'guid': self.uuid,
//					'device_id': self.device_id,
//					'password': self.password,
//					'login_attempt_count': '0'}
		}
	}
}
