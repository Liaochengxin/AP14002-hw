#ifndef Q2_H
#define Q2_H

#include <algorithm>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace q2{

  struct Patient
  {
  	std::string name;
  	size_t age;
  	size_t smokes;
  	size_t area_q;
  	size_t alkhol;
  };

  inline std::vector<Patient> read_file(std::string filename){
    std::vector<Patient> patients;  
    std::ifstream file(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;

    std::getline(file, line);
    std::getline(file, line);

    while(std::getline(file, line)){
      if (line.empty()) continue;
      Patient p;
      char comma;

      std::stringstream ss(line);
      std::string name, surname; 

      std::getline(ss, name, ',');
      std::getline(ss, surname, ',');
 
      if (!name.empty() && !surname.empty()) {
          if (!std::isspace(name.back()) && !std::isspace(surname.front())) {
              p.name = name + " " + surname;
          } else {
              p.name = name + surname;
          }
      } else {
          p.name = name + surname;
      }
      
      ss >> p.age >> comma >> p.smokes >> comma >> p.area_q >> comma >> p.alkhol;

      patients.push_back(p);
    }
    return patients;
  }
  
  
  inline double risk(Patient& p){
    return 3*p.age + 5*p.smokes + 2*p.area_q + 4*p.alkhol;
  }

  inline bool compare(Patient& p1, Patient& p2){
    return risk(p1) > risk(p2);
  }
  inline void sort(std::vector<Patient>& patients){
    std::sort(patients.begin(), patients.end(), compare);
  }

} //namespace q2
#endif //Q2_H
