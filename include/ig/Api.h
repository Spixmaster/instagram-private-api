#ifndef TGBOT_ENDPOINTS_H
#define TGBOT_ENDPOINTS_H

#include <string>
#include <memory>

//@brief represents the Instagram Api which interacts with the Instagram servers

namespace ig
{
	class Api
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<Api> ptr;

	private:
		//member variables
		//needed for the endpoints
		std::string m_token;

	public:
		//constructors
		//@param token: token which the member functions need for the requests they make
		Api(const std::string &token);

		//member functions

	};
}

#endif
