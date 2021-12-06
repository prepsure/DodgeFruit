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

        void move(Vector2 pos) {
            pos_ = pos;
            draw();
        }

        void swapImage(string spriteName, Vector2 spriteSize) {
            ifstream sprFile;
            sprFile.open("sprites/" + spriteName + ".spr");

            int pixelCount = 0;
            int next;

            cout << spriteSize.x() << endl;

            while(sprFile >> next){
                int x = pixelCount / (int)spriteSize.x();
                int y = pixelCount % (int)spriteSize.x();
                image[x][y] = next;
                pixelCount++;
            }

            sprFile.close();
        }

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

        bool isPointWithin(Vector2 screenPoint) {
            float leftBound = pos().x() - size().x() * scale().x() * anchorPoint().x();
            float topBound = pos().y() - size().y() * scale().y() * anchorPoint().y();
            float rightBound = leftBound + size().x() * scale().x();
            float bottomBound = topBound + size().y() * scale().y();

            return
                leftBound <= screenPoint.x() &&
                rightBound >= screenPoint.x() &&
                topBound <= screenPoint.y() &&
                bottomBound >= screenPoint.y();
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

        void drawScaledPixel(Vector2 pos) {
            pos -= size() * scale() * anchorPoint();

            for(int i = 0; i < scale().x(); i++) {
                for(int j = 0; j < scale().y(); j++) {
                    LCD.DrawPixel(pos.x() + i, pos.y() + j);
                }
            }
        }
};