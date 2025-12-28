#include <iostream>
#include <cstring>
using namespace std;

int i = 3;
int j = 5;
int *p = &i;
int *q = &j;

int main() {
// 1a)
/*
    cout << i << ", " << &i <<"\n";
    cout << j << ", " << &j <<"\n";
    cout << p << ", " << &p <<"\n";
    cout << q << ", " << &q <<"\n";
*/
// 1b)

    *p = 7; // Set i = 7
    *q += 4; // Øker vedien til j med 4
    *q = *p + 1; // j = i + 1 = 8
    p = q; // p peker der q peker (j)
    cout << *p << " " << *q << endl; // siden p og q peker samme adresse => 8 8 
    cout << i << ", " << &i <<"\n"; 
    cout << j << ", " << &j <<"\n";
    cout << p << ", " << &p <<"\n";
    cout << q << ", " << &q <<"\n";
}