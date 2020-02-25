#include "ig/Api.h"
#include "tools/http/HttpClient.h"
#include "tools/http/InputFile.h"
#include <iostream>
#include "tools/Tools.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "tools/http/HttpHeader.h"
#include <boost/uuid/detail/md5.hpp>
#include <iomanip>
#include <Poco/URI.h>
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

namespace ig
{
	Api::Api(const std::string &username, const std::string &password, const std::string &files_path) : m_username(username), m_password(password),
			m_file_app_info(files_path + username + "_app_info.dat"), m_file_cookies(files_path + username + "_cookies.dat"), m_del_cookies_uuids(false)
	{
		//create necessary folders
		if(!tools::Tools::file_exists(Constants::folder))
		{
			try
			{
				boost::filesystem::create_directories(Constants::folder);
			}
			catch(const std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		if(!tools::Tools::file_exists(files_path))
		{
			try
			{
				boost::filesystem::create_directories(files_path);
			}
			catch(const std::exception &e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

		//also determines whether a new login is required
		setup_cookies_app_info();

		//login
		if(login())
		{
			save_app_info_in_file();
			save_cookies_in_file();
		}
	}

	Api::~Api()
	{
		if(m_del_cookies_uuids)
		{
			if(remove(m_file_app_info.c_str()) != 0)
				std::cerr << "Error: " << m_file_app_info << " - " << strerror(errno) << std::endl;

			if(remove(m_file_cookies.c_str()) != 0)
				std::cerr << "Error: " << m_file_cookies << " - " << strerror(errno) << std::endl;
		}
	}

	std::vector<tools::HttpHeader> Api::get_ig_http_headers() const noexcept
	{
		//get time
		time_t raw_time;
		time(&raw_time);

		//seed for rand
		srand(raw_time);

		std::vector<tools::HttpHeader> http_headers = std::vector<tools::HttpHeader>();
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
		http_headers.push_back(tools::HttpHeader("User-Agent", m_useragent));
		http_headers.push_back(tools::HttpHeader("X-IG-Connection-Speed", "-1kbps"));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-Speed-KBPS", std::to_string((rand() % 3001) + 7000)));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalBytes-B", std::to_string((rand() % 400001) + 500000)));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalTime-MS", std::to_string((rand() % 101) + 50)));

		return http_headers;
	}

	std::string Api::mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const noexcept
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

	void Api::setup_cookies_app_info() noexcept
	{
		if(tools::Tools::file_exists(m_file_app_info))
		{
			//phone id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_app_info, "phone id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_phone_id = args.at(args.size() - 1);
					else
						std::cerr << Messages::field_no_value_in_file("phone id", m_file_app_info) << std::endl;
				}
				else
					std::cerr << Messages::field_not_found_in_file("phone id", m_file_app_info) << std::endl;
			}

			//uuid
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_app_info, "uuid"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_uuid = args.at(args.size() - 1);
					else
						std::cerr << Messages::field_no_value_in_file("uuid", m_file_app_info) << std::endl;
				}
				else
					std::cerr << Messages::field_not_found_in_file("uuid", m_file_app_info) << std::endl;
			}

			//client session id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_app_info, "client session id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_client_session_id = args.at(args.size() - 1);
					else
						std::cerr << Messages::field_no_value_in_file("client session id", m_file_app_info) << std::endl;
				}
				else
					std::cerr << Messages::field_not_found_in_file("client session id", m_file_app_info) << std::endl;
			}

			//advertising id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_app_info, "advertising id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_advertising_id = args.at(args.size() - 1);
					else
						std::cerr << Messages::field_no_value_in_file("advertising id", m_file_app_info) << std::endl;
				}
				else
					std::cerr << Messages::field_not_found_in_file("advertising id", m_file_app_info) << std::endl;
			}

			//device id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_app_info, "device id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_device_id = args.at(args.size() - 1);
					else
						std::cerr << Messages::field_no_value_in_file("device id", m_file_app_info) << std::endl;
				}
				else
					std::cerr << Messages::field_not_found_in_file("device id", m_file_app_info) << std::endl;
			}

			//last login
			{
				std::string entry = tools::Tools::get_file_ln_w_srch(m_file_app_info, "last login");
				if(!entry.empty())
						m_last_login = tools::Tools::get_num_ln_end(entry);
				else
					std::cerr << Messages::field_not_found_in_file("last login", m_file_app_info) << std::endl;
			}

			//last experiments
			{
				std::string entry = tools::Tools::get_file_ln_w_srch(m_file_app_info, "last experiments");
				if(!entry.empty())
						m_last_experiments = tools::Tools::get_num_ln_end(entry);
				else
					std::cerr << Messages::field_not_found_in_file("last experiments", m_file_app_info) << std::endl;
			}

			//useragent
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_app_info, "useragent"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						for(size_t j = 1; j < args.size(); ++j)
						{
							m_useragent.append(args.at(j));

							//insert whitespace correctly
							if(j < (args.size() - 1))
								m_useragent.append(" ");
						}
					else
						std::cerr << Messages::field_no_value_in_file("useragent", m_file_app_info) << std::endl;
				}
				else
					std::cerr << Messages::field_not_found_in_file("useragent", m_file_app_info) << std::endl;
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

		//just for orientation about the cookies
		if(get_cookie_val("ds_user").empty())
			std::cerr << Messages::cookie_missing("ds_user") << std::endl;

		if(get_cookie_val("csrftoken").empty())
			std::cerr << Messages::cookie_missing("csrftoken") << std::endl;

		//it seems that this cookie is not necessary
