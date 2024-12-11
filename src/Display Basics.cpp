#include "Display Basics.hpp"

std::array <std::string, 2> Display::Exit_Parts {"MERKELREX APPLICATION", "MerkelRex Application"};

ImVec4 textColor, separatorColor, backgroundColor, buttonColor, buttonHoveredColor, buttonActiveColor, frameColor;
ImFont* smallFont = nullptr, *largeFont = nullptr, *normalFont = nullptr, *boldFont = nullptr;

void LoadFonts(){
     textColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);             //Text Color
     frameColor = ImVec4(0.8f, 0.9f, 1.0f, 1.0f);            //Frames Color
     separatorColor = ImVec4(0.2f, 0.2f, 0.3f, 1.0f);        //Separator or Underline Color
     backgroundColor = ImVec4(0.7f, 0.8f, 0.9f, 1.0f);       // Slightly darker blueish tone
     buttonColor = ImVec4(0.5f, 0.7f, 0.9f, 1.0f);           // Base button color
     buttonHoveredColor = ImVec4(0.4f, 0.6f, 0.8f, 1.0f);    // Slightly darker when hovered
     buttonActiveColor = ImVec4(0.3f, 0.5f, 0.7f, 1.0f);     // Darker when active (clicked)

     //Loading Fonts
     if (ImGui::GetCurrentContext() == nullptr) ImGui::CreateContext();
     ImGuiIO& io = ImGui::GetIO(); // Now you can load fonts
     normalFont = io.Fonts->AddFontFromFileTTF("../dependencies/Consolas/CONSOLA.TTF", 25.0f);
     if (!normalFont) std::cerr << "Failed to load small font.\n";
     largeFont = io.Fonts->AddFontFromFileTTF("../dependencies/Arial/ARIBL0.ttf", 50.0f);
     if (!largeFont) std::cerr << "Failed to load large font.\n";
     smallFont = io.Fonts->AddFontFromFileTTF("../dependencies/Consolas/Consolas.ttf", 20.0f);
     if (!smallFont) std::cerr << "Failed to load small font.\n";
     boldFont = io.Fonts->AddFontFromFileTTF("../dependencies/Arial/ARIBL0.ttf", 35.0f);
     if (!boldFont) std::cerr << "Failed to load large font.\n";
}

void Display::printLine(bool newLines = true) {
    if (newLines) ImGui::NewLine();
    ImU32 color = ImColor(separatorColor);
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    float separatorStartX = windowPos.x;
    float separatorEndX = windowPos.x + windowSize.x;
    float separatorY = windowPos.y + ImGui::GetCursorPosY() - ImGui::GetScrollY();
    drawList->AddLine(ImVec2(separatorStartX, separatorY), ImVec2(separatorEndX, separatorY), color, 6.0f);
    ImGui::NewLine();
}

ImVec2 Display::padding(const std::string text){
     ImVec2 windowSize = ImGui::GetWindowSize();
     float windowWidth = windowSize.x;
     float windowHeight = windowSize.y;
     ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
     float xPos = (windowWidth - textSize.x) * 0.5f; // Center horizontally
     return ImVec2(xPos, ImGui::GetCursorPosY());
}

