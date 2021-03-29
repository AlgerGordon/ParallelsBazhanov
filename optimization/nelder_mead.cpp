//
// Created by General on 10.01.2021.
//


#include <random>
#include <ctime>
#include <iomanip>
#include "optimization_methods.h"

std::pair<double, InteractionParameters> nelder_mead(const Quantities& trg_quantities,
                                  const std::function<double(const Quantities&, const Quantities&)>& loss_func,
                                  double accuracy,
                                  const NelderMeadParams& nmp,
                                  size_t max_iter,
                                  size_t str_size,
                                  const ParametersEdges& pe) {


    Structure str;
    str.createStructure(10, str_size, trg_quantities.base_type());

    size_t kNOptParams = PARAMETERS_SIZE * 3;

    std::vector<InteractionParameters> ip_simplex(kNOptParams + 1);
    double loss_values[ip_simplex.size()];
    double prev_value = 0;

    Quantities tmp_quantities(trg_quantities.base_type(),
                                 trg_quantities.alloy_type(),
                                 trg_quantities.E_Acoh());

    std::mt19937 generator; // mt19937 как один из вариантов
    generator.seed(std::time(nullptr));
    std::normal_distribution<double> distribution{0,1};

    double min_value, max_value, mu, sigma, new_value;
    INTERACTION_ENUM inter_type;
    PARAMETERS_ENUM parameter_type;

    for (size_t point_ind = 0; point_ind < ip_simplex.size(); point_ind++) {
        for (size_t inter_ind = 0; inter_ind < 3; inter_ind++) {
            inter_type = static_cast<INTERACTION_ENUM>(inter_ind);
            for (size_t param_ind = 0; param_ind < PARAMETERS_SIZE; param_ind++) {
                parameter_type = static_cast<PARAMETERS_ENUM>(param_ind);
                min_value = pe[2 * param_ind];
                max_value = pe[2 * param_ind + 1];
                mu = (max_value + min_value) / 2;
                sigma = (max_value - min_value) / 6;
                new_value = sigma * distribution(generator) + mu;
                if ((new_value < min_value) || (max_value < new_value)) {
                    new_value = sigma / 2 * distribution(generator) + mu;
                }
                ip_simplex[point_ind][inter_type][parameter_type] = new_value;
            }
        }
        str.lattice_constant = ip_simplex[point_ind][BB][R0_LOC] * sqrt(2);

        tmp_quantities.computeQuantities(ip_simplex[point_ind], str);

        loss_values[point_ind] = loss_func(trg_quantities, tmp_quantities);

    }

    size_t h_ind = 0;
    size_t g_ind = 1;
    size_t l_ind = 2;

    for (int i = 0; i < 3; i++) {
        if(loss_values[i] > loss_values[(i + 1)%3] && loss_values[i] > loss_values[(i + 2)%3]) {
            h_ind = i;
        } else if (loss_values[i] < loss_values[(i + 1)%3] && loss_values[i] < loss_values[(i + 2)%3])  {
            l_ind = i;
        } else {
            g_ind = i;
        }
    }

    for (size_t point_ind = 0; point_ind < ip_simplex.size(); ++point_ind) {
        if (loss_values[point_ind] > loss_values[h_ind]) {
            g_ind = h_ind;
            h_ind = point_ind;
        } else if (loss_values[point_ind] < loss_values[h_ind]
                   && loss_values[g_ind] < loss_values[point_ind]) {
            g_ind = point_ind;
        } else if (loss_values[point_ind] < loss_values[l_ind]) {
            l_ind = point_ind;
        }
    }

    size_t count_iter = 0;

    InteractionParameters x_center, x_r, x_e, x_s;
    double f_r, f_e, f_s;
    bool need_compr = false;

    while (count_iter < max_iter && loss_values[l_ind] > accuracy) {

        for(size_t ind = 0; ind < ip_simplex.size(); ind++) {
            if (ind == h_ind) {
                continue;
            }
            x_center+= ip_simplex[ind];
        }

        x_center /= (ip_simplex.size() - 1);

        x_r = x_center * (1 + nmp.alpha) - ip_simplex[h_ind] * nmp.alpha;

        str.lattice_constant = x_r[BB][R0_LOC] * sqrt(2);
        tmp_quantities.computeQuantities(x_r, str);
        f_r = loss_func(trg_quantities, tmp_quantities);


        if (f_r < loss_values[l_ind]) {
            // std::cout << "f_r < f_l" << '\n';
            x_e = x_center * (1 - nmp.gamma) + x_r * nmp.gamma;
            str.lattice_constant = x_e[BB][R0_LOC] * sqrt(2);
            tmp_quantities.computeQuantities(x_e, str);
            f_e = loss_func(trg_quantities, tmp_quantities);
            if (f_e < f_r) {
                // std::cout << "\tx_h replaced with x_e" << '\n';
                ip_simplex[h_ind] = x_e;
                loss_values[h_ind] = f_e;
            } else {
                // std::cout << "\tx_h replaced with x_r" << '\n';
                ip_simplex[h_ind] = x_r;
                loss_values[h_ind] = f_r;
            }
        } else if (loss_values[l_ind] <= f_r && f_r < loss_values[g_ind]) {
            // std::cout << "f_l <= f_r < f_g" << '\n';
            ip_simplex[h_ind] = x_r;
            loss_values[h_ind] = f_r;
            // std::cout << "\tx_h replaced with x_r" << '\n';
        } else if (loss_values[g_ind] <= f_r && f_r < loss_values[h_ind]) {
            // std::cout << "f_g <= f_r < f_h" << '\n';
            ip_simplex[h_ind] = x_r;
            loss_values[h_ind] = f_r;
            //std::cout << "\tx_h replaced with x_r" << '\n';
            need_compr = true;
        } else if (loss_values[h_ind] <= f_r) {
            // std::cout << "f_h <= f_r" << '\n';
            need_compr = true;
        } else {
            std::cout << "BUG!!!!!" << '\n';
            std::cout << "\tf_h: " << loss_values[h_ind] << '\n';
            std::cout << "\tf_g: " << loss_values[g_ind] << '\n';
            std::cout << "\tf_l: " << loss_values[l_ind] << '\n';
            std::cout << "\t\tf_r" << f_r << '\n';
            std::cout << "\t x_r[R0_LOC]: " << x_r[BB][R0_LOC] << " " << x_r[AA][R0_LOC] << " " << x_r[AB][R0_LOC] << '\n';
            std::cout.flush();
            return {loss_values[l_ind], ip_simplex[l_ind]};
            // throw std::runtime_error("BUG!!!");
        }

        if (need_compr) {
            x_s = x_center * (1 - nmp.beta) + ip_simplex[h_ind] * nmp.beta;

            str.lattice_constant = x_s[BB][R0_LOC] * sqrt(2);
            tmp_quantities.computeQuantities(x_s, str);
            f_s = loss_func(trg_quantities, tmp_quantities);
            if (f_s < loss_values[h_ind]) {
                ip_simplex[h_ind] = x_s;
                loss_values[h_ind] = f_s;
                // std::cout << "In compression: replacing x_h with x_s" << '\n';
            } else {
                for (size_t ind = 0; ind < ip_simplex.size(); ind++) {
                    if (ind == l_ind) {
                        continue;
                    }
                    ip_simplex[ind] = ip_simplex[l_ind] + (ip_simplex[ind] - ip_simplex[l_ind]) * nmp.sigma;
                    str.lattice_constant = ip_simplex[ind][BB][R0_LOC] * sqrt(2);
                    tmp_quantities.computeQuantities(ip_simplex[ind], str);
                    loss_values[ind] = loss_func(trg_quantities, tmp_quantities);
                }
                // std::cout << "Regular compression" << '\n';
            }
        }

        for (int i = 0; i < 3; i++) {
            if(loss_values[i] > loss_values[(i + 1)%3] && loss_values[i] > loss_values[(i + 2)%3]) {
                h_ind = i;
            } else if (loss_values[i] < loss_values[(i + 1)%3] && loss_values[i] < loss_values[(i + 2)%3])  {
                l_ind = i;
            } else {
                g_ind = i;
            }
        }

        for (size_t point_ind = 0; point_ind < ip_simplex.size(); ++point_ind) {
            if (loss_values[point_ind] > loss_values[h_ind]) {
                g_ind = h_ind;
                h_ind = point_ind;
            } else if (loss_values[point_ind] < loss_values[h_ind]
                       && loss_values[g_ind] < loss_values[point_ind]) {
                g_ind = point_ind;
            } else if (loss_values[point_ind] < loss_values[l_ind]) {
                l_ind = point_ind;
            }
        }

        x_center *= 0.0;
        need_compr = false;
        if ((count_iter % 500) == 0 ) {
            std::cout << "Iteration #" << count_iter << " " << std::fixed << std::setprecision(7) << loss_values[l_ind] << " " << l_ind << '\n';
            if (std::abs(prev_value - loss_values[l_ind]) < 1e-7) {
                std::cout << "Too small improvement. Quit!" << '\n';
                break;
            }
            prev_value = loss_values[l_ind];
        }
        count_iter++;
        // break;
    }

    if (count_iter == max_iter) {
        std::cout << "Left because of iterations" << '\n';
    }

    return {loss_values[l_ind], ip_simplex[l_ind]};;
}