#include <iostream>   // for standard input and output
#include <string>     // for string operations
#include <vector>     // for using the vector container
#include <thread>     // for multi-threading
#include <chrono>     // for time-based functions
#include <Windows.h>  // for Windows-specific functions
#include "utilities/memory.h"  // custom memory management functions

// menu colors using ANSI escape codes
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string white = "\033[37m";
const std::string reset = "\033[0m";

// offsets for game memory addresses
constexpr auto localPlayer = 0x10F4F4;
constexpr auto health = 0xF8;
constexpr auto armor = 0xFC;
constexpr auto mtpAmmo = 0x150;
constexpr auto nameOffsetWithinPadding = 0x0225;

// class to handle name padding in memory
class NamePadding {
public:
    char preNamePadding[549];
    char maxCharactersInName[16];
    char postNamePadding[3609];
};

// main function - entry point of the program
int main() {
    // create a Memory object for the game "ac_client.exe"
    Memory memory{ "ac_client.exe" };
    // get the base address of the game module
    const auto ModuleBaseAddress = memory.GetModuleAddress("ac_client.exe");

    // calculate addresses for player-related data
    const auto localPlayerAddress = memory.Read<std::uintptr_t>(ModuleBaseAddress + localPlayer);
    const auto healthAddress = localPlayerAddress + health;
    const auto armorAddress = localPlayerAddress + armor;
    const auto mtpAmmoAddress = localPlayerAddress + mtpAmmo;
    const auto paddingAddress = localPlayerAddress + nameOffsetWithinPadding;

    // read the player's name from memory
    std::string name = memory.Read<NamePadding>(paddingAddress).preNamePadding;

    // vector containing the new logo art
    std::vector<std::string> logo {
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠿⠋⠛⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠃⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡇⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠁⠀⠀⠀⠀⠀⠀⠀⣾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠔⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⢀⡔⠉⠀⠀⠀⠀⣠⣴⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱⣄⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣤⣤⣤⡀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⢠⠋⣠⣦⣟⣻⣦⣼⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢶⠒⠛⠉⠉⠀⠀⠀⠀⠀⣹⣿⣿⣿⣦⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⢸⠀⡏⠿⣎⣿⠏⠹⠟⠿⠟⠁⠀⠀⠀⠀⠀⠀⠀⢀⣴⣶⣶⣤⠀⠈⠃⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣷⡀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠈⡆⠛⠷⠟⢻⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⣀⡠⠜⠛⠛⢯⣙⠿⣿⣷⣄⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠹⡄⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⡿⠃⠀⠀⡀⠀⣠⠴⠊⠁⠀⠀⠀⠀⠀⠈⠓⢽⣿⣿⣷",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡀⠀⠘⢿⣿⣿⣿⣷⣆⠀⠀⠀⠀⠀⠀⠈⠻⢿⠿⠛⠡⣄⠀⢠⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⡀⠀⠀⠀⠀⠀⠸⣿⣤⣤⡀⠀⠀⠀⣤⣲⣖⠢⡀⠀⠀⠀⡜⠀⠀⠀⠀⠀⠀⠀⣀⣤⢄⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣦⡀⠀⠀⠀⠀⠈⠉⠻⣿⣤⣤⣿⣶⠆⣩⠿⠅⠀⠀⡜⠁⠀⠀⠀⢀⡤⠖⠋⠀⣾⠈⣧⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⠑⠦⢀⠀⠀⠀⠀⠙⠻⣋⣩⣭⣶⣞⠋⠀⢀⡞⠀⠀⠀⣠⠖⠉⠀⠀⠀⠀⢻⡀⢸⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⠀⠀⠀⠀⠀⠀⠐⢲⡤⠀⠈⠉⠉⠉⠁⣀⡠⠴⠋⠀⠀⡠⠎⠁⠀⢀⡠⠄⠀⠀⠸⡀⢸⠄⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢙⡏⠉⠉⠉⠉⠁⠀⠀⠀⣠⠞⠁⢀⣤⠞⣉⠄⠀⢀⡠⢔⡳⠋⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⢀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⠀⠀⠀⠀⠀⢰⠁⠀⠀⠛⠐⠋⣀⠤⣒⡭⠒⠋⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢦⠀⠀⠀⠀⠈⢦⡀⠀⢠⠴⠟⠚⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⣾⣇⠀⠀⠀⠀⠈⢷⠀⠀⢀⡴⠋⠀⠀⠈⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⠀⡏⠀⠀⠀⠀⠀⠀⢸⡗⠀⠀⠀⠸⣿⠀⠀⠀⠀⠀⠀⢧⠀⢏⠀⠈⢳⡶⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⣸⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡄⠀⣳⠄⠀⡃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠀⠀⠀⠀⠀⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⡞⢁⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠀⠻⣗⣒⠒⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠓⠤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⣠⠤⠖⠛⣛⡻⢶⣄⠀⠀⠀⠀⣀⣀⡀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⢠⣤⣤⣄⣀⣀⣈⣱⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
        "⠉⠉⠉⠉⠉⠗⠚⠹⣤⡖⠊⠉⠻⠿⠋⠑⢦⣄⣴⠿⣽⣿⠒⠲⣤⣤⣀⣈⡷⠤⠤⠵⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
    };

    // print the logo with cyan color
    std::cout << std::endl;
    for (const auto& line : logo) std::cout << cyan << line << reset << std::endl;
    std::cout << std::endl << yellow << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << reset << std::endl << std::endl;

    // print welcome message and menu options
    std::cout << "Welcome to desynced, " << magenta << name << "\n" << std::endl;
    std::cout << green << "F1: Health Hack" << reset << std::endl;
    std::cout << green << "F2: Armor Hack" << reset << std::endl;
    std::cout << green << "F3: Rifle Ammo Hack" << reset << std::endl << std::endl;

    // infinite loop to check for key presses
    while (true) {
        // check if F1 key is pressed
        if (GetAsyncKeyState(VK_F1) & 0x8000) {
            // write 1000 to health address
            memory.Write<int>(healthAddress, 1000);
            std::cout

