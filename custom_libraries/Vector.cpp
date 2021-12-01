// 2D Vector class
// Paige Mickol

#define VECTOR_INCLUDED

#include <cmath>
#include <ostream>
#include <string>

// a small delta (used for comparing floats due to floating point inaccuracies)
#define DELTA 0.00001


class Vector2 {
    public:
        Vector2(float x = 0, float y = 0) {
            this->x_ = x;
            this->y_ = y;
            this->mag_ = sqrt(x*x + y*y);
        }


        // operator overloading to make vector2 operate as a mathmatical vector

        // overload x+y
        Vector2 operator+(const Vector2& that) {
            return Vector2(this->x_ + that.x_, this->y_ + that.y_);
        }

        void operator+=(const Vector2& that) {
            *this = *this + that;
        }

        // overload -x
        Vector2 operator-() {
            return Vector2(-(this->x_), -(this->y_));
        }

        // overload x-y
        Vector2 operator-(const Vector2& that) {
            return Vector2(this->x_ - that.x_, this->y_ - that.y_);
        }

        void operator-=(const Vector2& that) {
            *this = *this - that;
        }

        // overload x * a
        Vector2 operator*(float scalar) {
            return Vector2(scalar * this->x_, scalar * this->y_);
        }

        // overload x * y (element-by-element multiplication)
        Vector2 operator*(const Vector2& that) {
            return Vector2(that.x_ * this->x_, that.y_ * this->y_);
        }

        // overload a == b
        bool operator==(const Vector2& that) {
            return abs(this->x_ - that.x_) < DELTA && abs(this->y_ - that.y_) < DELTA;
        }

        // overload a != b
        bool operator!=(const Vector2& that) {
            return !(*this == that);
        }

        std::string toString() {
            return "(" + std::to_string(this->x_) + ", " + std::to_string(this->y_) + ")";
        }

        // the dot product of the 2 vectors
        float dot(const Vector2& that) {
            return this->x_ * that.x_ + this->y_ * that.y_;
        }


        // getters for x component, y component, and the magnitude

        float x() const {
            return x_;
        }

        float y() const {
            return y_;
        }

        float mag() const {
            return mag_;
        }

    // internal variables for x, y, and magnitude
    private:
        float x_, y_, mag_;
};


// overload the opposite order for scalar multiplication
Vector2 operator*(float a, Vector2 x) {
    return x * a;
}

// overload ostream with vector
std::ostream& operator<<(std::ostream& os, Vector2 v) {
    os << v.toString();
    return os;
}