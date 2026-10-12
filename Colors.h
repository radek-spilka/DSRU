//
// Created by Radek on 19.06.2026.
//

#ifndef PROJEKT_ZOO_COLORS_H
#define PROJEKT_ZOO_COLORS_H

#include <string>

class Colors {
    static Colors * s_instance;

    Colors();
public:
    static Colors* getInstance();

    const std::string RADIATION_COLOR = "\x1b[92m";
    const std::string RADIATION_ICON_COLOR = "\x1b[92m";
    const std::string ENEMY_COLOR = "\x1b[91m";
    const std::string HATCH_COLOR = "\x1b[97m";
    const std::string LOCKED_HATCH_COLOR = "\x1b[91m";
    const std::string INNER_WALL_COLOR = "\x1b[90m";
    const std::string OUTER_WALL_COLOR = "\x1b[97m";
    const std::string DRONE_COLOR = "\x1b[35m";
    const std::string ENERGY_COLOR = "\x1b[94m";
    const std::string INTERACTION_MESSAGE_COLOR = "\x1b[97m";
    const std::string FINAL_COLOR = "\x1b[93m";
    const std::string MALFUNCTION_TEXT_COLOR = "\x1b[91m";
    const std::string HAZARD_ICON_COLOR = "\x1b[91m";
    const std::string ICON_COLOR = "\x1b[32m";
    const std::string INVENTORY_COLOR = "\x1b[97m";
    const std::string DSRD_LOGO = "\x1b[93m";
    const std::string MAIN_MENU_TEXT = "\x1b[90m";
    const std::string MAIN_MENU_SELECTED_TEXT = "\x1b[97m";
    const std::string FRAME_COLOR = "\x1b[90m";
    const std::string PROLOGUE_COLOR = "\x1b[91m";
    const std::string NORMAL_TEXT = "\x1b[97m";
    const std::string DARK_NORMAL_TEXT = "\x1b[37m";
    const std::string LOSE_TEXT = "\x1b[91m";
    const std::string VICTORY_TEXT = "\x1b[92m";
    const std::string TIME_TEXT = "\x1b[93m";
    const std::string OPTIONS_TEXT = "\x1b[37m";
    const std::string MESSAGE_TEXT = "\x1b[94m";
    const std::string VICTORY1_TEXT = "\x1b[92m";
    const std::string CREDITS_HEADER_TEXT = "\x1b[90m";
    const std::string CREDITS_NAMES_TEXT = "\x1b[93m";
    const std::string ACHIEVEMENTS_LOCKED = "\x1b[90m";
    const std::string ACHIEVEMENTS_UNLOCKED = "\x1b[93m";
    const std::string ACHIEVEMENTS_ICON = "\x1b[33m";


};


#endif //PROJEKT_ZOO_COLORS_H
