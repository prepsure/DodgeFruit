// Fruit Projectile Class
// Paige Mickol & Alina Mueez

#define FRUIT_INCLUDED
#define FRUIT_SIZE Vector2(8, 8)

#ifndef GAME_SCALE
    #define GAME_SCALE 1
#endif

#ifndef SPRITE_INCLUDED
    #include "Sprite.cpp"
#endif

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// fruit types!
#define APPLE "apple"
float applePos(float t);

#define BANANA "banana"
float bananaPos(float t);

#define TANGARINE "tangerine"
float tangerinePos(float t);

#define STRAWBERRY "strawberry"
float strawberryPos(float t);

#define KIWI "kiwi"
float kiwiPos(float t);

#define WATERMELON "watermelon"
float watermelonPos(float t);



class Fruit {
    public:
        Fruit(string type) : sprite_(type, FRUIT_SIZE) {
            type_ = type;
        }

    private:
        Sprite sprite_;
        string type_;
};