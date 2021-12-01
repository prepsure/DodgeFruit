#define GAME_SCALE 3
#define SCREEN_SIZE_X 320.0
#define SCREEN_SIZE_Y 240.0

// sim libraries
#include "simulator_libraries/FEHLCD.h"

// paige libraries :)
#include "custom_libraries/Vector.cpp"
#include "custom_libraries/Sprite.cpp"

// c++ libraries
#include <fstream>
#include <iostream>

void doGameplayLoop();
void showStatsScreen();
void showHowToScreen();
void quitGame();

/*
 * Entry point to the application
 */
int main() {
    // Clear background

    Vector2 menuOffset(0, 24);

    Sprite logo("menu/splash", Vector2(48, 24));
    logo.anchorPoint(Vector2(0.5, 0));
    logo.move(Vector2(SCREEN_SIZE_X/2, 2*GAME_SCALE) + menuOffset);

    Sprite play("menu/play_button", Vector2(24, 7));
    play.anchorPoint(Vector2(0.5, 0));
    play.move(Vector2(SCREEN_SIZE_X/2, 27*GAME_SCALE) + menuOffset);

    Sprite stats("menu/stats_button", Vector2(24, 7));
    stats.anchorPoint(Vector2(0.5, 0));
    stats.move(Vector2(SCREEN_SIZE_X/2, 35*GAME_SCALE) + menuOffset);

    Sprite howto("menu/instruction_button", Vector2(24, 7));
    howto.anchorPoint(Vector2(0.5, 0));
    howto.move(Vector2(SCREEN_SIZE_X/2, 43*GAME_SCALE) + menuOffset);

    Sprite quit("menu/quit_button", Vector2(24, 7));
    quit.anchorPoint(Vector2(0.5, 0));
    quit.move(Vector2(SCREEN_SIZE_X/2, 51*GAME_SCALE) + menuOffset);


    // make character
    Sprite character("character", Vector2(8, 8));
    character.anchorPoint(Vector2(0.5, 0.5));

    while (1) {
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear();

        // draw menu
        logo.draw();
        play.draw();
        stats.draw();
        howto.draw();
        quit.draw();

        // START GAMEPLAY LOOP

        // get touch pos
        int xpos, ypos;
        // continue as long as the user is touching the screen
        while (LCD.Touch(&xpos, &ypos)) {
            // make the screen blank
            LCD.Clear();
            LCD.SetBackgroundColor(BLACK);

            character.move(Vector2(xpos, ypos));

            LCD.Update();
        }

        //cout << "not touching" << endl;
        LCD.Update();
    }

    return 0;
}