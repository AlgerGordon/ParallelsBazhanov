//
// Created by General on 10.01.2021.
//


#include <optimization_methods.h>
#include <iostream>
#include <fstream>

void TestInvTask() {
    {
        double a0 = 3.615;
        double E_Acoh = -4.386;
        Quantities target = Quantities(a0,
                                       -3.544,
                                       1.42,
                                       1.76,
                                       1.25,
                                       0.82,
                                       0.4,
                                       -0.26,
                                       -1.04,
                                       -4.386,
                                       ATOM_ENUM::CU,
                                       ATOM_ENUM::CO);

        double accuracy = 0.1;
        std::pair<double, InteractionParameters> loss_and_ip;
        std::pair<double, InteractionParameters> best_loss_and_ip;
        best_loss_and_ip.first = 10000.0;

        for (int i = 0; i < 5; i++) {
            loss_and_ip = nelder_mead(target, default_loss, accuracy);
            if (loss_and_ip.first < best_loss_and_ip.first) {
                best_loss_and_ip = loss_and_ip;
            }
        }

        std::cout << "Result:\n" << std::endl;
        std::cout << "Best loss: " << best_loss_and_ip.first << std::endl;

        std::cout << "Target:\n" << target << std::endl;
        Quantities q(ATOM_ENUM::CU, ATOM_ENUM::CO, E_Acoh);
        Structure str;
        str.createStructure(best_loss_and_ip.second[BB][R0_LOC] * sqrt(2), 3 , ATOM_ENUM::CU);
        q.computeQuantities(best_loss_and_ip.second, str);
        std::cout << "Model:\n " << q << std::endl;

        std::cout << "Model parameters:\n " << best_loss_and_ip.second << std::endl;

        const char* output_path = "C:\\Users\\General\\CLionProjects\\ParallelDataProcessing\\optimization\\CoCu.txt";
        std::ofstream output;
        output.open(output_path, std::ofstream::out | std::ofstream::app);
        if (output) {
            output << "Best loss: " << best_loss_and_ip.first << std::endl;

            output << "Target:\n" << target << std::endl;
            str.createStructure(best_loss_and_ip.second[BB][R0_LOC] * sqrt(2), 3 , ATOM_ENUM::CU);
            q.computeQuantities(best_loss_and_ip.second, str);
            output << "Model:\n " << q << std::endl;

            output << "Model parameters:\n " << best_loss_and_ip.second << std::endl;

            char prev = output.fill ('_');
            output.width (40);
            output << '\n';
            output.fill(prev);
            output << '\n';
        }
        output.close();
    }
//    {
//        double a0 = 3.615;
//        Quantities target = Quantities(a0,
//                                       -3.544,
//                                       1.42,
//                                       1.76,
//                                       1.25,
//                                       0.82,
//                                       0.4,
//                                       -0.26,
//                                       -1.04,
//                                       -4.386,
//                                       ATOM_ENUM::CU,
//                                       ATOM_ENUM::CO);
//
//        double accuracy = 0.1;
//        std::pair<double, InteractionParameters> loss_and_ip;
//        std::pair<double, InteractionParameters> best_loss_and_ip;
//
//        for (int i = 0; i < 50; i++) {
//            loss_and_ip = nelder_mead(target, default_loss, accuracy);
//            if (loss_and_ip.first < best_loss_and_ip.first) {
//                best_loss_and_ip = loss_and_ip;
//            }
//        }
//
//        std::cout << "Result:\n" << std::endl;
//        std::cout << "Best loss: " << best_loss_and_ip.first << std::endl;
//
//        std::cout << "Target:\n" << target << std::endl;
//        std::cout << "Model: " << best_loss_and_ip.second << std::endl;
//
//        const char* output_path = "C:\\Users\\General\\CLionProjects\\ParallelDataProcessing\\optimization\\CoAu.txt";
//        std::ofstream output;
//        output.open(output_path, std::ofstream::out | std::ofstream::app);
//        if (output) {
//            output << "Best loss: " << best_loss_and_ip.first << std::endl << std::endl;
//
//            output << "Target:\n" << target << std::endl;
//            output << "Model: " << best_loss_and_ip.second << std::endl;
//            char prev = output.fill ('_');
//            output.width (40);
//            output << '\n';
//            output.fill(prev);
//            output << '\n';
//        }
//        output.close();
//
//    }
};