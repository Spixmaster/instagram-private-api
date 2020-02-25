#include "ig/constants/Messages.h"
#include <iostream>

namespace ig
{
	const std::string Messages::no_cookies_found = std::string("No cookies from a previous session were found. Thus a new login is required whose ") +
			"cookies will be stored for the next logins.";
	const std::string Messages::wrong_choice_try_again = "Error: Wrong choice. Try again!";
	const std::string Messages::hints_from_last_server_response = "If you do not know your personal data like phone number or email here are some hints:";
	const std::string Messages::server_respone_not_json_obj = "Error: The server response is not a json object.";
	const std::string Messages::challenge_not_solved = "Error: The login challenge could not be solved.";
	const std::string Messages::not_ig_post = "Error: This is not an Instagram post.";
	const std::string Messages::new_login_required_as_logged_out = std::string("######################\n") +
			"Warning!\n" +
			"A new login is required as you have been logged out.\n" +
			"######################";
	const std::string Messages::acc_soft_ban = std::string("######################\n") +
			"Use a different account!\n" +
			"This response is similar to a soft ban from my experience when I encountered this problem. I could not even login in from the official " +
			"Android app. For me, my account was set free again after a few hours but it depends.\n" +
			"######################";
	const std::string Messages::manual_challenge = std::string("######################\n") +
			"Warning!\n" +
			"If this is not the login process it may be that you need to solve a challenge manually. Log in into your Instagram account " +
			"in your browser and you should be requested to verify your identity. Do so.\n" +
			"######################";

	std::string Messages::field_no_value_in_file(const std::string &field, const std::string &file) noexcept
	{
		return "Error: Field \"" + field + "\" has no value in " + file + ".";
	}

	std::string Messages::field_not_found_in_file(const std::string &field, const std::string &file) noexcept
	{
		return "Error: Field \"" + field + "\" could not be found in " + file + ".";
	}

	std::string Messages::cookie_missing(const std::string &name) noexcept
	{
		return "The cookie \"" + name + "\" is missing.";
	}

	std::string Messages::field_not_correct_value(const std::string &field, const std::string &value) noexcept
	{
		return "Error: Field \"" + field + "\" does not have the value \"" + value + "\".";
	}

	std::string Messages::field_not_contain_string(const std::string &field) noexcept
	{
		return "Error: Field \"" + field + "\" does not contain a string.";
	}

	std::string Messages::field_not_found(const std::string &field) noexcept
	{
		return "Error: Field \"" + field + "\" is not found.";
	}

	std::string Messages::field_not_contain_json_array(const std::string &field) noexcept
	{
		return "Error: Field \"" + field + "\" does not contain a json array.";
	}

	std::string Messages::field_not_contain_bool(const std::string &field) noexcept
	{
		return "Error: Field \"" + field + "\" does not contain a bool.";
	}

	std::string Messages::json_array_has_size_0(const std::string &field) noexcept
	{
		return "Error: Field \"" + field + "\" does not contain a json array with size greater than 0.";
	}

	std::string Messages::field_not_contain_int(const std::string &field) noexcept
	{
		return "Error: Field \"" + field + "\" does not contain an int.";
	}
}
