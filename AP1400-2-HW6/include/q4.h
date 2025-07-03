#ifndef Q4_H
#define Q4_H
#include <vector>
#include <numeric>

namespace q4{

  struct Vector2D
  {
  double x{};
  double y{}; 
  };

  struct Sensor
  {
    Vector2D pos;
    double accuracy;    
  };

  inline Vector2D kalman_filter(std::vector<Sensor> sensors){
    Vector2D result{0.0, 0.0};
    double total_weight = 0.0;
    size_t i = 0;

    while (i < sensors.size()){
      result.x += sensors[i].pos.x * sensors[i].accuracy;
      result.y += sensors[i].pos.y * sensors[i].accuracy;
      total_weight += sensors[i].accuracy;
      ++i;
    }

    if (total_weight != 0.0){
      result.x = result.x / total_weight;
      result.y = result.y / total_weight;
    }
    return result;
  }
}
#endif //Q4_H