void Display::Header (const char * Heading){
     ImGui::PushFont(smallFont); //Small Font pushed for Navigation Bar

     ImGuiIO& io = ImGui::GetIO(); // Retrieve ImGui input/output settings
     ImVec2 window_size = io.DisplaySize; // Get current window width and height

     //Top Navigation Bar
     ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
     ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.3f, 1.0f));
     ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.3f, 1.0f));

     float top_bar_height = 40.0f; // Adjust height as needed
     ImGui::SetNextWindowPos(ImVec2(0, 0));
     ImGui::SetNextWindowSize(ImVec2(window_size.x, top_bar_height));
     ImGui::Begin("Top Navigation Bar", nullptr, fixedWindowFlags);
     ImGui::Button("MERKELREX APPLICATION");

     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.5f, 0.7f, 1.0f));
     ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.4f, 0.6f, 1.0f));
     ImGui::SameLine(ImGui::GetContentRegionAvail().x - 300);
     if (ImGui::Button("Contact Developer")) {
          std::system("start https://www.linkedin.com/in/khajanbhatt/");
     }
     ImGui::SameLine();
     ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 28.0f); // Add 50 pixels
     if (ImGui::Button("Exit")) exit(0);
     ImGui::PopStyleColor();
     ImGui::PopStyleColor();

     ImGui::End();
     ImGui::PopStyleColor();
     ImGui::PopStyleColor();
     ImGui::PopStyleColor();

     //Middle Part
     ImGui::NewLine(); ImGui::NewLine();
     ImGui::PushFont(largeFont);  // Push the large font
     ImGui::SetCursorPos(padding(Heading));
     ImGui::Text(Heading);
     ImGui::PopFont();  // Pop the font back to default
     printLine(); ImGui::NewLine();

     //Bottom Status Bar
     float bottom_bar_height = 30.0f; // Adjust height as needed
     ImGui::SetNextWindowPos(ImVec2(0, window_size.y - bottom_bar_height));
     ImGui::SetNextWindowSize(ImVec2(window_size.x, bottom_bar_height));
     ImGui::Begin("Bottom Status Bar", nullptr, fixedWindowFlags);
     ImGui::Text("Status: All systems operational");
     ImGui::End();

     ImGui::PopFont();
}

bool Display::sleepForSeconds(int seconds) {
     static auto startTime = std::chrono::steady_clock::now();
     static bool isTiming = false;
     if (!isTiming) {
          startTime = std::chrono::steady_clock::now();
          isTiming = true;
     }
     auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::steady_clock::now() - startTime
     );
     if (elapsed.count() >= seconds) {
          isTiming = false;
          return false;
     }
     return true;
}

AppState Display::Bottom_Line(int page, AppState appState) {
     printLine();
     ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - 150, ImGui::GetCursorPosY()));
     char menu_choice = '\0';
     if (ImGui::Button("Main Menu")) menu_choice = 'M';
     ImGui::SameLine();
     ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
     if (ImGui::Button((page == 1)? "Matching Engine" : "Exit")) menu_choice = 'E';
     if (menu_choice == 'E'){
          PopStyles(); ImGui::PopFont(); ImGui::End();
          return (page == 1)? AppState::Matching_Engine : AppState::ExitingWindow;
     }
     else if (menu_choice == 'M'){
          PopStyles(); ImGui::PopFont(); ImGui::End();
          return AppState::Main_Menu;
     }
     PopStyles(); ImGui::PopFont(); ImGui::End();
     return appState;
}

void Display::Exiting_Window (){
     ImGuiIO& io = ImGui::GetIO();
     ImVec2 window_size = io.DisplaySize;

     ImGui::SetNextWindowSize(window_size);
     ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
     PushStyles();
     
     ImGui::Begin("MerkelRex Application", nullptr, WindowFlags); //New Window

     std::string exitLine = Display::Exit_Parts[0] + ": EXIT WINDOW";
     Header(exitLine.c_str());
     ImGui::PushFont(normalFont);

     ImGui::SetCursorPos(padding("Thank You!")); ImGui::Text("Thank You!"); ImGui::NewLine();
     exitLine = "for using "+Exit_Parts[1];
     ImGui::SetCursorPos(padding(exitLine)); ImGui::Text(exitLine.c_str()); ImGui::NewLine(); ImGui::NewLine();
     ImGui::SetCursorPos(padding("WE WILL WAIT FOR YOU!...")); ImGui::Text("WE WILL WAIT FOR YOU!..."); ImGui::NewLine();
     printLine();

     static bool isWaiting = true;
     isWaiting = Display::sleepForSeconds(2);
     if (!isWaiting) {
          ImGui::PopFont();
          ImGui::End(); //Ended the Opened Window
          PopStyles();
          exit(0);
     }

     ImGui::PopFont();
     ImGui::End(); //Ended the Opened Window
     PopStyles();
}

void Display::PushStyles (){
     ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
     ImGui::PushStyleColor(ImGuiCol_Text, textColor);
     ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
     ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonActiveColor);
     ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonHoveredColor);
     ImGui::PushStyleColor(ImGuiCol_FrameBg, frameColor);
}

void Display::PopStyles(){
     for (int i = 0; i < 6; ++i) ImGui::PopStyleColor();
}