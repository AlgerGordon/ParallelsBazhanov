//
// Created by General on 10.01.2021.
//


#include <optimization_methods.h>
#include <iostream>

void TestInvTask() {

    double a0 = 3.615;
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

    for (int i = 0; i < 50; i++) {
        loss_and_ip = nelder_mead(target, default_loss, accuracy);
        if (loss_and_ip.first < best_loss) {
            best_loss =
        }
    }

    std::cout << "Result:\n" << std::endl;
    std::cout << "Best loss: " << best_loss_and_ip.first << std::endl;

    std::cout << target << std::endl;
    std::cout << best_loss_and_ip.second << std::endl;

};