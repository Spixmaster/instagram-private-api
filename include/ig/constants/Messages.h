#ifndef IG_CONSTANTS_MESSAGES_H
#define IG_CONSTANTS_MESSAGES_H

#include <string>
#include <memory>

/*
 * @brief class contains messages which are used throughout the programme
 * @brief it is a monostate
 */

namespace ig
{
	class Messages
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<Messages> ptr;

		//member variables
		static const std::string no_cookies_found;
		static const std::string wrong_choice_try_again;
		static const std::string hints_from_last_server_response;
		static const std::string server_respone_not_json_obj;
		static const std::string challenge_not_solved;
		static const std::string not_ig_post;
		static const std::string new_login_required_as_logged_out;
		static const std::string acc_soft_ban;
		static const std::string manual_challenge;

		//member functions
		/*
		 * @brief message states that the field has no value in the file
		 * @param field: which field has no value
		 * @param file: in which file the field has no value
		 * @return the message
		 */
		static std::string field_no_value_in_file(const std::string &field, const std::string &file) noexcept;

		/*
		 * @brief message states that the field is not found the file
		 * @param field: which field is not found
		 * @param file: in which file the field is not found
		 * @return the message
		 */
		static std::string field_not_found_in_file(const std::string &field, const std::string &file) noexcept;

		/*
		 * @brief message states that the cookie is missing
		 * @param name: name of the cookie
		 * @return the message
		 */
		static std::string cookie_missing(const std::string &name) noexcept;

		/*
		 * @brief message states that the field does not have the proper value
		 * @param field: field which does not have the right value
		 * @param value: value which is not there but was expected
		 * @return the message
		 */
		static std::string field_not_correct_value(const std::string &field, const std::string &value) noexcept;

		/*
		 * @brief message that the field does not contain a string
		 * @param field: field which does not contain a string
		 * @return the message
		 */
		static std::string field_not_contain_string(const std::string &field) noexcept;

		/*
		 * @brief message that the field is not found
		 * @param field: field which is not found
		 * @return the message
		 */
		static std::string field_not_found(const std::string &field) noexcept;

		/*
		 * @brief message that the field does not contain a json array
		 * @param field: field which does not contain a json array
		 * @return the message
		 */
		static std::string field_not_contain_json_array(const std::string &field) noexcept;

		/*
		 * @brief message that the field does not contain a bool
		 * @param field: field which does not contain a bool
		 * @return the message
		 */
		static std::string field_not_contain_bool(const std::string &field) noexcept;


		/*
		 * @brief message that the json array has a size of zero
		 * @param field: field which contains the json array
		 * @return the message
		 */
		static std::string json_array_has_size_0(const std::string &field) noexcept;

		/*
		 * @brief message that the field does not contain an int
		 * @param field: field which does not contain an int
		 * @return the message
		 */
		static std::string field_not_contain_int(const std::string &field) noexcept;
	};
}

#endif
