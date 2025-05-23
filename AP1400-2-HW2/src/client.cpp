#include "client.h"
#include "server.h"

Client(std::string id, const Server& server) : id(id), server(&server){
  crypto::generate_key(this->public_key, this->private_key);
}

std::string get_id(){
  return this->id;
}

std::string get_publickey(){
  return this->public_key;
}

double get_wallet() const{
  return server->get_wallet((this->id));
}

std::string sign(std::string txt){
  return crypto::signMassage(this->private_key, txt);
}

bool transfer_money(std::string receiver, double value){
  std::string trx = this->id + "-" + receiver + "-" + std::to_string(valuea);
  if (value > get_wallet()){
    throw std::runtime_error("Don't have enough value in your account");
  }

  return server->add_pending_trx(trx, sign(trx)); 
}

size_t generate_nonce(){
  std::random rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, INT_MAX);
  return dist(gen());
}

void  show_wallets(const  Server& server)
{
std::cout << std::string(20, '*') << std::endl;
for(const auto& client: server.clients)
  std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
std::cout << std::string(20, '*') << std::endl;
}
