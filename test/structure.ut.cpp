//
// Created by General on 03.12.2020.
//

#include <structure.h>
#include <test_runner.h>
#include <cmath>


void TestMinimizeDist(){
    {
        XYZ a1(0, 0, 0);
        XYZ a2(9, 9, 0);
        XYZ period(10, 10, 0);
        Matrix identity = {};
        double dist = minimizeDistance<ZPERIOD::Z_OFF>(a1, a2, period, identity);
        double ans = sqrt(2);
        ASSERT_EQUAL(dist, ans);
    }
    {
        XYZ a1(0, 0, 0);
        XYZ a2(9, 0, 0);
        XYZ period(10, 10, 0);
        Matrix identity = {};
        double dist = minimizeDistance<ZPERIOD::Z_OFF>(a1, a2, period, identity);
        double ans = 1;
        ASSERT_EQUAL(dist, ans);
    }
    {
        XYZ a1(5, 5, 5);
        XYZ a2(6, 5, 5);
        XYZ period(10, 10, 0);
        Matrix identity = {};
        double dist = minimizeDistance<ZPERIOD::Z_OFF>(a1, a2, period, identity);
        double ans = 1;
        ASSERT_EQUAL(dist, ans);
    }
    {
        XYZ a1(0, 0, 0);
        XYZ a2(9, 9, 9);
        XYZ period(10, 10, 10);
        Matrix identity = {};
        double dist = minimizeDistance<ZPERIOD::Z_ON>(a1, a2, period, identity);
        double ans = sqrt(3);
        ASSERT_EQUAL(dist, ans);
    }
}

void TestStructure() {
    TestRunner tr;
    RUN_TEST(tr, TestMinimizeDist);
    std::cout.flush();
    std::cerr.flush();
}
