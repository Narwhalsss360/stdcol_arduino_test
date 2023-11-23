#include <iostream>
#include <fstream>
#include "TestFunctionWrapper.h"

using std::cout;
using std::cin;

constexpr char results_file_name[] = "Test Results.log";

TesterFunction tests[] = {
	{
		"TesterFunction Test",
		[](TesterFunction& this_test) {
			cout << this_test << " Ran test for TesterFunction!" << '\n';
			return test_pass;
		}
	},
	{
		"TesterFunction exception catcher test",
		[](TesterFunction& this_test) {
			this_test.result = true;
			throw std::exception("Exception that should be caught, and logged.");
			return test_pass;
		}
	}
};

int main() {
	using std::ofstream;
	using std::exception;

	ofstream f = ofstream(results_file_name);
	f << "Text";
	f.close();

	for (TesterFunction& test : tests) {
		try {
			cout << "Running test " << test.name << ": " << resulString[test()] << '\n';
		} catch (std::exception e) {
			cout << "An exception was thrown in test " << test.name << ", " << e.what() << '\n';
		}
	}

	cout << "Press enter to exit...\n";
	cin.get();
	return 0;
}
