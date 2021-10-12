/*
文件读取写入辅助函数库
*/

#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <exception>
#include <concepts>


namespace io_utils
{
	using namespace std;

	// 获得文件大小
	template <typename T>
	inline size_t Size(T& f)
	{
		auto cur_pos = f.tellg();
		f.seekg(0, ios::end);
		size_t size = f.tellg();
		f.seekg(cur_pos, ios::beg);
		return size;
	}

	// 获得文件剩余大小
	template <typename T>
	inline size_t RemainingSize(T& f)
	{
		auto pos_begin = f.tellg();
		f.seekg(0, ios::end);
		size_t size = f.tellg() - pos_begin;
		f.seekg(pos_begin);
		return size;
	}

	/*
	从文件流里读入一些字节
	*/
	template <typename T>
	inline void ReadAll(T& f, vector<char>& buf, size_t size_limit=-1)
	{
		auto size = RemainingSize(f);
		if (size > size_limit)
			throw runtime_error("ReadAll read size bigger than size_limit.");
		buf.resize(size);
		f.read((char*)buf.data(), size);
		if (f.gcount() != size)
			throw runtime_error("Read data len small than size.");
	}

	/*
	从文件流里读入一些字节
	*/
	template <typename T>
	inline void Read(T& f, size_t size, char* buf)
	{
		f.read(buf, size);
		if (f.gcount() != size)
			throw runtime_error("Read data len small than size.");
	}

	/*
	往文件流里写入一些字节
	*/
	template <typename T>
	inline void Write(T& f, size_t size, const char* buf)
	{
		f.write(buf, size);
	}

	/*
	读入一个T类的模版函数，注意T类必须为简单类型，不能包含指针或引用之类的东西，间接包含也不行。
	*/
	template <typename T1, typename T2>
	inline void ReadType(T1& f, T2& t)
	{
		Read(f, sizeof(t), (char*)&t);
	}

	/*
	保存一个T类的模版函数，注意T类必须为简单类型，不能包含指针或引用之类的东西，间接包含也不行。
	*/
	template <typename T1, typename T2>
	inline void WriteType(T1& f, const T2& t)
	{
		Write(f, sizeof(t), (char*)&t);
	}

	// 读入一个string
	template <typename T>
	inline void ReadString(T& f, string& s)
	{
		uint32_t size;
		ReadType(f, size);
		s.resize(size);
		Read(f, size, (char*)s.data());
	}

	// 读入一个u8string
	template <typename T>
	inline void ReadString(T& f, u8string& s)
	{
		uint32_t size;
		ReadType(f, size);
		s.resize(size);
		Read(f, size, (char*)s.data());
	}

	// 保存一个string
	template <typename T>
	inline void WriteString(T& f, const string& s)
	{
		uint32_t size = s.size();
		WriteType(f, size);
		Write(f, size, (char*)s.data());
	}

	// 保存一个u8string
	template <typename T>
	inline void WriteString(T& f, const u8string& s)
	{
		uint32_t size = s.size();
		WriteType(f, size);
		Write(f, size, (char*)s.data());
	}

	/*
	读入一个vector的模版函数，注意T类必须为简单类型，不能包含指针或引用之类的东西，间接包含也不行。
	如果需要用此函数读入复杂类型，请特化此模板函数
	*/
	template <typename T1, typename T2>
	inline void ReadVector(T1& f, vector<T2>& buf)
	{
		uint32_t size;
		ReadType(f, size);
		buf.resize(size);
		Read(f, sizeof(T2) * size, (char*)buf.data());
	}

	/*
	保存一个vector的模版函数，注意T类必须为简单类型，不能包含指针或引用之类的东西，间接包含也不行。
	如果需要用此函数写入复杂类型，请特化此模板函数
	*/
	template <typename T1, typename T2>
	inline void WriteVector(T1& f, const vector<T2>& buf)
	{
		uint32_t size = buf.size();
		WriteType(f, size);
		Write(f, sizeof(T2) * size, (char*)buf.data());
	}

	/*
	特化vector<string>的模板
	ReadVector函数偏特化失败，使用新名字，其他以后再说
	*/
	template <typename T1, typename T2>
	inline void ReadStringVector(T1& f, vector<T2>& buf)
	{
		uint32_t size;
		ReadType(f, size);
		buf.resize(size);
		for (auto& i : buf)
			ReadString(f, i);
	}

	/*
	特化vector<string>的模板
	WriteVector函数偏特化失败，使用新名字，其他以后再说
	*/
	template <typename T1, typename T2>
	inline void WriteStringVector(T1& f, const vector<T2>& buf)
	{
		uint32_t size = buf.size();
		WriteType(f, size);
		for (const auto& i : buf)
			WriteString(f, i);
	}


	// 读入一个T类的vector的模版函数，要求T类必须实现和可见Read，Write函数
	template <typename T1, typename T2>
	inline void ReadClassVector(T1& f, vector<T2>& data)
	{
		uint32_t size;
		ReadType(f, size);
		data.resize(size);
		for (size_t i = 0; i < size; ++i)
			data[i].Read(f);
	}

	// 写入一个T类的vector的模版函数，要求T类必须实现和可见Read，Write函数
	template <typename T1, typename T2>
	inline void WriteClassVector(T1& f, vector<T2>& data)
	{
		uint32_t size = data.size();
		WriteType(f, size);
		for (size_t i = 0; i < size; ++i)
			data[i].Write(f);
	}

};

