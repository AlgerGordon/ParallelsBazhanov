//
// Created by General on 10.01.2021.
//


#pragma once
#include <tb_sma.h>
#include <functional>

double default_loss(const Quantities& tmp, const Quantities& target);

struct NelderMeadParams {
    double alpha = 1;
    double beta = 0.5;
    double gamma = 2;
    double sigma = 0.5;
};


std::pair<double, InteractionParameters> nelder_mead(const Quantities& target_quantities,
                                        const std::function<double(const Quantities&, const Quantities&)>& loss_func,
                                        double accuracy = 1e-1,
                                        const NelderMeadParams& nmp = {},
                                        size_t max_iter = 10'000,
                                        size_t str_size = 3,
                                        const ParametersEdges& pe = {});