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
Vector2 applepos(float t, Vector2 offset);

#define TANGERINE "tangerine"
Vector2 tangerinePos(float t, Vector2 offset);

#define STRAWBERRY "strawberry"
Vector2 strawberryPos(float t, Vector2 offset);

#define WATERMELON "watermelon"
Vector2 watermelonpos(float t, Vector2 offset);

#define LEMON "lemon"
Vector2 lemonpos(float t, Vector2 offset);



class Fruit {
    public:
        Fruit(string type = "lemon", float speed = 1, Vector2 offset=Vector2()) :
        sprite_("fruits/" + type, FRUIT_SIZE), offset_(offset.x(), offset.y()) {
            type_ = type;
            speed_ = speed;
        }

        void stepPath(float dt) {
            // time * speed = position
            t_ += dt * speed_;

            // pick function based on fruit type
            if(type_ == APPLE) {
                sprite_.move(applepos(t_, offset_));
            } else if (type_ == WATERMELON) {
                sprite_.move(watermelonpos(t_, offset_));
            } else if (type_ == LEMON) {
                sprite_.move(lemonpos(t_, offset_));
            } else if (type_ == TANGERINE) {
                sprite_.move(tangerinePos(t_, offset_));
            }
        }

        Sprite* sprite() {
            return &sprite_;
        }

    private:
        Sprite sprite_;
        string type_;
        float t_ = 0;
        float speed_;
        Vector2 offset_;
};

// star
Vector2 applepos(float t, Vector2 offset) {
    return Vector2(SCREEN_SIZE_Y/2 * pow(cos(t),5) + offset.x(), SCREEN_SIZE_Y/2 * pow(sin(t),5) + offset.y());
}

// diamond
Vector2 tangerinePos(float t, Vector2 offset) {
    return Vector2(SCREEN_SIZE_Y/2 * t, -1.0/((int)offset.y() % 10) * t * SCREEN_SIZE_Y/2);
}

// sin wave
Vector2 strawberryPos(float t, Vector2 offset) {
    return Vector2();
}

// infinity
Vector2 watermelonpos(float t, Vector2 offset) {
    return Vector2(SCREEN_SIZE_Y/2 * cos(t) + offset.x(), SCREEN_SIZE_Y/2*((sin(2*t))/2) + offset.y());
}

// circle
Vector2 lemonpos(float t, Vector2 offset) {
    return Vector2(SCREEN_SIZE_Y/2 * cos(t) + offset.x(), SCREEN_SIZE_Y/2 * sin(t) + offset.y());
}
