// my_cpp_lib.cpp : 定义 DLL 的导出函数。
//
#define MYCPPLIB_EXPORTS 1

#include "mcl/my_cpp_lib.h"

// 这是已导出类的构造函数。
__Example::__Example()
{
    return;
}

// 这是导出变量的一个示例
MYCPPLIB_API int __example_value = 0;

// 这是导出函数的一个示例。
MYCPPLIB_API int __example_func(void)
{
    return 0;
}
