#include "Help.hpp"
using namespace std;

AppState MerkelMain::helpAndFeedback(){
     Help help;
     help.helpMenu_items = {"MERKELREX APPLICATION : HELP MENU", "About The Application", "Help With Main Menu Options", "Usage Examples", "Error Handling", "Contact/Support"};
     help.TXTReader();
     static int Helpchoice = 0;
     if (Helpchoice) return help.HelpWindow(Helpchoice);
     else Helpchoice = help.Main_Menu(help.helpMenu_items);
     return AppState::Print_HelpMenu;
}

int Help::Main_Menu (std::vector <std::string> Menu_items){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(window_size);
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header(helpMenu_items[0].c_str());
     ImGui::PushFont(normalFont);

     int size = helpMenu_items.size();
     std::string Menu_items_padding (50, ' ');
     static int choice = 0;
     for (int i = 1; i < size; i++){
          std::string menuLine = "\n" + Menu_items_padding;
          ImGui::Text(menuLine.c_str());
          ImGui::SameLine();
          menuLine = 'A' + i - 1; menuLine += ".";
          if (ImGui::Button(menuLine.c_str())) choice = i;
          menuLine = helpMenu_items[i];
          ImGui::SameLine();
          ImGui::Text(menuLine.c_str());
     }
     if (choice){
          Display::printLine(true);
          ImGui::SetCursorPos(Display::padding("Initiating your request..."));
          ImGui::Text("Initiating your request...");
          static bool isWaiting = true;
          isWaiting = Display::sleepForSeconds(1);
          if (!isWaiting){
               Display::PopStyles(); ImGui::PopFont(); ImGui::End();
               int temp = choice; choice = 0;
               return temp;
          }
     }
     Display::PopStyles(); ImGui::PopFont(); ImGui::End();
     return 0;
}

AppState Help::HelpWindow (int& Helpchoice){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y - 30.0f));
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window
     
     Display::Header("HELP AND FEEDBACK");

     ImGui::PushFont(normalFont);
     processHelpOptions(Helpchoice);
     AppState nextState = Display::Bottom_Line(2, AppState::Print_HelpMenu);
     if (nextState == AppState::Main_Menu || nextState == AppState::ExitingWindow) Helpchoice = 0;
     return nextState;
}

void Help::processHelpOptions (int Helpchoice){
     switch (Helpchoice){
     case 1:
          about();
          break;
     case 2:
          menuOptions();
          break;
     case 3:
          usageExamples();
          break;
     case 4:
          errorHandling();
          break;
     case 5:
          support();
          break;
     }
     return;
}

void Help::about(void){ImGui::TextWrapped(Information[0].c_str());}
void Help::menuOptions(void){ImGui::TextWrapped(Information[1].c_str());}
void Help::usageExamples(void){ImGui::TextWrapped(Information[2].c_str());}
void Help::errorHandling(void){ImGui::TextWrapped(Information[3].c_str());}
void Help::support(void){
     ImGui::NewLine(); ImGui::TextWrapped("For further assistance, bug reports, or feedback on the MerkelRex Application, feel free to reach out to:");ImGui::NewLine();
     
     ImGui::Text("Developer : ");ImGui::SameLine(); DisplayLink("Khajan Bhatt", "https://khajan38.github.io/Portfolio/");
     ImGui::Text("Call : "); ImGui::SameLine(); DisplayLink("+91-8279571252", "tel:+918279571252");
     ImGui::Text("Mail : "); ImGui::SameLine(); DisplayLink("khajanbhatt@gmail.com", "mailto:tanujbhatt8279@gmail.com");
     ImGui::Text("Linked In: "); ImGui::SameLine(); DisplayLink("khajan_bhatt", "https://www.linkedin.com/in/khajanbhatt/");
     ImGui::Text("GitHub : "); ImGui::SameLine(); DisplayLink("Khajan38", "https://github.com/Khajan38");

     ImGui::Text("\nWe appreciate your feedback and contributions to improve the MerkelRex Application!"); ImGui::NewLine();
}

void Help::TXTReader(void){
     ifstream txtFile{"../docs/Help.txt"};
     if (!txtFile.is_open()) throw std::runtime_error("Could not open file: Help.txt");
     string txtLine; int lineNumber {0};
     getline(txtFile, txtLine, '#');
     while (getline(txtFile, txtLine, '#')) {
          getline(txtFile, txtLine, '#');
          try {
               if (txtLine == "") continue;
               lineNumber++;
               Information.push_back(txtLine);
          }
          catch (const std::exception& e) {
               string errorLine = "Error processing line " + to_string(lineNumber) + ": " + e.what() + "\n";
               ImGui::Text(errorLine.c_str());
               break;
          }
     }
     return;
}

void Help::DisplayLink(const char* label, const char* url, ImVec4 color) {
     ImGui::TextColored(color, "%s", label);
     if (ImGui::IsItemHovered()) {
          ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
          if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) ShellExecute(0, 0, url, 0, 0, SW_SHOW);
     }
}