#include <iostream>
#include <unordered_map>
#include <format>
#include "MerkelRex Engine.hpp"
using namespace std;

class WalletClass {
          unordered_map <string, double> wallet;
     public :
          WalletClass (); //Constructor
          void insertCurrency (string product, double amount, bool hasToInsert);
          void removeCurrency (string product, double amount, bool hasToInsert);
          bool hasCurrency (string product, double amount);
          bool canFullfillOrder (OrderBookEntry & order);
          const unordered_map<std::string, double>& getWalletData() const;
};