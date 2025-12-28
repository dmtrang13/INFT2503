//
// fraction/fraction.hpp
//
#include "fraction.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int numberator, int denominator) {
  set(numberator, denominator);
}

void Fraction::set(int numberator_, int denominator_) {
  if (denominator_ != 0) {
    numerator = numberator_;
    denominator = denominator_;
    reduce();
  } else {
    throw "nevneren ble null";
  }
}

Fraction Fraction::operator+(const Fraction &other) const {
  Fraction fraction = *this;
  fraction += other;
  return fraction;
}

Fraction &Fraction::operator+=(const Fraction &other) {
  set(numerator * other.denominator + denominator * other.numerator,
      denominator * other.denominator);
  return *this;
}

Fraction &Fraction::operator++() {
  numerator += denominator;
  return *this;
}

Fraction Fraction::operator-(const Fraction &other) const {
  Fraction fraction = *this;
  fraction -= other;
  return fraction;
}

Fraction Fraction::operator-(int number) const {
  return (*this) - Fraction(number, 1);
}

Fraction &Fraction::operator-=(const Fraction &other) {
  set(numerator * other.denominator - denominator * other.numerator,
      denominator * other.denominator);
  return *this;
}

Fraction &Fraction::operator--() {
  numerator -= denominator;
  return *this;
}

Fraction Fraction::operator-() const {
  Fraction fraction;
  fraction.numerator = -numerator;
  fraction.denominator = denominator;
  return fraction;
}

Fraction Fraction::operator*(const Fraction &other) const {
  Fraction fraction = *this;
  fraction *= other;
  return fraction;
}

Fraction &Fraction::operator*=(const Fraction &other) {
  set(numerator * other.numerator, denominator * other.denominator);
  return *this;
}

Fraction Fraction::operator/(const Fraction &other) const {
  Fraction fraction = *this;
  fraction /= other;
  return fraction;
}

Fraction &Fraction::operator/=(const Fraction &other) {
  set(numerator * other.denominator, denominator * other.numerator);
  return *this;
}

/* -Wdeprecated-copy
Fraction &Fraction::operator=(const Fraction &other) {
  numerator = other.numerator;
  denominator = other.denominator;
  return *this;
}
*/ 

bool Fraction::operator==(const Fraction &other) const {
  return (compare(other) == 0) ? true : false;
}

bool Fraction::operator!=(const Fraction &other) const {
  return (compare(other) != 0) ? true : false;
}

bool Fraction::operator<=(const Fraction &other) const {
  return (compare(other) <= 0) ? true : false;
}

bool Fraction::operator>=(const Fraction &other) const {
  return (compare(other) >= 0) ? true : false;
}

bool Fraction::operator<(const Fraction &other) const {
  return (compare(other) < 0) ? true : false;
}

bool Fraction::operator>(const Fraction &other) const {
  return (compare(other) > 0) ? true : false;
}

//-------------------------------------------------------------------
//
// Sørg for at nevneren alltid er positiv.
// Bruker Euclids algoritme for å finne fellesnevneren.
//
void Fraction::reduce() {
  if (denominator < 0) {
    numerator = -numerator;
    denominator = -denominator;
  }
  int a = numerator;
  int b = denominator;
  int c;
  if (a < 0)
    a = -a;

  while (b > 0) {
    c = a % b;
    a = b;
    b = c;
  }
  numerator /= a;
  denominator /= a;
}

//-------------------------------------------------------------------
//
// Returnerer +1 hvis *this > other, 0 hvis de er like, -1 ellers
//
int Fraction::compare(const Fraction &other) const {
  Fraction fraction = *this - other;
  if (fraction.numerator > 0)
    return 1;
  else if (fraction.numerator == 0)
    return 0;
  else
    return -1;
}

void print(const string &text, const Fraction &broek) {
  cout << text << broek.numerator << " / " << broek.denominator << endl;
}

//  a)
Fraction operator-(int number, const Fraction& broek) {
    return Fraction(number*broek.denominator - broek.numerator, broek.denominator);
}

int main() {
  Fraction a(10, 20);
  Fraction b(3, 4);
  Fraction c;
  c.set(5);
  Fraction d = a / b;

  print("a = ", a);
  print("b = ", b);
  print("c = ", c);
  print("d = ", d);

  b += a;
  ++c;
  d *= d;

  print("b = ", b);
  print("c = ", c);
  print("d = ", d);

  c = a + b - d * a;
  c = -c;

  print("a - 5 = ", a - 5);
  print("5 - a = ", 5 - a);

  //  b)
  // Dette er pga. "b += a" linja som gir b = 5/4 => ((((5 - 3) - 1/2) - 7) - 5/4) = -27/4
  // Dersom vi kommenterer ut "b += a" vil svaret være -25/4 (det riktige svaret)
  print("5 - 3 - a - 7 - b = ", 5 - 3 - a - 7 - b);   //= -27/4

  if (a + b != c + d)
    cout << "a + b != c + d" << endl;
  else
    cout << " a + b == c + d" << endl;
  while (b > a)
    b -= a;
  print("b = ", b);
}

// Utskrift:
// a = 1 / 2
// b = 3 / 4
// c = 5 / 1
// d = 2 / 3
// b = 5 / 4
// c = 6 / 1
// d = 4 / 9
// c = -55 / 36
// a + b != c + d
// b = 1 / 4