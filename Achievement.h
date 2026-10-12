//
// Created by Radek on 21.06.2026.
//

#ifndef PROJEKT_ZOO_ACHIVEMENT_H
#define PROJEKT_ZOO_ACHIVEMENT_H
#include <string>
#include <vector>

struct Achievement {
    std::string id;
    std::string title;
    std::string description;
    bool unlocked;
    std::vector<std::string> icon;
};



#endif //PROJEKT_ZOO_ACHIVEMENT_H
