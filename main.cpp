// game constants
#define SCREEN_SIZE_X 320.0
#define SCREEN_SIZE_Y 240.0

// gameplay params
#define GAME_SCALE 3
#define MENU_SCALE 4
#define TIME_BETWEEN_FRUITS 2.0


// sim libraries
#include "simulator_libraries/FEHLCD.h"
#include "simulator_libraries/FEHUtility.h"
#include "simulator_libraries/FEHRandom.h"

// paige libraries :)
#include "custom_libraries/Vector.cpp"
#include "custom_libraries/Sprite.cpp"
#include "custom_libraries/Fruit.cpp"

// c++ libraries
#include <fstream>
#include <iostream>
#include <vector>


void doGameplayLoop();
void showGameOverScreen();

void showStatsScreen();
void showHowToScreen();
void showCredits();
void quitGame();

void waitForBackButtonPress();

/*
 * Entry point to the application
 */
int main() {
    // Clear background
    Vector2 menuOffset(0, 0);

    Sprite logo("menu/splash", Vector2(48, 24));
    logo.scale(MENU_SCALE);
    logo.anchorPoint(Vector2(0.5, 0));
    logo.move(Vector2(SCREEN_SIZE_X/2, 2*MENU_SCALE) + menuOffset);

    Sprite play("menu/play_button", Vector2(24, 7));
    play.scale(MENU_SCALE);
    play.anchorPoint(Vector2(0.5, 0));
    play.move(Vector2(SCREEN_SIZE_X/2, 27*MENU_SCALE) + menuOffset);

    Sprite stats("menu/stats_button", Vector2(24, 7));
    stats.scale(MENU_SCALE);
    stats.anchorPoint(Vector2(0.5, 0));
    stats.move(Vector2(SCREEN_SIZE_X/2, 35*MENU_SCALE) + menuOffset);

    Sprite howto("menu/howtobutton", Vector2(24, 7));
    howto.scale(MENU_SCALE);
    howto.anchorPoint(Vector2(0.5, 0));
    howto.move(Vector2(SCREEN_SIZE_X/2, 43*MENU_SCALE) + menuOffset);

    Sprite credits("menu/creditsbutton", Vector2(24, 7));
    credits.scale(MENU_SCALE);
    credits.anchorPoint(Vector2(0.5, 0));
    credits.move(Vector2(SCREEN_SIZE_X/2, 51*MENU_SCALE) + menuOffset);

    // start the menu
    while (true) {
        LCD.SetBackgroundColor(4200974);
        LCD.Clear();

        // draw menu
        logo.draw();
        play.draw();
        stats.draw();
        howto.draw();
        credits.draw();

        // check for button presses
        int xpos, ypos;
        if (LCD.Touch(&xpos, &ypos)) {
            Vector2 screenPoint(xpos, ypos);

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

        // update screen
        LCD.Update();
    }

    return 0;
}


/*
 * gameplay!!
 */
void doGameplayLoop() {
    // make character
    Sprite character("pointer", Vector2(8, 8));
    character.anchorPoint(Vector2(0.5, 0.5));
    character.scale(2);

    vector<Fruit*> projectiles;

    float lastTime = TimeNow();
    float lastFruitSpawnTime = TimeNow();

    // game should keep playing as long as the screen is being touched
    int xpos, ypos;
    while (LCD.Touch(&xpos, &ypos)) {
        Vector2 mousePos = Vector2(xpos, ypos);

        // clear
        LCD.Clear();

        // draw background
        LCD.SetBackgroundColor(WHITE);

        // draw character
        character.move(mousePos);

        // move fruits
        float dt = TimeNow()-lastTime;
        for(Fruit* f : projectiles) {
            f->stepPath(dt);
            // check if its hitting the mouse
            if(f->sprite()->isPointWithin(mousePos)){
                cout << "touching!" << endl;
            }
        }
        lastTime = TimeNow();

        // create new fruit
        if (TimeNow() - lastFruitSpawnTime > 5) {
            Fruit* newFruit = new Fruit(LEMON, 2, Vector2(Random.RandInt(), Random.RandInt()));
            newFruit->sprite()->scale(2);

            projectiles.push_back(newFruit);

            lastFruitSpawnTime = TimeNow();
        }


        // test if the player touched a fruit

        // update screen
        LCD.Update();
    }
}



/*
 * menu screens!!
 */

void showStatsScreen() {
    LCD.Clear();

    Sprite statsBack("menu/stats_background", Vector2(80, 60));
    statsBack.scale(3);
    statsBack.anchorPoint(Vector2(0.5, 0.5));
    statsBack.pos(Vector2(SCREEN_SIZE_X/2, SCREEN_SIZE_Y/2));

    statsBack.draw();
    LCD.Update();

    waitForBackButtonPress();
}

void showHowToScreen() {
    LCD.Clear();

    Sprite howToBack("menu/instruction_background", Vector2(80, 60));
    howToBack.scale(3);
    howToBack.anchorPoint(Vector2(0.5, 0.5));
    howToBack.pos(Vector2(SCREEN_SIZE_X/2, SCREEN_SIZE_Y/2));

    howToBack.draw();
    LCD.Update();

    waitForBackButtonPress();
}

void showCredits() {
    LCD.Clear();

    Sprite creditsBack("menu/credits_background", Vector2(80, 60));
    creditsBack.anchorPoint(Vector2(0.5, 0.5));
    creditsBack.pos(Vector2(SCREEN_SIZE_X/2, SCREEN_SIZE_Y/2));

    creditsBack.draw();
    LCD.Update();

    waitForBackButtonPress();
}

void waitForBackButtonPress() {
    Sprite backButton("menu/back_button", Vector2(16, 8));
    backButton.anchorPoint(Vector2(0, 1));
    backButton.pos(Vector2(8, SCREEN_SIZE_Y - 8));//
    backButton.draw();

    LCD.Update();

    bool touching = false;
    int xpos=0, ypos=0;

    while(!(touching && backButton.isPointWithin(Vector2(xpos, ypos)))) {
        touching = LCD.Touch(&xpos, &ypos);
        Vector2 screenPoint(xpos, ypos);
    }
}