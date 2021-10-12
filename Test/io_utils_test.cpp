#include <mcl/header_only/io_utils.hpp>
#include <mcl/header_only/mem_fstream.hpp>
#include <iostream>


class _E
{
public:
	int a;
	_E()
	{
		a = rand();
	}

	bool operator==(const _E& b) const
	{
		return b.a == a;
	}

	template<typename T1>
	void Write(T1& f)
	{
		io_utils::WriteType(f, a);
	}

	template<typename T1>
	void Read(T1& f)
	{
		io_utils::ReadType(f, a);
	}
};


void io_utils_test()
{

	using namespace io_utils;
	using namespace std;

	cout << "io_utils_test begin" << endl;

	auto mb = mem_fstream();

	string in_str = "asadasdasdadad";
	string out_str;
	WriteString(mb, in_str);
	ReadString(mb, out_str);

	if (in_str != out_str)
		cout << "bad1" << endl;

	vector<int> in_v(100, 100);
	vector<int> out_v;

	WriteVector(mb, in_v);
	ReadVector(mb, out_v);

	if (in_v != out_v)
		cout << "bad2" << endl;

	vector<string> in_sv(100, "asdasdasd");
	vector<string> out_sv;

	WriteStringVector(mb, in_sv);
	ReadStringVector(mb, out_sv);

	if (in_sv != out_sv)
		cout << "bad3" << endl;

	vector<_E> in_ev(100);
	vector<_E> out_ev;

	WriteClassVector(mb, in_ev);
	ReadClassVector(mb, out_ev);

	if (in_ev != out_ev)
		cout << "bad4" << endl;

	cout << "Size " << Size(mb) << endl;

	mb.seekg(Size(mb) / 2, ios::beg);
	cout << "RemainingSize " << RemainingSize(mb) << endl;

	cout << "io_utils_test end" << endl;
}