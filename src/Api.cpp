#include "ig/Api.h"
#include "tools/http/HttpClient.h"
#include "tools/http/InputFile.h"
#include <iostream>
#include "tools/Tools.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "tools/http/HttpHeader.h"
#include "ig/devices/OnePlus7.h"
#include "ig/devices/SamsungGalaxyS7.h"
#include <cstdlib>
#include <rapidjson/document.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include "ig/devices/HuaweiMate9Pro.h"
#include "ig/devices/LgG5.h"
#include "ig/devices/OnePlus3T.h"
#include "ig/devices/SamsungGalaxyS7Edge.h"
#include "ig/devices/SamsungGalaxyS9Plus.h"
#include "ig/devices/ZteAxon7.h"
#include <boost/algorithm/string.hpp>
#include "ig/constants/Constants.h"
#include <unistd.h>
#include "ig/constants/Messages.h"
#include "tools/constants/Messages.h"
#include <boost/locale.hpp>
#include <boost/format.hpp>
#include <rapidjson/rapidjson.h>

namespace ig
{
	Api::Api(const std::string &username, const std::string &password, const std::string &files_folder) : m_username(username), m_password(password),
			m_file_app_info(files_folder + username + "_app_info.dat"), m_file_cookies(files_folder + username + "_cookies.dat"), m_del_app_info_and_cookies(false)
	{
		//Create necessary folders.
		if(!tools::Tools::file_exists(Constants::folder))
			tools::Tools::mkdir(Constants::folder);

		if(!tools::Tools::file_exists(files_folder))
			tools::Tools::mkdir(files_folder);

		//This function determines whether a new login is required.
		setup_app_info_and_cookies();

		if(login())
		{
			save_app_info_in_file();
			save_cookies_in_file();
		}
	}

	Api::~Api()
	{
		if(m_del_app_info_and_cookies)
		{
			tools::Tools::del_file(m_file_app_info);
			tools::Tools::del_file(m_file_cookies);
		}
	}

	void Api::setup_app_info_and_cookies() noexcept
	{
		if(tools::Tools::file_exists(m_file_app_info))
		{
			//m_x_google_ad_id
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_x_google_ad_id"));

				if(!val.empty())
					m_x_google_ad_id = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_x_google_ad_id", m_file_app_info));
			}

			//m_x_pigeon_session_id
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_x_pigeon_session_id"));

				if(!val.empty())
					m_x_pigeon_session_id = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_x_pigeon_session_id", m_file_app_info));
			}

			//m_x_ig_device_id
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_x_ig_device_id"));

				if(!val.empty())
					m_x_ig_device_id = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_x_ig_device_id", m_file_app_info));
			}

			//m_x_ig_android_id
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_x_ig_android_id"));

				if(!val.empty())
					m_x_ig_android_id = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_x_ig_android_id", m_file_app_info));
			}

			//m_useragent
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_useragent"));

				if(!val.empty())
					m_useragent = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_useragent", m_file_app_info));
			}

			//m_x_ig_www_claim
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_x_ig_www_claim"));

				if(!val.empty())
					m_x_ig_www_claim = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_x_ig_www_claim", m_file_app_info));
			}

			//m_authorization
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_authorization"));

				if(!val.empty())
					m_authorization = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_authorization", m_file_app_info));
			}

			//m_phone_id
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_phone_id"));

				if(!val.empty())
					m_phone_id = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_phone_id", m_file_app_info));
			}

			//m_last_seen_feed_media_id
			{
				std::string val = tools::Tools::get_file_ln_val(tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_last_seen_feed_media_id"));

				if(!val.empty())
					m_last_seen_feed_media_id = val;
				else
					tools::Tools::write_err_log_tmp(Messages::field_no_value_in_file("m_last_seen_feed_media_id", m_file_app_info));
			}

			//m_last_app_opening
			{
				std::string entry = tools::Tools::get_file_ln_w_srch(m_file_app_info, "m_last_app_opening");
				if(!entry.empty())
					m_last_app_opening = tools::Tools::get_num_ln_end(entry);
				else
					tools::Tools::write_err_log_tmp(Messages::field_not_found_in_file("m_last_app_opening", m_file_app_info));
			}
		}
		else
			tools::Messages::file_non_existent(m_file_app_info);

		if(tools::Tools::file_exists(m_file_cookies))
		{
			for(int j = 1; j <= tools::Tools::get_amnt_file_lns(m_file_cookies); ++j)
				if(!tools::Tools::get_file_ln(m_file_cookies, j).empty())
					m_cookies.push_back(tools::HttpCookie(tools::Tools::get_file_ln(m_file_cookies, j)));
		}
		else
			tools::Messages::file_non_existent(m_file_cookies);

		//Just for orientation about the cookies.
		if(get_cookie_val("ds_user").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("ds_user"));

		if(get_cookie_val("csrftoken").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("csrftoken"));

		//It seems that this cookie is not necessary.
//		if(get_cookie_val("shbid").empty())
//			tools::Tools::write_err_log_tmp(Messages::cookie_missing("shbid"));

		//It seems that this cookie is not necessary.
