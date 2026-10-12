#include <iostream>
#include <ostream>

#include "Achievements.h"
#include "Colors.h"
#include "Game.h"

Colors* Colors::s_instance = nullptr;
Achievements* Achievements::m_instance = nullptr;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Game* game = new Game;
    game->run();
    delete game;

    std::cout <<"Thanks for playing\nCreators: xspilka1, xgabrie3, xzouha10, xstefka"<< std::endl;
    std::cin.get();




}