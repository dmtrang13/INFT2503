#include <cctype>   // char-behandling
#include <cstring>  // strengbehandling
#include <iostream> // innlesing/utskrift

using namespace std; // bruker standard navnerom

int main() {
  char text[5];             // en streng med maks lengde 5, etterhvert brukes klassen string
  cout << "Skriv et ord: "; // utskrift, bruker <iostream>
  cin >> text;              // innlesing, bruker <iostream>

  // size_t er som (unsigned) int, men det garanteres at en minne relatert lengde kan lagres i en size_t variabel.
  // En int variabel kan for eksempel ikke være stor nok til å lagre alle mulige verdier strlen kan returnere
  for (size_t i = 0; i < strlen(text); i++) {
    text[i] = toupper(text[i]); // gjør til store bokstaver, bruker <cctype>
  }
  cout << "Bare store bokstaver: " << text << endl;

  for (size_t j = 0; j < strlen(text); j++) {
    text[j] = tolower(text[j]); // gjør til små bokstaver, bruker <cctype>
  }
  cout << "Bare små bokstaver: " << text << endl;
  return 0; // 0 betyr at programmet avslutter vellykket
}

/* Kjøring av programmet:
Skriv et ord: test
Bare store bokstaver: TEST
Bare små bokstaver: test
*/
