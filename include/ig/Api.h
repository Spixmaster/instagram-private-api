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
		 * @brief Instagram only accepts very specific http bodies which the function provides
		 * @param http_args: the key value pairs which shall be contained in the request's http body
		 * @return the modified http body
		 */
		std::string Api::mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const;

		/*
		 * @brief contains all the http headers which each request to the Instagram server should contain
		 * @return vecor of the headers
		 */
		std::vector<tools::HttpHeader> Api::get_ig_http_headers() const;

		/*
		 * @brief gets all uuids and cookie values from the cookie file
		 * @brief if it cannot get all necessary values it generates new ones and set m_new_login = true
		 * @brief also sets m_final_cookies
		 */
		void Api::get_cookies_uuids();

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: /
		 * @brief Set-Cookie: csrftoken, rur, mid
		 * @return server response
		 */
		std::string Api::read_msisdn_header() const;

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string Api::launcher_sync() const;

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string Api::qe_sync() const;

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string Api::log_attribution() const;

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string Api::contact_point_prefill() const;

	public:
		bool login();
	};
}

#endif
