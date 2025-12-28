#include <iostream>

using namespace std;

const double pi = 3.141592;

class Circle {
  public:
    // Konstruktør burde ha stor forbokstav/samme navn som klassen (Circle)
    //circle(double radius_); 
    Circle(double radius_);                                  
    //int get_area() const;                                     //  burde være type double
    double get_area() const;
    double get_circumference() const;
  //private double radius;                                      // mangler " : " bak private
  private : double radius;
//}                                                             // mangler " ; " etter parantesen
};

// ==> Implementasjon av klassen Circle

// ingen public utenfor klassen, burde være " radius(radius_) ""
//public Circle::Circle(double radius_) : radius_(radius) {}  
 Circle::Circle(double radius_) : radius(radius_) {}    


// returtypen burde være double, mangler "const" mot slutten
//int Circle::get_area() {   
double Circle::get_area() const {                             
  return pi * radius * radius;
}

//Circle::get_circumference() const {                           // ingen returtype (double)
double Circle::get_circumference() const {
  // localvariabelen circumfrence eksisterer ikke
  //circumference = 2.0 * pi * radius;                          
  //return circumference;                                       // kan bare returnere funksjonen direkte
  return 2.0 * pi * radius; 
}

// jeg tok denne med bare for å kunne builde prosjekt
int main() {
  return 0;                                                     
}