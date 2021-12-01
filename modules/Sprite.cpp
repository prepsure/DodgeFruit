// Sprite class
// Paige Mickol

#define SPRITE_INCLUDED

#define SPRITE_SIZE 8

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
        Sprite(string spriteName, Vector2 pos, Vector2 scale) {
            ifstream sprFile;
            sprFile.open("sprites/" + spriteName + ".dat");

            this->pos_ = pos;
            this->scale_ = scale;

            int lineCount = 0;
            char line[SPRITE_SIZE];
            while(sprFile >> line) {
                strcpy(this->image[lineCount], line);
                lineCount++;
            }

            sprFile.close();
        }

        void move(Vector2 pos) {
            pos_ = pos;
            draw();
        }

        void resize(Vector2 size) {
            size_ = size;
            draw();
        }

        void draw() {
            for(int i = 0; i < SPRITE_SIZE; i++) {
                for(int j = 0; j < SPRITE_SIZE; j++) {

                    bool transparent = false;
                    int color = 0;

                    switch (image[j][i]) {
                        case 'B':
                            color = BLACK;
                            break;
                        case 'W':
                            color = WHITE;
                            break;
                        case 'R':
                            color = RED;
                            break;
                        case 'U':
                            color = BLUE;
                            break;
                        case 'S':
                            color = SCARLET;
                            break;
                        case 'A':
                            color = GRAY;
                            break;
                        case 'G':
                            color = GREEN;
                            break;
                        case 'Y':
                            color = YELLOW;
                            break;
                        default:
                            transparent = true;
                            break;
                    }

                    if (!transparent) {
                        LCD.SetFontColor(color);
                        drawScaledPixel(pos().x() + (i * scale().x()), pos().y() + (j * scale().y()));
                    }

                }
            }
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

        void anchorPoint(Vector2 newAnchorPoint) {
            anchorPoint_ = newAnchorPoint;
        }

    private:
        Vector2 pos_, size_, scale_, anchorPoint_ = Vector2(0.5, 0.5);
        char image[SPRITE_SIZE+1][SPRITE_SIZE+1];

        void drawScaledPixel(int x, int y) {
            x -= SPRITE_SIZE * scale().x() * anchorPoint_.x();
            y -= SPRITE_SIZE * scale().y() * anchorPoint_.y();

            for(int i = 0; i < scale().x(); i++) {
                for(int j = 0; j < scale().y(); j++) {
                    LCD.DrawPixel(x + i, y + j);
                }
            }
        }
};