//		if(get_cookie_val("shbts").empty())
//			tools::Tools::write_err_log_tmp(Messages::cookie_missing("shbts"));

		if(get_cookie_val("rur").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("rur"));

		if(get_cookie_val("ds_user_id").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("ds_user_id"));

		if(get_cookie_val("urlgen").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("urlgen"));

		if(get_cookie_val("sessionid").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("sessionid"));

		if(get_cookie_val("mid").empty())
			tools::Tools::write_err_log_tmp(Messages::cookie_missing("mid"));

		/*
		 * If some app info is missing.
		 * If a cookie is missing. I already know the names of those which are needed.
		 * It is not checked for last_login as it is not necessary and would only cause problems.
		 * The same it true for m_last_seen_feed_media_id because it is not even set when there is no feed.
		 */
		if(m_x_google_ad_id.empty() || m_x_pigeon_session_id.empty() || m_x_ig_device_id.empty() || m_x_ig_android_id.empty() || m_useragent.empty() ||
				m_x_ig_www_claim.empty() || m_authorization.empty() || m_phone_id.empty() ||
				get_cookie_val("ds_user").empty() || get_cookie_val("csrftoken").empty() || get_cookie_val("rur").empty() ||
				get_cookie_val("ds_user_id").empty() || get_cookie_val("urlgen").empty() || get_cookie_val("sessionid").empty() || get_cookie_val("mid").empty())
		{
			m_new_login = true;

			//Empty the cookies so that the existing entries are not used for the next login. The app info can remain.
			std::ofstream outf(m_file_cookies);
			outf.close();

			//Get a random device.
			std::vector<Device::ptr> devices;
			devices.push_back(std::make_shared<HuaweiMate9Pro>());
			devices.push_back(std::make_shared<LgG5>());
			devices.push_back(std::make_shared<OnePlus3T>());
			devices.push_back(std::make_shared<OnePlus7>());
			devices.push_back(std::make_shared<SamsungGalaxyS7>());
			devices.push_back(std::make_shared<SamsungGalaxyS7Edge>());
			devices.push_back(std::make_shared<SamsungGalaxyS9Plus>());
			devices.push_back(std::make_shared<ZteAxon7>());

			srand(tools::Tools::get_seed());
			int random_index = std::rand() % devices.size();
			m_device = devices.at(random_index);

			//Generate new uuids.
			m_x_google_ad_id = boost::uuids::to_string(boost::uuids::random_generator()());
			m_x_pigeon_session_id = boost::uuids::to_string(boost::uuids::random_generator()());
			m_x_ig_device_id = boost::uuids::to_string(boost::uuids::random_generator()());
			//m_x_ig_android_id has to be a uuid with length 16 and hex in format "android-...".
			std::string m_x_ig_android_id_temp = boost::uuids::to_string(boost::uuids::random_generator()());
			m_x_ig_android_id_temp.erase(std::remove(m_x_ig_android_id_temp.begin(), m_x_ig_android_id_temp.end(), '-'), m_x_ig_android_id_temp.end());
			m_x_ig_android_id_temp.resize(16);
			m_x_ig_android_id = "android-" + m_x_ig_android_id_temp;
			m_useragent = m_device->get_useragent();
			m_phone_id = boost::uuids::to_string(boost::uuids::random_generator()());

			std::cout << Messages::no_cookies_found << std::endl;
		}
		else
		{
			m_new_login = false;
			set_cookie_str();
		}
	}

	std::vector<tools::HttpHeader> Api::get_ig_http_headers() const noexcept
	{
		boost::locale::generator gen;
		std::locale loc = gen(""); //Uses system default.

		std::vector<tools::HttpHeader> http_headers;
		http_headers.push_back(tools::HttpHeader("X-Ads-Opt-Out", "0"));
		http_headers.push_back(tools::HttpHeader("X-Google-AD-ID", m_x_google_ad_id));
		http_headers.push_back(tools::HttpHeader("X-Device-ID", m_x_ig_device_id));
		http_headers.push_back(tools::HttpHeader("X-CM-Bandwidth-KBPS", "-1.000"));
		http_headers.push_back(tools::HttpHeader("X-CM-Latency", "-1.000"));
		http_headers.push_back(tools::HttpHeader("X-IG-App-Locale", "en_US"));
		http_headers.push_back(tools::HttpHeader("X-IG-Device-Locale", "en_US"));
		http_headers.push_back(tools::HttpHeader("X-IG-Mapped-Locale", "en_US"));
		http_headers.push_back(tools::HttpHeader("X-Pigeon-Session-Id", m_x_pigeon_session_id));
		http_headers.push_back(tools::HttpHeader("X-Pigeon-Rawclienttime", std::to_string(tools::Tools::get_time_w_millisec())));
		http_headers.push_back(tools::HttpHeader("X-IG-Connection-Speed", "-1kbps"));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-Speed-KBPS", "-1.000"));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalBytes-B", "0"));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalTime-MS", "0"));
		http_headers.push_back(tools::HttpHeader("X-IG-Prefetch-Request", "foreground"));
