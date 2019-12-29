#include "ig/Api.h"
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
#include "ig/devices/SamsungGalaxyS7.h"
#include <cstdlib>
#include <rapidjson/document.h>
#include <fstream>
#include <boost/filesystem.hpp>
#include "tools/Constants.h"

namespace ig
{
	Api::Api(const std::string &username, const std::string &password) : m_username(username), m_password(password),
			m_file_uuids(Constants::files_folder + username + "_uuids.dat"), m_file_cookies(Constants::files_folder + username + "_cookies.dat"), m_del_cookies_uuids(false)
	{
		//create necessary folders
		try
		{
			boost::filesystem::create_directories("files/ig");
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

		//also determines whether an new login is required
		setup_cookies_uuids();

		//login
		if(login())
		{
			save_uuids_in_file();
			save_cookies_in_file();
		}
	}

	Api::~Api()
	{
		if(!m_del_cookies_uuids)
		{
			save_uuids_in_file();
			save_cookies_in_file();
		}
		else
		{
			if(remove(m_file_uuids.c_str()) != 0)
				std::cerr << "Error: " << m_file_uuids << " - " << strerror(errno) << std::endl;

			if(remove(m_file_cookies.c_str()) != 0)
				std::cerr << "Error: " << m_file_cookies << " - " << strerror(errno) << std::endl;
		}
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
		http_headers.push_back(tools::HttpHeader("User-Agent", SamsungGalaxyS7::user_agent));
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

	void Api::setup_cookies_uuids()
	{
		if(tools::Tools::file_exists(m_file_uuids))
		{
			//phone id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_uuids, "phone id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_phone_id = args.at(args.size() - 1);
				}
				else
					std::cerr << "Error: \"phone id\" could not be found in " << m_file_uuids << "." << std::endl;
			}

			//uuid
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_uuids, "uuid"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_uuid = args.at(args.size() - 1);
				}
				else
					std::cerr << "Error: \"uuid\" could not be found in " << m_file_uuids << "." << std::endl;
			}

			//client session id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_uuids, "client session id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_client_session_id = args.at(args.size() - 1);
				}
				else
					std::cerr << "Error: \"client session id\" could not be found in " << m_file_uuids << "." << std::endl;
			}

			//advertising id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_uuids, "advertising id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_advertising_id = args.at(args.size() - 1);
				}
				else
					std::cerr << "Error: \"advertising id\" could not be found in " << m_file_uuids << "." << std::endl;
			}

			//device id
			{
				std::vector<std::string> args = tools::Tools::get_args(tools::Tools::get_file_ln_w_srch(m_file_uuids, "device id"));
				if(!args.empty())
				{
					if(!tools::Tools::ends_w(args.at(args.size() - 1), ":"))
						m_device_id = args.at(args.size() - 1);
				}
				else
					std::cerr << "Error: \"device id\" could not be found in " << m_file_uuids << "." << std::endl;
			}
		}
		else
			tools::Constants::file_non_existent(m_file_uuids);

		if(tools::Tools::file_exists(m_file_cookies))
		{
			for(int j = 1; j <= tools::Tools::get_amnt_file_lns(m_file_cookies); ++j)
				if(!tools::Tools::get_file_ln(m_file_cookies, j).empty())
					m_cookies.push_back(tools::HttpCookie(tools::Tools::get_file_ln(m_file_cookies, j)));
		}
		else
			tools::Constants::file_non_existent(m_file_cookies);

		//just for orientation about the cookies
		if(get_cookie_val("ds_user").empty())
			std::cerr << "Error: The cookie \"ds_user\" is missing." << std::endl;

		if(get_cookie_val("csrftoken").empty())
			std::cerr << "Error: The cookie \"csrftoken\" is missing." << std::endl;

		//it seems that this cookie is not necessary
//		if(get_cookie_val("shbid").empty())
//			std::cerr << "Error: The cookie \"shbid\" is missing." << std::endl;

		//it seems that this cookie is not necessary
