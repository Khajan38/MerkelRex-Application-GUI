// MarkelMain Interface Functions Definitions

#include "MerkelMain.hpp"
using namespace std;

MerkelMain::MerkelMain(string fileName) : fileName(fileName){
     firstTime = orderbook.getEarliestTime();
     currentTime = firstTime;
} // Constructor for MerkelMain

AppState MerkelMain::Main_Menu (std::vector <std::string> Menu_items){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(window_size);
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header(Menu_items[0].c_str());

     ImGui::PushFont(normalFont);
     int size = Menu_items.size();
     std::string Menu_items_padding (50, ' ');
     static int choice = 0;
     for (int i = 1; i < size; ++i){
          std::string menuLine = "\n" + Menu_items_padding;
          ImGui::Text(menuLine.c_str());
          ImGui::SameLine();
          menuLine = 'A' + i - 1; menuLine += ".";
          if (ImGui::Button(menuLine.c_str())) choice = i;
          menuLine = Menu_items[i];
          ImGui::SameLine();
          ImGui::Text(menuLine.c_str());
     }
     if (choice && choice != 6){
          Display::printLine(true);
          ImGui::SetCursorPos(Display::padding("Initiating your request..."));
          ImGui::Text("Initiating your request...");
          static bool isWaiting = true;
          isWaiting = Display::sleepForSeconds(1);
          if (!isWaiting){
               Display::PopStyles(); ImGui::PopFont(); ImGui::End();
               return processUserOption(choice);
          }
     }
     else if (choice == 6){
          static string prevTime = currentTime;
          Display::printLine(true);
          ImGui::SetCursorPos(Display::padding("Continuing, Going to the next frame..."));
          ImGui::Text("Continuing, Going to the next frame..."); ImGui::NewLine();
          ImGui::Text(("Current Time is : " + prevTime).c_str()); ImGui::NewLine();
          if (prevTime == currentTime) currentTime = orderbook.getNextTime(currentTime);
          ImGui::Text(("Next Time is : " + currentTime).c_str());
          static bool isWaiting = true;
          isWaiting = Display::sleepForSeconds(2);
          if (!isWaiting){
               Display::PopStyles(); ImGui::PopFont(); ImGui::End();
               prevTime = currentTime;
               return processUserOption(choice);
          }
     }
     Display::PopStyles(); ImGui::PopFont(); ImGui::End();
     return AppState::Main_Menu;
}

AppState MerkelMain::processUserOption(int& choice) {
     AppState nextState = AppState::Main_Menu; // Default
     switch (choice) {
          case 1: nextState = AppState::Print_HelpMenu; break;
          case 2: nextState = AppState::Print_Exchange_Stats; break;
          case 3: nextState = AppState::Place_Ask; break;
          case 4: nextState = AppState::Place_Bid; break;
          case 5: nextState = AppState::Print_Wallet; break;
          case 6: nextState = AppState::Main_Menu; break;
          case 7: nextState = AppState::ExitingWindow; break;
          default: break;
     }
     choice = 0;
     return nextState;
}

pair <bool, OrderBookEntry> MerkelMain::BidAsk(int choice) {
     string a, b, product, price, amount;
     string orderType = (choice == 3) ? "ask" : "bid";
     static char baseCurrency[12] = "";
     static char quoteCurrency[12] = "";
     static char priceInput[12] = "";
     static char amountInput[12] = "";
     bool errorOccurred = false;
     string errorMessage;
     static bool submit = false;
     try {
          ImGuiIO& io = ImGui::GetIO();
          ImVec2 window_size = io.DisplaySize;
          ImGui::Text(("Placing an " + orderType + " of : ").c_str()); ImGui::NewLine();
          if (!submit){
               ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f); ImGui::SetNextItemWidth(200); 
               ImGui::InputText(": Base Currency", baseCurrency, IM_ARRAYSIZE(baseCurrency));
               ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f); ImGui::SetNextItemWidth(200);
               ImGui::InputText(": Quote Currency", quoteCurrency, IM_ARRAYSIZE(quoteCurrency));
               ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f); ImGui::SetNextItemWidth(200);
               ImGui::InputText(": Price", priceInput, IM_ARRAYSIZE(priceInput));
               ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 150.0f); ImGui::SetNextItemWidth(200); 
               ImGui::InputText(": Amount", amountInput, IM_ARRAYSIZE(amountInput));
               ImGui::NewLine(); ImGui::NewLine(); ImGui::SetCursorPosX(window_size.x/2 - 80.0f);
               if (ImGui::Button("Submit")) submit = true;
          }
          else{
               a = baseCurrency;
               b = quoteCurrency;
               product = a + "/" + b;
               price = priceInput;
               amount = amountInput;
               if (a.empty() || b.empty() || price.empty() || amount.empty()) {
                    errorOccurred = true; ImGui::SetCursorPos(Display::padding("All feilds are required..."));
                    errorMessage = "All fields are required...";
                    throw std::runtime_error(errorMessage);
               }
               if (std::stod(price) <= 0 || std::stod(amount) <= 0) {
                    errorOccurred = true;
                    errorMessage = "Price and amount must be positive numbers.";
                    throw std::runtime_error(errorMessage);
               }
               submit = false;
               std::vector<std::string> tokens{currentTime, product, orderType, price, amount};
               CSV_Reader::stringToOrderBookEntry(tokens).display();
               return {true, CSV_Reader::stringToOrderBookEntry(tokens)};
          }
     } catch (const std::exception& e){
          submit = false;
          errorOccurred = true;
          errorMessage = e.what();
     }
     if (errorOccurred) ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), errorMessage.c_str());
     return {false, OrderBookEntry()}; 
}

AppState MerkelMain::EngineWindow(){
     return matchingEngine(orderbook, currentTime);
}