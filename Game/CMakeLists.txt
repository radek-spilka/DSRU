cmake_minimum_required(VERSION 3.20)

project(Projekt-zoo)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Projekt-zoo main.cpp
        Input.cpp
        Input.h
        Renderer.cpp
        Renderer.h
        Hatch.cpp
        Hatch.h
        Module.cpp
        Module.h
        Station.cpp
        Station.h
        ModuleFactory.cpp
        ModuleFactory.h
        Position.h
        Action.h
        Drone.cpp
        Drone.h
        Item.cpp
        Item.h
        ItemType.h
        Hazard.h
        HazardType.h
        Game.cpp
        Game.h
        Menu.cpp
        Menu.h
        IGameState.h
        MainMenuState.cpp
        MainMenuState.h
        PlayingState.cpp
        PlayingState.h
        HackingGameState.cpp
        HackingGameState.h
        ICommand.h
        NewGameCommand.cpp
        NewGameCommand.h
        ResumeGameCommand.cpp
        ResumeGameCommand.h
        ExitGameCommand.cpp
        ExitGameCommand.h
        MenuItem.h
        ItemFactory.cpp
        ItemFactory.h
        HazardFactory.cpp
        HazardFactory.h
        Radiation.cpp
        Radiation.h
        Malfunction.cpp
        Malfunction.h
        Enemy.cpp
        Enemy.h
        CreditsCommand.cpp
        CreditsCommand.h
        CreditsState.cpp
        CreditsState.h
        VictoryState.cpp
        GameOverState.cpp
        GameOverState.h
        ProlougeState.cpp
        ProlougeState.h
        Colors.cpp
        Colors.h
        LoadGameCommand.cpp
        LoadGameCommand.h
        SaveGameCommand.cpp
        SaveGameCommand.h
        Achievements.cpp
        Achievements.h
        Achievement.h
        AchievementsState.cpp
        AchievementsState.h
        AchievementsCommand.cpp
        AchievementsCommand.h
        MainMenuCommand.cpp
        MainMenuCommand.h
)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")