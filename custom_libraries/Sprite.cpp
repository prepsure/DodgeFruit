// Sprite class
// Paige Mickol

#define SPRITE_INCLUDED

#ifndef GAME_SCALE
    #define GAME_SCALE 1
#endif
#ifndef SCREEN_SIZE_X
    #define SCREEN_SIZE_X 320.0
#endif
#ifndef SCREEN_SIZE_Y
    #define SCREEN_SIZE_Y 240.0
#endif

#define SPRITE_SIZE_X (int) SCREEN_SIZE_X / GAME_SCALE
#define SPRITE_SIZE_Y (int) SCREEN_SIZE_Y / GAME_SCALE

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#ifndef VECTOR_INCLUDED
    #include "Vector.cpp"
#endif

#ifndef FEHLCD_H
    #include "../simulator_libraries/FEHLCD.h"
#endif

class Sprite {
    public:
        Sprite(string spriteName, Vector2 spriteSize) {
            size(spriteSize);
            swapImage(spriteName, spriteSize);
        }

        // sets the positions, then draws the sprite to the graphics buffe
        void move(Vector2 pos) {
            pos_ = pos;
            draw();
        }

        // replaces the sprite image
        void swapImage(string spriteName, Vector2 spriteSize) {
            ifstream sprFile;
            sprFile.open("sprites/" + spriteName + ".spr");

            int pixelCount = 0;
            int next;

            while(sprFile >> next){
                int x = pixelCount / (int)spriteSize.x();
                int y = pixelCount % (int)spriteSize.x();
                image[x][y] = next;
                pixelCount++;
            }

            sprFile.close();
        }

        // draw the sprite onto the graphics buffer
        void draw() {
            for(int i = 0; i < size_.x(); i++) {
                for(int j = 0; j < size_.y(); j++) {
                    int color = image[j][i];
                    bool transparent = (color == -1);

                    // draw pixel on the screen
                    if (!transparent) {
                        LCD.SetFontColor(color);
                        drawScaledPixel(pos() + Vector2(i, j) * scale());
                    }

                }
            }
        }

        // checks whether screenpoint is overlapping the sprite (useful for collision)
        bool isPointWithin(Vector2 screenPoint) {
            // need to mod position because the simulator does that as well
            // eg: if you draw off the screen to the right it'll wrap around to the left
            float modX = (int)pos().x() % (int)SCREEN_SIZE_X;
            float modY = (int)pos().y() % (int)SCREEN_SIZE_Y;

            float leftBound = modX - size().x() * scale().x() * anchorPoint().x();
            float topBound = modY - size().y() * scale().y() * anchorPoint().y();
            float rightBound = leftBound + size().x() * scale().x();
            float bottomBound = topBound + size().y() * scale().y();

            float screenPointModX = (int)screenPoint.x() % (int)SCREEN_SIZE_X;
            float screenPointModY = (int)screenPoint.y() % (int)SCREEN_SIZE_Y;

            // check that the screenpoint is within the bounds, returning false if any of them fail
            return
                leftBound <= screenPointModX &&
                rightBound >= screenPointModX &&
                topBound <= screenPointModY &&
                bottomBound >= screenPointModY;
        }


        // getters for internal fields
        Vector2 pos() {
            return pos_;
        }

        Vector2 size() {
            return size_;
        }

        Vector2 scale() {
            return scale_;
        }

        Vector2 anchorPoint() {
            return anchorPoint_;
        }

        // setters for internal fields
        void pos(Vector2 newPos) {
            pos_ = newPos;
        }

        void size(Vector2 newSize) {
            size_ = newSize;
        }

        void scale(Vector2 newScale) {
            scale_ = newScale;
        }

        // extra setter for scale for uniform scaling
        void scale(int n) {
            scale(Vector2(n, n));
        }

        void anchorPoint(Vector2 newAnchorPoint) {
            anchorPoint_ = newAnchorPoint;
        }

    private:
        Vector2 pos_ = Vector2(0, 0);
        Vector2 size_;
        Vector2 scale_ = GAME_SCALE * Vector2(1, 1);
        Vector2 anchorPoint_ = Vector2(0, 0);

        int image[SPRITE_SIZE_X + 1][SPRITE_SIZE_Y + 1];

        // draws a pixel the size of the sprite's scale
        void drawScaledPixel(Vector2 pos) {
            pos -= size() * scale() * anchorPoint();

            for(int i = 0; i < scale().x(); i++) {
                for(int j = 0; j < scale().y(); j++) {
                    LCD.DrawPixel(pos.x() + i, pos.y() + j);
                }
            }
        }
};