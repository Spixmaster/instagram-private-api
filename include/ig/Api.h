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

/**
 * @mainpage instagram-private-api
 * @author Matheus Gabriel Werny de Lima
 * @copyright GNU General Public License v2.0
 * @version
 * 0.5.13 (23.05.2020)
 * - Submodule update.
 * - Contributing update.
 * @version
 * 0.5.12 (22.05.2020)
 * - Submodule updated.
 * @version
 * 0.5.11 (17.05.2020)
 * - Comment updated.
 * @version
 * 0.5.10 (15.05.2020)
 * - Submodule update.
 * @version
 * 0.5.9 (15.05.2020)
 * - Contributing updated.
 * - Readme updated.
 * - Submodule updated.
 * @version
 * 0.5.8 (11.05.2020)
 * - Submodule and readme update.
 * @version
 * 0.5.7 (01.05.2020)
 * - Regenerated the documentation.
 * @version
 * 0.5.6 (29.04.2020)
 * - Updated the contributing file.
 * - Submodule updated.
 * @version
 * 0.5.5 (29.04.2020)
 * - Submodule updated.
 * @version
 * 0.5.4 (28.04.2020)
 * - Submodule updated.
 * @version
 * 0.5.3 (28.04.2020)
 * - Updated the README.md.
 * @version
 * 0.5.2 (28.04.2020)
 * - Updated the README.md.
 * @version
 * 0.5.1 (28.04.2020)
 * - Updated the README.md.
 * @version
 * 0.5.0 (27.04.2020)
 * - Made the get_media_likers() function more secure.
 * - Revision of the whole code.
 * - Adjusted all comments to fit the Doxygen syntax.
 */

namespace ig
{
	/**
	 * @class Api
	 * @brief This class represents the Instagram API which interacts with the Instagram servers.
	 * @note The cookies need to be updated whenever an endpoint is called as even then cookies are set.
	 * @note Every function that calls post_req_check cannot be "noexcept".
	 * @note Every "feed/timeline/" call needs to set the most recent seen media id.
	 */
	class Api
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<Api> ptr;

	private:
		//Member variables
		//Instagram's login credentials
		/**
		 * @var m_username
		 * @brief The account's username.
		 */
		std::string m_username;
		/**
		 * @var m_password
		 * @brief The account's password.
		 */
		std::string m_password;
		//Files
		/**
		 * @var m_file_app_info
		 * @brief It is a file path to a file which contains general information that needs to be saved.
		 */
		std::string m_file_app_info;
		/**
		 * @var m_file_cookies
		 * @brief It is a file path to a file which contains all the cookies.
		 */
		std::string m_file_cookies;
		/**
		 * @var m_device
		 * @brief Device which makes the request.
		 */
		Device::ptr m_device;
		/**
		 * @var m_del_app_info_and_cookies
		 * @brief The boolean decides whether the cookies and app information files are deleted when the destructor is called.
		 * @note This is necessary because when this is done during the life time of the class the cookies and app information will later still be saved and thus the deletion was pointless.
		 */
		bool m_del_app_info_and_cookies;
		/**
		 * @var m_new_login
		 * @brief The boolean states if a new login is required.
		 */
		bool m_new_login;
		//App info
		//HTTP header values
		/**
		 * @var m_x_google_ad_id
		 * @brief The value for a header. It is the Google ad id.
		 * @note The alternative header name is "adid".
		 */
		std::string m_x_google_ad_id;
		/**
		 * @var m_x_pigeon_session_id
		 * @brief The value for a header. The pigeon session id. I do not know what it is exactly.
		 */
		std::string m_x_pigeon_session_id;
		/**
		 * @var m_x_ig_device_id
		 * @brief The value for a header.
		 * @note The alternative header name is "X-DEVICE-ID".
		 */
		std::string m_x_ig_device_id;
		/**
		 * @var m_x_ig_android_id
		 * @brief The value for a header.
		 */
		std::string m_x_ig_android_id;
		/**
		 * @var m_useragent
		 * @brief The useragent from our mobile device.
		 */
		std::string m_useragent;
		//Only known after successful login.
		/**
		 * @var m_x_ig_www_claim
		 * @brief The value for a header.
		 * @details Default: "0".
		 */
		std::string m_x_ig_www_claim;
		/**
		 * @var m_authorization
		 * @brief The value for a header.
		 * @details Default: "Bearer IGT:2:".
		 */
		std::string m_authorization;
		//HTTP body values
		/**
		 * @var m_phone_id
		 * @brief The phone id.
		 * @note The alternative name is "family_device_id"
		 */
		std::string m_phone_id;
		//Only known after "/feed/timeline/" called.
		/**
		 * @var m_last_seen_feed_media_id
		 * @brief The last seen media id.
		 * @details When the endpoint "/feed/timeline/" is called the most recent media in the feed is saved.
		 * @details The next time when calling that endpoint that value is sent.
		 */
		std::string m_last_seen_feed_media_id;
		//Rest
		/**
		 * @var m_last_app_opening
		 * @brief It is a Unix time value and states the last time time when the app was opened.
		 * @details An app opening is not simulated every time the object is constructed.
		 * @details This happens only after a certain time span after the last app opening.
		 */
		long long m_last_app_opening = 0;
		/**
		 * @var m_cookies
		 * @brief All the cookies which are sent by the Instagram servers.
		 */
		std::vector<tools::HttpCookie> m_cookies;
		/**
		 * @var m_cookie_str
		 * @brief All cookies concatenated as key-value-pairs to be used as a header value.
		 */
		std::string m_cookie_str;

