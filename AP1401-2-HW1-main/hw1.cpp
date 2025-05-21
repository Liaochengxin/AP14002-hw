#include "hw1.h"
#include <cmath>
#include <stdexcept>
#include <random>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>


double linear_combination(const std::vector<double>& inputs, 
                          const std::vector<double>& weights,
                          double bias){
  if (inputs.size() != weights.size()) {
    throw std::invalid_argument("inputs and weights vectors must have the same size");
  }
  double z = 0.0;
  for (size_t i = 0; i < inputs.size(); ++i) {
    z += weights[i] * inputs[i];
  }
  z += bias;
  return z;
}

double sigmoid(double z){
  return 1.0/(1.0 + std::exp(-z));
}


double neuron_output(const std::vector<double>& inputs,
                     const std::vector<double>& weights,
                     double bias){
  double z = linear_combination(inputs, weights, bias);
  return sigmoid(z);
}

std::vector<std::shared_ptr<std::vector<double>>> read_csv(std::string filename){
  std::vector<std::shared_ptr<std::vector<double>>> data;
  std::ifstream file(filename);
  
  if (!file.is_open()){
    throw std::runtime_error("could not open file" + filename);
  }

  std::string line;
  while (std::getline(file, line)){
    if (line.empty()) continue;

    std::istringstream iss(line);
    std::string value;
    auto row = std::make_shared<std::vector<double>>();

    while (std::getline(iss, value, ',')){
      try{
        row->push_back(std::stod(value));
      } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse value '" + value + "' in file " + filename);
      }
    }

    if (!row->empty()){
      data.push_back(row);
    }
  }
  if(data.empty()){
    throw std::runtime_error("No valid data found in file " + filename);
  }
  return data;
}

std::vector<double> train(std::vector<std::shared_ptr<std::vector<double>>> training_data, double learning_rate, int num_iter){
  if (training_data.empty()){
    throw std::invalid_argument("Training data cannot be empty");
  }
  size_t feature_size = training_data[0]->size() - 1;
  if (feature_size < 1){
    throw std::invalid_argument("Each training smaple mush contain features and label");
  }

  std::vector<double> weights(feature_size);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-0.5, 0.5);

  for (auto& w : weights){
    w = dis(gen);
  }

  double bias = dis(gen);

  for (int iter = 0; iter < num_iter; ++iter){
    for (const auto& sample : training_data){
      if(sample->size() != feature_size + 1){
        throw std::invalid_argument("All samples must have same dimension");
      }

      const std::vector<double>& features = *sample;
      double real_value =  features.back();
      
      std::vector<double> input_features(features.begin(), features.end() - 1);

      double prediction = linear_combination(input_features, weights, bias);

      double predicted_value = (sigmoid(prediction) >= 0.5) ? 1.0 : 0.0;

      double error = real_value - predicted_value;
      for (size_t i = 0; i < feature_size; ++i){
        weights[i] += learning_rate * error * features[i];
      }
      bias += learning_rate * error;
    }
  }

  weights.push_back(bias);
  return weights;
}
