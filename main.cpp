#define SCREEN_SIZE Vector2(320, 240)

#include "simulator_libraries/FEHLCD.h"

// paige libraries :)
#include "modules/Vector.cpp"
#include "modules/Sprite.cpp"

// c++ libraries
#include <fstream>

/*
 * Entry point to the application
 */
int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    // make character
    Sprite smile("smile", Vector2(100, 100), Vector2(3,3));

    while (1) {
        // make the screen blank
        LCD.Clear();
        LCD.SetBackgroundColor(BLACK);

        // get touch pos
        int xpos, ypos;
        bool isTouched = LCD.Touch(&xpos, &ypos);
        // move smile to touch pos
        if(isTouched){
            smile.move(Vector2(xpos, ypos));
        }



        LCD.Update();
        // Never end
    }
    return 0;
}