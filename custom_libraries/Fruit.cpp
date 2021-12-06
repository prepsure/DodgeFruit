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

#define LEMON "lemon"
Vector2 lemonpos(float t, Vector2 offset);



class Fruit {
    public:
        Fruit(string type = "lemon", float speed = 1, Vector2 offset=Vector2()) :
        sprite_("fruits/" + type, FRUIT_SIZE), offset_(offset.x(), offset.y()) {
            type_ = type;
            speed_ = speed;
            cout << "reconstructing" << endl;
        }

        void stepPath(float dt) {
            t_ += dt * speed_;
            sprite_.move(lemonpos(t_, offset_));
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


Vector2 lemonpos(float t, Vector2 offset) {
    return Vector2(SCREEN_SIZE_Y/2 * cos(t) + offset.x(), SCREEN_SIZE_Y/2 * sin(t) + offset.y());
}

Vector2 watermelonpos(float t) {
    return Vector2();
}

Vector2 applepos(float t) {
    return Vector2();
}