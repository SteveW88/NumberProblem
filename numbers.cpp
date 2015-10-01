// numbers.cpp
//
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <memory>
#include "numbers.hpp"


/////////////////////////////////////////////////
// ****  CONSTRUCTORS 
// ****
//

/////
// Constructor: Integer()
//
// Standard constructor passing int as argument.
//
Integer::Integer(int num) : mNum(num) {mType = cInt;};


/////
// Constructor: Integer()
//
// Implicit conversion from any number reference
// to Integer using the To_Integer() method.
//
Integer::Integer(const Number & num) {
  mNum = num.To_Integer().Value();
  mType = cInt;
}


/////
// Constructor: Integer()
//
// Implicit conversion from any shared_ptr number
// to Integer using the To_Integer() method.
//
Integer::Integer(const std::shared_ptr<Number> & numPtr){
  mType = cInt;
 
  switch (numPtr->Type()){
  case cInt:{
    Integer temp = numPtr->To_Integer();
    mNum = temp.Value();
    break;
  }
  case cFrac:{
    Integer temp = numPtr->To_Integer();
    mNum = temp.Value();
    break;
  }
  default:
    std::cerr << "Invalid Integer constructor" << std::endl;
    exit(1);
  }
}


/////
// Constructor: Fraction()
//
// Standard constructor passing two ints as arguments.
//
Fraction::Fraction(int top, int bot): mTop(top), mBot(bot) {
  mType = cFrac;
  if(bot == 0){         //No division by zero
    std::cerr << top << " " << bot << std::endl;
    std::cerr << "invalid fraction" << std::endl;
    exit(1);
  }
}


/////
// Constructor: Fraction()
//
// Implicit conversion from any number reference
// to Fraction using the To_Fraction() method.
//
Fraction::Fraction(const Number & num){
  mType = cFrac;

  switch (num.Type()){
  case cInt:{
    Fraction temp = num.To_Fraction();
    mTop = temp.ValueTop();
    mBot = temp.ValueBot();
    break;
  }
  case cFrac:{
    Fraction temp = num.To_Fraction();
    mTop = temp.ValueTop();
    mBot = temp.ValueBot();
    break;
  }
  default:
    std::cerr  << "Invalid Fraction constructor" << std::endl;
    exit(1);
  }
}


/////
// Constructor: Fraction()
//
// Implicit conversion from any shared_ptr number
// to Fraction using the To_Fraction() method.
//
Fraction::Fraction(const std::shared_ptr<Number> & numPtr){
  Number & num = *numPtr;
  mType = cFrac;

  switch (num.Type()){
  case cInt:{
    Fraction temp = num.To_Fraction();
    mTop = temp.ValueTop();
    mBot = temp.ValueBot();
    break;
  }
  case cFrac:{
    Fraction temp = num.To_Fraction();
    mTop = temp.ValueTop();
    mBot = temp.ValueBot();
    break;
  }
  default:
    std::cerr  << "Invalid Fraction constructor" << std::endl;
    exit(1);
  }
}
//************************************************//


/////////////////////////////////////////////////
// **** Virtual Functions 
// ****
//
//  o Display
//  o operator==
//  o operator+
//  o To_Integer
//  o To_Fraction


///// 
// Display -- Integer::Display
//
void Integer::Display() const {
  std::cout << Value() << std::endl;
}


/////
// Display -- Fraction::Display
//
// Output Fraction value in original form
// e.g.  "2/4"
//
void Fraction::Display() const{
  std::cout << ValueTop() << "/" << ValueBot() << std::endl;
}

//**********//


///// 
// operator== -- Integer::operator==
//
// Takes constant number reference and converts
// to Integer using the To_Integer() method.
// 
// Compares Integer.Value() to converted Integer.Value()
//
bool Integer::operator==(const Number & rhs) const{
  return (Value() == rhs.To_Integer().Value());
}


///// 
// operator== -- Fraction::operator==
//
// Takes constant number reference and converts
// to Fraction using the To_Integer() method.
//
// Performs cross multiplication prior to comparison
// of numerators.
//
bool Fraction::operator==(const Number & rhs) const{
  Fraction rhs_frac = rhs.To_Fraction();
  return ((ValueTop()*rhs_frac.ValueBot()) == (rhs_frac.ValueTop()*ValueBot()));  
}

////
// operator== -- Global operator==
//
// Functions defined taking a shared_ptr<Number> as either
// lhs or rhs.  Ugly method of casting shared_ptr<Number>
// to a Number reference.
//
bool operator==(const std::shared_ptr<Number> & lhs, const Number & rhs){
  Number & lhs_ref = *lhs;
  return (lhs_ref == rhs);
}

