//
// Created by General on 12.07.2020.
//

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <sstream>

#include "my_print.h"

using namespace std;

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define AS_KV(x) (#x) << " = " << (x)
#define RUN_TEST(tr, func) tr.RunTest(func, #func)
#define ASSERT_EQUAL(x, y) {                                        \
    ostringstream __assert_equal_private_os;                        \
    __assert_equal_private_os << #x << " != " << #y << ", "         \
        << __FILENAME__ << ":" << __LINE__;                         \
    AssertEqual(x, y, __assert_equal_private_os.str());             \
}
#define ASSERT(x) {                                                 \
    ostringstream __assert_equal_private_os;                        \
    __assert_equal_private_os << #x << " is false" << ", "          \
        << __FILE__ << ":" << __LINE__;                             \
    Assert(x, __assert_equal_private_os.str());                     \
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);
inline void Assert(bool b, const string& hint) {
    AssertEqual(b,true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name);
    ~TestRunner();
private:
    int fail_count = 0;
};


template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint) {
    if (!(t == u)) {
        ostringstream  os;
        os << "Assertion failed: " << endl<< AS_KV(t) << " != " << endl << AS_KV(u)
            << endl << "Hint: " << hint;
        throw runtime_error(os.str());
    }
}

template<class TestFunc>
void TestRunner::RunTest(TestFunc func, const string &test_name) {
    try {
        func();
        cerr << test_name << " OK" << endl;
    } catch (runtime_error &e) {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    }
}

