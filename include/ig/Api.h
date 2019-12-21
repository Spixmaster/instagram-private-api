#ifndef TGBOT_ENDPOINTS_H
#define TGBOT_ENDPOINTS_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"
#include "tools/http/HttpArg.h"
#include "tools/http/HttpCookie.h"

/*
 * @brief represents the Instagram Api which interacts with the Instagram servers
 * @brief the cookies need to be updated every time whenever an endpoint is called as even then cookies are set
 */

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
			//all the cookies which are sent by the Instagram servers
		std::vector<tools::HttpCookie> m_cookies;
		std::string m_cookie_str; //all cookies concatenated as key-value-pairs to be used as a header value

	public:
		//constructors
		/*
		 * @param username: username for the Instagram login
		 * @param password: password for the Instagram login
		 */
		Api(const std::string &username, const std::string &password);

		//destructors
		~Api();

		//member functions
	private:
		/*
		 * @brief contains all the http headers which each request to the Instagram server should contain
		 * @return vector of the headers
		 */
		std::vector<tools::HttpHeader> get_ig_http_headers() const;

		/*
		 * @brief Instagram only accepts very specific http bodies which the function provides
		 * @param http_args: the key value pairs which shall be contained in the request's http body
		 * @return the modified http body
		 */
		std::string mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const;

		/*
		 * @brief gets all uuids and cookie values from files
		 * @brief if it cannot get all necessary values it generates new ones and sets m_new_login = true
		 * @brief also sets m_cookie_str
		 */
		void setup_cookies_uuids();

		/*
		 * @brief with the given cookies the function updates the old as member variable saved cookies
		 * @param http_cookies: cookies with which the as member variable saved cookies shall be updated
		 */
		void update_cookies(const std::vector<tools::HttpCookie> &http_cookies);

		/*
		 * @brief saves the uuids in the proper file
		 * @brief saved are all member variables which represent uuids
		 */
		void save_uuids_in_file() const;

		/*
		 * @brief saves the cookies in the proper file
		 * @brief saved are all member variables which represent cookie values
		 */
		void save_cookies_in_file() const;

		/*
		 * @brief all cookie values are concatenated for the header value for the cookie header
		 * @brief the cookie values are got from the member variable m_cookies
		 * @brief saved in member variable m_cookie_str
		 */
		void set_cookie_str();

		/*
		 * @brief gets the value of the cookie
		 * @param name: the name of the cookie whose value we want
		 * @return the cookie value
		 */
		std::string get_cookie_val(const std::string &cookie_name) const;

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
		std::string get_media_comments(const std::string &media_id, const std::string &max_id="");
	};
}

#endif
