#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <numeric>  // for std::accumulate
#include <stdexcept> // for std::invalid_argument
#include <memory>
#include <map>
#include <random>
#include <iostream>
#include "client.h"

class Server
{
  public:
    Server();
    std::shared_ptr<Client> add_client(std::string id);
    std::shared_ptr<Client> get_client(std::string id);
    double get_wallet(std::string id);
    bool parse_trx(std::string trx, std::string sender, std::string receiver, double value);
    bool add_pending_trx(std::string trx, std::string signature);
    size_t mine();
    double get_wallet();
  private:
    std::map<std::shared_ptr<Client>, double> clients;
}

std::vector<std::string> pending_trxs;
void show_pending_transactions();
void show_wallets(const Server& server);
#endif //SERVER_H
