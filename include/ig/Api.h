#ifndef IG_API_H
#define IG_API_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"
#include "tools/http/HttpArg.h"
#include "tools/http/HttpCookie.h"
#include "ig/devices/Device.h"
#include "tools/http/HttpResponse.h"
#include "tools/http/HttpClient.h"

/*
 * @brief represents the Instagram Api which interacts with the Instagram servers
 * @brief the cookies need to be updated every time whenever an endpoint is called as even then cookies are set
 * @brief EVERY FUNCTION THAT CALLS post_req_check CANNOT BE NOEXCEPT
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
			//device which makes the request
		Device::ptr m_device;
			//files which contain the session values - cookies and app info is important data and general information I want to save
		std::string m_file_app_info;
		std::string m_file_cookies;
			/*
			 * whether cookies and app info file are deleted when destructor is called
			 * this is necessary as when these files are deleted immediately the functions save_app_info_in_file() and save_cookies_in_file()
			 * will undo the deletion because they save the files again
			 */
		bool m_del_cookies_uuids;
			/*
			 * whether the user logs in and thus no cookies are available
			 * bool on which some actions depend
			 */
		bool m_new_login;
			//app info todo order changed
		std::string m_x_pigeon_session_id;
		std::string m_x_ig_device_id; //alternative header name "X-DEVICE-ID"
		std::string m_x_ig_android_id;
		std::string m_phone_id;//alternative name family_device_id
		std::string m_uuid;
		std::string m_client_session_id;
		std::string m_advertising_id;
		long long m_last_login = 0;
		long long m_last_experiments = 0;
		std::string m_useragent;
		std::string m_request_id;//for feed_timeline
		std::string m_session_id;//for feed_timeline
			//all the cookies which are sent by the Instagram servers
		std::vector<tools::HttpCookie> m_cookies;
			//all cookies concatenated as key-value-pairs to be used as a header value
		std::string m_cookie_str;

	public:
		//constructors
		/*
		 * @param username: username for the Instagram login
		 * @param password: password for the Instagram login
		 * @param files_path: folder where the files shall be saved; with trailing "/"
		 */
		Api(const std::string &username, const std::string &password, const std::string &files_path);

		//destructors
		~Api();

		//member functions
	private:
		/*
		 * @brief contains the http headers for the Instagram servers
		 * @param x_device_id: whether this header shall be included
		 * @param x_ig_www_claim: whether this header shall be included
		 * @param authorization: whether this header shall be included
		 * @return vector of the headers
		 */
		std::vector<tools::HttpHeader> get_ig_http_headers(const bool &x_device_id, const bool &x_ig_www_claim, const bool &authorization) const noexcept;

		/*
		 * @brief Instagram mostly only accepts very specific http bodies which the function provides
		 * @param http_args: the key value pairs which shall be contained in the request's http body
		 * @return the modified http body
		 */
		std::string mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const noexcept;

		/*
		 * @brief gets all app info and cookie values from files
		 * @brief if it cannot get all necessary values it generates new ones and sets m_new_login = true
		 * @brief also sets m_cookie_str
		 */
		void setup_cookies_and_app_info() noexcept;

		/*
		 * @brief with the given cookies the function updates the old as member variable saved cookies
		 * @brief it also updates m_cookie_str and the two files (cookie and app info file)
		 * @param http_cookies: cookies with which the as member variable saved cookies shall be updated
		 */
		void update_data(const std::vector<tools::HttpCookie> &http_cookies) noexcept;

		//@brief saves the proper member variables in the proper file
		void save_app_info_in_file() const noexcept;

		/*
		 * @brief saves the cookies in the proper file
		 * @brief saved are all member variables which represent cookie values
		 */
		void save_cookies_in_file() const noexcept;

		/*
		 * @brief all cookie values are concatenated for the header value for the cookie header
		 * @brief the cookie values are got from the member variable m_cookies
		 * @brief saved in member variable m_cookie_str
		 */
		void set_cookie_str() noexcept;

		/*
		 * @brief gets the value of the cookie
		 * @param name: the name of the cookie whose value we want
		 * @return the cookie value
		 */
		std::string get_cookie_val(const std::string &cookie_name) const noexcept;

		/*
		 * these requests occur when the Instagram app is opened but no one is logged in yet
		 * if someone is logged in and the app is opened these requests are not made
		 */
		//##############################pre login request##############################
		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string accounts_get_prefill_candidates();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string qe_sync();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string launcher_sync();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string accounts_contact_point_prefill();

		//@brief makes all pre login http requests
		void pre_login_requests();

		//of course the login endpoint and possibly a challenge too
		//##############################login requests##############################
		/*
		 * @brief logs into Instagram
		 * @return true on success; otherwise false
		 */
		bool login();

		/*
		 * @brief on Instagram login it can occur that a challenge is required for fulfillment
		 * @param server_resp: the server response which contains the challenge
		 * @return true on success; otherwise false
		 */
		bool solve_challenge(const std::string &server_resp);

		/*
		 * after successful login
		 * like a normal opening of the app
		 */
		//##############################post login requests##############################
		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string launcher_sync();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string multiple_accounts_get_account_family();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string qe_sync();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string launcher_sync();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string qe_sync();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string zr_token_result();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string banyan_banyan();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string feed_timeline();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string feed_reels_tray();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string push_register();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string media_blocked();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string news_inbox();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string scores_bootstrap_users();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string loom_fetch_config();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string business_eligibility_get_monezization_products_eligibility_data();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string linked_accounts_get_linkage_status();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string business_branded_content_should_require_professional_account();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string qp_get_cooldowns();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string users_arlink_download_info();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string push_register();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string users_x_info();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string attribution_log_resurrect_attribution();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string creatives_write_supported_capabilities();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string notifications_store_client_push_permissions();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string accounts_process_contact_point_signals();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string direct_v2_get_presence();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string qp_batch_fetch();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string status_get_viewable_statuses();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string direct_v2_inbox();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string direct_v2_inbox();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string notifications_badge();

		/*
		 * @brief an http request
		 * @return server response
		 */
		std::string discover_topical_explore();

		/*
		 * @brief makes all http requests which are necessary after the actual login
		 * @brief simulates that the app is opened
		 */
		void open_app(const bool &recent_login);
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

		/*
		 * @brief the rank token is assembled out of the user id an the uuid
		 * @return the rank token
		 */
		std::string get_rank_token() noexcept;

		/*
		 * @brief on every request Instagram can respond with error messages --> this function catches and handles them
		 * @brief manages a log with a certain number of the last requests
		 * @param http_client: needed for the log functionality
		 * @param server_resp: the server response
		 */
		void post_req_check(const tools::HttpClient &http_client, const tools::HttpResponse &server_resp);

	public:
		/*
		 * @brief gets all likers of the Instagram media
		 * @param media_id: the proper media id
		 * @return the server response
		 */
		std::string get_media_likers(const std::string &media_id);

		/*
		 * @brief gets the comments of the Instagram media
		 * @brief only a part of all comments is shown
		 * @brief Normally, the function is called without max_id. If there are more possible comments to show ("has_more_comments":true,)
		 * 		the following attribute will be set:
		 * 		"next_max_id":"{\"server_cursor\": \"QVFDNHZuUmxaTFJzeHJSQ0UyejVwcGFpXzBOWGVHQXpfeTNhalVOS1lUTUFrRWZuaHBoakFBbXlVWEV1ejE4aWFGLXZPS29TZUI4c3F5dXl1RHZULVZ2Wg==\",
		 * 		\"is_server_cursor_inverse\": false}",
		 * 		Use that value for max_id to receive the next "page". The pagination does not work like: 1, 2, 3,...
		 * @param media_id: the proper media id
		 * @param max_id: for pagination
		 * @return the server response
		 */
		std::string get_media_comments(const std::string &media_id, const std::string &max_id = "");

		/*
		 * @brief gets the comments of the Instagram media
		 * @brief it requests all comments by concatenating every page of the comments
		 * @brief the returned string are several modified server responses
		 * @param media_id: the proper media id
		 * @param max_id: for pagination
		 * @return the server response
		 */
		std::string get_media_comments_all(const std::string &media_id);

		/*
		 * @brief gets the available information about the Instagram media
		 * @param media_id: the proper media id
		 * @return the server response
		 */
		std::string get_media_info(const std::string &media_id);

		/*
		 * @brief gets the user feed --> the medias the user uploaded
		 * @brief Normally, the function is called without max_id. If there are more possible comments to show ("has_more_comments":true,)
		 * 		the following attribute will be set:
		 * 		"next_max_id":"{\"server_cursor\": \"QVFDNHZuUmxaTFJzeHJSQ0UyejVwcGFpXzBOWGVHQXpfeTNhalVOS1lUTUFrRWZuaHBoakFBbXlVWEV1ejE4aWFGLXZPS29TZUI4c3F5dXl1RHZULVZ2Wg==\",
		 * 		\"is_server_cursor_inverse\": false}",
		 * 		Use that value for max_id to receive the next "page". The pagination does not work like: 1, 2, 3,...
		 * @param user_id: the proper user id
		 * @param max_id: for pagination
		 * @param min_timestamp: todo no idea
		 * @return the server response
		 */
		std::string get_user_feed(const std::string &user_id, const std::string &max_id = "", const std::string &min_timestamp = "");

		/*
		 * @brief gets the available user info
		 * @param user_id: the proper user id
		 * @return the server response
		 */
		std::string get_user_info(const std::string &user_id);

		/*
		 * @brief gets media id of an Instagram post
		 * @param ig_post: url to Instagram post
		 * @return when error "Error:"
		 * @return media id
		 */
		static std::string get_media_id(const std::string &ig_post) noexcept;

		/*
		 * @brief checks whether url is a valid Instagram post
		 * @param url: url to Instagram post
		 * @return true when valid Instagram link
		 */
		static bool is_ig_post(const std::string &url) noexcept;

		/*
		 * @brief looks whether comments are allowed for the Instagram post
		 * @param media_id: states media which we want to check
		 * @return true when comments are allowed; otherwise false
		 */
		bool media_comments_allowed(const std::string &media_id);

		/*
		 * @brief gets Instgram username of an Instagram profile
		 * @param user_id: Instagram user id which leads to the Instagram username
		 * @return on error: "Error:"
		 * @return Instagram username
		 */
		std::string get_username_from_user_id(const std::string &user_id);

		/*
		 * @brief gets Instgram username from a media
		 * @param media_id: proper media id
		 * @return Instagram username
		 */
		std::string get_username_from_media_id(const std::string &media_id);

		/*
		 * @brief gets amount of followers
		 * @param user_id: from which we want the follower amount
		 * @return by default, returns 0
		 * @return amount of followers
		 */
		int get_amnt_flwrs(const std::string &user_id);

		/*
		 * @brief get the user id from a media
		 * @param media: proper media id
		 * @return user id
		 */
		std::string get_user_id_from_media_id(const std::string &media_id);

		/*
		 * @brief logs out which means that the session with its corresponding cookies will not longer be usable
		 * @return the server response
		 */
		std::string logout();
	};
}

#endif
