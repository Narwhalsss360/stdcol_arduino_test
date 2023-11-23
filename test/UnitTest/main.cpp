#include <iostream>
#include <fstream>
#include <sstream>
#include "TestFunctionWrapper.h"
#include <stdcol>

constexpr char flog_name[] = "Test Results.log";

std::ofstream flog = std::ofstream(flog_name);
std::stringstream tlog;

TesterFunction tests[] = {
	{
		"[Runtime] TesterFunction Test",
		[](TesterFunction& this_test) {
			tlog << this_test << " Ran test for TesterFunction!" << '\n';
			return test_pass;
		}
	},
	{
		"[Runtime] TesterFunction exception catcher test",
		[](TesterFunction& this_test) {
			this_test.result = true;
			throw std::exception("Exception that should be caught, and logged.");
			return test_pass;
		}
	},
	{
		"[Compile] index",
		[](TesterFunction& this_test) {
			using stdcol::index;
			using stdcol::findex;

			findex fi = (findex::int_type)index(32);
			for (index i = 0; i < 10; i++, fi = i * 2 + 1);

			fi = findex();
			fail_if(fi.found());

			return test_pass;
		}
	},
	{
		"[Compile | Runtime] HEADER: iterables",
		[](TesterFunction& this_test) {
			using stdcol::general_iterator;
			using stdcol::iterable;
			using stdcol::iterate;

			{
				tlog << "Using general_iterator... ";
				for (
					auto fname_begin = general_iterator<const char*, const char&>(flog_name, 0),
					fname_end = general_iterator<const char*, const char&>(flog_name, sizeof(flog_name));
					fname_begin != fname_end;
					++fname_begin) {
						tlog << *fname_begin;
					}
					tlog << '\n';
			}

			{
				tlog << "Using iterable... ";
				auto fname_iter = iterable<const char*>((const char*)flog_name, flog_name + sizeof(flog_name));
				for (const char& c : fname_iter) {
					tlog << c;
				}
				tlog << '\n';
			}

			{
				tlog << "Using iterate(T (&)[size])... ";
				for (const char& c : iterate(flog_name)) {
					tlog << c;
				}
				tlog << '\n';
			}

			return test_pass;
		}
	},
	{
		"[Compile | Runtime] Header: enumerables",
		[](TesterFunction& this_test) {
			using stdcol::general_iterator;
			using stdcol::iterate;
			using stdcol::enumerator;
			using stdcol::enumerable;
			using stdcol::enumerate;

			{
				tlog << "Using enumerator... ";
				for (
					auto fname_begin = enumerator<general_iterator<const char*, const char&>, const char&>(general_iterator<const char*, const char&>(flog_name, 0), 0),
					fname_end = enumerator<general_iterator<const char*, const char&>, const char&>(general_iterator<const char*, const char&>(flog_name, sizeof(flog_name)), sizeof(flog_name));
					fname_begin != fname_end;
					++fname_begin) {
						tlog << '(' << (*fname_begin).index << ", " << *fname_begin << ") ";
					}
					tlog << '\n';
			}

			{
				tlog << "Using enumerable... ";
				auto fname_enum = iterate(enumerable<const char*, const char&>((const char*)flog_name, flog_name + sizeof(flog_name)));
				for (auto e : fname_enum) {
					tlog << '(' << e.index << ", " << e << ") ";
				}
				tlog << '\n';
			}

			{
				tlog << "Using enumerate(T (&)[size])... ";
				for (auto e : iterate(enumerate(flog_name))) {
					tlog << '(' << e.index << ", " << e << ") ";
				}
				tlog << '\n';
			}
			return test_pass;
		}
	}
};

int main() {
	using std::cout;
	using std::cin;
	using std::exception;

	for (TesterFunction& test : tests) {
		try {
			tlog << "Running test " << test.name << ":\n";
			tlog << test << ": " << resulString[test()] << '\n';
		} catch (std::exception e) {
			tlog << "An exception was thrown in test " << test.name << ", " << e.what() << '\n';
		}
		cout << tlog.str();
		flog << tlog.str();
		tlog.str("");
	}

	cout << "Press enter to exit...\n";
	cin.get();
	return 0;
}
