#include "MerkelMain.hpp"
using namespace std;

AppState MerkelMain::exchangeStatus(){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y - 30.0f));
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header("EXCHANGE STATUS WINDOW");
     ImGui::PushFont(normalFont);
     
     ImGui::SetCursorPos(Display::padding("MARKET STATISTICS OF " + currentTime));
     ImGui::Text(("MARKET STATISTICS OF " + currentTime).c_str());
     vector<string> productList = orderbook.getKnownProducts();
     for (string &p : productList){
          ImGui::NewLine(); ImGui::Text((p + " :").c_str());
          vector<OrderBookEntry> matchedEntries = orderbook.getOrders(OrderBookType::ask, p, currentTime);
          ImGui::Text(("\tNo. of Asks -> " + std::to_string(matchedEntries.size())).c_str());
          ImGui::Text(("\tMin Ask -> " + std::to_string(OrderBook::getLowPrice(matchedEntries))).c_str());
          ImGui::Text(("\tSMA of Asks -> " + std::to_string(OrderBook::simpleMovingAverage(matchedEntries))).c_str());
          ImGui::Text(("\tEMA of Asks -> " + std::to_string(OrderBook::exponentialMovingAverage(matchedEntries))).c_str());
     }
     return Display::Bottom_Line(2, AppState::Print_Exchange_Stats);
}

AppState MerkelMain::placeAsk (){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y - 30.0f));
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header("PLACE AN ASK WINDOW");
     ImGui::PushFont(normalFont);
     static bool done = false;
     static pair <bool, OrderBookEntry> entrybool;
     bool canProceed = entrybool.first;
     OrderBookEntry entry = entrybool.second;
     if (!done) {
          entrybool = BidAsk(3);
          canProceed = entrybool.first;
          entry = entrybool.second;
     }
     else {
          ImGui::Text("Placing an ask of : "); ImGui::NewLine();
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f);
          ImGui::Text((entry.getProduct().substr(0, 3) + " : Base Currency").c_str());
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f); 
          ImGui::Text((entry.getProduct().substr(4)  + " : Quote Currency").c_str());
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f);
          ImGui::Text((to_string(entry.getPrice())+ " : Price").c_str());
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f);
          ImGui::Text((to_string(entry.getAmount()) + " : Amount").c_str());
          ImGui::NewLine();
     }
     if (canProceed && Wallet.canFullfillOrder(entry)){
          static OrderBookEntry * entryReference = nullptr;
          if (!done) entryReference = orderbook.insertOrder(entry);
          vector <double> sales = newBidAskEngine(orderbook, currentTime, entryReference);
          vector <string> currencies = callToknise(entry.getProduct(), '/');
          if (done){
               Wallet.removeCurrency(currencies[0], sales[0], false);
               Wallet.insertCurrency(currencies[1], sales[1], false);
          } else {
               Wallet.removeCurrency(currencies[0], sales[0], true);
               Wallet.insertCurrency(currencies[1], sales[1], true);
               done = true;
          }
          AppState nextState = Display::Bottom_Line(2, AppState::Place_Ask);
          if (nextState == AppState::Main_Menu || nextState == AppState::ExitingWindow) done = false;
          return nextState;
     }
     Display::PopStyles(); ImGui::PopFont(); ImGui::End();
     return AppState::Place_Ask;
}

AppState MerkelMain::placeBid (){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y - 30.0f));
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header("PLACE AN BID WINDOW");
     ImGui::PushFont(normalFont);
     static bool done = false;
     static pair <bool, OrderBookEntry> entrybool;
     bool canProceed = entrybool.first;
     OrderBookEntry entry = entrybool.second;
     if (!done) {
          entrybool = BidAsk(4);
          canProceed = entrybool.first;
          entry = entrybool.second;
     }
     else {
          ImGui::Text("Placing an bid of : "); ImGui::NewLine();
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f);
          ImGui::Text((entry.getProduct().substr(0, 3) + " : Base Currency").c_str());
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f); 
          ImGui::Text((entry.getProduct().substr(4)  + " : Quote Currency").c_str());
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f);
          ImGui::Text((to_string(entry.getPrice())+ " : Price").c_str());
          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f);
          ImGui::Text((to_string(entry.getAmount()) + " : Amount").c_str());
          ImGui::NewLine();
     }
     if (canProceed && Wallet.canFullfillOrder(entry)){
          static OrderBookEntry * entryReference = nullptr;
          if (!done) entryReference = orderbook.insertOrder(entry);
          vector <double> sales = newBidAskEngine(orderbook, currentTime, entryReference);
          vector <string> currencies = callToknise(entry.getProduct(), '/');
          if (done){
               Wallet.removeCurrency(currencies[1], sales[1], false);
               Wallet.insertCurrency(currencies[0], sales[0], false);
          } else {
               Wallet.removeCurrency(currencies[1], sales[1], true);
               Wallet.insertCurrency(currencies[0], sales[0], true);
               done = true;
          }
          AppState nextState = Display::Bottom_Line(2, AppState::Place_Ask);
          if (nextState == AppState::Main_Menu || nextState == AppState::ExitingWindow) done = false;
          return nextState;
     }
     Display::PopStyles(); ImGui::PopFont(); ImGui::End();
     return AppState::Place_Ask;
}

AppState MerkelMain::printWallet() { 
     ImGuiIO& io = ImGui::GetIO();     
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y - 30.0f));
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); // New Window

     Display::Header("YOUR WALLET");
     ImGui::PushFont(normalFont);

     const auto& walletData = Wallet.getWalletData();
     if (walletData.empty()) {
          ImGui::SetCursorPos(Display::padding("Wallet is empty..."));
          ImGui::Text("Wallet is Empty...");
          return AppState::Print_Wallet;
     }

     float tableWidth = window_size.x * 0.5f;
     ImGui::SetCursorPosX((window_size.x - tableWidth) / 2);
     if (ImGui::BeginTable("WalletTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(tableWidth, 0))) {
          ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.4f, 0.8f, 1.0f));
          ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
          ImGui::PushFont(boldFont);

          ImGui::TableSetupColumn(" Currencies ", ImGuiTableColumnFlags_WidthStretch);
          ImGui::TableSetupColumn(" Total Amounts ", ImGuiTableColumnFlags_WidthStretch);

          ImGui::TableHeadersRow();
          ImGui::PopFont();
          ImGui::PopStyleColor(2);

          // Display wallet data
          for (const auto& currency : walletData) {
               ImGui::TableNextRow();
               ImGui::TableSetColumnIndex(0); // First column: Currency name
               ImGui::Text("%s", currency.first.c_str());
               ImGui::TableSetColumnIndex(1); // Second column: Amount
               ImGui::Text("%.6f", currency.second);
          }
          ImGui::EndTable();
     }
     return Display::Bottom_Line(2, AppState::Print_Wallet);
}