#include "Display Basics.hpp"
#include "MerkelMain.hpp"

std::pair <std::string, AppState> LoginPage (void){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(window_size);
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     Display::PushStyles();
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window

     Display::Header("MERKELREX DATABASE");

     ImGui::PushFont(normalFont);

     static bool pressed = false;
     static char inputBuffer[150] = "";
     const char* placeholder = "../data/data.csv";
     static std::string fileName = "";  // Final database file name
     ImGui::Text("Enter Database Location (Relative Path) : ");
     ImGui::SameLine();
     if (!pressed){
          if (strlen(inputBuffer) == 0) {
               ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() - 3));
               ImGui::SetNextItemWidth(window_size.x - ImGui::GetCursorPosX() - 135);
               ImGui::InputTextWithHint("##DatabaseInput", placeholder, inputBuffer, sizeof(inputBuffer));
          } else{
               ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() - 3));
               ImGui::SetNextItemWidth(window_size.x - ImGui::GetCursorPosX() - 135);
               ImGui::InputText("##DatabaseInput", inputBuffer, sizeof(inputBuffer));
          }
          ImGui::SameLine(); 
          ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY() - 3));
          if (ImGui::Button("Proceed")) pressed = true;
     }
     else{
          if (strlen(inputBuffer) == 0) {
               fileName = placeholder;
               ImGui::Text(fileName.c_str()); ImGui::NewLine();
               ImGui::SetCursorPos(Display::padding("Using Default Database: %s"+ fileName));
               ImGui::Text("Using Default Database: %s", fileName.c_str());
          } else {
               fileName = std::string("../data/") + std::string(inputBuffer);
               ImGui::Text(fileName.c_str()); ImGui::NewLine();
               ImGui::SetCursorPos(Display::padding("Using Database: %s"+ fileName));
               ImGui::Text("Using Database: %s", fileName.c_str());
          }
          ImGui::NewLine();
          return {fileName, AppState::LoginPage};
     }
     return {"\0", AppState::LoginPage};
}