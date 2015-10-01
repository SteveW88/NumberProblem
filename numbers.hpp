//numbers.hpp
//
#include <vector>
#include <memory>  // shared_ptr

class Integer;  // forward declaration 
class Fraction; // forward declaration


/////////////////////////////////////////////
// **** Class Number ( Base Class )
// ****
//
//  -- Derived Classes --
//    o Integer
//    o Fraction
//
//  Base class for all 'numbers'. Contains
//  several virtual functions for use in 
//  all derived classes:
//
//  - Display()   -- Displays number in original form
//  - operator==  -- Compare two numbers
//  - operator+   -- Addition of two numbers
//  - Type()      -- Return number type (stored as enum classType)
//  - To_Derived  -- Conversion from a Number to another Number
//
//
class Number{
protected:

  enum classType {cInt,cFrac};  
  classType mType;               // stores Number type (cInt for Integer, ect)

public:
   
  // Virtual Functions
  virtual void Display() const =0;
  virtual bool operator==(const Number &) const =0;
  virtual std::shared_ptr<Number> operator+(const Number &) const =0;
  virtual classType Type()const{return mType;};
  virtual Integer To_Integer() const =0;
  virtual Fraction To_Fraction() const =0;

}; // End class Number
  

//////////////////////////////////////////////
// **** Class Integer
// ****
//
// Derived from base class Number.
//
// Basic Functionality:
//     o stores an int value (mNum)
//     o access int value through Value() method
//
class Integer : public Number {
private:

  int mNum;
 
public:

  // Constructors
  Integer() : mNum(0) {mType = cInt;};
  Integer(int num);
  Integer(const Number & num);
  Integer(const std::shared_ptr<Number> & numPtr);

  // Virtual Function Overrides
  void Display() const;
  bool operator==(const Number & rhs) const;
  std::shared_ptr<Number> operator+(const Number & rhs) const;
  Integer To_Integer() const;
  Fraction To_Fraction() const;

  // Class Specific Functions
  int Value() const{return mNum;};
         
};  // End class Integer


//////////////////////////////////////////////
// **** Class Fraction
// ****
//
// Derived from base class Number.
//
// Basic Functionality:
//     o stores fraction as two ints (mTop, mBot)
//         corresponding to numerator and denominator respectively
//     o access to mTop and mBot through ValueTop() and ValueBot() methods
//     o determine if fraction is a whole number -- IsInt()
//
class Fraction : public Number {
private:

  int mTop;  // Numerator
  int mBot;  // Denominator

public: 
 
  // Constructors
  Fraction() : mTop(0), mBot(1) {mType = cFrac;};
  Fraction(int top, int bot);
  Fraction(const Number & num);
  Fraction(std::shared_ptr<Number> const & numPtr);        

  // Virtual Function Overrides
  void Display() const;
  bool operator==(const Number & rhs) const;
  std::shared_ptr<Number> operator+(const Number & rhs) const;
  Integer To_Integer() const;
  Fraction To_Fraction() const;
 

  // Class Functions
  int ValueTop() const{return mTop;};
  int ValueBot() const{return mBot;};
  bool IsInt() const{return (ValueTop() % ValueBot() == 0);};
  
}; // End class Fraction


/////
// Greatest Common Divisor  (assumption non-negative integers)
//      
// Used to simplify Fractions.
int GCD(int a, int b);


/////////////////////////////////////////////
// **** Global Function Declarations
// ****
//
// Ugly method to convert shared_ptr<Number> to number reference.
//      o operator+
//      o operator==
//

// cast lhs shared_ptr to number reference
std::shared_ptr<Number> operator+(const std::shared_ptr<Number> & lhs, const Number & rhs);
bool operator==(const std::shared_ptr<Number> & lhs, const Number & rhs);

// cast rhs shared_ptr to number reference
std::shared_ptr<Number> operator+(const Number & lhs, const std::shared_ptr<Number> & rhs);
bool operator==(const Number & lhs, const std::shared_ptr<Number> & rhs);

// cast both lhs and rhs shared_ptr to number reference
std::shared_ptr<Number> operator+(const std::shared_ptr<Number> & lhs, const std::shared_ptr<Number> & rhs);
bool operator==(const std::shared_ptr<Number> & lhs, const std::shared_ptr<Number> & rhs);

///
// Sum()
//
// Sums a vector of numbers (number pointers).  Returns a smart pointer to
// dynamically allocated number of the type determined by
// class addition operators.
//
std::shared_ptr<Number> Sum(const std::vector<Number*> & vec);
