// Fruit Projectile Class
// Paige Mickol & Alina Mueez

#define FRUIT_INCLUDED
#define FRUIT_SIZE Vector2(16, 16)

#ifndef GAME_SCALE
    #define GAME_SCALE 1
#endif
#ifndef SCREEN_SIZE_X
    #define SCREEN_SIZE_X 320.0
#endif
#ifndef SCREEN_SIZE_Y
    #define SCREEN_SIZE_Y 240.0
#endif

#ifndef VECTOR_INCLUDED
    #include "Vector.cpp"
#endif
#ifndef SPRITE_INCLUDED
    #include "Sprite.cpp"
#endif

#include <cstring>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

// fruit types!
#define APPLE "apple"
Vector2 applePos(float t);

#define BANANA "banana"
Vector2 bananaPos(float t);

#define TANGARINE "tangerine"
Vector2 tangerinePos(float t);

#define STRAWBERRY "strawberry"
Vector2 strawberryPos(float t);

#define KIWI "kiwi"
Vector2 kiwiPos(float t);

#define WATERMELON "watermelon"
Vector2 watermelonPos(float t);

#define LEMON
Vector2 lemonpos(float t);



class Fruit {
    public:
        Fruit(string type, float speed) : sprite_("fruits/" + type, FRUIT_SIZE) {
            type_ = type;
            time_ = 0;
            speed_ = speed;
        }

        void stepPath(float dt) {
            time_ += dt * speed_;
            sprite_.move(lemonpos(time_));
        }

        Sprite sprite() {
            return sprite_;
        }

        void scale(float n) {
            sprite_.scale(n);
        }

    private:
        Sprite sprite_;
        string type_;
        float time_;
        float speed_;
};


Vector2 lemonpos(float t) {
    return Vector2(SCREEN_SIZE_Y/2 * cos(t), SCREEN_SIZE_Y/2 * sin(t));
}