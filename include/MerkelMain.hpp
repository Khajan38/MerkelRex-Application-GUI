//MarkelMain Interface Functions

#pragma once
#include <iostream>
#include <vector>
#include "Display Basics.hpp"
#include "OrderBook.hpp"
#include "MerkelRex Engine.hpp"
#include "Wallet.hpp"
using namespace std;

class Help;

class MerkelMain{
    string fileName;
    OrderBook orderbook {fileName};
    WalletClass Wallet;
    string currentTime, firstTime;

public:
    MerkelMain(string fileName = "data.csv");
    AppState Main_Menu (std::vector <std::string> Menu_items);
    AppState processUserOption(int & choice);
    std::pair <bool, OrderBookEntry> BidAsk(int choice);
    AppState EngineWindow ();

    //Menu Options Functions
    AppState helpAndFeedback(void);
    AppState exchangeStatus(void);
    AppState placeAsk(void);
    AppState placeBid(void);
    AppState printWallet(void);
};