//		http_headers.push_back(tools::HttpHeader("X-IG-EU-DC-ENABLED", "true")); Only in EU activated.
		http_headers.push_back(tools::HttpHeader("X-IG-App-Startup-Country", std::use_facet<boost::locale::info>(loc).country()));
		http_headers.push_back(tools::HttpHeader("X-Bloks-Version-Id", Constants::bloks_version_id));
		http_headers.push_back(tools::HttpHeader("X-IG-WWW-Claim", m_x_ig_www_claim));
		http_headers.push_back(tools::HttpHeader("X-Bloks-Is-Layout-RTL", "false"));
		http_headers.push_back(tools::HttpHeader("X-Bloks-Enable-RenderCore", "false"));
		http_headers.push_back(tools::HttpHeader("X-IG-Device-ID", m_x_ig_device_id));
		http_headers.push_back(tools::HttpHeader("X-IG-Android-ID", m_x_ig_android_id));
		http_headers.push_back(tools::HttpHeader("X-IG-Connection-Type", "WIFI"));
		http_headers.push_back(tools::HttpHeader("X-IG-Capabilities", Constants::x_ig_capabilities));
		http_headers.push_back(tools::HttpHeader("X-IG-App-ID", Constants::x_ig_app_id));
		http_headers.push_back(tools::HttpHeader("User-Agent", m_useragent));
		http_headers.push_back(tools::HttpHeader("Accept-Language", "en-US"));
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));
		if(m_authorization != "Bearer IGT:2:")
			http_headers.push_back(tools::HttpHeader("Authorization", m_authorization));
		http_headers.push_back(tools::HttpHeader("X-MID", get_cookie_val("mid")));
		http_headers.push_back(tools::HttpHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8"));
		http_headers.push_back(tools::HttpHeader("Accept-Encoding", "gzip, deflate"));
		http_headers.push_back(tools::HttpHeader("Host", "i.instagram.com"));
		http_headers.push_back(tools::HttpHeader("X-FB-HTTP-Engine", "Liger"));
		http_headers.push_back(tools::HttpHeader("Connection", "close"));

		return http_headers;
	}

	std::string Api::mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const noexcept
	{
		//HTTP body as JSON.
		std::string raw_http_body;
		raw_http_body.append("{");
		for(std::size_t j = 0; j < http_args.size(); ++j)
		{
			if(std::holds_alternative<long long>(http_args.at(j).m_value))
			{
				raw_http_body.append("\"" + http_args.at(j).m_key + "\": " + std::to_string(std::get<long long>(http_args.at(j).m_value)));

				//Add "&" for next key-value pair.
				if(j != http_args.size() - 1)
					raw_http_body.append(", ");
			}
			else if(std::holds_alternative<std::string>(http_args.at(j).m_value))
			{
				raw_http_body.append("\"" + http_args.at(j).m_key + "\": \"" + std::get<std::string>(http_args.at(j).m_value) + "\"");

				//Add "&" for next key-value pair.
				if(j != http_args.size() - 1)
					raw_http_body.append(", ");
			}
			//The value is type of InputFile::ptr and thus ignored.
		}
		raw_http_body.append("}");

		//Now, the raw HTTP body is made to the correct HTTP body.
		std::string http_body;
		http_body.append("signed_body=" + tools::Tools::hmac_sha256_hash(Constants::ig_sig_key, raw_http_body) +
				"." + raw_http_body);
		http_body.append("&ig_sig_key_version=" + Constants::ig_sig_key_version);

		return http_body;
	}

	void Api::save_app_info_in_file() const noexcept
	{
		std::ofstream outf(m_file_app_info);
		outf << "m_x_google_ad_id: " << m_x_google_ad_id << std::endl;
		outf << "m_x_pigeon_session_id: " << m_x_pigeon_session_id << std::endl;
		outf << "m_x_ig_device_id: " << m_x_ig_device_id << std::endl;
		outf << "m_x_ig_android_id: " << m_x_ig_android_id << std::endl;
		outf << "m_useragent: " << m_useragent << std::endl;
		outf << "m_x_ig_www_claim: " << m_x_ig_www_claim << std::endl;
		outf << "m_authorization: " << m_authorization << std::endl;
		outf << "m_phone_id: " << m_phone_id << std::endl;
		outf << "m_last_seen_feed_media_id: " << m_last_seen_feed_media_id << std::endl;
		outf << "m_last_app_opening: " << m_last_app_opening << std::endl;
		outf.close();
	}

	void Api::save_cookies_in_file() const noexcept
	{
		std::ofstream outf(m_file_cookies);

		for(std::size_t j = 0; j < m_cookies.size(); ++j)
			outf << m_cookies.at(j).to_string() << std::endl;

		outf.close();
	}

	void Api::set_cookie_str() noexcept
	{
		std::string temp;

		for(std::size_t j = 0; j < m_cookies.size(); ++j)
		{
			temp.append(m_cookies.at(j).get_name() + "=" + m_cookies.at(j).get_value());

			//Check whether a semicolon is needed.
			if(j != m_cookies.size() - 1)
				temp.append("; ");
		}

		m_cookie_str = temp;
	}

	void Api::update_data(const std::vector<tools::HttpCookie> &http_cookies) noexcept
	{
		//Update the cookies:
		for(std::size_t j = 0; j < http_cookies.size(); ++j)
		{
			//Does the cookie already exist?
			bool found = false;
			std::size_t pos_old_cookie_to_updt;

			for(std::size_t k = 0; k < m_cookies.size(); ++k)
			{
				if(http_cookies.at(j).get_name() == m_cookies.at(k).get_name())
				{
					found = true;
					pos_old_cookie_to_updt = k;
					break;
				}
			}

			//Add a new cookie.
			if(found == false)
				m_cookies.push_back(http_cookies.at(j));
			//Update all old cookies.
			else
			{
				m_cookies.erase(m_cookies.begin() + pos_old_cookie_to_updt);
				m_cookies.push_back(http_cookies.at(j));
			}
		}

		m_cookies.shrink_to_fit();

		save_app_info_in_file();
		save_cookies_in_file();
		set_cookie_str();
	}

	std::string Api::get_cookie_val(const std::string &cookie_name) const noexcept
	{
		std::string cookie_val;

		for(std::size_t j = 0; j < m_cookies.size(); ++j)
		{
			if(m_cookies.at(j).get_name() == cookie_name)
			{
				cookie_val = m_cookies.at(j).get_value();
				break;
			}
		}

		return cookie_val;
	}

	std::string Api::get_jazoest() const noexcept
	{
		int sum = 0;

		for(std::size_t j = 0; j < m_phone_id.size(); ++j)
			sum += m_phone_id.at(j);

		return "2" + std::to_string(sum);
	}

	std::string Api::get_rank_token() const noexcept
	{
		return get_cookie_val("ds_user_id") + "_" + m_x_ig_device_id;
	}

	void Api::set_last_seen_feed_media_id(const std::string &last_feed_timeline) noexcept
	{
		rapidjson::Document doc;
		doc.Parse(last_feed_timeline.c_str());

		if(doc.IsObject())
			if(doc.HasMember("feed_items"))
				if(doc["feed_items"].IsArray())
					if(doc["feed_items"].Size() > 0)
						if(doc["feed_items"][0].HasMember("media_or_ad"))
							if(doc["feed_items"][0]["media_or_ad"].HasMember("id"))
								if(doc["feed_items"][0]["media_or_ad"]["id"].IsString())
									m_last_seen_feed_media_id = doc["feed_items"][0]["media_or_ad"]["id"].GetString();
								else
									tools::Tools::write_err_log(Messages::field_not_contain_string("id"));
							else
								tools::Tools::write_err_log(Messages::field_not_found("id"));
						else
							tools::Tools::write_err_log(Messages::field_not_found("media_or_ad"));
					else
						tools::Tools::write_err_log(Messages::json_array_has_size_0("feed_items"));
				else
					tools::Tools::write_err_log(Messages::field_not_contain_json_array("feed_items"));
			else
				tools::Tools::write_err_log(Messages::field_not_found("feed_items"));
		else
			tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
	}

	std::string Api::get_feed_view_info() const noexcept
	{
		srand(tools::Tools::get_seed());

		//feed_view_info
		std::string feed_view_info;
		//The condition is needed because if the user has no feed (when having subscribed to nobody) it cannot be that madia_pct is set.
		if(!m_last_seen_feed_media_id.empty())
		{
			feed_view_info = "[{";
			feed_view_info.append("\"media_id\":\"" + m_last_seen_feed_media_id + "\",");
			feed_view_info.append("\"version\":24,");
			double d = (rand() % 101) / 100.0;

			if(d < 0.3)
				d += 0.7;

			feed_view_info.append("\"media_pct\":" + std::to_string(d) + ",");
			int i = (rand() % 132491) + 3217;
			feed_view_info.append("\"time_info\":{" +
					std::string("\"10\":") + std::to_string(i) + "," +
					std::string("\"25\":") + std::to_string(i) + "," +
					std::string("\"50\":") + std::to_string(i) + "," +
					std::string("\"75\":") + std::to_string(i) + "}");
			feed_view_info.append("}]");
		}
		else
			feed_view_info = "[]";

		return feed_view_info;
	}

	void Api::post_req_check(const tools::HttpClient &http_client, const tools::HttpResponse &server_resp, const bool &no_throw)
	{
		//Search for values we need.
		for(std::size_t j = 0;  j < server_resp.m_headers.size(); ++j)
		{
			if(server_resp.m_headers.at(j).m_key == "x-ig-set-www-claim")
				m_x_ig_www_claim = server_resp.m_headers.at(j).m_value;

			if(server_resp.m_headers.at(j).m_key == "ig-set-authorization")
				m_authorization = server_resp.m_headers.at(j).m_value;
		}

		//Log
		if(tools::Tools::get_amnt_file_lns(Constants::file_log) < Constants::log_lns)
		{
			std::ofstream outf(Constants::file_log, std::ios::app);
			outf << m_username << " " << tools::Tools::get_date() << " --> " << http_client.get_url() << std::endl;
			outf.close();
		}
		else
		{
			//Get the last Constants::log_lns lines of the file.
			std::string file_cont = tools::Tools::get_last_lns_file(Constants::file_log, tools::Tools::get_amnt_file_lns(Constants::file_log) - Constants::log_lns);
			std::ofstream outf(Constants::file_log);
			outf << file_cont;
			outf << m_username << " " << tools::Tools::get_date() << " --> " << http_client.get_url() << std::endl;
			outf.close();
		}

		//Server response check.
		rapidjson::Document doc;
		doc.Parse(server_resp.m_body.c_str());

		if(doc.IsObject())
		{
			/*
			 * {
			 * 		"message":"challenge_required",
			 * 		"challenge":
			 * 		{
			 * 			"url":"https://i.instagram.com/challenge/?next=/api/v1/launcher/sync/",
			 * 			"api_path":"/challenge/",
			 * 			"hide_webview_header":true,
			 * 			"lock":true,
			 * 			"logout":false,
			 * 			"native_flow":true
			 * 		},
			 * 		"status":"fail"
			 * }
			 */
			if(doc.HasMember("message"))
			{
				if(doc["message"].IsString())
				{
					if(doc["message"].GetString() == std::string("challenge_required"))
						std::cout << Messages::manual_challenge << std::endl;
				}
				else
					tools::Tools::write_err_log(Messages::field_not_contain_string("message"));
			}

			/*
			 * A response like the following is sent back for example if the wrong cookies are sent and you are logged out as a consequence.
			 * You will also get the response below if the session is revoked on "https://www.instagram.com/session/login_activity/".
			 *
			 * {
			 * 		"message":"login_required",
			 * 		"error_title":"You've Been Logged Out",
			 * 		"error_body":"Please log back in.",
			 * 		"logout_reason":2,
			 * 		"status":"fail"
			 * }
			 */
			if(doc.HasMember("message"))
			{
				if(doc["message"].IsString())
				{
					if(doc["message"].GetString() == std::string("login_required"))
					{
						m_del_app_info_and_cookies= true;
						std::cout << Messages::new_login_required_as_logged_out << std::endl;
					}
				}
				else
					tools::Tools::write_err_log(Messages::field_not_contain_string("message"));
			}
		}

		//Oops, an error occurred.
		if(boost::iequals(server_resp.m_body, "Oops, an error occurred."))
			std::cout << Messages::acc_soft_ban << std::endl;

		//Too many requests.
		if(server_resp.m_code == 429 && (!no_throw))
			throw std::runtime_error("Error. The Instagram servers refused the request as they are too many.");
	}

	std::string Api::accounts_contact_point_prefill()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("usage", "prefill"));

		tools::HttpClient http_client(Constants::ig_api_url + "accounts/contact_point_prefill/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::qe_sync()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("id", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("server_config_retrieval", 1));
		http_args.push_back(tools::HttpArg("experiments", Constants::qe_sync_experiments));

		tools::HttpClient http_client(Constants::ig_api_url + "qe/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::accounts_get_prefill_candidates()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("android_device_id", m_x_ig_android_id));
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("usages", "[\\\"account_recovery_omnibox\\\"]"));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("device_id", m_x_ig_device_id));

		tools::HttpClient http_client(Constants::ig_api_url + "accounts/get_prefill_candidates/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::launcher_sync()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("id", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));

		tools::HttpClient http_client(Constants::ig_api_url + "launcher/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	void Api::pre_login_requests()
	{
		accounts_contact_point_prefill();
		qe_sync();
		accounts_get_prefill_candidates();
		launcher_sync();
	}

	bool Api::login()
	{
		if(m_new_login == true)
		{
			pre_login_requests();

			//Actual login
			//HTTP headers
			std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

			//HTTP args
			std::vector<tools::HttpArg> http_args;
			http_args.push_back(tools::HttpArg("jazoest", get_jazoest()));
			http_args.push_back(tools::HttpArg("country_codes", "[{\\\"country_code\\\":\\\"1\\\",\\\"source\\\":[\\\"default\\\"]}]"));
			http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
			http_args.push_back(tools::HttpArg("username", m_username));
			http_args.push_back(tools::HttpArg("adid", m_x_google_ad_id));
			http_args.push_back(tools::HttpArg("guid", m_x_ig_device_id));
			http_args.push_back(tools::HttpArg("device_id", m_x_ig_android_id));
			http_args.push_back(tools::HttpArg("google_tokens", "[]"));
			http_args.push_back(tools::HttpArg("password", m_password));
			http_args.push_back(tools::HttpArg("login_attempt_count", "0"));

			tools::HttpClient http_client(Constants::ig_api_url + "accounts/login/", http_headers);
			tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

			update_data(http_res.m_cookies);
			post_req_check(http_client, http_res);

			if(http_res.m_code == 200)
			{
				post_login_requests();
				m_last_app_opening = tools::Tools::get_time();
				std::cout << Messages::successful_login(m_file_cookies) << std::endl;
				return true;
			}
			else
			{
				//checkpoint_challenge_required
				rapidjson::Document doc;
				doc.Parse(http_res.m_body.c_str());

				if(doc.IsObject())
					if(doc.HasMember("error_type"))
						if(doc["error_type"].IsString())
							if(doc["error_type"].GetString() == std::string("checkpoint_challenge_required"))
								if(solve_challenge(http_res.m_body))
								{
									post_login_requests();
									m_last_app_opening = tools::Tools::get_time();
									return true;
								}
								else
									std::cout << Messages::challenge_not_solved << std::endl;
							else
								tools::Tools::write_err_log(Messages::field_not_correct_value("error_type", "checkpoint_challenge_required"));
						else
							tools::Tools::write_err_log(Messages::field_not_contain_string("error_type"));
					else
						tools::Tools::write_err_log(Messages::field_not_found("error_type"));
				else
					tools::Tools::write_err_log(Messages::server_respone_not_json_obj);

				return false;
			}
		}
		else
		{
			if((m_last_app_opening + Constants::app_refresh_interval) < tools::Tools::get_time())
			{
				open_app();
				m_last_app_opening = tools::Tools::get_time();
			}

			return true;
		}
	}

	bool Api::solve_challenge(const std::string &server_resp)
	{
		/*
		 * The different HTTP clients:
		 * *1 Get the challenge content.
		 * *2 Send the choice concerning the verification method.
		 * *3 Send the verification code.
		 */
		rapidjson::Document doc;
		doc.Parse(server_resp.c_str());

		if(doc.IsObject())
		{
			if(doc.HasMember("error_type"))
			{
				if(doc["error_type"].IsString())
				{
					if(doc["error_type"].GetString() == std::string("checkpoint_challenge_required"))
					{
						if(doc.HasMember("challenge"))
						{
							const rapidjson::Value &challenge = doc["challenge"];

							if(challenge.HasMember("api_path"))
							{
								if(challenge["api_path"].IsString())
								{
									std::string challenge_path = tools::Tools::cut_off_first_char(challenge["api_path"].GetString());

									//HTTP headers
									std::vector<tools::HttpHeader> http_headers1 = get_ig_http_headers();

									tools::HttpClient http_client1(Constants::ig_api_url + challenge_path + "?guid=" + m_x_ig_device_id +
											"&device_id=" + m_x_ig_android_id, http_headers1);
									tools::HttpResponse http_res1 = http_client1.send_get_req();

									update_data(http_res1.m_cookies);
									post_req_check(http_client1, http_res1);

									rapidjson::Document doc;
									doc.Parse(http_res1.m_body.c_str());

									if(doc.IsObject())
									{
										if(doc.HasMember("step_name"))
										{
											if(doc["step_name"].IsString())
											{
												if(doc["step_name"].GetString() == std::string("select_verify_method"))
												{
													if(doc.HasMember("step_data"))
													{
														const rapidjson::Value &step_data = doc["step_data"];
														std::string choices;

														if(step_data.HasMember("phone_number"))
															choices.append("0 - " + Messages::phone_number);
														if(step_data.HasMember("email"))
															choices.append("\n1 - " + Messages::email);

														std::cout << Messages::hints_from_last_server_response << std::endl;
														std::cout << http_res1.m_body << std::endl;
														std::cout << Messages::verify_login << std::endl;
														std::cout << choices << std::endl;
														int choice = -1;

														if(step_data.HasMember("phone_number") && step_data.HasMember("email"))
														{
															while(!(choice == 0 || choice == 1))
															{
																std::cout << Messages::your_choice_inp;
																std::cin >> choice;

																if(!(choice == 0 || choice == 1))
																	std::cout << Messages::wrong_choice_try_again << std::endl;
															}
														}
														else if(step_data.HasMember("phone_number"))
														{
															while(choice != 0)
															{
																std::cout << Messages::your_choice_inp;
																std::cin >> choice;

																if(choice != 0)
																	std::cout << Messages::wrong_choice_try_again << std::endl;
															}
														}
														else if(step_data.HasMember("email"))
														{
															while(choice != 1)
															{
																std::cout << Messages::your_choice_inp;
																std::cin >> choice;

																if(choice != 1)
																	std::cout << Messages::wrong_choice_try_again << std::endl;
															}
														}

														//HTTP headers
														std::vector<tools::HttpHeader> http_headers2 = get_ig_http_headers();

														//HTTP args
														std::vector<tools::HttpArg> http_args2;
														http_args2.push_back(tools::HttpArg("choice", choice));
														http_args2.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
														http_args2.push_back(tools::HttpArg("guid", m_x_ig_device_id));
														http_args2.push_back(tools::HttpArg("device_id", m_x_ig_android_id));

														tools::HttpClient http_client2(Constants::ig_api_url + challenge_path, http_headers2);
														tools::HttpResponse http_res2 = http_client2.send_post_req_urlencoded(mk_ig_http_body(http_args2));

														update_data(http_res2.m_cookies);
														post_req_check(http_client2, http_res2);

														std::cout << Messages::ver_code_sent << std::endl;
														std::string security_code;
														std::cout << Messages::prompt_ver_code_inp;
														std::cin >> security_code;

														//HTTP headers
														std::vector<tools::HttpHeader> http_headers3 = get_ig_http_headers();

														//HTTP args
														std::vector<tools::HttpArg> http_args3;
														http_args3.push_back(tools::HttpArg("security_code", security_code));
														http_args2.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
														http_args2.push_back(tools::HttpArg("guid", m_x_ig_device_id));
														http_args2.push_back(tools::HttpArg("device_id", m_x_ig_android_id));

														tools::HttpClient http_client3(Constants::ig_api_url + challenge_path, http_headers3);
														tools::HttpResponse http_res3 = http_client3.send_post_req_urlencoded(mk_ig_http_body(http_args3));

														update_data(http_res3.m_cookies);
														post_req_check(http_client3, http_res3);

														if(http_res3.m_code == 200)
														{
															std::cout << Messages::successful_login(m_file_cookies) << std::endl;
															return true;
														}
													}
													else
														tools::Tools::write_err_log(Messages::field_not_found("step_data"));
												}
												//I do not know whether this code works as it was copied from instabot on GitHub.
												else if(doc["step_name"].GetString() == std::string("delta_login_review"))
												{
													std::string choices;

													choices.append(boost::str(boost::format("0 - %1%\n") % Messages::it_was_me));
													choices.append(boost::str(boost::format("1 - %1%\n") % Messages::it_was_not_me));

													std::cout << Messages::hints_from_last_server_response << std::endl;
													std::cout << http_res1.m_body << std::endl;
													std::cout << Messages::was_it_you << std::endl;
													std::cout << choices << std::endl;
													int choice = -1;

													while(!(choice == 0 || choice == 1))
													{
														std::cout << Messages::your_choice_inp;
														std::cin >> choice;

														if(!(choice == 0 || choice == 1))
															std::cout << Messages::wrong_choice_try_again << std::endl;
													}

													//HTTP headers
													std::vector<tools::HttpHeader> http_headers2 = get_ig_http_headers();
													http_headers2.push_back(tools::HttpHeader("Cookie", m_cookie_str));

													//HTTP args
													std::vector<tools::HttpArg> http_args2;
													http_args2.push_back(tools::HttpArg("choice", choice));

													tools::HttpClient http_client2(Constants::ig_api_url + challenge_path, http_headers2, http_args2);
													tools::HttpResponse http_res2 = http_client2.send_post_req_urlencoded(mk_ig_http_body(http_args2));

													update_data(http_res2.m_cookies);
													post_req_check(http_client2, http_res2);

													if(http_res2.m_code == 200)
													{
														std::cout << Messages::successful_login(m_file_cookies) << std::endl;
														return true;
													}
												}
												else
													tools::Tools::write_err_log(Messages::field_not_correct_value("step_name", "select_verify_method or delta_login_review"));
											}
											else
												tools::Tools::write_err_log(Messages::field_not_contain_string("step_name"));
										}
										else
											tools::Tools::write_err_log(Messages::field_not_found("step_name"));
									}
									else
										tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
								}
								else
									tools::Tools::write_err_log(Messages::field_not_contain_string("api_path"));
							}
							else
								tools::Tools::write_err_log(Messages::field_not_found("api_path"));
						}
						else
							tools::Tools::write_err_log(Messages::field_not_found("challenge"));
					}
					else
						tools::Tools::write_err_log(Messages::field_not_correct_value("error_type", "checkpoint_challenge_required"));
				}
				else
					tools::Tools::write_err_log(Messages::field_not_contain_string("error_type"));
			}
			else
				tools::Tools::write_err_log(Messages::field_not_found("error_type"));
		}
		else
			tools::Tools::write_err_log(Messages::server_respone_not_json_obj);

		return false;
	}

	std::string Api::multiple_accounts_get_account_family()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "multiple_accounts/get_account_family/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::banyan_banyan()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "banyan/banyan/?views=[\"story_share_sheet\",\"threads_people_picker\"," +
				"\"group_stories_share_sheet\",\"reshare_share_sheet\"]", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::feed_reels_tray()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("supported_capabilities_new", Constants::supported_capabilities_new));
		http_args.push_back(tools::HttpArg("reason", "cold_start"));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));

		tools::HttpClient http_client(Constants::ig_api_url + "feed/reels_tray/", http_headers, http_args);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::feed_timeline()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		srand(tools::Tools::get_seed());
		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("feed_view_info", get_feed_view_info()));
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("reason", "cold_start_fetch"));
		http_args.push_back(tools::HttpArg("battery_level", (std::rand() % 101) + 8));
