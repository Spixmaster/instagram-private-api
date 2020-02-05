#ifndef IG_TOOMANYREQUESTSEXCEPTION_H
#define IG_TOOMANYREQUESTSEXCEPTION_H

#include <memory>
#include <exception>

/*
 * @brief an exception class that is thrown when the Instagram servers complain about too many requests
 * @brief it is a monostate
 */

namespace ig
{
	class TooManyRequestsException : public std::exception
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<TooManyRequestsException> ptr;

		//member functions
		const char* what() const noexcept;
	};
}

#endif
