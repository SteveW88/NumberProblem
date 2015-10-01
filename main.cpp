#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <memory>
#include "numbers.hpp"


// Forward Declaration of Test Functions
void TestAddition();
void TestBool();


////////////// MAIN //////////////////
/////////
int main(){

  TestAddition();
  TestBool();
   
}

/////TEST FUNCTIONS
///

///TestDisplay -- includes addition testing 
void TestAddition(){
  
  std::cout << "////// BEGIN Addition TEST //////////\n" << std::endl;
  Integer int_four = Integer(4);
  Integer int_six = Integer(6);
  Fraction frac_8_2 = Fraction(8,2);  // whole number int
  Fraction frac_3_4 = Fraction(3,4);  // standard fraction

  std::cout << "Expected: 4     Result: "; int_four.Display();
  std::cout << "Expected: 6     Result: "; int_six.Display();
  std::cout << "Expected: 8/2   Result: "; frac_8_2.Display();
  std::cout << "Expected: 3/4   Result: "; frac_3_4.Display();
  
  Integer  f = int_four + int_six;  // int, int
  Fraction g = int_four + int_six;  // int , int  (as frac)
  Fraction h = int_six + frac_8_2;  // int, whole num frac
  Fraction i = frac_8_2 + frac_3_4;  // frac, frac
  Fraction j = frac_3_4 + int_four;  // frac, int
  Integer  k = int_four + frac_3_4;  // int, frac (rounds frac to nearest whole num)
  
  std::cout << "Expected: 10    Result: "; f.Display();
  std::cout << "Expected: 10/1  Result: "; g.Display();
  std::cout << "Expected: 10/1  Result: "; h.Display();
  std::cout << "Expected: 19/4  Result: "; i.Display();
  std::cout << "Expected: 19/4  Result: "; j.Display();
  std::cout << "Expected: 5 (19/4 as int)  Result: "; k.Display();
  
  std::vector<Number*> numVec = {&f,&g,&h,&i,&j,&k};
  std::shared_ptr<Number> sum_of_vec = Sum(numVec);

  std::cout << "\nSum of 10,10,10,19/4,19/4" << std::endl;
  std::cout << "Expected: 89/2  Result: "; sum_of_vec->Display();

  
  std::cout << "\n////// End Addition TEST //////////\n" << std::endl;
  
}


///TestBool
void TestBool(){
  
  std::cout << "////// BEGIN BOOL TEST //////////\n" << std::endl;
  
  Integer int_four = Integer(4);
  Integer int_four_other = Integer(4);
  Integer int_two = Integer(2);
  Fraction frac_four_whole = Fraction(8,2);
  Fraction frac_2_3 = Fraction(2,3);
  Fraction frac_2_3_other = Fraction(2,3);
  Fraction frac_4_6 = Fraction(4,6);

  // Test: Integer lhs, x rhs
  std::cout << "Test Integer lhs, variable rhs" << std::endl;
  (int_four == int_four_other) ? printf("int==int\n") : printf("ERROR: int==int\n");
  (int_four == int_two) ? printf("ERROR: int!=int\n") : printf("int!=int\n");
  (int_four == frac_four_whole)? printf("int==wholefrac\n") : printf("ERROR: int==wholefrac\n");
  (int_four == frac_2_3) ? printf("ERROR: int!=frac\n") : printf("int!=frac\n");
  (int_four == (Integer(2)+Integer(2))) ? printf("int==expr\n") : printf("ERROR: int==expr\n");
  (int_four == (Integer(2)+Integer(1))) ? printf("ERROR: int!=expr\n") : printf("int!=expr\n");

  // Test: x rhs, Integer lhs
  std::cout << "\nTest variable rhs, Integer lhs" << std::endl;
  (int_four_other == int_four) ? printf("int==int\n") : printf("ERROR: int==int\n");
  (int_two == int_four) ? printf("ERROR: int!=int\n") : printf("int!=int\n");
  (frac_four_whole == int_four)? printf("wholefrac==int\n") : printf("ERROR: wholefrac==int\n");
  (frac_2_3 == int_four) ? printf("ERROR: frac!=int\n") : printf("frac!=int\n");
  ((Integer(2)+Integer(2)) == int_four) ? printf("expr==int\n") : printf("ERROR: expr==int\n");
  ((Integer(2)+Integer(1)) == int_four) ? printf("ERROR: expr!=int\n") : printf("expr!=int\n");

  // Test: Fraction lhs, x rhs
  std::cout << "\nTest Fraction lhs, variable rhs" << std::endl;
  (frac_four_whole == int_four) ? printf("frac==int\n") : printf("ERROR: frac==int\n");
  (frac_2_3 == frac_4_6) ? printf("frac!=frac\n") : printf("ERROR: frac!=frac\n");
  (frac_2_3 == frac_2_3)? printf("frac==frac\n") : printf("ERROR: frac==frac\n");
  (frac_2_3 == frac_four_whole) ? printf("ERROR: frac!=int\n") : printf("frac!=int\n");
  (frac_2_3 == (Fraction(2,6)+Fraction(1,3))) ? printf("frac==expr\n") : printf("ERROR: frac==expr\n");
  (frac_2_3 == (Fraction(1,6)+Fraction(1,3))) ? printf("ERROR: frac!=expr\n") : printf("frac!=expr\n");

  // Test: x lhs, Fraction rhs
  std::cout << "\nTest variable lhs, Fraction rhs" << std::endl;
  (int_four == frac_four_whole) ? printf("int==frac\n") : printf("ERROR: int==frac\n");
  (frac_4_6 == frac_2_3) ? printf("frac!=frac\n") : printf("ERROR: frac!=frac\n");
  (frac_2_3 == frac_2_3)? printf("frac==frac\n") : printf("ERROR: frac==frac\n");
  (frac_four_whole == frac_2_3) ? printf("ERROR: int!=frac\n") : printf("int!=frac\n");
  ((Fraction(2,6)+Fraction(1,3)) == frac_2_3) ? printf("expr==frac\n") : printf("ERROR: expr==frac\n");
  ((Fraction(1,6)+Fraction(1,3)) == frac_2_3) ? printf("ERROR: expr!=frac\n") : printf("expr!=frac\n");

  std::cout << "\n////// END BOOL TEST //////////\n" << std::endl;

}



