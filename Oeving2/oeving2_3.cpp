#include <iostream>
#include <cstring>
using namespace std;

int main() {

// 3)
    char text[5];                           // maks 4 tegn + "\0" (null character = terminate C-style string)
    char *pointer = text;
    char search_for = 'e';
    cin >> text;                            // begrenser ikke lengden => segmentation fault om lengden > 5
        while (*pointer != search_for) {    // skriver ut garbage output når 'e' ikke finnes
            *pointer = search_for;
            pointer++;
        }
    cout << pointer;                        // skriver bare ut fra og med første 'e' i ordet. Eks. beef -> eef
}