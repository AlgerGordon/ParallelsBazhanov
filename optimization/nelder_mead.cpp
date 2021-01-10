//
// Created by General on 10.01.2021.
//


#include <random>
#include <ctime>
#include "optimization_methods.h"

InteractionParameters nelder_mead(const Quantities& target_quantities,
                                  std::function<double(const Quantities&, const Quantities&)> loss_func,
                                  const ConstsForOptimization& cfo,
                                  const NelderMeaParams& nmp,
                                  double accuracy,
                                  size_t max_iter,
                                  const ParametersEdges& pe) {

    std::mt19937 generator(std::time(nullptr));
    std::normal_distribution<double> distribution;

    size_t kNOptParams = PARAMETERS_SIZE * 3;

    std::vector<InteractionParameters> ip_simplex(kNOptParams + 1);
    double loss_values[ip_simplex.size()];

    InteractionParameters x_h, x_g, x_l, x_center;
    double f_h, f_g, f_l, tmp_loss;

    std::cout << ip_simplex.size() << '\n';

    double min_value, max_value, mu, sigma, new_value;

    Structure str;


//    for (size_t point_ind = 0; point_ind < ip_simplex.size(); point_ind++) {
//        for (size_t inter_ind = 0; inter_ind < 3; inter_ind++) {
//            for (size_t param_ind = 0; param_ind < PARAMETERS_SIZE; param_ind++) {
//                min_value = pe[2 * param_ind];
//                max_value = pe[2 * param_ind + 1];
//                mu = (max_value + min_value) / 2;
//                sigma = (max_value - min_value) / 3;
//                new_value = sigma * distribution(generator) + mu;
//                auto it = static_cast<INTERACTION_ENUM>(inter_ind);
//                auto pt = static_cast<PARAMETERS_ENUM>(param_ind);
//                ip_simplex[point_ind][it][pt] = new_value;
//                computeQuantities()
//                loss_values[point_ind] = tmp_loss;
//            }
//        }
//    }





}