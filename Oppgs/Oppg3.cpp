#include <iostream>
#include <cmath>

using namespace std;

int norm(int x) {
    int r = x % 360;
    if (r < 0) r += 360;
    return r;
}

/* 
// For å normalisere radians => utskrifta blir 30, 30, 33, 1.5708, 1.5708, 1.4292
double norm(double x) {
    double r = fmod(x, 3.14159265359);
    if (r < 0) r += 3.14159265359;
    return r;
}
*/

// ikke normalisere radians => utskrifta blir 30, 30, 33, 1.5708, 4.71239, 4.5708
double norm(double x) {return x;}

template <class T>
struct Angle {
    T deg{};
    constexpr explicit Angle(T a) : deg(norm(a)){}
    constexpr operator T() const {return deg;}
};

Angle<int> operator+(Angle<int> a, int b) {return Angle<int>(a.deg + b);}
Angle<int> operator+(Angle<int> a, double b) {return Angle<int>(a.deg + static_cast<int>(b));}
Angle<int> operator+(int b, Angle<int> a) {return a + b;}
Angle<int> operator/(Angle<int> a, int b) {return Angle<int>(a.deg / b);}

Angle<double> operator+(Angle<double> a, double b) {return Angle<double>(a.deg + b);}
Angle<double> operator+(Angle<double> a, int b) {return Angle<double>(a.deg + static_cast<double>(b));}
Angle<double> operator+(double b, Angle<double> a) {return a + b;}
Angle<double> operator/(Angle<double> a, double b) {return Angle<double>(a.deg / b);}
Angle<double> operator/(Angle<double> a, int b) {return Angle<double>(a.deg / b);}

int main() {
    cout << Angle<int>(30) << endl;
    cout << (Angle<int>(30) + 360) << endl;
    cout << (Angle<int>(30) + 3.14159265359) << endl;
    cout << Angle<double>(3.14159265359 / 2) << endl;
    cout << (Angle<double>(3.14159265359 / 2) + 3.14159265359) << endl;
    cout << (Angle<double>(3.14159265359 / 2) + 3) << endl;

    return 0;
}