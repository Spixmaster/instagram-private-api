#include "ig/constants/Messages.h"
#include <iostream>
#include <boost/format.hpp>
#include <boost/locale.hpp>

#define _(STRING) boost::locale::translate(STRING)

namespace ig
{
	const std::string Messages::no_cookies_found = _("No cookies from a previous session were found. Thus, a new login is required whose cookies will be stored for the next logins.");
	const std::string Messages::wrong_choice_try_again = _("Wrong choice. Try again!");
	const std::string Messages::hints_from_last_server_response = _("If you do not know your personal data like phone number or email, here are some hints:");
	const std::string Messages::server_respone_not_json_obj = _("The server response is not a JSON object.");
	const std::string Messages::server_respone_not_json_arr = _("The server response is not a JSON array.");
	const std::string Messages::challenge_not_solved = _("The login challenge could not be solved.");
	const std::string Messages::not_ig_post = _("This is not an Instagram post.");
	const std::string Messages::new_login_required_as_logged_out = _("Warning!\nA new login is required as you have been logged out.");

	const std::string Messages::acc_soft_ban = _("Use a different account!\nThis response is similar to a soft ban from my experience when I encountered this problem. I could not even login in from the official Android app. For me, my account was set free again after a few hours but it depends.");
	const std::string Messages::manual_challenge = _("Warning!\nIf this is not the login process, it may be that you need to solve a challenge manually. Log in into your Instagram account in your browser and you should be requested to verify your identity. Do so.");
	const std::string Messages::phone_number = _("Phone number");
	const std::string Messages::email = _("Email");
	const std::string Messages::verify_login = _("You need to verify your login. Choose the approval method.");
	const std::string Messages::your_choice_inp = _("Your choice: ");
	const std::string Messages::ver_code_sent = _("A verification code has been sent to the selected method, please check.");
	const std::string Messages::prompt_ver_code_inp = _("Enter your verification code: ");
	const std::string Messages::was_it_you = _("You need to verify your login. Choose on whether the last login was you.");
	const std::string Messages::it_was_me = _("It was me.");
	const std::string Messages::it_was_not_me = _("It was not me.");

	std::string Messages::field_no_value_in_file(const std::string &field, const std::string &file) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" has no value in the file \"%2%\".")) % field % file);
	}

	std::string Messages::field_not_found_in_file(const std::string &field, const std::string &file) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" could not be found in the file \"%2%\".")) % field % file);
	}

	std::string Messages::cookie_missing(const std::string &name) noexcept
	{
		return boost::str(boost::format(_("The cookie \"%1%\" is missing.")) % name);
	}

	std::string Messages::field_not_correct_value(const std::string &field, const std::string &value) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not have the value \"%2%\".")) % field % value);
	}

	std::string Messages::field_not_contain_string(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not contain a string.")) % field);
	}

	std::string Messages::field_not_found(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" was not found.")) % field);
	}

	std::string Messages::field_not_contain_json_array(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not contain a JSON array.")) % field);
	}

	std::string Messages::field_not_contain_bool(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not contain a boolean.")) % field);
	}

	std::string Messages::json_array_has_size_0(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not contain a JSON array with size greater than 0.")) % field);
	}

	std::string Messages::field_not_contain_int(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not contain an integer.")) % field);
	}

	std::string Messages::field_not_contain_int64(const std::string &field) noexcept
	{
		return boost::str(boost::format(_("The field \"%1%\" does not contain a 64 bits integer.")) % field);
	}

	std::string Messages::successful_login(const std::string &cookie_file) noexcept
	{
		return boost::str(boost::format(_("Successful login! The cookies are saved to \"%1%.\"")) % cookie_file);
	}
}
