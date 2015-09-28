//Numbers.h
#include <vector>

class Fraction;

//Class Number -- base class for all numbers (assumed to be whole number)
template<typename T>
class Number{
public:

  // Virtual Functions
  virtual void Display() const =0;
  virtual bool operator==(const T &) =0;
  virtual T operator+(const T &) =0;
  
    
}; // End class Number
  

//Class Integer
class Integer : public Number<Integer> {
protected:

  int mNum;

public:

  // Constructors
  Integer() : mNum(0) {};
  Integer(int num);
  Integer(Fraction Frac);

  // Virtual Function Overrides
  void Display() const;
  bool operator==(const Integer & rhs);
  Integer operator+(const Integer & rhs);
  Fraction operator+(const Fraction & rhs);

  // Class Functions
  int Value() const{return mNum;};
         
};  // End class Integer


//Class Fraction
class Fraction : public Number<Fraction> {
protected:

  int mTop;  // Numerator
  int mBot;  // Denominator

public: 
 
  // Constructors
  Fraction() : mTop(0), mBot(1) {};
  Fraction(int top, int bot);
  Fraction(Integer Int);         //Implicit Cast Integer to Fraction

  // Virtual Function Overrides
  void Display() const;
  bool operator==(const Fraction & rhs);
  Fraction operator+(const Fraction & rhs);
  
  // Class Functions
  int ValueTop() const{return mTop;};
  int ValueBot() const{return mBot;};
  bool IsInt() const{return (ValueTop() % ValueBot() == 0);};
  
}; // End class Fraction


/// Greatest Common Divisor  (assumption non-negative integers)
//      Used to simplify Fractions
int GCD(int a, int b);
