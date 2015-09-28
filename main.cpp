#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "numbers.hpp"


// Forward Declaration of Test Functions
void TestDisplay();
void TestBool();
Fraction Sum(const std::vector<Fraction> &);


////////////// MAIN //////////////////
/////////
int main(){

  // Test basic functions (TestDisplay() includes addition testing)
  TestDisplay();
  TestBool();


}


/////TEST FUNCTIONS
///

///TestDisplay -- includes addition testing 
void TestDisplay(){
  
  std::cout << "//////BEGIN DISPLAY TEST//////////" << std::endl;
  Integer a = Integer(4);
  Integer b = Integer(6);
  Fraction c = Fraction(8,2);  // whole number int
  Fraction d = Fraction(3,4);  // standard fraction

  std::cout << "Expected: 4  Result: "; a.Display();
  std::cout << "Expected: 6  Result: ";b.Display();
  std::cout << "Expected: 8/2  Result: ";c.Display();
  std::cout << "Expected: 3/4  Result: ";d.Display();
  
  Integer  f = a + b;  // int, int
  Fraction g = a + b;  // int , int  (as frac)
  Fraction h = b + c;  // int, whole num frac
  Fraction i = c + d;  // frac, frac
  Fraction j = d + a;  // frac, int
  Integer  s = a + d;  // int, frac (rounds frac to nearest whole num)
  
  std::cout << "Expected: 10  Result: "; f.Display();
  std::cout << "Expected: 10/1  Result: "; g.Display();
  std::cout << "Expected: 10/1  Result: "; h.Display();
  std::cout << "Expected: 19/4  Result: "; i.Display();
  std::cout << "Expected: 19/4  Result: "; j.Display();
  std::cout << "Expected: 5 (19/4 as int)  Result: "; s.Display();
  
  Fraction k = a + b + c + d;  //all
   
  std::cout << "Expected: 59/4  Result: "; k.Display();


  // Vector of type Fraction (implicit casts Integers to Fractions)
  std::vector<Fraction> numVector;
  numVector.push_back(a);
  numVector.push_back(b);
  numVector.push_back(c);
  numVector.push_back(d);

  Fraction l = Sum(numVector);

  std::cout << "Expected: 59/4  Result: "; l.Display();


  std::cout << "//////End DISPLAY TEST//////////\n" << std::endl;
  
}


///TestBool
void TestBool(){
  
  std::cout << "//////BEGIN BOOL TEST//////////" << std::endl;
  Integer a = Integer(4);
  Integer b = Integer(4);
  Fraction c = Fraction(8,2);  // whole number int
  
  Fraction d = Fraction(1,3);  // standard fraction
  Fraction e = Fraction(3,9);


  if(a == b)
    std::cout << "int, int ==" << std::endl;
  if(b == c)
     std::cout << "int, whole num frac ==" << std::endl;
  if(d == e)
    std::cout << "frac, frac ==" << std::endl;
  
  // Reversable 
  if(c == b)
     std::cout << "whole num frac, int ==" << std::endl;
 

  // Cases that should fail
  Integer a1 = Integer(5);
  Fraction c1 = Fraction(4,2);
  Fraction d1 = Fraction(1,4);

  if(a == a1)
    std::cout << "ERROR:: int, int ==" << std::endl;
  if(a1 == c1)
    std::cout << "ERROR:: int, whole num frac ==" << std::endl;
  if(d == d1)
    std::cout << "ERROR:: frac, frac ==" << std::endl;

  //Reverse Error
  if(c1 == a1)
    std::cout << "ERROR:: whole num frac, int ==" << std::endl;

  std::cout << "//////END BOOL TEST//////////\n" << std::endl;

}


Fraction Sum(const std::vector<Fraction> & numVec){
  Fraction retVal;
  for(int i=0; i<numVec.size(); i++){
    retVal = retVal + numVec[i];
  }

  return retVal;
}
