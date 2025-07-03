#ifndef Q1_H
#define Q1_H

#include <cmath>
#include <functional>

namespace q1 {
  template<typename Func>
  double gradient_descent(double initial_value, double step_size, Func func){
    double x = initial_value;
    double prev_x = x;
    const double epsilon = 1e-5;
    const int max_iterations = 1000;

    for (int i = 0; i < max_iterations; ++i){
      const double delta_x = 1e-5;
      double derivative = (func(x+delta_x) - func(x-delta_x))/(2*delta_x);

      //update x value
      x = x - step_size * derivative;
    
      if (std::abs(x - prev_x) < epsilon){
        break;
      }
      prev_x = x;
    }
    return x;
  }

  template<typename T, typename Func>
  T gradient_descent(T initial_value, T step_size){
    Func func{};
    return gradient_descent(initial_value, step_size, func);
  }
} //namespace q1

#endif //Q1_H
