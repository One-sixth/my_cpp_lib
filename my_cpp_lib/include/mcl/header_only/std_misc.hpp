/*
* 标准库杂类工具
*/

#pragma once
#include <vector>
#include <list>
#include <array>
#include <string>
#include <chrono>


// 临时转换string数组到const char*数组
inline static
std::vector<const char*> to_cstr_arr(const std::vector<std::string>& str_arr)
{
	std::vector<const char*> cstr_arr(str_arr.size(), nullptr);
	for (int i = 0; i < str_arr.size(); ++i)
		cstr_arr[i] = str_arr[i].c_str();
	return cstr_arr;
}

// 计算vector占用内存大小
template <class T>
inline static size_t vector_mem_size(const std::vector<T>& v)
{
	return v.size() * sizeof(T);
}

// 计算list占用内存大小
template <class T>
inline static size_t list_mem_size(const std::list<T>& v)
{
	return v.size() * sizeof(T);
}

// 检查并释放指针
template <class T>
inline static void check_and_release_ptr(T*& ptr)
{
	if (ptr)
		delete ptr;
	ptr = nullptr;
}

// 获得当前Unix时间戳，也就是1970时间戳
inline static uint64_t get_now_time()
{
	using namespace std;
	auto now = chrono::steady_clock::now();
	return chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()).count();
}


//inline void upscale_im_ensure_size_specified_multiple(const cv::Mat& m)
//{
//	m.rows * m.cols * m.elemSize() * m.elemSize1();
//}