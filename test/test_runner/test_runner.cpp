//
// Created by General on 13.07.2020.
//

#include "test_runner.h"

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        cerr << fail_count << " test failed. Terminate";
        exit(1);
    }
}