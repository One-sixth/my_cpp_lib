/*
* ��ֹ�ิ��
* ʹ������

class ASD
{
	dont_copy_class(ASD);
}

ASD a();
ASD b = a;	// error!

*/

#pragma once

#define dont_copy_class(T) T(const T&)=delete; \
						   T& operator=(const T&)=delete;
