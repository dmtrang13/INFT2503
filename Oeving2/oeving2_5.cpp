#include <iostream>
#include <cstring>
using namespace std;

int main() {

// 5)

    double number;
    double *p = &number;    // peker
    double &r = number;     // referanse

    number = 6.7;           // 1) direkte
    *p = 6.7;               // 2) gjennom pekeren
    r = 6.7;                // 3) gjennom referansen
    
}