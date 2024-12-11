#pragma once
#include <iostream>
#include <windows.h>
#include "Display Basics.hpp"
#include "MerkelMain.hpp"
using namespace std;

class Help {
     friend MerkelMain;
     vector <string> Information;
     vector <string> helpMenu_items;
     public :
          int Main_Menu (std::vector <std::string> Menu_items);
          AppState HelpWindow (int& choice);
          void processHelpOptions(int helpChoice);
          void about(void);
          void menuOptions(void);
          void usageExamples(void);
          void errorHandling(void);
          void support(void);
          void TXTReader(void);
          void DisplayLink(const char* label, const char* url, ImVec4 color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
};