//		if(get_cookie_val("shbts").empty())
//			std::cerr << "Error: The cookie \"shbts\" is missing." << std::endl;

		if(get_cookie_val("rur").empty())
			std::cerr << "Error: The cookie \"rur\" is missing." << std::endl;

		if(get_cookie_val("ds_user_id").empty())
			std::cerr << "Error: The cookie \"ds_user_id\" is missing." << std::endl;

		if(get_cookie_val("urlgen").empty())
			std::cerr << "Error: The cookie \"urlgen\" is missing." << std::endl;

		if(get_cookie_val("sessionid").empty())
			std::cerr << "Error: The cookie \"sessionid\" is missing." << std::endl;

		if(get_cookie_val("mid").empty())
			std::cerr << "Error: The cookie \"mid\" is missing." << std::endl;

		/*
		 * if a uuid is missing
		 * if a cookie is missing (I already know the names of those which are needed)
		 */
		if(m_phone_id.empty() || m_uuid.empty() || m_client_session_id.empty() || m_advertising_id.empty() || m_device_id.empty() ||
				get_cookie_val("ds_user").empty() || get_cookie_val("csrftoken").empty() || get_cookie_val("rur").empty() ||
				get_cookie_val("ds_user_id").empty() || get_cookie_val("urlgen").empty() || get_cookie_val("sessionid").empty() || get_cookie_val("mid").empty())
		{
			m_new_login = true;

			//generate new uuids
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
			set_cookie_str();
			std::cout << "Cookies are used from a previous session!" << std::endl;
		}
	}

	void Api::update_cookies(const std::vector<tools::HttpCookie> &http_cookies)
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
		set_cookie_str();
	}

	void Api::save_uuids_in_file() const
	{
		std::ofstream outf(m_file_uuids);
		outf << "All ids:" << std::endl;
		outf << "phone id: " << m_phone_id << std::endl;
		outf << "uuid: " << m_uuid << std::endl;
		outf << "client session id: " << m_client_session_id << std::endl;
		outf << "advertising id: " << m_advertising_id << std::endl;
		outf << "device id: " << m_device_id << std::endl;
		outf.close();
	}

	void Api::save_cookies_in_file() const
	{
		std::ofstream outf(m_file_cookies);

		for(size_t j = 0; j < m_cookies.size(); ++j)
			outf << m_cookies.at(j).to_string() << std::endl;

		outf.close();
	}

	void Api::set_cookie_str()
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

	std::string Api::get_cookie_val(const std::string &cookie_name) const
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

	std::string Api::read_msisdn_header()
	{
		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("device_id", m_uuid));
		http_args.push_back(tools::HttpArg("mobile_subno_usage", "default"));

		tools::HttpClient http_client(Constants::ig_url + "accounts/read_msisdn_header/", get_ig_http_headers());
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

		return http_res.m_body;
	}

	std::string Api::launcher_sync()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));
		http_args.push_back(tools::HttpArg("experiments", Constants::launcher_configs));
		if(m_new_login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		}

		tools::HttpClient http_client(Constants::ig_url + "launcher/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

		return http_res.m_body;
	}

	std::string Api::qe_sync()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("server_config_retrieval", "1"));
		http_args.push_back(tools::HttpArg("experiments", Constants::login_experiments));
		if(m_new_login == false)
		{
			http_args.push_back(tools::HttpArg("_uuid", m_uuid));
			http_args.push_back(tools::HttpArg("_uid", get_cookie_val("ds_user_id")));
			http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		}

		tools::HttpClient http_client(Constants::ig_url + "qe/sync/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

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

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

		return http_res.m_body;
	}

	std::string Api::contact_point_prefill()
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		//http args
		std::vector<tools::HttpArg> http_args;
		http_args.push_back(tools::HttpArg("id", m_uuid));
		http_args.push_back(tools::HttpArg("phone_id", m_phone_id));
		http_args.push_back(tools::HttpArg("_csrftoken", get_cookie_val("csrftoken")));
		http_args.push_back(tools::HttpArg("usage", "prefill"));

		tools::HttpClient http_client(Constants::ig_url + "accounts/contact_point_prefill/", http_headers);
		tools::HttpResponse http_res = http_client.send_post_req_urlencoded(mk_ig_http_body(http_args));

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

		return http_res.m_body;
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
				if(doc["error_type"].GetString() == std::string("checkpoint_challenge_required"))
				{
					if(doc.HasMember("challenge"))
					{
						const rapidjson::Value &challenge = doc["challenge"];

						if(challenge.HasMember("api_path"))
						{
							std::string challenge_path = tools::Tools::cut_off_first_char(challenge["api_path"].GetString());

							//http headers
							std::vector<tools::HttpHeader> http_headers1 = get_ig_http_headers();
							http_headers1.push_back(tools::HttpHeader("Cookie", m_cookie_str));

							tools::HttpClient http_client1(Constants::ig_url + challenge_path, http_headers1);
							tools::HttpResponse http_res1 = http_client1.send_get_req();

							update_cookies(http_res1.m_cookies);

							rapidjson::Document doc;
							doc.Parse(http_res1.m_body.c_str());

							if(doc.IsObject())
							{
								if(doc.HasMember("step_name"))
								{
									if(doc["step_name"].GetString() == std::string("select_verify_method"))
									{
										const rapidjson::Value &step_data = doc["step_data"];
										std::string choices;

										if(step_data.HasMember("phone_number"))
											choices.append("0 - Phone number\n");
										if(step_data.HasMember("email"))
											choices.append("1 - Email");

										std::cout << "If you do not know your personal data like phone number or email here are some hints:" << std::endl;
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
													std::cout << "Error: Wrong choice. Try again!" << std::endl;
											}
										}
										else if(step_data.HasMember("phone_number"))
										{
											while(choice != 0)
											{
												std::cout << "Your choice: ";
												std::cin >> choice;

												if(choice != 0)
													std::cout << "Error: Wrong choice. Try again!" << std::endl;
											}
										}
										else if(step_data.HasMember("email"))
										{
											while(choice != 1)
											{
												std::cout << "Your choice: ";
												std::cin >> choice;

												if(choice != 1)
													std::cout << "Error: Wrong choice. Try again!" << std::endl;
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

										update_cookies(http_res2.m_cookies);

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

										update_cookies(http_res3.m_cookies);

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

										std::cout << "Here you have the last server response:" << std::endl;
										std::cout << http_res1.m_body << std::endl;
										std::cout << "You need to verify your login. Choose on whether the last login was you." << std::endl;
										std::cout << choices << std::endl;
										int choice = -1;

										while(!(choice == 0 || choice == 1))
										{
											std::cout << "Your choice: ";
											std::cin >> choice;

											if(!(choice == 0 || choice == 1))
												std::cout << "Error: Wrong choice. Try again!" << std::endl;
										}

										//http headers
										std::vector<tools::HttpHeader> http_headers2 = get_ig_http_headers();
										http_headers2.push_back(tools::HttpHeader("Cookie", m_cookie_str));

										//http args
										std::vector<tools::HttpArg> http_args2;
										http_args2.push_back(tools::HttpArg("choice", choice));

										tools::HttpClient http_client2(Constants::ig_url + challenge_path, http_headers2, http_args2);
										tools::HttpResponse http_res2 = http_client2.send_post_req_urlencoded(mk_ig_http_body(http_args2));

										update_cookies(http_res2.m_cookies);

										if(http_res2.m_code == 200)
										{
											std::cout << "Successful login! The cookies are saved to " << m_file_cookies << "!" << std::endl;

											return true;
										}
									}
									else
										std::cerr << std::string("Error: The challenge response's field \"step_name\" does not have the value ") +
										"\"select_verify_method\" or \"delta_login_review\"." << std::endl;
								}
								else
									std::cerr << "Error: The challenge response does not have a field \"step_name\"." << std::endl;
							}
							else
								std::cerr << "Error: The challenge response is not a json object." << std::endl;
						}
						else
							std::cerr << "Error: Field \"challenge\" does not have field \"api_path\"." << std::endl;
					}
					else
						std::cerr << "Error: There is not field \"challenge\"." << std::endl;
				}
				else
					std::cerr << "Error: Field \"error_type\" does not have the value \"checkpoint_challenge_required\"." << std::endl;
			}
			else
				std::cerr << "Error: There is not field \"error_type\"." << std::endl;
		}
		else
			std::cerr << "Error: The given server response is not a json object." << std::endl;

		return false;
	}

	std::string Api::get_rank_token()
	{
		return get_cookie_val("ds_user_id") + "_" + m_uuid;
	}

	void Api::post_req_check(const std::string &server_resp)
	{
		rapidjson::Document doc;
		doc.Parse(server_resp.c_str());

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
				if(doc["message"].GetString() == std::string("challenge_required"))
				{
					std::cerr << "######################" << std::endl;
					std::cerr << "Warning!" << std::endl;
					std::cerr << "It seems that it is needed to solve a challenge manually. Log into your Instagram account in your browser " <<
							"and you should be requested to verify your identity." << std::endl;
					std::cerr << "######################" << std::endl;
				}
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
				if(doc["message"].GetString() == std::string("login_required"))
				{
					m_del_cookies_uuids = true;

					std::cerr << "######################" << std::endl;
					std::cerr << "Warning!" << std::endl;
					std::cerr << "A new login is required as you have been logged out." << std::endl;
					std::cerr << "######################" << std::endl;
				}
			}
		}
	}

	bool Api::login()
	{
		//requests that are done before the actual login
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

			update_cookies(http_res.m_cookies);

			if(http_res.m_code == 200)
			{
				std::cout << "Successful login! The cookies are saved to " << m_file_cookies << "!" << std::endl;

				return true;
			}
			else
			{
				std::cerr << "Error: The server response on the login request does not have status code 200." << std::endl;

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
							if(solve_challenge(http_res.m_body))
								return true;
							else
								std::cerr << "Error: The login challenge could not be solved." << std::endl;
						}
					}
				}
				return false;
			}
		}
		return true;
	}

	std::string Api::get_media_likers(const std::string &media_id)
	{
		//http headers
		std::vector<tools::HttpHeader> http_headers = get_ig_http_headers();
		http_headers.push_back(tools::HttpHeader("Cookie", m_cookie_str));

		tools::HttpClient http_client(Constants::ig_url + "media/" + media_id + "/likers/", http_headers);
		tools::HttpResponse http_res = http_client.send_get_req();

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

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

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

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
					for(size_t j = 0; j < comments.Size(); ++j)
					{
						result.append(tools::Tools::get_json_as_string(comments[j]));
						result.append(", ");
					}

					//perhaps, next page
					if(doc.HasMember("has_more_comments") && doc.HasMember("next_max_id"))
						response = get_media_comments(media_id, doc["next_max_id"].GetString());
					else
						break;
				}
				else
					break;
			}
			else
				break;
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

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

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

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

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

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

		return http_res.m_body;
	}

	std::string Api::get_media_id(const std::string &ig_post)
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
					return doc["media_id"].GetString();
				else
					return "Error: There is no field \"media_id\" in the json.";
			}
			else
				return "Error: The string is not a json object.";
		}
		else
			return "Error: This is not an Instagram post.";
	}

	bool Api::is_ig_post(const std::string &url)
	{
		if(url.find("https://www.instagram.com/p/") != std::string::npos)
		{
			tools::HttpClient http_client(url);
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
				if(doc.HasMember("comments_disabled"))
					comments_allowed = !(doc["comments_disabled"].GetBool());
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

					if(items.IsArray() && items.GetArray().Size() > 0)
					{
						const rapidjson::Value &media_info = items[0];

						if(media_info.HasMember("commenting_disabled_for_viewer"))
							comments_allowed = !(media_info["commenting_disabled_for_viewer"].GetBool());
					}
				}
			}
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
					return user["username"].GetString();
				else
					return "Error: There is no field \"username\" in the json.";
			}
			else
				return "Error: There is no field \"user\" in the json.";
		}
		else
			return "Error: The string is not a json object.";
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

				if(items.IsArray() && items.GetArray().Size() > 0)
				{
					const rapidjson::Value &media_info = items[0];

					if(media_info.HasMember("user"))
					{
						const rapidjson::Value &user = media_info["user"];

						if(user.HasMember("username"))
							return user["username"].GetString();
						else
							return "Error: There is no field \"username\" in the json.";
					}
					else
						return "Error: There is no field \"user\" in the json.";
				}
				else
					return "Error: The field \"items\" is not a json array of size greater than 0.";
			}
			else
				return "Error: There is no field \"items\" in the json.";
		}
		else
			return "Error: The string is not a json object.";
	}

	int Api::get_amnt_flwrs(const std::string &user_id)
	{
		std::string json = get_user_info(user_id);

		rapidjson::Document doc;
		doc.Parse(json.c_str());

		if(doc.IsObject())
			if(doc.HasMember("user"))
			{
				const rapidjson::Value &user = doc["user"];
				if(user.HasMember("follower_count"))
					return user["follower_count"].GetInt();
			}
		return 0;
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

		update_cookies(http_res.m_cookies);
		post_req_check(http_res.m_body);

		m_del_cookies_uuids = true;

		return http_res.m_body;
	}
}
