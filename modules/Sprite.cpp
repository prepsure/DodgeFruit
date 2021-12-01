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

        void Move(Vector2 pos) {

        }

        void Resize(Vector2 size) {

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

    private:
        Vector2 pos_, size_, scale_;
        char image[SPRITE_SIZE+1][SPRITE_SIZE+1];

        void drawScaledPixel(int x, int y) {
            for(int i = 0; i < scale().x(); i++) {
                for(int j = 0; j < scale().y(); j++) {
                    LCD.DrawPixel(x + i, y + j);
                }
            }
        }
};