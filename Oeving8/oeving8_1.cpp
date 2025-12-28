#include <iostream>
#include <iomanip> 
#include <cmath>
using namespace std;

template<typename Type>
bool equal(const Type& a, const Type& b) {
    cout << "[template<T>] ";
    return a == b;
}
bool equal(double a, double b) {
    cout << "[double]      ";
    return abs(a-b) < 1e-5;
}


int main() {
    cout << fixed << setprecision(10);

    int i1 = 3, i2 = 2;
    cout << i1 << " = " << i2 << ": " << boolalpha << equal(i1,i2) << "\n";

    double a = 0.1 + 0.2;
    double b = 0.3;
    cout << a << " = " << b << ": " << boolalpha << equal(a,b) << "\n";

    double c = 1.0000000;
    double d = 1.0000200;
    cout << c << " = " << d << ": " << boolalpha << equal(c,d) << "\n";

    double e = 2.0000000;
    double f = 2.0000049;
    cout << e << " = " << f << ": " << boolalpha << equal(e,f) << "\n";

    return 0;
}