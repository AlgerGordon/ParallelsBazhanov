//
// Created by General on 10.01.2021.
//


#pragma once
#include <tb_sma.h>
#include <functional>

double default_loss(const Quantities& tmp, const Quantities& target);



struct NelderMeaParams {
    double alpha = 1;
    double beta = 0.5;
    double gamma = 2;
    double sigma = 0.5;
};


InteractionParameters nelder_mead(const Quantities& target_quantities,
                                        std::function<double(const Quantities&, const Quantities&)> loss_func,
                                        const ConstsForOptimization& cfo,
                                        double accuracy = 1e-3,
                                        size_t max_iter = 1e+6,
                                        const NelderMeaParams& nmp = {},
                                        const ParametersEdges& pe = {});