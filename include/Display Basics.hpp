#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <array>
#include <chrono>
#include <imgui.h>
#include <vulkan/vulkan.h>
#include <glfw/glfw3.h>

static constexpr auto WindowFlags = ImGuiWindowFlags_NoCollapse |
ImGuiWindowFlags_NoResize |
ImGuiWindowFlags_NoMove |
ImGuiWindowFlags_NoScrollbar |
ImGuiWindowFlags_NoTitleBar |
ImGuiWindowFlags_NoBringToFrontOnFocus;

static constexpr auto fixedWindowFlags = ImGuiWindowFlags_NoCollapse |
ImGuiWindowFlags_NoResize |
ImGuiWindowFlags_NoMove |
ImGuiWindowFlags_NoScrollbar | 
ImGuiWindowFlags_NoTitleBar;

extern ImVec4 textColor, separatorColor, backgroundColor, buttonColor, buttonHoveredColor, buttonActiveColor, frameColor;
extern ImFont * smallFont, * largeFont, *normalFont, *boldFont;

void LoadFonts();

enum class AppState {
    LoginPage,
    Main_Menu,
    Matching_Engine,
    Print_HelpMenu,
    Print_Exchange_Stats, 
    Place_Ask, 
    Place_Bid, 
    Print_Wallet, 
    ExitingWindow
};
class MerkelMain;

class Display{
     static std::array <std::string, 2> Exit_Parts;

     public:
          static void printLine(bool newLines);
          static bool sleepForSeconds(int timed);
          static ImVec2 padding (const std::string text);
          static void Header (const char * Heading);
          static AppState Bottom_Line (int page, AppState appstate);
          static void Exiting_Window ();
          static void PushStyles();
          static void PopStyles();
};

std::pair <std::string, AppState> LoginPage (void);