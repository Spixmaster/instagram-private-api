#include "ig/Endpoints.h"
#include "tools/http/HttpClient.h"
#include "tools/http/InputFile.h"
#include <iostream>
#include "tools/Tools.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace ig
{
	Endpoints::Endpoints(const std::string &username, const std::string &password) : m_username(username), m_password(password)
	{}

	bool Endpoints::login() const
	{
		boost::uuids::uuid uuid = boost::uuids::random_generator()();

		//req nach si/fetch_headers/?challenge_type=signup&guid=

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("chat_id", "asdf"));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("chat_id", "asdf"));

		tools::HttpClient http_client("https://api.telegram.org/bot" + m_token + "/sendMessage", http_args);
		std::string json = http_client.send_post_req_multipart().txt;


	}
}
