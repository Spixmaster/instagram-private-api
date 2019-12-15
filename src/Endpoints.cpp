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
#include "ig/devices/one_plus_7.h"
#include <cstdlib>
#include <rapidjson/document.h>

namespace ig
{
	Endpoints::Endpoints(const std::string &username, const std::string &password) : m_username(username), m_password(password)
	{
		login();
	}

	std::vector<tools::HttpHeader> Endpoints::get_ig_http_headers()
	{
		//get time
		time_t raw_time;
		time(&raw_time);

		//seed for rand
		srand(raw_time);

		std::vector<tools::HttpHeader> http_headers;
		http_headers.push_back(tools::HttpHeader("Connection", "Keep-Alive"));
		http_headers.push_back(tools::HttpHeader("X-IG-Capabilities", "IT7nCQ=="));
		http_headers.push_back(tools::HttpHeader("X-IG-App-ID", "567067343352427"));
		http_headers.push_back(tools::HttpHeader("X-IG-Connection-Type", "WIFI"));
		http_headers.push_back(tools::HttpHeader("X-IG-Prefetch-Request", "foreground"));
		http_headers.push_back(tools::HttpHeader("X-IG-VP9-Capable", "false"));
		http_headers.push_back(tools::HttpHeader("X-FB-HTTP-Engine", "Liger"));
		http_headers.push_back(tools::HttpHeader("Accept", "*/*"));
		http_headers.push_back(tools::HttpHeader("Accept-Encoding", "gzip,deflate"));
		http_headers.push_back(tools::HttpHeader("Accept-Language", "en-US"));
		http_headers.push_back(tools::HttpHeader("Content-type", "application/x-www-form-urlencoded; charset=UTF-8"));
		http_headers.push_back(tools::HttpHeader("Cookie2", "$Version=1"));
		http_headers.push_back(tools::HttpHeader("User-Agent", one_plus_7::user_agent));
		http_headers.push_back(tools::HttpHeader("X-IG-Connection-Speed", "-1kbps"));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-Speed-KBPS", std::to_string(rand() % 3000 + 7000)));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalBytes-B", std::to_string(rand() % 400000 + 500000)));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalTime-MS", std::to_string(rand() % 100 + 50)));

		return http_headers;
	}

	std::string Endpoints::mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const
	{
		//http body as json
		std::string raw_http_body;
		raw_http_body.append("{");
		for (std::size_t j = 0; j < http_args.size(); ++j)
		{
			if(std::holds_alternative<long long>(http_args.at(j).m_value))
			{
				raw_http_body.append("\"" + http_args.at(j).m_key + "\": " + std::to_string(std::get<long long>(http_args.at(j).m_value)));

				//add & for next key value pair
				if(j < (http_args.size() - 1))
					raw_http_body.append(", ");
			}
			else if(std::holds_alternative<std::string>(http_args.at(j).m_value))
			{
				raw_http_body.append("\"" + http_args.at(j).m_key + "\": \"" + std::get<std::string>(http_args.at(j).m_value) + "\"");

				//add & for next key value pair
				if(j < (http_args.size() - 1))
					raw_http_body.append(", ");
			}
			//value is type of InputFile::ptr and thus ignored
		}
		raw_http_body.append("}");

		//raw_http_body --> http_body
		std::string http_body;
		http_body.append("ig_sig_key_version=" + Constants::ig_sig_key_version + "&signed_body=");
		http_body.append(tools::Tools::hmac_sha256_hash(Constants::ig_sig_key, raw_http_body) +
				"." + tools::Tools::parse_url(raw_http_body, "@&="));

		return http_body;
	}

	bool Endpoints::login()
	{
		std::string csrftoken;
		std::string mid;
		std::string rur;
		//#####first request#####
		{
			std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			uuid.erase(std::remove(uuid.begin(), uuid.end(), '-'), uuid.end());

			tools::HttpClient http_client(Constants::ig_url + "si/fetch_headers/?challenge_type=signup&guid=" + uuid, get_ig_http_headers());
			tools::HttpResponse http_res = http_client.send_get_req(true);

			//get the cookies
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
		{
			std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			//device id has to be uuid with length 16 and hex in format android-...
			std::string device_id_temp = boost::uuids::to_string(boost::uuids::random_generator()());
			device_id_temp.resize(16);
			std::stringstream sstream;
			sstream << std::hex << device_id_temp;
			std::string device_id = "android-" + sstream.str();

			//http headers
			std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
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

			tools::HttpClient http_client(Constants::ig_url + "accounts/login/", http_headers, http_args);
			tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args), true);

			//get the cookies
			for(size_t j = 0; j < http_res.m_headers.size(); ++j)
			{
				if(csrftoken.empty())
					csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

				if(mid.empty())
					mid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "mid");

				if(rur.empty())
					rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");
			}

			//todo
			std::cout << "ACHHTUNLAKSDNFÖLKSDJF: " << tools::Tools::encode_utf8(http_res.m_body) << std::endl;

			//#####checkpoint_challenge_required#####
			rapidjson::Document doc;
			doc.Parse(http_res.m_body.c_str());

			if(doc.IsObject())
			{
				if(doc.HasMember("error_type"))
				{
					if(doc["error_type"].GetString() == std::string("checkpoint_challenge_required"))
					{
						if(doc.HasMember("challenge"))
						{
							const rapidjson::Value &challenge = doc["challenge"];

							if(challenge.HasMember("api_path"))
							{
								std::string api_path = tools::Tools::cut_off_first_char(challenge["api_path"].GetString());

								//http headers
								std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
								http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + csrftoken + "; mid=" + mid + "; rur=" + rur));

								tools::HttpClient http_client(Constants::ig_url + api_path, http_headers);
								tools::HttpResponse http_res = http_client.send_get_req();
							}
						}
					}
				}
			}
			else
			{
				std::cerr << "Error. The server response on the login request is not a json object." << std::endl;
				return false;
			}
		}
		return true;
	}
}
