#define GAME_SCALE 4

#include "simulator_libraries/FEHLCD.h"

// paige libraries :)
#include "custom_libraries/Vector.cpp"
#include "custom_libraries/Sprite.cpp"

// c++ libraries
#include <fstream>
#include <iostream>

/*
 * Entry point to the application
 */
int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    // make character
    Sprite character("character", Vector2(8, 8));
    character.anchorPoint(Vector2(0.5, 0.5));

    while (1) {

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
        LCD.Clear();
        LCD.Update();
    }
    return 0;
}