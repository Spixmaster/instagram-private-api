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

namespace ig
{
	Endpoints::Endpoints(const std::string &username, const std::string &password) : m_username(username), m_password(password)
	{}

	bool Endpoints::login() const
	{
		boost::uuids::uuid uuid = boost::uuids::random_generator()();

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
		http_args.push_back(tools::HttpArg("chat_id", "asdf"));

		tools::HttpClient http_client(Constants::ig_url + "si/fetch_headers/?challenge_type=signup&guid=" + uuid, http_args);
		std::string json = http_client.send_post_req_multipart().txt;


	}
}
