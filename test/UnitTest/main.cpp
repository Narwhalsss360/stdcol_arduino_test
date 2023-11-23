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
