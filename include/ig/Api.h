#ifndef IG_API_H
#define IG_API_H

#include <string>
#include <memory>
#include <vector>
#include "tools/http/HttpHeader.h"
#include "tools/http/HttpArg.h"
#include "tools/http/HttpCookie.h"
#include "ig/devices/Device.h"
#include "Constants.h"
#include "tools/http/HttpResponse.h"

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
			//devices
		Device::ptr m_device;
			//session values(cookies, app info)
		std::string m_file_app_info;
		std::string m_file_cookies;
			/*
			 * whether cookies and app info file are deleted when destructor is called
			 * this is necessary as when these files are deleted immediately the functions save_app_info_in_file() and save_cookies_in_file()
			 * will undo the deletion because they save the files again
			 */
		bool m_del_cookies_uuids;
			//bool on which some actions depend
		bool m_new_login;
			//app info
		std::string m_phone_id;
		std::string m_uuid;
		std::string m_client_session_id;
		std::string m_advertising_id;
		std::string m_device_id;
		long long m_last_login = 0;
		long long m_last_experiments = 0;
		std::string m_useragent;
			//all the cookies which are sent by the Instagram servers
		std::vector<tools::HttpCookie> m_cookies;
		std::string m_cookie_str; //all cookies concatenated as key-value-pairs to be used as a header value

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
		 * @brief gets all app info and cookie values from files
		 * @brief if it cannot get all necessary values it generates new ones and sets m_new_login = true
		 * @brief also sets m_cookie_str
		 */
		void setup_cookies_app_info();

		/*
		 * @brief with the given cookies the function updates the old as member variable saved cookies
		 * @brief it also updates m_cookie_str and the two files (cookie and app info file)
		 * @param http_cookies: cookies with which the as member variable saved cookies shall be updated
		 */
		void update_data(const std::vector<tools::HttpCookie> &http_cookies);

		//@brief saves the proper member variables in the proper file
		void save_app_info_in_file() const;

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

		//##############################pre login request##############################
		/*
		 * @brief the request is part of the login process
		 * @param usage: defines part of the http body
		 * @return server response
		 */
		std::string read_msisdn_header(const std::string &usage);

		/*
		 * @brief the request is part of the login process
		 * @param login: the http body depends on it
		 * @return server response
		 */
		std::string launcher_sync(const bool &login);

		/*
		 * @brief the request is part of the login process
		 * @param login: the http body depends on it
		 * @return server response
		 */
		std::string sync_device_features(const bool &login);

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string log_attribution();

		/*
		 * @brief the request is part of the login process
		 * @param usage: defines part of the http body
		 * @return server response
		 */
		std::string contact_point_prefill(const std::string &usage);

		//@brief makes all http requests which are necessary before the actual login
		void pre_login_requests();

		//##############################post login requests##############################
		/*
		 * @brief the request is part of the login process
		 * @param login: adds some data to the http body
		 * @return server response
		 */
		std::string sync_launcher(const bool &login);

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string sync_user_features();

		/*
		 * @brief the request is part of the login process
		 * @param is_pull_to_refresh: would be part of the http body
		 * @param push_disabled: would be part of the http body
		 * @param recovered_from_crash: would be part of the http body
		 * @return server response
		 */
		std::string get_timeline_feed(const bool &is_pull_to_refresh, const bool &push_disabled, const bool &recovered_from_crash);

		/*
		 * @brief the request is part of the login process
		 * @param reason: possible values are "cold_start" and "pull_to_refresh"
		 * @return server response
		 */
		std::string get_reels_tray_feed(const std::string &reason);

		/*
		 * @brief the request is part of the login process
		 * @param type: search term
		 * @return server response
		 */
		std::string get_suggested_searches(const std::string &type);

		/*
		 * @brief the request is part of the login process
		 * @param mode: part of the http body, possible "reshare", "save"
		 * @param show_threads: part of the http body
		 * @param query: part of the http body
		 * @return server response
		 */
		std::string get_ranked_recipients(const std::string &mode, const bool &show_threads, const std::string &query = "");

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string get_inbox_v2();

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string get_presence();

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string get_recent_activity();

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string get_loom_fetch_config();

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string get_profile_notice();

		/*
		 * @brief the request is part of the login process
		 * @return server response
		 */
		std::string batch_fetch();

		/*
		 * @brief the request is part of the login process
		 * @param is_prefetch: part of the http body
		 * @return server response
		 */
		std::string explore(const bool &is_prefetch);

		/*
		 * @brief makes all http requests which are necessary after the actual login
		 * @brief simulates that the app is opened
		 */
		void open_app(const bool &recent_login);
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

		/*
		 * @brief on Instagram login it can occur that a challenge is required for fulfillment
		 * @param server_resp: the server response which contains the challenge
		 * @return true on success; otherwise false
		 */
		bool solve_challenge(const std::string &server_resp);

		/*
		 * @brief the rank token is assembled out of the user id an the uuid
		 * @return the rank token
		 */
		std::string get_rank_token();

		/*
		 * @brief on every request Instagram can respond with error messages --> this function catches and handles them
		 * @param server_resp: the server response
		 */
		void post_req_check(const tools::HttpResponse &server_resp);

		/*
		 * @brief logs into Instagram
		 * @return true on success; otherwise false
		 */
		bool login();

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
		std::string get_media_comments(const std::string &media_id, const std::string &max_id="");

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
		static std::string get_media_id(const std::string &ig_post);

		/*
		 * @brief checks whether url is a valid Instagram post
		 * @param url: url to Instagram post
		 * @return true when valid Instagram link
		 */
		static bool is_ig_post(const std::string &url);

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
