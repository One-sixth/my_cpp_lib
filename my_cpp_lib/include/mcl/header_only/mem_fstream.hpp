/*
* 简单的基于标准库的内存文件流实现
*/

#pragma once

#include <sstream>

class mem_fstream : virtual public std::istream, virtual public std::ostream
{
public:
	inline mem_fstream() : std::istream(&buf), std::ostream(&buf)
	{
	}

private:
	std::stringbuf buf;
};

