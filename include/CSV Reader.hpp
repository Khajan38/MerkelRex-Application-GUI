#pragma once
#include <iostream>
#include <fstream>
#include <imgui.h>
#include "OrderBookEntry.hpp"
using namespace std;

class CSV_Reader{
          static OrderBookType stringToOrderBookType(const string& type);
          static vector <string> tokenise (const string csvLine, const char seperator);
          friend vector <string> callToknise (const string csvLine, const char seperator);
     public:
          CSV_Reader();
          static OrderBookEntry stringToOrderBookEntry (const vector <string> &tokens);
          static vector <OrderBookEntry> readCSV (const string csvFileInput);
};