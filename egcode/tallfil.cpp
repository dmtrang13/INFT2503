// Programmet leser tall fra fil og skriver summen av tallene til skjermen.

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  const char filename[] = "tallfil.dat";
  ifstream file;       // definerer filvariabel
  file.open(filename); // åpner filen
  if (!file) {         // innfil kan brukes som et logisk uttrykk
    cout << "Feil ved åpning av innfil." << endl;
    exit(EXIT_FAILURE); // uthopp fra programmet
  }

  int number;
  int sum = 0;
  while (file >> number) { // leser fram til filslutt
    sum += number;
  }
  cout << "Summen er " << sum << endl;
  file.close();
}

/* Eksempel kjøring:
Datafil:
3 4 5 5
17

Utskrift:
Summen er 34
*/