	public:
		//Constructors
		/**
		 * @param[in] username The username for the Instagram login.
		 * @param[in] password The password for the Instagram login.
		 * @param[in] files_folder The folder where the files shall be saved.
		 */
		Api(const std::string &username, const std::string &password, const std::string &files_folder);

		//Destructors
		~Api();

		//Member functions
	private:
		/**
		 * @brief Gets all app info and cookie values from the files and assigns them to the member variables.
		 * @details If the function cannot get all necessary values, it generates new ones and sets m_new_login to true.
		 * @details It also sets m_cookie_str.
		 */
		void setup_app_info_and_cookies() noexcept;

		/**
		 * @brief Contains the HTTP headers for the Instagram servers.
		 * @return A vector in which each element represents one HTTP header.
		 */
		std::vector<tools::HttpHeader> get_ig_http_headers() const noexcept;

		/**
		 * @brief Instagram accepts very specific HTTP bodies most of the times. This function provides them.
		 * @param[in] http_args The key value pairs which shall be contained in the request's HTTP body.
		 * @return The modified HTTP body.
		 */
		std::string mk_ig_http_body(const std::vector<tools::HttpArg> &http_args) const noexcept;

		/**
		 * @brief The app information in saved in a file.
		 * @details The app information is stored in member variables.
		 */
		void save_app_info_in_file() const noexcept;

		/**
		 * @brief Saves the cookies in the a file.
		 * @details The cookies are stored in a member variable.
		 */
		void save_cookies_in_file() const noexcept;

		/**
		 * @brief The function concatenates all cookie values to one string which can then be used as the header value.
		 * @details The result is assigned to the suitable member variable.
		 */
		void set_cookie_str() noexcept;

		/**
		 * @brief This function updates the currently saved cookies and the cookies and app information file.
		 * @details The member variable which saves the cookies string is also updated.
		 * @param[in] http_cookies The cookies with which the as member variable saved cookies shall be updated.
		 */
		void update_data(const std::vector<tools::HttpCookie> &http_cookies) noexcept;

		/**
		 * @brief Gets the value of the passed cookie key.
		 * @param[in] name The name of the cookie whose value we want.
		 * @return The cookie value.
		 */
		std::string get_cookie_val(const std::string &cookie_name) const noexcept;

