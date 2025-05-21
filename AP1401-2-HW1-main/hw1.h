#ifndef HW1_H
#define HW1_H
#include <vector>
#include <cmath>
#include <stdexcept>
#include <random>
#include <vector>
#include <memory>


double linear_combination(const std::vector<double>& inputs, 
                          const std::vector<double>& weights,
                          double bias);


double sigmoid(double z);

double neuron_output(const std::vector<double>& inputs,
                     const std::vector<double>& weights,
                     double bias);

std::vector<std::shared_ptr<std::vector<double>>> read_csv(std::string filename);
std::vector<double> train(std::vector<std::shared_ptr<std::vector<double>>>, double learning_rate, int num_iter);

#endif
