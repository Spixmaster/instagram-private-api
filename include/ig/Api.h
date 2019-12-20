#ifndef TGBOT_ENDPOINTS_H
#define TGBOT_ENDPOINTS_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"
#include "tools/http/HttpArg.h"

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
		std::string m_urlgen;
		std::string m_sessionid;
		std::string m_mid;
		std::string m_final_cookies; //the cookie string for the proper header value

	public:
		//constructors

		/*
		 * @param username: username for the Instagram login
		 * @param password: password for the Instagram login
		 */
		Api(const std::string &username, const std::string &password);

		//member functions
	private:
		/*
		 * @brief contains all the http headers which each request to the Instagram server should contain
		 * @return vecor of the headers
		 */
		std::vector<tools::HttpHeader> get_ig_http_headers() const;

		/*
		 * @brief Instagram only accepts very specific http bodies which the function provides
		 * @param http_args: the key value pairs which shall be contained in the request's http body
		 * @return the modified http body
		 */
		std::string mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const;

		/*
		 * @brief gets all uuids and cookie values from the cookie file
		 * @brief if it cannot get all necessary values it generates new ones and set m_new_login = true
		 * @brief also sets m_final_cookies
		 */
		void get_cookies_uuids_from_file();

		/*
		 * @brief goes through the headers and searches for the necessary cookies
		 * @brief searches for all cookies like the names of the member variables
		 * @brief assigns the values to the corresponding member variables
		 */
		void get_cookies_from_headers(const std::vector<tools::HttpHeader> &http_headers);

		/*
		 * @brief saves the cookies in the cookies file
		 * @brief saved are all member variables which represent cookie values
		 */
		void save_cookies_in_file() const;

		/*
		 * @brief all cookie values are concatenated for the header value for the cookie header
		 * @brief save in member variable m_final_cookies
		 */
		void save_whole_cookie();

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: /
		 * @brief Set-Cookie: csrftoken, rur, mid
		 * @return server response
		 */
		std::string read_msisdn_header();

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string launcher_sync();

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string qe_sync();

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string log_attribution();

		/*
		 * @brief the request is part of the login process
		 * @brief Cookie: csrftoken, rur, mid
		 * @brief Set-Cookie: csrftoken, rur (same as before)
		 * @return server response
		 */
		std::string contact_point_prefill();

		/*
		 * @brief on Instagram login it can occur that a challenge is required for fulfillment
		 * @param server_resp: the server response which contains the challenge
		 * @return true on success; otherwise false
		 */
		bool solve_challenge(const std::string &server_resp);

	public:
		/*
		 * @brief logs into Instagram
		 * @return true on success; otherwise false
		 */
		bool login();

		/*
		 * @brief gets all likers of an Instagram media
		 * @param media_id: the proper media id
		 * @return the server response
		 */
		std::string get_media_likers(const std::string &media_id);

		/*
		 * @brief gets all comments of an Instagram media
		 * @param media_id: the proper media id
		 * @param mas_id: todo noch keine Ahnung
		 * @return the server response
		 */
		std::string get_media_comments(const std::string &media_id, const std::string &max_id);
	};
}

#endif
