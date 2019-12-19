#ifndef SPECIALTOOLS_H
#define SPECIALTOOLS_H

#include <memory>

//@brief contains functions which can only be used in this project

namespace ig
{
	class SpecialTools
	{
	public:
		//pointer of itself
		typedef std::shared_ptr<SpecialTools> ptr;
	};
}

#endif
