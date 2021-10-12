/*
* �򵥵Ļ��ڱ�׼����ڴ��ļ���ʵ��
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

