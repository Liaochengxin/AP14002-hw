#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "hw1.h"

#include <iostream>
#include <fstream>

int main (int argc, char *argv[]) {
    std::cout << "Step 1: Training on data.csv...\n";

    auto training_data = read_csv("data.csv");

    double learning_rate = 0.1;
    int num_iterations = 10;
    
    auto weights = train(training_data, learning_rate, num_iterations);

    std::cout << "\n Trained weights(including bias as last element):\n";

    for (size_t i = 0; i < weights.size(); i++){
      std::cout << "w" << i << ": " << weights[i] << "\n";
    }

    std::cout << "Step 2: Predicting on moons.csv..\n";

    auto test_data = read_csv("moons.csv");

    std::vector<double> predictions;

    std::vector<double> model_weights(weights.begin(), weights.end());

    double model_bias = weights.back();

    for (const auto& sample : test_data){
      const std::vector<double>& features = *sample;

      double z = linear_combination(features, model_weights, model_bias);

      double prediction = (z >= 0) ? 1.0 : 0.0;

      predictions.push_back(prediction);
    }

   std::cout << "Step 3: Save the Prections..\n";

   std::ofstream output_file("./predictions.csv");
   for (double pred : predictions){
     output_file << pred << "\n";
   }

   if (!output_file.is_open()) {
    std::cerr << "Error: Failed to open file!\n";
   }
   output_file.close();

   std::cout << "\n Predictions saved to predictions.csv\n";
   std::cout << "First 5 Prediction";

   for (size_t i = 0; i < 5 && i < predictions.size(); i++){
     std::cout << predictions[i] << " ";
   }
   std::cout << "\n";
} 
