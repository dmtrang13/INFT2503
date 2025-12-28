// Prøver getline() og ignore()

#include <iostream>

using namespace std;

const int max_line_length = 81;

int main() {
  char name[max_line_length];
  char address[max_line_length];
  int age;
  char position[max_line_length];

  cout << "Navn: ";
  cin.getline(name, max_line_length);
  cout << "Adresse: ";
  cin.getline(address, max_line_length);
  cout << "Alder: ";
  cin >> age;
  cin.get(); // Tar bort newline ('\n')
  cout << "Stilling: ";
  cin.getline(position, max_line_length);

  cout << name << endl << address << endl << age << endl << position << endl;
}

/*
Kjøring av programmet:

Uten get():

Navn: Kari Ås
Adresse: Storgt 17, 7000 Trondheim
Alder: 26
Stilling: Kari Ås
Storgt 17, 7000 Trondheim
26

Med get():

Navn: Kari Ås
Adresse: Storgt 17, 7000 Trondheim
Alder: 25
Stilling: Frisør
Kari Ås
Storgt 17, 7000 Trondheim
25
Frisør
*/