// rhs
bool operator==(const Number & lhs, const std::shared_ptr<Number> & rhs){
  Number & rhs_ref = *rhs;
  return (lhs == rhs_ref);
}


//**********//


///// 
// operator+ -- Integer::operator+
//
// Determines derived Number type using
// Type() method.  Based on derived type,
// dynamically allocates appropriate derived
// object and returns smart pointer.  This allows for
// a dynamic return type.
//
std::shared_ptr<Number> Integer::operator+(const Number & rhs) const{
  switch (rhs.Type()){
  case cInt:{
    return std::shared_ptr<Number>(new Integer(Value() + rhs.To_Integer().Value()));
  }
  case cFrac:{
    return std::shared_ptr<Number>(new Fraction(To_Fraction() + rhs.To_Fraction()));
  }
  }
}


///// 
// operator+ -- Fraction::operator+
//
// At the moment Fraction is the most precise 
// Number.  Converts provided Number reference
// to Fraction using the To_Fraction() method. 
// Utilizes greatest common divisor method GCD()
// to simplify the new Fraction. Returns smart
// pointer to dynamically allocated new Fraciton.
//
std::shared_ptr<Number> Fraction::operator+(const Number & rhs) const{
  Fraction rhs_frac = rhs.To_Fraction();
  
  int numerator = (ValueTop()*rhs_frac.ValueBot()) +  (rhs_frac.ValueTop()*ValueBot());
  int denominator = ValueBot() * rhs_frac.ValueBot();
  
  int gcd = GCD(numerator,denominator);

  return std::shared_ptr<Number>(new Fraction(numerator/gcd, denominator/gcd));
 
  
}


///// 
// operator+ -- Global operator+
//
// Functions defined taking a shared_ptr<Number> as either
// lhs or rhs.  Ugly method of casting shared_ptr<Number>
// to a Number reference.
//
std::shared_ptr<Number> operator+(const std::shared_ptr<Number> & lhs, const Number & rhs){
  Number & lhs_ref = *lhs;
  return (lhs_ref + rhs);
}

//rhs
std::shared_ptr<Number> operator+(const Number & lhs, const std::shared_ptr<Number> & rhs){
  Number & rhs_ref = *rhs;
  return (lhs + rhs_ref);
}

//**********//

//////// To_Integer() Methods /////////

///// 
// To_Integer() -- Integer::To_Integer()
//
// Converts Integer to Integer
// Used to access Integer functions
// when passing Integer as Number reference (or smart pointer).
//
Integer Integer::To_Integer() const{
  return Integer(mNum);
}


///// 
// To_Integer() -- Fraction::To_Integer()
//
// Converts Fraction to Integer
// Used to access Integer functions
// when passing Fraction as Number reference (or smart pointer).
//
Integer Fraction::To_Integer() const{
  int val = roundf((float)mTop/mBot);
  return Integer(val);
}


//////// To_Fraction() Methods /////////

///// 
// To_Fraction() -- Integer::To_Fraction()
//
// Converts Integer to Fraction
// Used to access Fraction functions
// when passing Fraction as Number reference (or smart pointer).
//
Fraction Integer::To_Fraction() const{
  return Fraction(mNum,1);
}


///// 
// To_Fraction() -- Fraction::To_Integer()
//
// Converts Fraction to Fraction
// Used to access Fraction functions
// when passing Fraction as Number reference (or smart pointer).
//
Fraction Fraction::To_Fraction() const{
  return Fraction(mTop,mBot);
}

//**********//


/// Greatest Common Divisor  (assumption non-negative integers)
//      Used to simplify Fractions  
int GCD(int a, int b){
  if(a!=0 && b!=0){
    while(a!=b){
      if(a > b)
        a -= b;
      else
        b -= a;
    }
    return a;
  }
  return 1;
}


///
// Sum()
//
// Sums a vector of numbers (number pointers).  Returns a smart pointer
// to a dynamically allocated number of the type determined by
// class addition operators.
//
std::shared_ptr<Number> Sum(const std::vector<Number*> & vec){
  if(vec.size()<2){
    std::cout << "Invalid Sum() call" << std::endl;
    exit(1);
  }

  std::shared_ptr<Number> temp = *vec[0] + *vec[1];
  for(int i=2; i<vec.size(); i++){
    temp = *temp + *vec[i];
  }
  return temp;
}

