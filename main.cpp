#define GAME_SCALE 3
#define SCREEN_SIZE_X 320.0
#define SCREEN_SIZE_Y 240.0

// sim libraries
#include "simulator_libraries/FEHLCD.h"
#include "simulator_libraries/FEHUtility.h"

// paige libraries :)
#include "custom_libraries/Vector.cpp"
#include "custom_libraries/Sprite.cpp"

// c++ libraries
#include <fstream>
#include <iostream>

void doGameplayLoop();
void showStatsScreen();
void showHowToScreen();
void showCredits();
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

    Sprite credits("menu/quit_button", Vector2(24, 7));
    credits.anchorPoint(Vector2(0.5, 0));
    credits.move(Vector2(SCREEN_SIZE_X/2, 51*GAME_SCALE) + menuOffset);


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
        credits.draw();

        int xpos, ypos;
        bool touching = LCD.Touch(&xpos, &ypos);
        Vector2 screenPoint(xpos, ypos);

        if (touching) {
            if (play.isPointWithin(screenPoint)) {
                doGameplayLoop();
            } else if (stats.isPointWithin(screenPoint)) {
                showStatsScreen();
            } else if (howto.isPointWithin(screenPoint)) {
                showHowToScreen();
            } else if (credits.isPointWithin(screenPoint)) {
                showCredits();
            }
        }

        // START GAMEPLAY LOOP

        // get touch pos

        /*
        // continue as long as the user is touching the screen
        while (LCD.Touch(&xpos, &ypos)) {
            // make the screen blank
            LCD.Clear();
            LCD.SetBackgroundColor(BLACK);

            character.move(Vector2(xpos, ypos));

            LCD.Update();
        }
        */

        //cout << "not touching" << endl;
        LCD.Update();
    }

    return 0;
}


void doGameplayLoop() {
    Sleep(5.0);
}

void showStatsScreen() {
    Sleep(5.0);
}

void showHowToScreen() {
    LCD.Clear();

    Sprite howToBack("menu/instructions_background", Vector2(16, 60));
    howToBack.draw();

    LCD.Update();
    Sleep(5.0);
}

void showCredits() {
    Sleep(5.0);
}