//		http_args.push_back(tools::HttpArg("last_unseed_ad_id", 0)); Not possible to get.
		http_args.push_back(tools::HttpArg("timezone_offset", tools::Tools::get_tm()->tm_gmtoff));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("device_id", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("request_id", boost::uuids::to_string(boost::uuids::random_generator()())));
		http_args.push_back(tools::HttpArg("is_pull_to_refresh", 0));
		http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("is_charging", std::rand() % 2 == 0 ? 1 : 0));
		http_args.push_back(tools::HttpArg("will_sound_on", 0));
		http_args.push_back(tools::HttpArg("session_id", boost::uuids::to_string(boost::uuids::random_generator()())));
		http_args.push_back(tools::HttpArg("bloks_versioning_id", Constants::bloks_version_id));

		tools::HttpClient http_client(Constants::ig_api_url + "feed/timeline/", http_headers, http_args);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);
		set_last_seen_feed_media_id(http_res.m_body);

		return http_res.m_body;
	}

//	std::string Api::push_register()
//	{
//		//HTTP headers
//		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
//
//		//HTTP args
//		std::vector<tools::HttpArg> http_args;
//		http_args.push_back(tools::HttpArg("device_type", "android_mqtt"));
//		http_args.push_back(tools::HttpArg("is_main_push_channel", "true"));
//		http_args.push_back(tools::HttpArg("device_sub_type", 2));
//		http_args.push_back(tools::HttpArg("device_token", "")) ;//Needs to be got via sent MQTT requests.
//		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
//		http_args.push_back(tools::HttpArg("guid", m_x_ig_device_id));
//		http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));
//		http_args.push_back(tools::HttpArg("users", get_cookie_val("ds_user_id")));
//		http_args.push_back(tools::HttpArg("family_device_id", m_phone_id));
//
//		tools::HttpClient http_client(Constants::ig_api_url + "launcher/sync/", http_headers);
//		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));
//
//		update_data(http_res.m_cookies);
//		post_req_check(http_client, http_res);
//
//		return http_res.m_body;
//	}

	std::string Api::media_blocked()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "media/blocked/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::loom_fetch_config()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "loom/fetch_config/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::scores_bootstrap_users()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "scores/bootstrap/users/?surfaces=[\"autocomplete_user_list\",\"coefficient_besties_list_ranking\","
				"\"coefficient_rank_recipient_user_suggestion\",\"coefficient_ios_section_test_bootstrap_ranking\",\"coefficient_direct_recipients_ranking_"
				"variant_2\"]", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::business_eligibility_get_monetization_products_eligibility_data()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "business/eligibility/get_monetization_products_eligibility_data/?product_types=branded_content",
				http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::linked_accounts_get_linkage_status()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "linked_accounts/get_linkage_status/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::business_branded_content_should_require_professional_account()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "business/branded_content/should_require_professional_account/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::news_inbox()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "news/inbox/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::qp_get_cooldowns()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;

		tools::HttpClient http_client(Constants::ig_api_url + "qp/get_cooldowns/?" + mk_ig_http_body(http_args), http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::accounts_process_contact_point_signals()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
		http_args.push_back(tools::HttpArg("device_id", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("google_tokens", "[]"));

		tools::HttpClient http_client(Constants::ig_api_url + "accounts/process_contact_point_signals/",
				http_headers, false); //This endpoint causes 429 responses regularly in the app.
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res, true); //This endpoint causes 429 responses regularly in the app.

		return http_res.m_body;
	}

	std::string Api::users_x_info()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "users/" + get_cookie_val("ds_user_id") + "/info/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::direct_v2_get_presence()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "direct_v2/get_presence/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::status_get_viewable_statuses()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "status/get_viewable_statuses/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::direct_v2_inbox()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "direct_v2/inbox/?visual_message_return_type=unseen&persistentBadging=true&limit=0", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::qp_batch_fetch()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("surfaces_to_triggers", "{\\\"4715\\\":[\\\"instagram_feed_header\\\"],\\\"5858\\\":[\\\"instagram_feed_tool_tip\\\"],"
				"\\\"5734\\\":[\\\"instagram_feed_prompt\\\"]}"));
		http_args.push_back(tools::HttpArg("surfaces_to_queries", Constants::surfaces_to_queries));
		http_args.push_back(tools::HttpArg("vc_policy", "default"));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
		http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("scale", "4"));
		http_args.push_back(tools::HttpArg("version", "1"));

		tools::HttpClient http_client(Constants::ig_api_url + "qp/batch_fetch/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::notifications_badge()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("user_ids", get_cookie_val("ds_user_id")));
		http_args.push_back(tools::HttpArg("device_id", m_x_ig_device_id));
		http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));

		tools::HttpClient http_client(Constants::ig_api_url + "notifications/badge/", http_headers, http_args);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::discover_topical_explore()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		tools::HttpClient http_client(Constants::ig_api_url + "discover/topical_explore/?is_prefetch=true&omit_cover_media=true&use_sectional_payload=true"
				"&timezone_offset=" + std::to_string(tools::Tools::get_tm()->tm_gmtoff) + "&session_id=" +
				boost::uuids::to_string(boost::uuids::random_generator()()) + "&include_fixed_destinations=true", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	void Api::post_login_requests()
	{
		multiple_accounts_get_account_family();
		banyan_banyan();
		feed_reels_tray();
		feed_timeline();
//		push_register();
		media_blocked();
		loom_fetch_config();
		scores_bootstrap_users();
		business_eligibility_get_monetization_products_eligibility_data();
		linked_accounts_get_linkage_status();
		business_branded_content_should_require_professional_account();
		news_inbox();
		qp_get_cooldowns();
		accounts_process_contact_point_signals();
		users_x_info();
		direct_v2_get_presence();
		status_get_viewable_statuses();
		direct_v2_inbox();
		qp_batch_fetch();
		notifications_badge();
		discover_topical_explore();
	}

	void Api::open_app()
	{
		feed_timeline();
		feed_reels_tray();
		banyan_banyan();
		loom_fetch_config();
		multiple_accounts_get_account_family();
		business_eligibility_get_monetization_products_eligibility_data();
		business_branded_content_should_require_professional_account();
		news_inbox();
		accounts_process_contact_point_signals();
		users_x_info();
		direct_v2_get_presence();
		direct_v2_inbox();
		status_get_viewable_statuses();
		scores_bootstrap_users();
		discover_topical_explore();
		notifications_badge();
	}

	std::string Api::get_media_likers(const std::string &media_id)
	{
		//I need some default values to be able to instantiate the object.
		tools::HttpResponse resp(0, std::vector<tools::HttpHeader>(), "", std::vector<tools::HttpCookie>());

		//The first part.
		{
			//HTTP headers
			std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

			tools::HttpClient http_client(Constants::ig_api_url + "media/" + media_id + "/likers/", http_headers);
			tools::HttpResponse http_res = http_client.send_get_req();

			update_data(http_res.m_cookies);
			post_req_check(http_client, http_res);

			resp = http_res;
		}

		//The second part.
		{
			//HTTP headers
			std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

			//HTTP args
			std::vector<tools::HttpArg> http_args;
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));

			//Get the value for user_ids.
			rapidjson::Document doc;
			doc.Parse(resp.m_body.c_str());
			std::string user_ids;

			if(doc.IsArray())
			{
				for(std::size_t j = 0; j < doc.GetArray().Size(); ++j)
				{
					if(doc[j].HasMember("pk"))
						if(doc[j]["pk"].IsInt64())
						{
							long long user_id = doc[j]["pk"].GetInt64();
							user_ids.append(std::to_string(user_id));

							//If not the last iteration.
							if(j != (doc.GetArray().Size() - 1))
								user_ids.append(",");
						}
						else
							tools::Tools::write_err_log(Messages::field_not_contain_int64("pk"));
					else
						tools::Tools::write_err_log(Messages::field_not_found("pk"));
				}
			}
			else
				tools::Tools::write_err_log(Messages::server_respone_not_json_arr);

			http_args.push_back(tools::HttpArg("user_ids", user_ids));
			http_args.push_back(tools::HttpArg("_uuid", m_x_ig_device_id));

			tools::HttpClient http_client(Constants::ig_api_url + "notifications/badge/", http_headers, http_args);
			tools::HttpResponse http_res = http_client.send_post_req_urlencoded();

			update_data(http_res.m_cookies);
			post_req_check(http_client, http_res);
		}

		return resp.m_body;
	}

	std::string Api::get_media_comments(const std::string &media_id, const std::string &max_id)
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		std::string url = Constants::ig_api_url + "media/" + media_id + "/comments/";

		if(!max_id.empty())
			url.append("?max_id=" + max_id);

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_media_comments_all(const std::string &media_id)
	{
		std::string response = get_media_comments(media_id);
		std::string result = "[";

		while(true)
		{
			rapidjson::Document doc;
			doc.Parse(response.c_str());

			if(doc.IsObject())
			{
				//Scrape the comments.
				if(doc.HasMember("comments"))
				{
					const rapidjson::Value &comments = doc["comments"];

					if(comments.IsArray())
					{
						for(std::size_t j = 0; j < comments.GetArray().Size(); ++j)
						{
							result.append(tools::Tools::get_json_as_string(comments[j]));
							result.append(", ");
						}
					}
					else
						tools::Tools::write_err_log(Messages::field_not_contain_json_array("comments"));

					//Perhaps, next page.
					if(doc.HasMember("has_more_comments") && doc.HasMember("next_max_id"))
						if(doc["next_max_id"].IsString())
							response = get_media_comments(media_id, doc["next_max_id"].GetString());
						else
						{
							tools::Tools::write_err_log(Messages::field_not_contain_string("next_max_id"));
							break;
						}
					else
						break;
				}
				else
				{
					tools::Tools::write_err_log(Messages::field_not_found("comments"));
					break;
				}
			}
			else
			{
				tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
				break;
			}
		}

		if(result.size() >= 2)
		{
			result.pop_back();
			result.pop_back();
		}

		return result.append("]");
	}

	std::string Api::get_media_info(const std::string &media_id)
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		std::string url = Constants::ig_api_url + "media/" + media_id + "/info/";

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_user_feed(const std::string &user_id, const std::string &max_id, const std::string &min_timestamp)
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		std::string url = Constants::ig_api_url + "feed/user/" + user_id + "/?max_id=" + max_id + "&min_timestamp=" + min_timestamp +
	            "&rank_token=" + get_rank_token() + "&ranked_content=true";

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_user_info(const std::string &user_id)
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		std::string url = Constants::ig_api_url + "users/" + user_id + "/info/";

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_media_id(const std::string &ig_post) noexcept
	{
		if(Api::is_ig_post(ig_post))
		{
			tools::HttpClient http_client("https://api.instagram.com/oembed/?callback=&url=" + ig_post);
			tools::HttpResponse http_res = http_client.send_get_req();

			rapidjson::Document doc;
			doc.Parse(http_res.m_body.c_str());

			if(doc.IsObject())
			{
				if(doc.HasMember("media_id"))
				{
					if(doc["media_id"].IsString())
						return doc["media_id"].GetString();
					else
					{
					    tools::Tools::write_err_log(Messages::field_not_contain_string("media_id"));
					    return "";
					}
				}
				else
				{
					tools::Tools::write_err_log(Messages::field_not_found("media_id"));
					return "";
				}
			}
			else
			{
				tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
				return "";
			}
		}
		else
		{
			tools::Tools::write_err_log(Messages::not_ig_post);
			return "";
		}
	}

	bool Api::is_ig_post(const std::string &url) noexcept
	{
		if(url.find("https://www.instagram.com/p/") != std::string::npos)
		{
			tools::HttpClient http_client(url, false);
			tools::HttpResponse http_response = http_client.send_get_req();

			if(http_response.m_code == 200)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	bool Api::media_comments_allowed(const std::string &media_id)
	{
		//The variable is true by default so that if the key is not found in the json the bool value is correct.
		bool comments_allowed = true;

		//Comments disabled
		{
			std::string json = get_media_comments(media_id);

			rapidjson::Document doc;
			doc.Parse(json.c_str());

			if(doc.IsObject())
			{
				if(doc.HasMember("comments_disabled"))
				{
					if(doc["comments_disabled"].IsBool())
						//The negation is need due to the value: {"comments_disabled": true, "status": "ok"}.
						comments_allowed = !(doc["comments_disabled"].GetBool());
					else
						tools::Tools::write_err_log(Messages::field_not_contain_bool("comments_disabled"));
				}
			}
			else
				tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
		}

		//Comments restricted
		{
			std::string json = get_media_info(media_id);

			rapidjson::Document doc;
			doc.Parse(json.c_str());

			if(doc.IsObject())
			{
				if(doc.HasMember("items"))
				{
					const rapidjson::Value &items = doc["items"];

					if(items.IsArray())
					{
						if(items.GetArray().Size() > 0)
						{
							const rapidjson::Value &media_info = items[0];

							if(media_info.HasMember("commenting_disabled_for_viewer"))
							{
								if(media_info["commenting_disabled_for_viewer"].IsBool())
									//The negation is need due to the value: "commenting_disabled_for_viewer":true.
									comments_allowed = !(media_info["commenting_disabled_for_viewer"].GetBool());
								else
									tools::Tools::write_err_log(Messages::field_not_contain_bool("commenting_disabled_for_viewer"));
							}
						}
						else
							tools::Tools::write_err_log(Messages::json_array_has_size_0("items"));
					}
					else
						tools::Tools::write_err_log(Messages::field_not_contain_json_array("items"));
				}
				else
					tools::Tools::write_err_log(Messages::field_not_found("items"));
			}
			else
				tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
		}

		return comments_allowed;
	}

	std::string Api::get_username_from_user_id(const std::string &user_id)
	{
		std::string json = get_user_info(user_id);

		rapidjson::Document doc;
		doc.Parse(json.c_str());

		if(doc.IsObject())
		{
			if(doc.HasMember("user"))
			{
				const rapidjson::Value &user = doc["user"];

				if(user.HasMember("username"))
					if(user["username"].IsString())
						return user["username"].GetString();
					else
					{
						tools::Tools::write_err_log(Messages::field_not_contain_string("username"));
					    return "";
					}
				else
				{
					tools::Tools::write_err_log(Messages::field_not_found("username"));
					return "";
				}
			}
			else
			{
				tools::Tools::write_err_log(Messages::field_not_found("user"));
				return "";
			}
		}
		else
		{
			tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
			return "";
		}
	}

	std::string Api::get_username_from_media_id(const std::string &media_id)
	{
		std::string json = get_media_info(media_id);

		rapidjson::Document doc;
		doc.Parse(json.c_str());

		if(doc.IsObject())
		{
			if(doc.HasMember("items"))
			{
				const rapidjson::Value &items = doc["items"];

				if(items.IsArray())
				{
					if(items.GetArray().Size() > 0)
					{
						const rapidjson::Value &media_info = items[0];

						if(media_info.HasMember("user"))
						{
							const rapidjson::Value &user = media_info["user"];

							if(user.HasMember("username"))
								if(user["username"].IsString())
									return user["username"].GetString();
								else
								{
									tools::Tools::write_err_log(Messages::field_not_contain_string("username"));
									return "";
								}
							else
							{
								tools::Tools::write_err_log(Messages::field_not_found("username"));
								return "";
							}
						}
						else
						{
							tools::Tools::write_err_log(Messages::field_not_found("user"));
							return "";
						}
					}
					else
					{
						tools::Tools::write_err_log(Messages::json_array_has_size_0("items"));
						return "";
					}
				}
				else
				{
					tools::Tools::write_err_log(Messages::field_not_contain_json_array("error_type"));
					return "";
				}
			}
			else
			{
				tools::Tools::write_err_log(Messages::field_not_found("items"));
				return "";
			}
		}
		else
		{
			tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
			return "";
		}
	}

	int Api::get_amnt_flwrs(const std::string &user_id)
	{
		std::string json = get_user_info(user_id);

		rapidjson::Document doc;
		doc.Parse(json.c_str());

		if(doc.IsObject())
		{
			if(doc.HasMember("user"))
			{
				const rapidjson::Value &user = doc["user"];

				if(user.HasMember("follower_count"))
				{
					if(user["follower_count"].IsInt())
						return user["follower_count"].GetInt();
					else
						tools::Tools::write_err_log(Messages::field_not_contain_int("follower_count"));
				}
				else
					tools::Tools::write_err_log(Messages::field_not_found("follower_count"));
			}
			else
				tools::Tools::write_err_log(Messages::field_not_found("user"));
		}
		else
			tools::Tools::write_err_log(Messages::server_respone_not_json_obj);

		return -1;
	}

	std::string Api::get_user_id_from_media_id(const std::string &media_id)
	{
		std::string json = get_media_info(media_id);

		rapidjson::Document doc;
		doc.Parse(json.c_str());

		if(doc.IsObject())
		{
			if(doc.HasMember("items"))
			{
				const rapidjson::Value &items = doc["items"];

				if(items.IsArray())
				{
					if(items.GetArray().Size() > 0)
					{
						const rapidjson::Value &media_info = items[0];

						if(media_info.HasMember("user"))
						{
							const rapidjson::Value &user = media_info["user"];

							if(user.HasMember("pk"))
								if(user["pk"].IsInt())
									return std::to_string(user["pk"].GetInt());
								else
								{
									tools::Tools::write_err_log(Messages::field_not_contain_int("pk"));
								    return "";
								}
							else
							{
								tools::Tools::write_err_log(Messages::field_not_found("pk"));
								return "";
							}
						}
						else
						{
							tools::Tools::write_err_log(Messages::field_not_found("user"));
							return "";
						}
					}
					else
					{
						tools::Tools::write_err_log(Messages::json_array_has_size_0("items"));
						return "";
					}
				}
				else
				{
					tools::Tools::write_err_log(Messages::field_not_contain_json_array("items"));
					return "";
				}
			}
			else
			{
				tools::Tools::write_err_log(Messages::field_not_found("items"));
				return "";
			}
		}
		else
		{
			tools::Tools::write_err_log(Messages::server_respone_not_json_obj);
			return "";
		}
	}

	std::string Api::logout()
	{
		//HTTP headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();

		//HTTP args
		std::vector<tools::HttpArg> http_args;

		tools::HttpClient http_client(Constants::ig_api_url + "accounts/logout/", http_headers, http_args);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		m_del_app_info_and_cookies = true;

		return http_res.m_body;
	}
}
