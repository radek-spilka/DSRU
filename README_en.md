<div align="center">

```text
 _____   _____ _____  _    _ 
|  __ \ / ____|  __ \| |  | |
| |  | | (___ | |__) | |  | |
| |  | |\___ \|  _  /| |  | |
| |__| |____) | | \ \| |__| |
|_____/\_____/|_|  \_\\____/ 
                             
  Deep Space Repair Unit
```

</div>
This project was created as part of the ZOO (Fundamentals of Object-Oriented Design) course. Its main goal was to create a sophisticated game with an emphasis on clean code, object-oriented design, and the use of design patterns.

## 👥 Authors
[@radek-spilka](https://github.com/radek-spilka) <br>
[@martin-gabriel](https://github.com/IamNitramis)

## 🎮 About the Game
In this game, you take control of a repair drone aboard a massive, gradually decaying space station. The internal schematics of this modular station have been lost, so careful exploration of the unknown environment awaits you. 

Your ultimate goal? To reach the blocked-off section of the ship where the main control center is located. There, you must run a return program on the main computer, which will safely navigate the entire ship back home. Along the way, however, you will need to repair critical systems (marked with **!**) and avoid various hazards.

## ⚙️ Game Mechanics
*   **Procedural module generation:** The game starts in the initial "Airlock" location. As soon as you head in an unexplored direction, a new module is randomly generated (the entire game is on a 50x50 grid, and each module is always 7x7 characters).
*   **Logical continuity:** New modules are generated so that their airlocks (doors == hatches) correctly connect to existing corridors. Sometimes you will come across locked doors, which can be unlocked later over time.
*   **Upgrades and inventory:** During your exploration, you collect components, batteries, and decoding chips. These items can be used later :).
*   **Hazards and combat:** Modules can hide radiation leaks that gradually damage the drone's integrity (HP). Another obstacle is rogue security bots, encounters with which can be resolved either by consuming energy or through a special hacking mini-game.

## 🖥️ ASCII Visualization
The game uses clear ASCII graphics that display the details of the current module and its connections to discovered neighboring modules. 

Example of a generated module (Laboratory, where `!` indicates a malfunction and `D` is the drone's position):
```text
+-----+-----+--H--+
|     |     |     |
|        D     !  |
|     |     |     |
+--H--+-----+-----+
```
