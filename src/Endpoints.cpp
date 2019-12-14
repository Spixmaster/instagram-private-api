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
#include <iomanip>
#include <Poco/URI.h>

namespace ig
{
	Endpoints::Endpoints(const std::string &username, const std::string &password) : m_username(username), m_password(password)
	{
		m_http_headers.push_back(tools::HttpHeader("Connection", "close"));
		m_http_headers.push_back(tools::HttpHeader("Accept", "*/*"));
		m_http_headers.push_back(tools::HttpHeader("Content-type", "application/x-www-form-urlencoded; charset=UTF-8"));
		m_http_headers.push_back(tools::HttpHeader("Cookie2", "$Version=1"));
		m_http_headers.push_back(tools::HttpHeader("Accept-Language", "en-US"));
		m_http_headers.push_back(tools::HttpHeader("User-Agent", Constants::ig_user_agent));
		m_http_headers.push_back(tools::HttpHeader("Accept-Encoding", "gzip, deflate"));
	}

	tools::HttpResponse Endpoints::send_req_ig(const std::string &url, const std::vector<tools::HttpHeader> &http_headers,
			const std::vector<tools::HttpArg> &http_args, const bool &debug)
	{
		//http body
		std::string raw_http_body;
		for (std::size_t j = 0; j < http_args.size(); ++j)
		{
			if(std::holds_alternative<long long>(http_args.at(j).m_value))
			{
				raw_http_body.append(http_args.at(j).m_key + "=" + std::to_string(std::get<long long>(http_args.at(j).m_value)));

				//add & for next key value pair
				if(j < (http_args.size() - 1))
					raw_http_body.append("&");
			}
			else if(std::holds_alternative<std::string>(http_args.at(j).m_value))
			{
				raw_http_body.append(http_args.at(j).m_key + "=" + std::get<std::string>(http_args.at(j).m_value));

				//add & for next key value pair
				if(j < (http_args.size() - 1))
					raw_http_body.append("&");
			}
			//value is type of InputFile::ptr and thus ignored
		}

		//raw_http_body --> http_body
		std::string http_body;
		http_body.append("ig_sig_key_version=" + Constants::ig_sig_key_version + "&signed_body=");
		http_body.append(tools::Tools::hmac_sha256_hash(Constants::ig_sig_key, raw_http_body) +
				"." + tools::Tools::parse_url(raw_http_body, "@&="));

		//http headers
		m_http_headers.push_back(tools::HttpHeader("Content-Length", std::to_string(http_body.size())));
		for(size_t j = 0; j < http_headers.size(); ++j)
			m_http_headers.push_back(tools::HttpHeader(http_headers.at(j).m_key, http_headers.at(j).m_value));

		//send the request
		tools::HttpClient http_client(url, m_http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(http_body, debug);

		return http_res;
	}

	bool Endpoints::login()
	{
		std::string csrftoken;
		std::string mid;
		std::string rur = "FRC";
		//#####first request#####
		{
			std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());

			tools::HttpClient http_client(Constants::ig_url + "si/fetch_headers/?challenge_type=signup&guid=" + uuid, m_http_headers);
			tools::HttpResponse http_res = http_client.send_get_req(true);

			/*
			 * get the cookies
			 * get the csrftoken
			 */
			for(size_t j = 0; j < http_res.m_headers.size(); ++j)
			{
				if(csrftoken.empty())
					csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

				if(mid.empty())
					mid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "mid");

				if(rur.empty())
					rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");
			}
		}

		//#####second request#####
		//todo
		{
			std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			//device id has to be uuid with length 16 and hex in format android-...
			std::string device_id_temp = boost::uuids::to_string(boost::uuids::random_generator()());
			device_id_temp.resize(16);
			std::stringstream sstream;
			sstream << std::hex << device_id_temp;
			std::string device_id = "android-" + sstream.str();

			//http headers
			std::vector<tools::HttpHeader> http_headers;
			//csrftoken=CKb0QvsxBuqzVr0b1sxLpDlqq2M85oTl; mid=XfSLcAABAAGrbIXIQOY8uOjJIPMi; rur=FRC
			http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + csrftoken + "; mid=" + mid + "; rur=" + rur));

			//http args
			std::vector<tools::HttpArg> http_args;
			http_args.push_back(tools::HttpArg("phone_id", uuid));
			http_args.push_back(tools::HttpArg("_csrftoken", csrftoken));
			http_args.push_back(tools::HttpArg("username", m_username));
			http_args.push_back(tools::HttpArg("guid", uuid));
			http_args.push_back(tools::HttpArg("device_id", device_id));
			http_args.push_back(tools::HttpArg("password", m_password));
			http_args.push_back(tools::HttpArg("login_attempt_count", 0));

			send_req_ig(Constants::ig_url + "accounts/login/", http_headers, http_args, true);
		}
		return true;
	}
}
