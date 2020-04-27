#ifndef IG_CONSTANTS_MESSAGES_H
#define IG_CONSTANTS_MESSAGES_H

#include <string>
#include <memory>

namespace ig
{
	/**
	 * @class Messages
	 * @brief This class contains messages which are used throughout the programme.
	 * @details it is a monostate.
	 */
	class Messages
	{
	public:
		//Pointer of itself
		/**
		 * @var ptr
		 * @brief A pointer of itself.
		 */
		typedef std::shared_ptr<Messages> ptr;

		//Member variables
		/**
		 * @var no_cookies_found
		 * @brief Message that no cookies were found.
		 */
		static const std::string no_cookies_found;
		/**
		 * @var wrong_choice_try_again
		 * @brief Message that the user input was wrong.
		 */
		static const std::string wrong_choice_try_again;
		/**
		 * @var hints_from_last_server_response
		 * @brief Message that states that there is following information.
		 */
		static const std::string hints_from_last_server_response;
		/**
		 * @var server_respone_not_json_obj
		 * @brief Message that the server response is not an JSON object.
		 */
		static const std::string server_respone_not_json_obj;
		/**
		 * @var server_respone_not_json_arr
		 * @brief Message that the server response is not an JSON array.
		 */
		static const std::string server_respone_not_json_arr;
		/**
		 * @var challenge_not_solved
		 * @brief Message that the challenge was not solved.
		 */
		static const std::string challenge_not_solved;
		/**
		 * @var not_ig_post
		 * @brief Message that it is not a link to an Instagram post.
		 */
		static const std::string not_ig_post;
		/**
		 * @var new_login_required_as_logged_out
		 * @brief Message that a new login is required as the account was logged out.
		 */
		static const std::string new_login_required_as_logged_out;
		/**
		 * @var acc_soft_ban
		 * @brief Message that the account was probably soft banned.
		 */
		static const std::string acc_soft_ban;
		/**
		 * @var manual_challenge
		 * @brief Message that a challenge needs to be done manually.
		 */
		static const std::string manual_challenge;
		/**
		 * @var phone_number
		 * @brief Contains the word for "phone number".
		 */
		static const std::string phone_number;
		/**
		 * @var email
		 * @brief Contains the word for "Email".
		 */
		static const std::string email;
		/**
		 * @var verify_login
		 * @brief This message is used when during the login process a verification is needed.
		 */
		static const std::string verify_login;
		/**
		 * @var your_choice_inp
		 * @brief Contains the word for "Your choice: ". The colon an space are needed as an input follows.
		 */
		static const std::string your_choice_inp;
		/**
		 * @var ver_code_sent
		 * @brief Message that says that the verification code was sent.
		 */
		static const std::string ver_code_sent;
		/**
		 * @var prompt_ver_code_inp
		 * @brief Message that prompt the user to input the verification code.
		 */
		static const std::string prompt_ver_code_inp;
		/**
		 * @var was_it_you
		 * @brief This is a message that is sent on a challenge to approve the recent login.
		 */
		static const std::string was_it_you;
		/**
		 * @var it_was_me
		 * @brief Contains the sentence "It was me.".
		 */
		static const std::string it_was_me;
		/**
		 * @var it_was_not_me
		 * @brief Contains the sentence "It was not me.".
		 */
		static const std::string it_was_not_me;

		//Member functions
		/**
		 * @brief The message states that the field has no value in the file.
		 * @param[in] field The field has no value.
		 * @param[in] file The file in which the field has no value.
		 * @return The message.
		 */
		static std::string field_no_value_in_file(const std::string &field, const std::string &file) noexcept;

		/**
		 * @brief The message states that the field is not found the file.
		 * @param[in] field The field which is not found.
		 * @param[in] file The file in which the field is not found.
		 * @return The message.
		 */
		static std::string field_not_found_in_file(const std::string &field, const std::string &file) noexcept;

		/**
		 * @brief The message states that the cookie is missing.
		 * @param[in] name Name of the cookie.
		 * @return The message.
		 */
		static std::string cookie_missing(const std::string &name) noexcept;

		/**
		 * @brief The message states that the field does not have the proper value.
		 * @param[in] field The field which does not have the right value.
		 * @param[in] value The value which is not there although it was expected.
		 * @return The message.
		 */
		static std::string field_not_correct_value(const std::string &field, const std::string &value) noexcept;

		/**
		 * @brief The message states that the field does not contain a string.
		 * @param[in] field The field which does not contain a string.
		 * @return The message.
		 */
		static std::string field_not_contain_string(const std::string &field) noexcept;

		/**
		 * @brief The message states that the field is not found.
		 * @param[in] field The field which is not found.
		 * @return The message.
		 */
		static std::string field_not_found(const std::string &field) noexcept;

		/**
		 * @brief The message states that the field does not contain a JSON array.
		 * @param[in] field The field which does not contain a JSON array.
		 * @return The message.
		 */
		static std::string field_not_contain_json_array(const std::string &field) noexcept;

		/**
		 * @brief The message states that the field does not contain a boolean.
		 * @param[in] field The field which does not contain a boolean.
		 * @return The message.
		 */
		static std::string field_not_contain_bool(const std::string &field) noexcept;


		/**
		 * @brief The message states that the JSON array has a size of zero.
		 * @param[in] field The field which contains the JSON array.
		 * @return The message.
		 */
		static std::string json_array_has_size_0(const std::string &field) noexcept;

		/**
		 * @brief The message states that the field does not contain an integer.
		 * @param[in] field The field which does not contain an integer.
		 * @return The message.
		 */
		static std::string field_not_contain_int(const std::string &field) noexcept;

		/**
		 * @brief The message states that the field does not contain a 64 bits integer.
		 * @param[in] field The field which does not contain a 64 bits integer.
		 * @return The message.
		 */
		static std::string field_not_contain_int64(const std::string &field) noexcept;

		/**
		 * @brief Returns a message which informs that the login was successful.
		 * @param[in] cookie_file The file to which the cookies are written.
		 */
		static std::string successful_login(const std::string &cookie_file) noexcept;
	};
}

#endif