		/*
		 * @brief This function returns the value which is needed by the login endpoint.
		 * @details It is the sum of the chars of the phone id which is sent too.
		 * @return The jazoest value.
		 */
		std::string get_jazoest() const noexcept;

		/**
		 * @brief It returns the rank token for our account.
		 * @details The rank token is assembled out of the user id and the device id.
		 * @return The rank token.
		 */
		std::string get_rank_token() const noexcept;

		/**
		 * @brief The last media id that was seen in the feed is needed for future feed requests. This function saves it.
		 * @details The value is got from the response of the endpoint "/api/v1/feed/timeline/".
		 * @param[in] last_feed_timeline The JSON object of last call of "/api/v1/feed/timeline/".
		 */
		void set_last_seen_feed_media_id(const std::string &last_feed_timeline) noexcept;

		/**
		 * @brief Creates the field data for "feed_view_info" for the "/feed/timeline/" endpoint.
		 * @return The field content.
		 */
		std::string get_feed_view_info() const noexcept;

		/**
		 * @brief On every request Instagram can respond with error messages. This function catches and handles them.
		 * @brief Additionally, it manages a log with a certain number of the last requests.
		 * @param[in] http_client The HTTP client which sent the request. It is needed for the log functionality.
		 * @param[in] server_resp The server response.
		 * @param[in] no_throw If true, no exception is thrown.
		 */
		void post_req_check(const tools::HttpClient &http_client, const tools::HttpResponse &server_resp, const bool &no_throw = false);

		/*
		 * These requests occur when the Instagram app is opened but no one is logged in yet.
		 * If someone is logged in and the app is opened these requests are not made.
		 */
		//Pre login requests
		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string accounts_contact_point_prefill();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string qe_sync();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string accounts_get_prefill_candidates();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string launcher_sync();


		/**
		 * @brief Makes all pre login HTTP requests.
		 * @return The server response.
		 */
		void pre_login_requests();

		/*
		 * The login endpoint and possibly a challenge too.
		 * Login requests.
		 */
		/**
		 * @brief Logs into Instagram.
		 * @return True on success, otherwise false.
		 */
		bool login();

		/**
		 * @brief During the Instagram login it can occur that a challenge is required as a security measure.
		 * @param[in] server_resp The server response of the failed login endpoint which contains the challenge.
		 * @return True on success, otherwise false.
		 */
		bool solve_challenge(const std::string &server_resp);

		//Post login requests
		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string multiple_accounts_get_account_family();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string banyan_banyan();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string feed_reels_tray();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string feed_timeline();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
//		std::string push_register();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string media_blocked();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string loom_fetch_config();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string scores_bootstrap_users();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string business_eligibility_get_monetization_products_eligibility_data();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string linked_accounts_get_linkage_status();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string business_branded_content_should_require_professional_account();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string news_inbox();
		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string qp_get_cooldowns();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string accounts_process_contact_point_signals();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string users_x_info();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string direct_v2_get_presence();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string status_get_viewable_statuses();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string direct_v2_inbox();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string qp_batch_fetch();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string notifications_badge();

		/**
		 * @brief An HTTP request.
		 * @return The server response.
		 */
		std::string discover_topical_explore();

		/**
		 * @brief Makes all HTTP requests which are made when the app is opened.
		 */
		void post_login_requests();

		/*
		 * App opening
		 * A few less requests are made compared to the post login process
		 */
		/**
		 * @brief Makes all HTTP requests which are sent when the app is opened.
		 */
		void open_app();
	public:
		/**
		 * @brief Gets all likers of the Instagram media.
		 * @param[in] media_id The proper media id.
		 * @return The server response.
		 */
		std::string get_media_likers(const std::string &media_id);

