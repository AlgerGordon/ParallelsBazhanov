//
// Created by General on 11.01.2021.
//

#include <fstream>
#include <iostream>
#include "optimization_methods.h"

int main() {

    const char* output_path = "C:\\Users\\General\\CLionProjects\\ParallelDataProcessing\\optimization\\CoCu.txt";
    std::ofstream output;
    output.open(output_path, std::ofstream::out | std::ofstream::app);
    if (output) {
        output << "Result:\n" << std::endl;
        char prev = output.fill ('_');
        output.width (40);
        output << '\n';
        output.fill(prev);
    }
    output.close();
}