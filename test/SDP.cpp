#include <iostream>
using namespace std;

#include "Libraries/Vector.cpp"


int main() {
    Vector2 a(1, 0), b(0, 1), c(0, 1);

    cout << a + b << endl;
    cout << a - b << endl;
    cout << -a << endl;

    cout << a.dot(b) << endl;
    cout << a.dot(a) << endl;

    cout << (a == b) << endl;
    cout << (b == c) << endl;

    cout << (a != b) << endl;
    cout << (b != c) << endl;

    cout << 0.2 * a + 3 * b << endl;

    cout << Vector2(1, 1).mag() << endl;
}