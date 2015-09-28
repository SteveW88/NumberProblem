#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "numbers.hpp"


/////  Class Integer //////
///

/// Constructor ///
Integer::Integer(int num) : mNum(num) {};

Integer::Integer(Fraction Frac) {
  mNum = roundf((float)Frac.ValueTop()/Frac.ValueBot());
}
/// Overridden Virtual Functions ///
//Display -- Integer returns Value
void Integer::Display() const {
  std::cout << Value() << std::endl;
}

//operator==(Integer) -- compares Integer to Number
bool Integer::operator==(const Integer & rhs){
  if(Value() == rhs.Value())
    return true;

  return false;

}

//operator+(Integer) -- addition of Integers
//  implicit casts Fraction to Int (roundf)
Integer Integer::operator+(const Integer & rhs){
  return Integer(Value() + rhs.Value());
}

Fraction Integer::operator+(const Fraction & rhs){
  int numerator = Value()*rhs.ValueBot() + rhs.ValueTop();

  int gcd = GCD(numerator, rhs.ValueBot());
  return Fraction(numerator/gcd , rhs.ValueBot()/gcd);
}
///////  End class Integer ///////////


//////  Class Fraction //////
///

/// Constructor  //
Fraction::Fraction(int top, int bot): mTop(top), mBot(bot) {
  if(bot == 0){         //No division by zero
    std::cerr << top << " " << bot << std::endl;
    std::cerr << "invalid fraction" << std::endl;
    exit(1);
  }
};

Fraction::Fraction(Integer Int) : mTop(Int.Value()), mBot(1){};  // Implicit cast

/// Overridden Virtual Functions ///
//Display -- Fraction displays number as 
//  numerator/denominator  i.e. "1/2"
void Fraction::Display() const{
  std::cout << ValueTop() << "/" << ValueBot() << std::endl;
}

//operator== Compare Fraction with Number
//  (if provided Integer, implicit cast to Fraction)
bool Fraction::operator==(const Fraction & rhs){
  if((ValueTop()*rhs.ValueBot()) == (rhs.ValueTop()*ValueBot()))
    return true;

  return false;
  
}

//operator+ Addition of Fraction with Number
//  (if provided Integer, implicit cast to Fraction)
Fraction Fraction::operator+(const Fraction & rhs){
  int numerator = (ValueTop()*rhs.ValueBot()) +  (rhs.ValueTop()*ValueBot());
  int denominator = ValueBot() * rhs.ValueBot();

  int gcd = GCD(numerator,denominator);
  return Fraction(numerator/gcd, denominator/gcd);
}

///////// End class Fraction  ///////////


/// Greatest Common Divisor  (assumption non-negative integers)
//      Used to simplify Fractions  
int GCD(int a, int b){
  while(a!=b){
    if(a > b)
      a -= b;
    else
      b -= a;
  }
  return a;
}
