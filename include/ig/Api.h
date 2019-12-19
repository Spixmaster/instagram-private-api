#ifndef TGBOT_ENDPOINTS_H
#define TGBOT_ENDPOINTS_H

#include <string>
#include <memory>

//@brief represents the Instagram Api which interacts with the Instagram servers

namespace ig
{
	class Api
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<Api> ptr;

	private:
		//member variables
			//Instagram's login credentials
		std::string m_username;
		std::string m_password;
			//bool on which some actions depend
		bool m_new_login;
			//uuids which are needed for Instagram
		std::string m_phone_id;
		std::string m_uuid;
		std::string m_client_session_id;
		std::string m_advertising_id;
		std::string m_device_id;
			//all the cookies that are required by the Instagram servers
		std::string m_ds_user;
		std::string m_csrftoken;
		std::string m_shbid;
		std::string m_shbts;
		std::string m_rur;
		std::string m_ds_user_id;
		std::string m_rur;
		std::string m_urlgen;
		std::string m_sessionid;
		std::string m_mid;
		std::string m_rur;
		std::string m_rur;
		std::string m_final_cookies; //the cookie string for the proper header value

	public:
		//constructors
		//@param username: username for the Instagram login
		//@param password: password for the Instagram login
		Api(const std::string &username, const std::string &password);

		//member functions
	private:
		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: /
		 * @brief Set-Cookie: csrftoken, rur, mid
		 * @return server response
		 */
		std::string Api::read_msisdn_header() const;

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: /
		 * @brief Set-Cookie: csrftoken, rur, mid
		 * @return server response
		 */
		std::string Api::read_msisdn_header() const;
	};
}

#endif