//		if(get_cookie_val("shbid").empty())
//			std::cerr << Messages::cookie_missing("shbid") << std::endl;

		//it seems that this cookie is not necessary
//		if(get_cookie_val("shbts").empty())
//			std::cerr << Messages::cookie_missing("shbts") << std::endl;

		if(get_cookie_val("rur").empty())
			std::cerr << Messages::cookie_missing("rur") << std::endl;

		if(get_cookie_val("ds_user_id").empty())
			std::cerr << Messages::cookie_missing("ds_user_id") << std::endl;

		if(get_cookie_val("urlgen").empty())
			std::cerr << Messages::cookie_missing("urlgen") << std::endl;

		if(get_cookie_val("sessionid").empty())
			std::cerr << Messages::cookie_missing("sessionid") << std::endl;

		if(get_cookie_val("mid").empty())
			std::cerr << Messages::cookie_missing("mid") << std::endl;

		/*
		 * if some app info is missing
		 * if a cookie is missing (I already know the names of those which are needed)
		 */
		if(m_phone_id.empty() || m_uuid.empty() || m_client_session_id.empty() || m_advertising_id.empty() || m_device_id.empty() || m_last_login == 0 ||
				m_last_experiments == 0 || m_useragent.empty() || get_cookie_val("ds_user").empty() || get_cookie_val("csrftoken").empty() || get_cookie_val("rur").empty() ||
				get_cookie_val("ds_user_id").empty() || get_cookie_val("urlgen").empty() || get_cookie_val("sessionid").empty() || get_cookie_val("mid").empty())
		{
			m_new_login = true;

			//get a random device
			std::vector<Device::ptr> devices;
			devices.push_back(std::make_shared<HuaweiMate9Pro>());
			devices.push_back(std::make_shared<LgG5>());
			devices.push_back(std::make_shared<OnePlus3T>());
			devices.push_back(std::make_shared<OnePlus7>());
			devices.push_back(std::make_shared<SamsungGalaxyS7>());
			devices.push_back(std::make_shared<SamsungGalaxyS7Edge>());
			devices.push_back(std::make_shared<SamsungGalaxyS9Plus>());
			devices.push_back(std::make_shared<ZteAxon7>());

				//get time
			time_t raw_time;
			time(&raw_time);

			srand(raw_time);
			int random_index = rand() % devices.size();
			m_device = devices.at(random_index);

			//generate new uuids
			m_phone_id = boost::uuids::to_string(boost::uuids::random_generator()());
			m_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			m_client_session_id = boost::uuids::to_string(boost::uuids::random_generator()());
			m_advertising_id = boost::uuids::to_string(boost::uuids::random_generator()());
				//device id has to be uuid with length 16 and hex in format android-...
			std::string device_id_temp = boost::uuids::to_string(boost::uuids::random_generator()());
			device_id_temp.erase(std::remove(device_id_temp.begin(), device_id_temp.end(), '-'), device_id_temp.end());
			device_id_temp.resize(16);
			m_device_id = "android-" + device_id_temp;
			m_useragent = m_device->get_useragent();

			std::cout << Messages::no_cookies_found << std::endl;
		}
		else
		{
			m_new_login = false;
			set_cookie_str();
		}
	}

	void Api::update_data(const std::vector<tools::HttpCookie> &http_cookies) noexcept
	{
		for(size_t j = 0; j < http_cookies.size(); ++j)
		{
			//add a new cookie
			bool found = false;
			size_t pos_old_cookie_to_updt;
			for(size_t k = 0; k < m_cookies.size(); ++k)
			{
				if(http_cookies.at(j).get_name() == m_cookies.at(k).get_name())
				{
					found = true;
					pos_old_cookie_to_updt = k;
					break;
				}
			}

			if(found == false)
				m_cookies.push_back(http_cookies.at(j));
			//update all old cookies
			else
			{
				m_cookies.erase(m_cookies.begin() + pos_old_cookie_to_updt);
				m_cookies.push_back(http_cookies.at(j));
			}
		}

		save_app_info_in_file();
		save_cookies_in_file();
		set_cookie_str();
	}

	void Api::save_app_info_in_file() const noexcept
	{
		std::ofstream outf(m_file_app_info);
		outf << "phone id: " << m_phone_id << std::endl;
		outf << "uuid: " << m_uuid << std::endl;
		outf << "client session id: " << m_client_session_id << std::endl;
		outf << "advertising id: " << m_advertising_id << std::endl;
		outf << "device id: " << m_device_id << std::endl;
		outf << "last login: " << m_last_login << std::endl;
		outf << "last experiments: " << m_last_experiments << std::endl;
		outf << "useragent: " << m_useragent << std::endl;
		outf.close();
	}

	void Api::save_cookies_in_file() const noexcept
	{
		std::ofstream outf(m_file_cookies);

		for(size_t j = 0; j < m_cookies.size(); ++j)
			outf << m_cookies.at(j).to_string() << std::endl;

		outf.close();
	}

	void Api::set_cookie_str() noexcept
	{
		std::string temp;

		for(size_t j = 0; j < m_cookies.size(); ++j)
		{
			temp.append(m_cookies.at(j).get_name() + "=" + m_cookies.at(j).get_value());

			//semicolon needed?
			if(j < (m_cookies.size() - 1))
				temp.append("; ");
		}

		m_cookie_str = temp;
	}

	std::string Api::get_cookie_val(const std::string &cookie_name) const noexcept
	{
		std::string cookie_val;

		for(size_t j = 0; j < m_cookies.size(); ++j)
			if(m_cookies.at(j).get_name() == cookie_name)
			{
				cookie_val = m_cookies.at(j).get_value();
				break;
			}

		return cookie_val;
	}

	std::string Api::read_msisdn_header(const std::string &usage)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("X-DEVICE-ID", m_uuid));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("device_id", m_uuid));
		http_args.push_back(tools::HttpArg("mobile_subno_usage", usage));

		tools::HttpClient http_client(Constants::ig_url + "accounts/read_msisdn_header/", get_ig_http_headers());
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::launcher_sync(const bool &login)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));
		http_args.push_back(tools::HttpArg("experiments", Constants::launcher_configs));
		if(login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		}

		tools::HttpClient http_client(Constants::ig_url + "launcher/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::sync_device_features(const bool &login)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("X-DEVICE-ID", m_uuid));
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));
		http_args.push_back(tools::HttpArg("experiments", Constants::login_experiments));
		if(login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		}

		tools::HttpClient http_client(Constants::ig_url + "qe/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::log_attribution()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("adid", m_advertising_id));

		tools::HttpClient http_client(Constants::ig_url + "attribution/log_attribution/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::contact_point_prefill(const std::string &usage)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("usage", usage));

		tools::HttpClient http_client(Constants::ig_url + "accounts/contact_point_prefill/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	void Api::pre_login_requests()
	{
		read_msisdn_header("default");
		launcher_sync(true);
		sync_device_features(true);
		log_attribution();
		contact_point_prefill("prefill");
	}

	std::string Api::sync_launcher(const bool &login)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", 1));
		http_args.push_back(tools::HttpArg("experiments", Constants::launcher_configs));
		if(login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		}

		tools::HttpClient http_client(Constants::ig_url + "launcher/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::sync_user_features()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("X-DEVICE-ID", m_uuid));
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("_uuid", m_uuid));
		http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("experiments", Constants::experiments));

		tools::HttpClient http_client(Constants::ig_url + "qe/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		//get time
		time_t raw_time;
		time(&raw_time);

		m_last_experiments = raw_time;

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_timeline_feed(const bool &is_pull_to_refresh, const bool &push_disabled, const bool &recovered_from_crash)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("X-Ads-Opt-Out", "0"));
		http_headers.push_back(tools::HttpHeader("X-DEVICE-ID", m_uuid));
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//get time
		time_t raw_time;
		time(&raw_time);
		struct tm *time_info;
		time_info = localtime(&raw_time);

		//for strftime()
		char buf[6];
		strftime(buf, sizeof(buf), "%z", time_info);

		//seed for rand
		srand(raw_time);

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("_uuid", m_uuid));
		http_args.push_back(tools::HttpArg("is_prefetch", 0));
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("device_id", m_uuid));
		http_args.push_back(tools::HttpArg("client_session_id", m_client_session_id));
		http_args.push_back(tools::HttpArg("battery_level", std::to_string((rand() % 23) + 70)));
		http_args.push_back(tools::HttpArg("is_charging", rand() % 2 ? "1" : "0"));
		http_args.push_back(tools::HttpArg("will_sound_on", rand() % 2 ? "1" : "0"));
		http_args.push_back(tools::HttpArg("is_on_screen", "1"));
		http_args.push_back(tools::HttpArg("timezone_offset", buf));
		if(is_pull_to_refresh)
		{
			http_args.push_back(tools::HttpArg("reason", "pull_to_refresh"));
			http_args.push_back(tools::HttpArg("is_pull_to_refresh", "1"));
		}
		else
		{
			http_args.push_back(tools::HttpArg("reason", "cold_start_fetch"));
			http_args.push_back(tools::HttpArg("is_pull_to_refresh", "0"));
		}
		if(push_disabled)
			http_args.push_back(tools::HttpArg("push_disabled", true));
		if(recovered_from_crash)
			http_args.push_back(tools::HttpArg("recovered_from_crash", "1"));

		tools::HttpClient http_client(Constants::ig_url + "feed/timeline/", http_headers, http_args);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(); //todo just normal http body, it seems to be correct

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_reels_tray_feed(const std::string &reason)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("supported_capabilities_new", Constants::supported_capabilities));
		http_args.push_back(tools::HttpArg("reason", reason));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("_uuid", m_uuid));

		tools::HttpClient http_client(Constants::ig_url + "feed/reels_tray/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_suggested_searches(const std::string &type)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("type", type));

		tools::HttpClient http_client(Constants::ig_url + "fbsearch/suggested_searches/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_ranked_recipients(const std::string &mode, const bool &show_threads, const std::string &query)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("mode", mode));
		http_args.push_back(tools::HttpArg("show_threads", show_threads ? "true" : "false"));
		http_args.push_back(tools::HttpArg("use_unified_inbox", "true"));
		if(!query.empty())
			http_args.push_back(tools::HttpArg("query", query));

		tools::HttpClient http_client(Constants::ig_url + "direct_v2/ranked_recipients/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_inbox_v2()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("persistentBadging", true));
		http_args.push_back(tools::HttpArg("use_unified_inbox", true));

		tools::HttpClient http_client(Constants::ig_url + "direct_v2/inbox/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_presence()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		tools::HttpClient http_client(Constants::ig_url + "direct_v2/get_presence/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_recent_activity()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		tools::HttpClient http_client(Constants::ig_url + "news/inbox/?limited_activity=true&show_su=true", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_loom_fetch_config()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		tools::HttpClient http_client(Constants::ig_url + "loom/fetch_config/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_profile_notice()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		tools::HttpClient http_client(Constants::ig_url + "users/profile_notice/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	/*
	 * todo this request returns
	 * 400
	 * {"message": "INVALID_REQUEST", "status": "fail"}
	 */
	std::string Api::batch_fetch()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("_uuid", m_uuid));
		http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("scale", 3));
		http_args.push_back(tools::HttpArg("version", 1));
		http_args.push_back(tools::HttpArg("vc_policy", "default"));
		http_args.push_back(tools::HttpArg("surfaces_to_triggers", "{\"5734\": [\"instagram_feed_prompt\"], \"4715\": [\"instagram_feed_header\"], "
				"\"5858\": [\"instagram_feed_tool_tip\"]}"));
		http_args.push_back(tools::HttpArg("surfaces_to_queries", Constants::batch_fetch_surfaces_to_queries));

		tools::HttpClient http_client(Constants::ig_url + "qp/batch_fetch/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::explore(const bool &is_prefetch)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//get time
		time_t raw_time;
		time(&raw_time);
		struct tm *time_info;
		time_info = localtime(&raw_time);

		//for strftime()
		char buf[6];
		strftime(buf, sizeof(buf), "%z", time_info);

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("is_prefetch", is_prefetch));
		http_args.push_back(tools::HttpArg("is_from_promote", false));
		http_args.push_back(tools::HttpArg("timezone_offset", buf));
		http_args.push_back(tools::HttpArg("session_id", m_client_session_id));
		http_args.push_back(tools::HttpArg("supported_capabilities_new", Constants::supported_capabilities));
		if(is_prefetch)
		{
			http_args.push_back(tools::HttpArg("max_id", 0));
			http_args.push_back(tools::HttpArg("module", "explore_popular"));
		}

		tools::HttpClient http_client(Constants::ig_url + "discover/explore/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	void Api::open_app(const bool &recent_login)
	{
		if(recent_login)
		{
			//sync
			sync_launcher(false);
			sync_user_features();

			//update feed and timeline
			get_timeline_feed(false, false, false);
			get_reels_tray_feed("cold_start");
			get_suggested_searches("users");
			get_suggested_searches("blended");

			//dm update
			get_ranked_recipients("reshare", true);
			get_ranked_recipients("save", true);
			get_inbox_v2();
			get_presence();
			get_recent_activity();

			//config and other requests
			get_loom_fetch_config();
			get_profile_notice();
			batch_fetch();
			explore(true);
		}
		else
		{
			//random
				//get time
			time_t raw_time;
			time(&raw_time);

			srand(raw_time);

			bool pull_to_refresh = (rand() % 101) % 2 == 0 ? true : false;
			get_timeline_feed(pull_to_refresh, false, false);
			get_reels_tray_feed(pull_to_refresh ? "pull_to_refresh" : "cold_start");

			//new client session
			if((raw_time - m_last_login) > Constants::app_refresh_interval)
			{
				m_last_login = raw_time;
				m_client_session_id = boost::uuids::to_string(boost::uuids::random_generator()());

				get_ranked_recipients("reshare", true);
				get_ranked_recipients("save", true);
				get_inbox_v2();
				get_presence();
				get_recent_activity();
				get_profile_notice();
				explore(false);
			}

			//new experiments
			if((raw_time - m_last_experiments) > Constants::app_experiments_interval)
			{
				sync_user_features(); //m_last_experiments is updated in that function
				sync_device_features(false);
			}
		}
	}

	bool Api::solve_challenge(const std::string &server_resp)
	{
		/*
		 * *1 get the challenge content
		 * *2 send the choice concerning the verification method
		 * *3 send the verification code
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

									//http headers
									std::vector<tools::HttpHeader> http_headers1 = get_ig_http_headers();
									http_headers1.push_back(tools::HttpHeader("Cookie", m_cookie_str));

									tools::HttpClient http_client1(Constants::ig_url + challenge_path, http_headers1);
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
													const rapidjson::Value &step_data = doc["step_data"];
													std::string choices;

													if(step_data.HasMember("phone_number"))
														choices.append("0 - Phone number");
													if(step_data.HasMember("email"))
														choices.append("\n1 - Email");

													std::cout << Messages::hints_from_last_server_response << std::endl;
													std::cout << http_res1.m_body << std::endl;
													std::cout << "You need to verify your login. Choose the method of approval." << std::endl;
													std::cout << choices << std::endl;
													int choice = -1;

													if(step_data.HasMember("phone_number") && step_data.HasMember("email"))
													{
														while(!(choice == 0 || choice == 1))
														{
															std::cout << "Your choice: ";
															std::cin >> choice;

															if(!(choice == 0 || choice == 1))
																std::cout << Messages::wrong_choice_try_again << std::endl;
														}
													}
													else if(step_data.HasMember("phone_number"))
													{
														while(choice != 0)
														{
															std::cout << "Your choice: ";
															std::cin >> choice;

															if(choice != 0)
																std::cout << Messages::wrong_choice_try_again << std::endl;
														}
													}
													else if(step_data.HasMember("email"))
													{
														while(choice != 1)
														{
															std::cout << "Your choice: ";
															std::cin >> choice;

															if(choice != 1)
																std::cout << Messages::wrong_choice_try_again << std::endl;
														}
													}

													//http headers
													std::vector<tools::HttpHeader> http_headers2 = get_ig_http_headers();
													http_headers2.push_back(tools::HttpHeader("Cookie", m_cookie_str));

													//http args
													std::vector<tools::HttpArg> http_args2;
													http_args2.push_back(tools::HttpArg("choice", choice));

													tools::HttpClient http_client2(Constants::ig_url + challenge_path, http_headers2, http_args2);
													tools::HttpResponse http_res2 = http_client2.send_post_req_urlencoded(mk_ig_http_body(http_args2));

													update_data(http_res2.m_cookies);
													post_req_check(http_client2, http_res2);

													std::cout << "A verification code has been sent to the selected method, please check." << std::endl;
													std::string security_code;
													std::cout << "Enter your verification code: ";
													std::cin >> security_code;

													//http headers
													std::vector<tools::HttpHeader> http_headers3 = get_ig_http_headers();
													http_headers3.push_back(tools::HttpHeader("Cookie", m_cookie_str));

													//http args
													std::vector<tools::HttpArg> http_args3;
													http_args3.push_back(tools::HttpArg("security_code", security_code));

													tools::HttpClient http_client3(Constants::ig_url + challenge_path, http_headers3, http_args3);
													tools::HttpResponse http_res3 = http_client3.send_post_req_urlencoded(mk_ig_http_body(http_args3));

													update_data(http_res3.m_cookies);
													post_req_check(http_client3, http_res3);

													if(http_res3.m_code == 200)
													{
														std::cout << "Successful login! The cookies are saved to " << m_file_cookies << "!" << std::endl;

														return true;
													}
												}
												else if(doc["step_name"].GetString() == std::string("delta_login_review"))
												{
													std::string choices;

													choices.append("0 - It was me\n");
													choices.append("1 - It wasn't me");

													std::cout << Messages::hints_from_last_server_response << std::endl;
													std::cout << http_res1.m_body << std::endl;
													std::cout << "You need to verify your login. Choose on whether the last login was you." << std::endl;
													std::cout << choices << std::endl;
													int choice = -1;

													while(!(choice == 0 || choice == 1))
													{
														std::cout << "Your choice: ";
														std::cin >> choice;

														if(!(choice == 0 || choice == 1))
															std::cout << Messages::wrong_choice_try_again << std::endl;
													}

													//http headers
													std::vector<tools::HttpHeader> http_headers2 = get_ig_http_headers();
													http_headers2.push_back(tools::HttpHeader("Cookie", m_cookie_str));

													//http args
													std::vector<tools::HttpArg> http_args2;
													http_args2.push_back(tools::HttpArg("choice", choice));

													tools::HttpClient http_client2(Constants::ig_url + challenge_path, http_headers2, http_args2);
													tools::HttpResponse http_res2 = http_client2.send_post_req_urlencoded(mk_ig_http_body(http_args2));

													update_data(http_res2.m_cookies);
													post_req_check(http_client2, http_res2);

													if(http_res2.m_code == 200)
													{
														std::cout << "Successful login! The cookies are saved to " << m_file_cookies << "!" << std::endl;

														return true;
													}
												}
												else
													std::cerr << Messages::field_not_correct_value("step_name", "select_verify_method or delta_login_review") << std::endl;
											}
											else
											    std::cerr << Messages::field_not_contain_string("step_name") << std::endl;
										}
										else
											std::cerr << Messages::field_not_found("step_name") << std::endl;
									}
									else
										std::cerr << Messages::server_respone_not_json_obj << std::endl;
								}
								else
								    std::cerr << Messages::field_not_contain_string("api_path") << std::endl;
							}
							else
								std::cerr << Messages::field_not_found("api_path") << std::endl;
						}
						else
							std::cerr << Messages::field_not_found("challenge") << std::endl;
					}
					else
						std::cerr << Messages::field_not_correct_value("error_type", "checkpoint_challenge_required") << std::endl;
				}
				else
					std::cerr << Messages::field_not_contain_string("error_type") << std::endl;
			}
			else
				std::cerr << Messages::field_not_found("error_type") << std::endl;
		}
		else
			std::cerr << Messages::server_respone_not_json_obj << std::endl;

		return false;
	}

	std::string Api::get_rank_token() noexcept
	{
		return get_cookie_val("ds_user_id") + "_" + m_uuid;
	}

	void Api::post_req_check(const tools::HttpClient &http_client, const tools::HttpResponse &server_resp)
	{
		//###log###
		//get time
		time_t raw_time;
		time(&raw_time);
		struct tm *time_info;
		time_info = localtime(&raw_time);

		//file length is under Constants::log_lns --> just append
		if(tools::Tools::get_amnt_file_lns(Constants::file_log) < Constants::log_lns)
		{
			std::ofstream outf(Constants::file_log, std::ios::app);
			//pop_back() as asctime() ends with \n
			std::string time = std::string(asctime(time_info));
			if(!time.empty())
				time.pop_back();
			outf << m_username << " " << time << " --> " << http_client.get_url() << std::endl;
			outf.close();
		}
		else
		{
			//get the last Constants::log_lns lines of the file
			std::string file_cont = tools::Tools::get_last_lns_file(Constants::file_log, tools::Tools::get_amnt_file_lns(Constants::file_log) - Constants::log_lns);
			std::ofstream outf(Constants::file_log);
			outf << file_cont;

			//pop_back() as asctime() ends with \n
			std::string time = std::string(asctime(time_info));
			if(!time.empty())
				time.pop_back();
			outf << m_username << " " << time << " --> " << http_client.get_url() << std::endl;
			outf.close();
		}

		//###server response check###
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
						std::cerr << Messages::manual_challenge << std::endl;
				}
				else
					std::cerr << Messages::field_not_contain_string("message") << std::endl;
			}

			/*
			 * a response like the following is sent back for example if the wrong cookies are sent and you are logged out as a consequence
			 * you will also get the response below if the session is revoked on https://www.instagram.com/session/login_activity/
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
						m_del_cookies_uuids = true;

						std::cerr << Messages::new_login_required_as_logged_out << std::endl;
					}
				}
				else
					std::cerr << Messages::field_not_contain_string("message") << std::endl;
			}
		}

		//Oops, an error occured.
		if(boost::iequals(server_resp.m_body, "Oops, an error occured."))
			std::cerr << Messages::acc_soft_ban << std::endl;

		//too many requests
		if(server_resp.m_code == 429)
			throw std::runtime_error("Error. The Instagram servers refused the request as they are too many.");
	}

	bool Api::login()
	{
		if(m_new_login == true)
		{
			pre_login_requests();

			/*
			 * actual login
			 * #####accounts/login/#####
			 * Cookie: csrftoken, rur, mid
			 * Set-Cookie: ds_user, csrftoken (csrftoken is different to before), shbid, shbts, rur, ds_user_id, urlgen, sessionid
			 */
			//http headers
			std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
			http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

			//http args
			std::vector<tools::HttpArg> http_args;
			http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
			http_args.push_back(tools::HttpArg("username", m_username));
			http_args.push_back(tools::HttpArg("guid", m_uuid));
			http_args.push_back(tools::HttpArg("device_id", m_device_id));
			http_args.push_back(tools::HttpArg("password", m_password));
			http_args.push_back(tools::HttpArg("login_attempt_count", 0));

			tools::HttpClient http_client(Constants::ig_url + "accounts/login/", http_headers, http_args);
			tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

			update_data(http_res.m_cookies);
			post_req_check(http_client, http_res);

			//get time
			time_t raw_time;
			time(&raw_time);

			if(http_res.m_code == 200)
			{
				open_app(true);
				m_last_login = raw_time;

				std::cout << "Successful login! The cookies are saved to " << m_file_cookies << "!" << std::endl;

				return true;
			}
			else
			{
				/*
				 * #####checkpoint_challenge_required#####
				 * Cookie: csrftoken, rur, mid
				 * Set-Cookie: csrftoken, rur (both same as before)
				 */
				rapidjson::Document doc;
				doc.Parse(http_res.m_body.c_str());

				if(doc.IsObject())
				{
					if(doc.HasMember("error_type"))
					{
						if(doc["error_type"].IsString())
						{
							if(doc["error_type"].GetString() == std::string("checkpoint_challenge_required"))
							{
								if(solve_challenge(http_res.m_body))
								{
									open_app(true);
									m_last_login = raw_time;

									return true;
								}
								else
									std::cerr << Messages::challenge_not_solved << std::endl;
							}
							else
								std::cerr << Messages::field_not_correct_value("error_type", "checkpoint_challenge_required") << std::endl;
						}
						else
							std::cerr << Messages::field_not_contain_string("error_type") << std::endl;
					}
					else
						std::cerr << Messages::field_not_found("error_type") << std::endl;
				}
				else
					std::cerr << Messages::server_respone_not_json_obj << std::endl;

				return false;
			}
		}
		else
		{
			open_app(false);

			return true;
		}
	}

	std::string Api::get_media_likers(const std::string &media_id)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		tools::HttpClient http_client(Constants::ig_url + "media/" + media_id + "/likers/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_media_comments(const std::string &media_id, const std::string &max_id)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		std::string url = Constants::ig_url + "media/" + media_id + "/comments/";
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
				//scrape comments
				if(doc.HasMember("comments"))
				{
					const rapidjson::Value &comments = doc["comments"];

					if(comments.IsArray())
					{
						for(size_t j = 0; j < comments.GetArray().Size(); ++j)
						{
							result.append(tools::Tools::get_json_as_string(comments[j]));
							result.append(", ");
						}
					}
					else
					    std::cerr << Messages::field_not_contain_json_array("comments") << std::endl;

					//perhaps, next page
					if(doc.HasMember("has_more_comments") && doc.HasMember("next_max_id"))
						if(doc["next_max_id"].IsString())
							response = get_media_comments(media_id, doc["next_max_id"].GetString());
						else
						{
							std::cerr << Messages::field_not_contain_string("next_max_id") << std::endl;
							break;
						}
					else
						break;
				}
				else
				{
					std::cerr << Messages::field_not_found("comments") << std::endl;
					break;
				}
			}
			else
			{
				std::cerr << Messages::server_respone_not_json_obj << std::endl;
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
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		std::string url = Constants::ig_url + "media/" + media_id + "/info/";

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_user_feed(const std::string &user_id, const std::string &max_id, const std::string &min_timestamp)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		std::string url = Constants::ig_url + "feed/user/" + user_id + "/?max_id=" + max_id + "&min_timestamp=" + min_timestamp +
	            "&rank_token=" + get_rank_token() + "&ranked_content=true";

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		return http_res.m_body;
	}

	std::string Api::get_user_info(const std::string &user_id)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		std::string url = Constants::ig_url + "users/" + user_id + "/info/";

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
					    std::cerr << Messages::field_not_contain_string("media_id") << std::endl;
					    return "";
					}
				}
				else
				{
					std::cerr << Messages::field_not_found("media_id") << std::endl;
					return "";
				}
			}
			else
			{
				std::cerr << Messages::server_respone_not_json_obj << std::endl;
				return "";
			}
		}
		else
		{
			std::cerr << Messages::not_ig_post << std::endl;
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
		//so that if the key is not found in the json the bool is correct
		bool comments_allowed = true;

		//###comments disabled###
		{
			std::string json = get_media_comments(media_id);

			rapidjson::Document doc;
			doc.Parse(json.c_str());

			/*
			 * in json file, it would be written:
			 * {"comments_disabled": true, "status": "ok"}
			 * therefore, the negation is needed
			 */
			if(doc.IsObject())
			{
				if(doc.HasMember("comments_disabled"))
				{
					if(doc["comments_disabled"].IsBool())
						comments_allowed = !(doc["comments_disabled"].GetBool());
					else
					    std::cerr << Messages::Messages::field_not_contain_bool("comments_disabled") << std::endl;
				}
			}
			else
				std::cerr << Messages::server_respone_not_json_obj << std::endl;
		}

		//###comments restricted###
		{
			std::string json = get_media_info(media_id);

			rapidjson::Document doc;
			doc.Parse(json.c_str());

			/*
			 * in json file, it would be written:
			 * "commenting_disabled_for_viewer":true
			 * therefore, the negation is needed
			 */
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
									comments_allowed = !(media_info["commenting_disabled_for_viewer"].GetBool());
								else
									std::cerr << Messages::field_not_contain_bool("commenting_disabled_for_viewer") << std::endl;
							}
						}
						else
							std::cerr << Messages::json_array_has_size_0("items") << std::endl;
					}
					else
					    std::cerr << Messages::field_not_contain_json_array("items") << std::endl;
				}
				else
					std::cerr << Messages::field_not_found("items") << std::endl;
			}
			else
				std::cerr << Messages::server_respone_not_json_obj << std::endl;
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
					    std::cerr << Messages::field_not_contain_string("username") << std::endl;
					    return "";
					}
				else
				{
					std::cerr << Messages::field_not_found("username") << std::endl;
					return "";
				}
			}
			else
			{
				std::cerr << Messages::field_not_found("user") << std::endl;
				return "";
			}
		}
		else
		{
			std::cerr << Messages::server_respone_not_json_obj << std::endl;
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
									std::cerr << Messages::field_not_contain_string("username") << std::endl;
									return "";
								}
							else
							{
								std::cerr << Messages::field_not_found("username") << std::endl;
								return "";
							}
						}
						else
						{
							std::cerr << Messages::field_not_found("user") << std::endl;
							return "";
						}
					}
					else
					{
						std::cerr << Messages::json_array_has_size_0("items") << std::endl;
						return "";
					}
				}
				else
				{
					std::cerr << Messages::field_not_contain_json_array("error_type") << std::endl;
					return "";
				}
			}
			else
			{
				std::cerr << Messages::field_not_found("items") << std::endl;
				return "";
			}
		}
		else
		{
			std::cerr << Messages::server_respone_not_json_obj << std::endl;
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
						std::cerr << Messages::field_not_contain_int("follower_count") << std::endl;
				}
				else
					std::cerr << Messages::field_not_found("follower_count") << std::endl;
			}
			else
				std::cerr << Messages::field_not_found("user") << std::endl;
		}
		else
			std::cerr << Messages::server_respone_not_json_obj << std::endl;

		return 0;
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
								    std::cerr << Messages::field_not_contain_int("pk") << std::endl;
								    return "";
								}
							else
							{
								std::cerr << Messages::field_not_found("pk") << std::endl;
								return "";
							}
						}
						else
						{
							std::cerr << Messages::field_not_found("user") << std::endl;
							return "";
						}
					}
					else
					{
						std::cerr << Messages::json_array_has_size_0("items") << std::endl;
						return "";
					}
				}
				else
				{
					std::cerr << Messages::field_not_contain_json_array("items") << std::endl;
					return "";
				}
			}
			else
			{
				std::cerr << Messages::field_not_found("items") << std::endl;
				return "";
			}
		}
		else
		{
			std::cerr << Messages::server_respone_not_json_obj << std::endl;
			return "";
		}
	}

	std::string Api::logout()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;

		tools::HttpClient http_client(Constants::ig_url + "accounts/logout/", http_headers, http_args);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_data(http_res.m_cookies);
		post_req_check(http_client, http_res);

		m_del_cookies_uuids = true;

		return http_res.m_body;
	}
}
