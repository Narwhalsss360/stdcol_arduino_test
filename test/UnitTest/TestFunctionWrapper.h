#pragma once

#include <string>
#include <ostream>

#define test_fail false
#define test_pass true

#define fail_if(expr) if (!(expr)) return test_fail
#define fail_if_msg(expr, msg) if (!(expr)) { std::cout << msg; return test_fail; }

#define pass_if(expr) if (expr) return test_pass
#define pass_if_msg(expr, msg) if (expr) { std::cout << msg; return test_pass; }

const char resulString[][5] = { "Fail", "Pass" };

struct TesterFunction;

using test_func = bool (*) (TesterFunction&);

struct TesterFunction {
	std::string name = "Unnamed | Uninitialized";
	test_func f = nullptr;
	bool result = false;

	bool operator()() {
		if (f) result = f(*this);
		return result;
	}

	operator const bool() const {
		return result;
	}
};

std::ostream& operator<<(std::ostream& stream, const TesterFunction& test) {
	stream << '[' << test.name << ']';
	return stream;
}
