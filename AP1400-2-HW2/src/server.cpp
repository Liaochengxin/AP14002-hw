#include "server.h"

#include "client.h"

std::vector<std::string> pending_trxs;

Server() {};

std::shared_ptr<Client> add_client(std::string id){
  for (const auto& [client, balance] : clients){
    if (client->get_id() == id){
      std::random rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(1000, 9999);
      id += std::string(dist(gen());
      }
  }

  auto new_client = std::shared_ptr<Client>(id, *this);

  clients[new_client] = 5.0;

  return clients;
}

std::shared_ptr<Client> get_client(std::string id){
  for (const auto& [client, balance] : clients){
      if (client->get_id() == id){
        return client;
      }
  }
  return nullptr;
}

double get_wallet(std::string id) const{
  for (const auto& [client, balance] : clients){
    if (client->get_id() == id){
      return balance;
    }
  }
  throw std::runtime_error("client is not exist");
}

bool parse_trx(std::string trx, std::string sender, std::string receiver, double value){
  //format sender-receiver-value
  if (trx.empty()){
    throw std::runtime_error("Empty transaction string");
  }
  size_t first_dash = trx.find("-");
  size_t second_dash = trx.rfind("-");
  // Validate dash positions
  if (first_dash == std::string::npos || 
      last_dash == std::string::npos || 
      first_dash == last_dash) {
    throw std::runtime_error("Invalid transaction format - needs two dashes");
  }

  sender = trx.substr(0, first_dash);
  if (sender.empty()){
    throw std::runtime_error("Sender ID can't be empty");
  }

  receiver = trx.substr(first_dash+1, second_dash - first_dash-1);
  if (receiver.empty()){
    throw std::runtime_error("receiver ID can't be empty");
  }

  value = trx.substr(second_dash+1);

  try {
    // Attempt risky operation
    size_t pos = 0;
    value = std::stod(value_str, &pos);  // <-- Potentially throws exceptions

    // Additional validation
    if (pos != value_str.length()) {
      throw std::runtime_error("Invalid characters in value");
    }
    if (value <= 0) {
      throw std::runtime_error("Value must be positive");
    }
  } 
  catch (const std::invalid_argument&) {
    throw std::runtime_error("Invalid value format");
  } 
  catch (const std::out_of_range&) {
    throw std::runtime_error("Value out of range");
  }
  return true;

}

bool add_pending_trx(std::string trx, std::string signature){
  if (trx.empty() || signature.empty()){
    return false;
  }

  size_t first_dash = trx.find("-");

  if (trx.substr(0, first_dash) != signature){
    return false;
  }
  //std::string trx_record = trx + "|" + signature;

  pending_trxs.push_back(trx);

  return true;
}

size_t mine(){
  if (pending_trxs.empty()){
    std::cout << "No transactions to mine" << std::endl;
    return 0;
  }

  std::string mempool;
  for (const auto& trx:pending_trxs){
    mempool += trx;
  }

  size_t nonce = 0;
  std::string hash;

  for (const auto&  [client, balance]:clients){
    size_t nonce = client->generate_nonce();
    std::string candidate = mempool + std::to_string(nonce);

    hash = sha256(candidate);

    if (hash.substr(0,10).find("000") != std::string::npos){
      balance += 6.25;
     
      for (const auto& trx:pending_trxs){
        std::string sender, receiver;
        double value;
        Server::parse_trx(trx, sender, receiver, value);
        clients[sender] -= value;
        clients[receiver] += value;
      }
      std::cout << "Mined by: " << client->get_id() << " with nonce: " << nonce << std::endl;
      pending_trxs.clear();
      return nonce;
    }
  }
  std::cout << "Mining failed this round" << std::endl;
  return 0;
}



//// Function to extract the numeric value from a single transaction
//double extract_value(const std::string& transaction) {
//    // Find the last '-' which precedes the value
//    size_t last_dash = transaction.find_last_of('-');
//    if (last_dash == std::string::npos || last_dash == transaction.length() - 1) {
//        return 0.0; // Invalid format
//    }
//    return std::stod(transaction.substr(last_dash + 1));
//}
//
//// Function to calculate the sum of all pending transaction values
//double sum_pending_values() {
//  if (pending_trxs.empty){
//    return 0;
//  }
//  return std::accumulate(
//      pending_trxs.begin(), 
//      pending_trxs.end(), 
//      0.0,
//      [](double sum, const std::string& trx) {
//            return sum + extract_value(trx);
//        });
//}
