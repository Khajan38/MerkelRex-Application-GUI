#include <iostream>
#include "Wallet.hpp"
using namespace std;

WalletClass::WalletClass (){
     wallet["BTC"] = 0.523798;
     wallet["ETH"] =  18.823674;
     wallet["DOGE"] =  1523.239622;
     wallet["USTD"] =  597.023246;
}

void WalletClass::insertCurrency (string product, double amount, bool hasToInsert){
     if (hasToInsert){
          if (wallet.count(product)) wallet[product] += amount;
          else wallet[product] = amount;
     }
     ImGui::Text((to_string(amount) + " " + product + " credited to Wallet...").c_str());
     return;
}

void WalletClass::removeCurrency (string product, double amount, bool hasToInsert){
     if (hasToInsert) wallet[product] -= amount; 
     ImGui::Text((to_string(amount) + " " + product + " debited to Wallet...").c_str());
}

bool WalletClass::hasCurrency (string product, double amount){
     try{
          if (amount <= 0){
               throw invalid_argument("Error: Invalid value for amount");
               return false;
          }
          auto it = wallet.find(product);
          if (wallet.count(product) && wallet[product] >= amount){
               ImGui::Text("%f %s present in Wallet...\n", it->second, product.c_str());
               return true;
          } else{
               ImGui::Text("Not enough %s in Wallet...\n", product.c_str());
               return false;
          }
     }
     catch(const invalid_argument& e) {
          ImGui::Text("\nError : %s\n", e.what()); 
          return false;
     }
}

bool WalletClass::canFullfillOrder (OrderBookEntry & entry){
     vector <string> currencies = callToknise(entry.getProduct(), '/');
     if (entry.getOrderType() == OrderBookType::ask){
          double amount = entry.getAmount();
          string currency = currencies[0];
          return hasCurrency (currency, amount);
     }
     else if (entry.getOrderType() == OrderBookType::bid){
          double amount = entry.getAmount() * entry.getPrice();
          string currency = currencies[1];
          return hasCurrency (currency, amount);
     }
     return false;
}

const unordered_map<std::string, double>& WalletClass::getWalletData() const {
    return wallet;
}