		/**
		 * @brief Gets the comments of the Instagram media.
		 * @details Only a part of all comments is shown.
		 * @details Normally, the function is called without max_id.
		 * @details If there are more possible comments to show, the field exists: ""has_more_comments":true".
		 * @details The following attribute will be set:
		 * @details "next_max_id":"{\"server_cursor\": \"QVFDNHZuUmxaTFJzeHJSQ0UyejVwcGFpXzBOWGVHQXpfeTNhalVOS1lUTUFrRWZuaHBoakFBbXlVWEV1ejE4aWFGLXZPS29TZUI4c3F5dXl1RHZULVZ2Wg==\",\"is_server_cursor_inverse\": false}"
		 * @details Use that value for max_id to receive the next page of comments.
		 * @note The pagination does not work like: 1, 2, 3,...
		 * @param[in] media_id The proper media id.
		 * @param[in] max_id For pagination.
		 * @return The server response.
		 */
		std::string get_media_comments(const std::string &media_id, const std::string &max_id = "");

		/**
		 * @brief Gets all comments of the Instagram media.
		 * @details The returned string are several modified server responses.
		 * @param[in] media_id The proper media id.
		 * @return The server response.
		 */
		std::string get_media_comments_all(const std::string &media_id);

		/**
		 * @brief Gets the available information about the Instagram media.
		 * @param[in] media_id The proper media id.
		 * @return The server response.
		 */
		std::string get_media_info(const std::string &media_id);

		/**
		 * @brief Gets the user feed which is the media the user uploaded.
		 * @details Normally, the function is called without max_id.
		 * @param[in] user_id The proper user id.
		 * @param[in] max_id For pagination. Use the field value of "next_max_id" that was sent when making the request without max id.
		 * @param[in] min_timestamp No idea.
		 * @return The server response.
		 */
		std::string get_user_feed(const std::string &user_id, const std::string &max_id = "", const std::string &min_timestamp = "");

		/**
		 * @brief Gets the available user info.
		 * @param[in] user_id The proper user id.
		 * @return The server response.
		 */
		std::string get_user_info(const std::string &user_id);

		/**
		 * @brief Gets the media id of an Instagram post.
		 * @param[in] ig_post The URL to the Instagram post.
		 * @return The media id.
		 * @retval "" An error occurred.
		 */
		static std::string get_media_id(const std::string &ig_post) noexcept;

		/**
		 * @brief Checks whether the URL is a valid Instagram post.
		 * @param[in] url The URL to the Instagram post.
		 * @return Returns true when it is a valid Instagram link.
		 */
		static bool is_ig_post(const std::string &url) noexcept;

		/**
		 * @brief Looks whether comments are allowed for the Instagram post.
		 * @param[in] media_id States the media which we want to check.
		 * @return Returns true when comments are allowed, otherwise false.
		 */
		bool media_comments_allowed(const std::string &media_id);

		/**
		 * @brief Gets the Instgram username of an Instagram profile.
		 * @param[in] user_id The Instagram user id which leads to the Instagram username.
		 * @return The Instagram username.
		 * @retval "" An error occurred.
		 */
		std::string get_username_from_user_id(const std::string &user_id);

		/**
		 * @brief Gets the Instgram username from a media id.
		 * @param[in] media_id The proper media id.
		 * @return The Instagram username.
		 * @retval "" An error occurred.
		 */
		std::string get_username_from_media_id(const std::string &media_id);

		/**
		 * @brief Gets the amount of followers.
		 * @param[in] user_id The id of the user from whom we want the follower amount.
		 * @return The amount of followers.
		 * @retval -1 An error occurred.
		 */
		int get_amnt_flwrs(const std::string &user_id);

		/**
		 * @brief Gets the user id from a media id.
		 * @param[in] media_id The proper media id.
		 * @return The user id.
		 */
		std::string get_user_id_from_media_id(const std::string &media_id);

		/**
		 * @brief Logs out which means that the session with its corresponding cookies will no longer be usable.
		 * @details This results in all files getting deleted upon object destruction.
		 * @note After that no request can be made with that object anymore.
		 * @return The server response.
		 */
		std::string logout();
	};
}

#endif
