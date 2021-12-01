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

    Sprite smile("smile", Vector2(100, 100), Vector2(3,3));
    smile.draw();


    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
}