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
#include "ig/devices/OnePlus7.h"
#include <cstdlib>
#include <rapidjson/document.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include <ig/Api.h>

namespace ig
{
	Api::Api(const std::string &username, const std::string &password) : m_username(username), m_password(password)
	{
		//create necessary folders
		try
		{
			boost::filesystem::create_directories("files");
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

		get_cookies_uuids();

		//login
		login();
	}

	std::vector<tools::HttpHeader> Api::get_ig_http_headers() const
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
		http_headers.push_back(tools::HttpHeader("User-Agent", OnePlus7::user_agent));
		http_headers.push_back(tools::HttpHeader("X-IG-Connection-Speed", "-1kbps"));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-Speed-KBPS", std::to_string(rand() % 3000 + 7000)));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalBytes-B", std::to_string(rand() % 400000 + 500000)));
		http_headers.push_back(tools::HttpHeader("X-IG-Bandwidth-TotalTime-MS", std::to_string(rand() % 100 + 50)));
		http_headers.push_back(tools::HttpHeader("X-DEVICE-ID", m_uuid));

		return http_headers;
	}

	std::string Api::mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const
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

	void Api::get_cookies_uuids()
	{
		//load the uuids and cookies if available in the proper file
		if(tools::Tools::file_exists(Constants::file_cookies))
		{
			//uuids
			//phone id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "phone id"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_phone_id = args.at(args.size() - 1);
			}

			//uuid
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "uuid"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_uuid = args.at(args.size() - 1);
			}

			//client session id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "client session id"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_client_session_id = args.at(args.size() - 1);
			}

			//advertising id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "advertising id"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_advertising_id = args.at(args.size() - 1);
			}

			//device id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "device id"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_device_id = args.at(args.size() - 1);
			}

			//cookies
			//ds user
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "ds user"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_ds_user = args.at(args.size() - 1);
			}

			//csrftoken
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "csrftoken"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_csrftoken = args.at(args.size() - 1);
			}

			//shbid
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "shbid"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_shbid = args.at(args.size() - 1);
			}

			//shbts
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "shbts"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_shbts = args.at(args.size() - 1);
			}

			//rur
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "rur"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_rur = args.at(args.size() - 1);
			}

			//ds user id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "ds user id"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_ds_user_id = args.at(args.size() - 1);
			}

			//urlgen
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "urlgen"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_urlgen = args.at(args.size() - 1);
			}

			//session id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "session id"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_sessionid = args.at(args.size() - 1);
			}

			//mid
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(Constants::file_cookies, "mid"));
				if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
					m_mid = args.at(args.size() - 1);
			}
		}

		//create all necessary uuids new
		if(m_phone_id.empty() || m_uuid.empty() || m_client_session_id.empty() || m_advertising_id.empty() || m_device_id.empty() || m_ds_user.empty() ||
				m_csrftoken.empty() || m_shbid.empty() || m_shbts.empty() || m_rur.empty() || m_ds_user_id.empty() || m_urlgen.empty() || m_sessionid.empty() ||
				m_mid.empty())
		{
			m_new_login = true;

			m_phone_id = boost::uuids::to_string(boost::uuids::random_generator()());
			m_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
			m_client_session_id = boost::uuids::to_string(boost::uuids::random_generator()());
			m_advertising_id = boost::uuids::to_string(boost::uuids::random_generator()());
				//device id has to be uuid with length 16 and hex in format android-...
			std::string device_id_temp = boost::uuids::to_string(boost::uuids::random_generator()());
			device_id_temp.resize(16);
			std::stringstream sstream;
			sstream << std::hex << device_id_temp;
			m_device_id = "android-" + sstream.str();

			std::cout << "No cookies from a previous session were found. Thus a new login is required whose cookies will be stored for the next logins." << std::endl;
		}
		else
		{
			m_new_login = false;

			//save the cookies in one string
			m_final_cookies = "csrftoken=" + m_csrftoken + "; ds_user=" + m_ds_user + "; ds_user_id=" + m_ds_user_id + "; mid=" + m_mid +
							"; rur=" + m_rur + "; sessionid=" + m_sessionid + "; shbid=" + m_shbid + "; shbts=" + m_shbts + "; urlgen=" + m_urlgen;

			std::cout << "Cookies are used from a previous session!" << std::endl;
		}
	}

	std::string Api::read_msisdn_header() const
	{
		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("device_id", m_uuid));
		http_args.push_back(tools::HttpArg("mobile_subno_usage", "default"));

		tools::HttpClient http_client(Constants::ig_url + "accounts/read_msisdn_header/", get_ig_http_headers());
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		//get the cookies
		for(size_t j = 0; j < http_res.m_headers.size(); ++j)
		{
			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
				m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
				m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");

			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "mid").empty())
				m_mid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "mid");
		}

		return http_res.m_body;
	}

	std::string Api::launcher_sync() const
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));
		http_args.push_back(tools::HttpArg("experiments", Constants::launcher_configs));
		if(m_new_login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", m_ds_user_id));
			http_args.push_back(tools::HttpArg("_csrftoken", m_csrftoken));
		}

		tools::HttpClient http_client(Constants::ig_url + "launcher/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		//get the cookies
		for(size_t j = 0; j < http_res.m_headers.size(); ++j)
		{
			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
				m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
				m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");
		}

		return http_res.m_body;
	}

	std::string Api::qe_sync() const
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));
		http_args.push_back(tools::HttpArg("experiments", Constants::login_experiments));
		if(m_new_login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", m_ds_user_id));
			http_args.push_back(tools::HttpArg("_csrftoken", m_csrftoken));
		}

		tools::HttpClient http_client(Constants::ig_url + "qe/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		//get the cookies
		for(size_t j = 0; j < http_res.m_headers.size(); ++j)
		{
			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
				m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
				m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");
		}

		return http_res.m_body;
	}

	std::string Api::log_attribution() const
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("adid", m_advertising_id));

		tools::HttpClient http_client(Constants::ig_url + "attribution/log_attribution/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		//get the cookies
		for(size_t j = 0; j < http_res.m_headers.size(); ++j)
		{
			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
				m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
				m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");
		}

		return http_res.m_body;
	}

	std::string Api::contact_point_prefill() const
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("_csrftoken", m_csrftoken));
		http_args.push_back(tools::HttpArg("usage", "prefill"));

		tools::HttpClient http_client(Constants::ig_url + "accounts/contact_point_prefill/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		//get the cookies
		for(size_t j = 0; j < http_res.m_headers.size(); ++j)
		{
			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
				m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

			if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
				m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");
		}

		return http_res.m_body;
	}

	bool Api::login()
	{
		read_msisdn_header();
		launcher_sync();
		qe_sync();
		log_attribution();
		contact_point_prefill();

		if(m_new_login == true)
		{
			/*
			 * actual login
			 * #####accounts/login/#####
			 * Cookie: csrftoken, rur, mid
			 * Set-Cookie: ds_user, csrftoken (csrftoken is different to before), shbid, shbts, rur, ds_user_id, urlgen, sessionid
			 */
			//http headers
			std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
			http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

			//http args
			std::vector<tools::HttpArg> http_args;
			http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
			http_args.push_back(tools::HttpArg("_csrftoken", m_csrftoken));
			http_args.push_back(tools::HttpArg("username", m_username));
			http_args.push_back(tools::HttpArg("guid", m_uuid));
			http_args.push_back(tools::HttpArg("device_id", m_device_id));
			http_args.push_back(tools::HttpArg("password", m_password));
			http_args.push_back(tools::HttpArg("login_attempt_count", 0));

			tools::HttpClient http_client(Constants::ig_url + "accounts/login/", http_headers, http_args);
			tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

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
					if(doc["error_type"].GetString() == std::string("checkpoint_challenge_required"))
					{
						if(doc.HasMember("challenge"))
						{
							const rapidjson::Value &challenge = doc["challenge"];

							if(challenge.HasMember("api_path"))
							{
								std::string challenge_path = tools::Tools::cut_off_first_char(challenge["api_path"].GetString());

								//http headers
								std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
								http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; mid=" + m_mid + "; rur=" + m_rur));

								tools::HttpClient http_client(Constants::ig_url + challenge_path, http_headers);
								tools::HttpResponse http_res = http_client.send_get_req();

								rapidjson::Document doc;
								doc.Parse(http_res.m_body.c_str());

								if(doc.IsObject())
								{
									if(doc.HasMember("step_name"))
									{
										if(doc["step_name"].GetString() == std::string("select_verify_method"))
										{
											const rapidjson::Value &step_data = doc["step_data"];
											std::string choices;

											if(step_data.HasMember("phone_number"))
												choices.append("0 - Phone number");
											else if(step_data.HasMember("email"))
												choices.append("1 - Email");

											std::cout << "You need to verify your login. Choose the method of approval." << std::endl;
											int choice = -1;

											if(step_data.HasMember("phone_number") && step_data.HasMember("email"))
											{
												while(!(choice == 0 || choice == 1))
												{
													std::cout << "Your choice: ";
													std::cin >> choice;

													if(!(choice == 0 || choice == 1))
														std::cout << "Error. Wrong choice. Try again!" << std::endl;
												}
											}
											else if(step_data.HasMember("phone_number"))
											{
												while(choice != 0)
												{
													std::cout << "Your choice: ";
													std::cin >> choice;

													if(choice != 0)
														std::cout << "Error. Wrong choice. Try again!" << std::endl;
												}
											}
											else if(step_data.HasMember("email"))
											{
												while(choice != 1)
												{
													std::cout << "Your choice: ";
													std::cin >> choice;

													if(choice != 1)
														std::cout << "Error. Wrong choice. Try again!" << std::endl;
												}
											}

											//http headers
											std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
											http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

											//http args
											std::vector<tools::HttpArg> http_args;
											http_args.push_back(tools::HttpArg("choice", choice));

											tools::HttpClient http_client(Constants::ig_url + challenge_path, http_headers, http_args);
											tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

											//todo
											std::cout << "A verification code has been sent to the selected method, please check." << std::endl;
											std::string security_code;
											std::cout << "Enter your verification code: ";
											std::cin >> security_code;

											{
												//http headers
												std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
												http_headers.push_back(tools::HttpHeader("Cookie", "csrftoken=" + m_csrftoken + "; rur=" + m_rur + "; mid=" + m_mid));

												//http args
												std::vector<tools::HttpArg> http_args;
												http_args.push_back(tools::HttpArg("security_code", security_code));

												tools::HttpClient http_client(Constants::ig_url + challenge_path, http_headers, http_args);
												tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

												if(http_res.m_code == 200)
												{
													//get the cookies
													for(size_t j = 0; j < http_res.m_headers.size(); ++j)
													{
														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user").empty())
															m_ds_user = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
															m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbid").empty())
															m_shbid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbid");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbts").empty())
															m_shbts = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbts");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
															m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user_id").empty())
															m_ds_user_id = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user_id");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "urlgen").empty())
															m_urlgen = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "urlgen");

														if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "sessionid").empty())
															m_sessionid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "sessionid");
													}

													//save the cookies in a file
													std::ofstream outf(Constants::file_cookies);
													outf << "All ids:" << std::endl;
													outf << "phone id: " << m_phone_id << std::endl;
													outf << "uuid: " << m_uuid << std::endl;
													outf << "client session id: " << m_client_session_id << std::endl;
													outf << "advertising id: " << m_advertising_id << std::endl;
													outf << "device id: " << m_device_id << std::endl;
													outf << std::endl;
													outf << "The cookies:" << std::endl;
													outf << "ds user: " << m_ds_user << std::endl;
													outf << "csrftoken: " << m_csrftoken << std::endl;
													outf << "shbid: " << m_shbid << std::endl;
													outf << "shbts: " << m_shbts << std::endl;
													outf << "rur: " << m_rur << std::endl;
													outf << "ds user id: " << m_ds_user_id << std::endl;
													outf << "urlgen: " << m_urlgen << std::endl;
													outf << "session id: " << m_sessionid << std::endl;
													outf << "mid: " << m_mid << std::endl;
													outf.close();

													//save the cookies in one string
													m_final_cookies = "csrftoken=" + m_csrftoken + "; ds_user=" + m_ds_user + "; ds_user_id=" + m_ds_user_id + "; mid=" + m_mid +
																	"; rur=" + m_rur + "; sessionid=" + m_sessionid + "; shbid=" + m_shbid + "; shbts=" + m_shbts + "; urlgen=" +
																	m_urlgen;

													std::cout << "The cookies are saved to " << Constants::file_cookies << "!" << std::endl;
											}
										}
										else
											std::cout << "Error. It was received an unknown challenge and thus cannot be handled." << std::endl;
									}
								}
							}
						}
					}
				}
			}
			else
				std::cerr << "Error. The server response on the login request is not a json object." << std::endl;

			if(http_res.m_code == 200)
			{
				//get the cookies
				for(size_t j = 0; j < http_res.m_headers.size(); ++j)
				{
					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user").empty())
						m_ds_user = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken").empty())
						m_csrftoken = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "csrftoken");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbid").empty())
						m_shbid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbid");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbts").empty())
						m_shbts = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "shbts");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur").empty())
						m_rur = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "rur");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user_id").empty())
						m_ds_user_id = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "ds_user_id");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "urlgen").empty())
						m_urlgen = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "urlgen");

					if(!tools::Tools::get_val(http_res.m_headers.at(j).m_value, "sessionid").empty())
						m_sessionid = tools::Tools::get_val(http_res.m_headers.at(j).m_value, "sessionid");
				}

				//save the cookies in a file
				std::ofstream outf(Constants::file_cookies);
				outf << "All ids:" << std::endl;
				outf << "phone id: " << m_phone_id << std::endl;
				outf << "uuid: " << m_uuid << std::endl;
				outf << "client session id: " << m_client_session_id << std::endl;
				outf << "advertising id: " << m_advertising_id << std::endl;
				outf << "device id: " << m_device_id << std::endl;
				outf << std::endl;
				outf << "The cookies:" << std::endl;
				outf << "ds user: " << m_ds_user << std::endl;
				outf << "csrftoken: " << m_csrftoken << std::endl;
				outf << "shbid: " << m_shbid << std::endl;
				outf << "shbts: " << m_shbts << std::endl;
				outf << "rur: " << m_rur << std::endl;
				outf << "ds user id: " << m_ds_user_id << std::endl;
				outf << "urlgen: " << m_urlgen << std::endl;
				outf << "session id: " << m_sessionid << std::endl;
				outf << "mid: " << m_mid << std::endl;
				outf.close();

				//save the cookies in one string
				m_final_cookies = "csrftoken=" + m_csrftoken + "; ds_user=" + m_ds_user + "; ds_user_id=" + m_ds_user_id + "; mid=" + m_mid +
								"; rur=" + m_rur + "; sessionid=" + m_sessionid + "; shbid=" + m_shbid + "; shbts=" + m_shbts + "; urlgen=" + m_urlgen;

				std::cout << "The cookies are saved to " << Constants::file_cookies << "!" << std::endl;
			}
			else
				std::cerr << "Error. The server response on the login request does not have status code 200." << std::endl;
		}
	}

	std::string Api::get_media_likers(const std::string &media_id)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_final_cookies));

		tools::HttpClient http_client(Constants::ig_url + "media/" + media_id + "/likers/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		return http_res.m_body;
	}

	std::string Api::get_media_comments(const std::string &media_id, const std::string &max_id)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_final_cookies));

		std::string url = Constants::ig_url + "media/" + media_id + "/comments/";
		if(!max_id.empty())
			url.append("?max_id=" + max_id);

		tools::HttpClient http_client(url, http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		return http_res.m_body;
	}
}
