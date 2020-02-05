#include "ig/TooManyRequestsException.h"

namespace ig
{
	const char* TooManyRequestsException::what() const noexcept
	{
		return "Error. The Instagram servers refused the request for the reason that they are too many.";
	}
}
