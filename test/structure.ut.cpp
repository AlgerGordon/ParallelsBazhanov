//
// Created by General on 03.12.2020.
//

#include <structure.h>
#include <test_runner.h>
#include <cmath>


void TestMinimizeDist(){
    {
        ATOM_ENUM a_type = ATOM_ENUM::CU;
        Atom a1(a_type);
        Atom a2(a_type, {9, 9, 0});
        XYZ period(10, 10, 0);
        Matrix identity = {};
        double res = minimizeDistance<ZPERIOD::Z_OFF>(a1, a2, period, identity, a_type);
        double ans = sqrt(2);
        ASSERT_EQUAL(res, ans);
    }
    {
        ATOM_ENUM a_type = ATOM_ENUM::CU;
        Atom a1(a_type);
        Atom a2(a_type, {9, 0, 0});
        XYZ period(10, 10, 0);
        Matrix identity = {};
        double res =minimizeDistance<ZPERIOD::Z_OFF>(a1, a2, period, identity, a_type);
        double ans = 1;
        ASSERT_EQUAL(res, ans);
    }
    {
        ATOM_ENUM a_type = ATOM_ENUM::CU;
        Atom a1(a_type, {5, 5, 5});
        Atom a2(a_type, {6, 5, 5});
        XYZ period(10, 10, 0);
        Matrix identity = {};
        double res =minimizeDistance<ZPERIOD::Z_OFF>(a1, a2, period, identity, a_type);
        double ans = 1;
        ASSERT_EQUAL(res, ans);
    }
    {
        ATOM_ENUM a_type = ATOM_ENUM::CU;
        Atom a1(a_type);
        Atom a2(a_type, {9, 9, 9});
        XYZ period(10, 10, 10);
        Matrix identity = {};
        double res =minimizeDistance<ZPERIOD::Z_ON>(a1, a2, period, identity, a_type);
        double ans = sqrt(3);
        ASSERT_EQUAL(res, ans);
    }
}

void TestStructure() {
    TestRunner tr;
    RUN_TEST(tr, TestMinimizeDist);
    std::cout.flush();
    std::cerr.flush();
}
