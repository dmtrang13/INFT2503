#include <iostream>
#include <cstring>
using namespace std;

int main() {

// 2)

    char *line = nullptr;   // eller char *line = 0;
    strcpy(line, "Dette er en tekst"); //Prøver å skrive til adresse til line => Segmentation fault 
/*
    Dette betyr at programmet prøver å få tilgang til et minnelokasjon den ikke har tilgang til. 
    I programmet skyldes det *line = nullptr, 
    hvorav null pointer er en verdi som indikerer at pointer/referansen refererer ikke til et gyldig objekt.
*/
}