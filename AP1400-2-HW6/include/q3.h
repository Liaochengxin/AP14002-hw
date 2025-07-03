#ifndef Q3_H
#define Q3_H

#include <string>
#include <queue>
#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>
namespace q3{

  struct flight
  {
	std::string flight_number;
	size_t duration;
	size_t connections;
	size_t connection_times;
	size_t price;
  };

  struct compareflight{
    bool operator() (const flight& a, const flight& b) const{
      size_t score_a = a.duration + a.connection_times + 3*a.price;
      size_t score_b = b.duration + b.connection_times + 3*b.price;
      
      return score_a > score_b;
    }
  };

  // --- parse "13h30m" to minutes
  inline size_t parse_duration(const std::string& str) {
      std::regex pattern(R"((\d+)h(?:(\d+)m)?)");
      std::smatch match;
      if (std::regex_match(str, match, pattern)) {
          size_t hours = std::stoul(match[1]);
          size_t minutes = match[2].matched ? std::stoul(match[2]) : 0;
          return hours * 60 + minutes;
      }
      return 0;
  }

  // --- parse "2h,1h30m,4h15m" to total minutes
  inline size_t parse_connection_times(const std::string& str) {
    size_t total = 0;
    std::stringstream ss(str);
    std::string segment;
    while (std::getline(ss, segment, ',')) {
        total += parse_duration(segment);
    }
    return total;
  }
    
  inline flight parse_flight(const std::string& line) {
      flight f;
      // Updated pattern: capture flight_number first
      std::regex pattern(R"(flight_number:([^\s]+)\s*-\s*duration:(\S+)\s*-\s*connections:(\d+)\s*-\s*connection_times:(\S+)\s*-\s*price:(\d+))");
      std::smatch match;
      if (std::regex_search(line, match, pattern)) {
          f.flight_number = match[1];
          f.duration = parse_duration(match[2]);
          f.connections = std::stoul(match[3]);
          f.connection_times = parse_connection_times(match[4]);
          f.price = std::stoul(match[5]);
      }
      return f;
  }

  inline std::priority_queue<flight, std::vector<flight>, compareflight> gather_flights(const std::string filename){

    std::ifstream file(filename);
    std::string line;
    std::priority_queue<flight, std::vector<flight>, compareflight> pq;
    
    while (std::getline(file, line)){
      flight f = parse_flight(line);
      pq.push(f);
    }
    return pq;
 }

}
#endif //Q3_H
