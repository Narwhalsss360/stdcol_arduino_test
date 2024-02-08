#include <iostream>
#include <fstream>
#include <sstream>
#include "TestFunctionWrapper.h"
#include "TestObjects.h"
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
			throw test_exception();
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
					auto fname_begin = general_iterator<const char[sizeof(flog_name)], const char&>(::flog_name, 0),
					fname_end = general_iterator<const char[sizeof(flog_name)], const char&>(flog_name, sizeof(flog_name));
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
					auto fname_begin = enumerator<general_iterator<const char[sizeof(flog_name)], const char&>, const char&>(general_iterator<const char[sizeof(flog_name)], const char&>(flog_name, 0), 0),
					fname_end = enumerator<general_iterator<const char[sizeof(flog_name)], const char&>, const char&>(general_iterator<const char[sizeof(flog_name)], const char&>(flog_name, sizeof(flog_name)), sizeof(flog_name));
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
	},
	{
		"[Compile | Runtime] array & collection",
		[](TesterFunction& this_test) {
			using stdcol::collection;
			using stdcol::array;
			using stdcol::enumerate;

			array<float, 10> numArray;
			collection<float>& nums = numArray;
			for (float& n : nums) {
				n = 1.0/2.0;
			}

			tlog << "Initial: ";
			for (auto e : enumerate(nums)) {
				tlog << '(' << e.index << ", " << e << ") ";
			}
			tlog << '\n';

			for (auto e : enumerate(nums)) {
				(float&)e = e.index / 2.0;
			}

			tlog << "Index-based: ";
			for (auto e : enumerate(nums)) {
				tlog << '(' << e.index << ", " << e << ") ";
			}
			tlog << '\n';

			return test_pass;
		}
	},
	{
		"[Compile | Runtime] dynamic_array & dynamic_collection",
		[](TesterFunction& this_test) {
			using stdcol::array;
			using stdcol::collection;
			using stdcol::dynamic_collection;
			using stdcol::dynamic_array;
			using stdcol::enumerate;

			dynamic_array<array<double, 2>> pairsArray;
			dynamic_collection<array<double, 2>>& pairs = pairsArray;

			auto f = [](double x) { return (x * x * x) - 2.5 * x; };

			constexpr double
				x_start = -3,
				x_step = 1,
				x_stop = 3;

			for (double x = x_start; x <= x_stop; x += x_step) {
				array<double, 2> pair;
				pair[0] = x;
				pair[1] = f(x);
				pairs.insert(pairs.size(), pair);
			}

			tlog << '[';
			for (auto e : enumerate(pairs)) {
				tlog << '[' << e.index << "]: (" << e.value[0] << ", " << e.value[1] << ')';
				if (e.index != pairs.size() - 1) {
					tlog << ", ";
				}
			}
			tlog << "]\n";
			pairs.resize(0);
			tlog << "Capacity: " << pairs.capacity() << '\n';
			return test_pass;
		}
	},
	{
		"[Compile] init_list",
		[](TesterFunction& this_test) {
			using stdcol::enumerate;
			using stdcol::initializer_list;
			using stdcol::array;
			using stdcol::dynamic_array;

			initializer_list<int> il = { 1, 2, 3 };

			tlog << "Init list: ";
			for (auto e : enumerate(il)) {
				tlog << '[' << e.index << "]:" << e << ' ';
			}
			tlog << '\n';

			array<int, 3> ints =  { 4, 5, 6 };

			ints = { 7, 8, 9 };

			auto f = [](double x) { return (x * x * x) - 2.5 * x; };

			dynamic_array<array<double, 2>> pairs = {
				{ 0, f(0) },
				{ 1, f(1) },
				{ 2, f(2) },
				{ 3, f(3) },
				{ 4, f(4) }
			};

			constexpr double extra = 4.3;
			constexpr double step = 0.5;

			const double end = pairs[pairs.size() - 1][0] + extra;
			for (double x = pairs[pairs.size() - 1][0]; x <= end; x += step) {
				pairs.insert(pairs.size(), { x, f(x) });
			}
			return test_pass;
		}
	},
	{
		"[Compile | Runtime] linked_node",
		[](TesterFunction& this_test) {
			using stdcol::linked_node;
			auto n = linked_node<NonDefaultConstructable>(nullptr, nullptr, 32, 1);
			return test_pass;
		}
	},
	{
		"linked_list",
		[](TesterFunction& this_test) {
			using stdcol::index;
			using stdcol::linked;
			linked<int> ints;

			for (int n = 1, i = 0; n <= 45; n += 2, i++) {
				ints.emplace(i, n);
			}

			ints.emplace(2, 6);
			ints.emplace(5, 10);

			return test_pass;
		}
	},
	{
		"linked_iterator",
		[](TesterFunction& this_test) {
			using stdcol::index;
			using stdcol::array;
			using stdcol::linked;
			using stdcol::linked_node;
			using stdcol::linked_iterator;
			using stdcol::initializer_list;
			using stdcol::iterate;
			using stdcol::enumerate;

			linked<NonDefaultConstructable> items;

			index i = 0;
			for (int n = 2; n <= 1000; n += n) {
				items.emplace(i, 2 * i, n);
			}

			for (auto& n : iterate(items)) {
				tlog << n.a << ':' << n.b << ", ";
			}

			tlog << '\n';

			index size = items.size();
			for (auto e : enumerate(items)) {
				tlog << '[' << e.index << "]: (" << e.value.a << ", " << e.value.b << ')';
				if (e.index != size - 1) {
					tlog << ", ";
				}
			}

			tlog << '\n';
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
		} catch (const std::exception& e) {
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
