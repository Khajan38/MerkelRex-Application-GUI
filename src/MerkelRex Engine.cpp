#include <iostream>
#include "MerkelRex Engine.hpp"
using namespace std;

AppState matchingEngine (OrderBook & orderbook, string currentTime){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y - 30.0f));
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header("MATCHING ENGINE : MATCHING PENDING BIDS AND BIDS");
     ImGui::PushFont(normalFont);

     vector <string> products = orderbook.getKnownProducts();
     for (string & product : products){
          ImGui::NewLine(); ImGui::Text((product + " :").c_str());
          vector <OrderBookEntry *> asks, bids;
          vector <OrderBookEntry> sales = orderbook.matchAsksToBids(product, currentTime, asks, bids);
          // Sales statistics
          ImGui::Text(("No. of Sales -> " + std::to_string(sales.size())).c_str());
          ImGui::Text(("Max Sale -> " + std::to_string(OrderBook::getHighPrice(sales))).c_str());
          ImGui::Text(("Min Sale -> " + std::to_string(OrderBook::getLowPrice(sales))).c_str());
          ImGui::Text(("SMA of Sales -> " + std::to_string(OrderBook::simpleMovingAverage(sales))).c_str());
          ImGui::Text(("EMA of Sales -> " + std::to_string(OrderBook::exponentialMovingAverage(sales))).c_str());
     }
     return Display::Bottom_Line(2, AppState::Matching_Engine);
}

vector <double> newBidAskEngine (OrderBook & orderbook, string currentTime, OrderBookEntry * &entry){
     static OrderBookEntry * prevEntry = nullptr;
     static vector <OrderBookEntry> sales;

     if (!prevEntry || !(*entry == *prevEntry)){
          if (entry == nullptr) return {0, 0};
          vector <OrderBookEntry *> asks, bids;
          if (entry->getOrderType() == OrderBookType::ask) asks.push_back(entry);
          else bids.push_back(entry);
          sales = orderbook.matchAsksToBids(entry->getProduct(), currentTime, asks, bids);
     }

     ImGui::SetCursorPos(Display::padding("SALES"));
     ImGui::Text("SALES"); ImGui::NewLine();
     
     // Sales statistics
     ImGui::Text(("No. of Sales -> " + std::to_string(sales.size())).c_str());
     ImGui::Text(("Max Sale -> " + std::to_string(OrderBook::getHighPrice(sales))).c_str());
     ImGui::Text(("Min Sale -> " + std::to_string(OrderBook::getLowPrice(sales))).c_str());
     ImGui::Text(("SMA of Sales -> " + std::to_string(OrderBook::simpleMovingAverage(sales))).c_str());
     ImGui::Text(("EMA of Sales -> " + std::to_string(OrderBook::exponentialMovingAverage(sales))).c_str());

     double totalAmount{0}, totalCurrAmount{0};
     for (OrderBookEntry & e : sales) {
          totalCurrAmount += e.getAmount() * e.getPrice();
          totalAmount += e.getAmount();
     }
     prevEntry = entry;
     return {totalAmount, totalCurrAmount};
}

vector <string> callToknise (const string csvLine, const char seperator){
     vector <string> tokens = CSV_Reader::tokenise (csvLine, seperator);
     return tokens;
}