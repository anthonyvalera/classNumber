/**
 * Number.h
 * Purpose: Custom classes for numbers, real numbers, and fractions
 *
 * @author Anthony Valera
 * @version 1.0 5/07/16
 */

#ifndef Number_h
#define Number_h

#include <iostream>
#include <fstream>

/**
 * Exception class for bad numbers
 */
class BadNumber {
public:
  BadNumber( const char* m)
  : _message(m)
  { };
  
  friend std::ostream& operator<< ( std::ostream& os, const BadNumber& m )
  {
    os << "Please enter a valid number. ";
    os << std::endl << m._message << std::endl;
    return os;
  }
private:
  const char* _message;
};

/**
 * Number class
 */
template <class T>
class Number {
public:
  Number<T>()
  : _data(NULL)
  {}
  
  Number<T>(T data)
  : _data(data)
  {}
  
  Number<T>& operator=(const Number<T> &n) {
    if (this != &n) {
      _data = n._data;
    }
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Number& n) {
    os << n._data;
    return os;
  }
  
  T operator +(const Number<T>& n) { return _data + n._data; }
  T operator +(const T& n) { return _data + n; }
  
  T operator -(const Number<T>& n) { return _data - n._data; }
  T operator -(const T& n) { return _data - n; }
  
  T operator /(const Number<T>& n) { return _data / n._data; }
  T operator /(const T& n) { return _data / n; }
  
  T operator *(const Number<T>& n) { return _data * n._data; }
  T operator *(const T& n) { return _data * n; }
  
  T operator ++() { return _data + 1; }
  T operator --() { return _data - 1; }
  
  T getData() const { return _data; }
  
private:
  T _data = NULL;
};

/**
 * Decimal class
 */
template <class T>
class Decimal {
public:
  Decimal<T>(){
    _data = 0.00;
  };
  
  Decimal<T>(T data) {
    if (data >= 0.00 && data < 1.00) {
      _data = data;
    } else {
        try { throw BadNumber("Decimal must be between 0.00 and 1!"); }
        catch(BadNumber& e) { std::cout << e;}
    }
  };
  
  Decimal<T>& operator=(const Decimal<T> &n) {
    if (this != &n) {
      _data = n._data;
    }
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Decimal& n) {
    os << n._data;
    return os;
  }
  
  T operator +(const Decimal<T>& n) { return _data + n._data; }
  T operator +(const T& n) { return _data + n; }
  
  T operator -(const Decimal<T>& n) { return _data - n._data; }
  T operator -(const T& n) { return _data - n; }
  
  T operator /(const Decimal<T>& n) { return _data / n._data; }
  T operator /(const T& n) { return _data / n; }
  
  T operator *(const Decimal<T>& n) { return _data * n._data; }
  T operator *(const T& n) { return _data * n; }
  
  T getData() const { return _data; }
  
private:
  T _data = 0.00;
};

/**
 * Real Number class that uses Number and Decimal class types
 */
template<class T>
class RealNumber {
public:
  RealNumber<T>()
  : _number(NULL)
  , _decimal(NULL)
  {}
  
  RealNumber<T>(T data) {
    _number = (int)data;
    _decimal = data-(int)data;
  };
  
  RealNumber<T>(T number, T decimal)
  : _number(number)
  , _decimal(decimal)
  {};
  
  RealNumber<T>& operator=(const RealNumber<T> &n) {
    if (this != &n) {
      _number = n._number;
      _decimal = n._decimal;
    }
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const RealNumber& n) {
    os << n.getData();
    return os;
  }
  
  T operator +(const RealNumber<T>& n) { return getData() + n.getData(); }
  T operator +(const T& n) { return getData() + n; }
  
  T operator -(const RealNumber<T>& n) { return getData() - n.getData(); }
  T operator -(const T& n) { return getData() - n; }
  
  T operator /(const RealNumber<T>& n) { return getData() / n.getData(); }
  T operator /(const T& n) { return getData() / n; }
  
  T operator *(const RealNumber<T>& n) { return getData() * n.getData(); }
  T operator *(const T& n) { return getData() * n; }
  
  T operator ++() { return getData() + 1; }
  T operator --() { return getData() - 1; }
  
  T getData() const {
    return combine(_number, _decimal);
  }

private:
  Number<T> _number = NULL;
  Decimal<T> _decimal = NULL;
  
  T combine(Number<T> n, Decimal<T> d) const {
    T number = n.getData();
    T decimal = d.getData();
    return number + decimal;
  }
};


/**
 * Fraction class that combines two numbers class types as numerator and denominator
 */
template<class T>
class Fraction {
public:
  Fraction<T>()
  : _numerator(NULL)
  , _denominator(NULL)
  {}
  
  Fraction<T>(Number<T> numerator, Number<T> denominator) {
    long num = numerator.getData();
    long den = denominator.getData();
    *this = Fraction<T>(num, den);
  }
  
  Fraction<T>(T numerator, T denominator) {
    if (denominator > 0) {
      _numerator = numerator;
      _denominator = denominator;
    } else if (denominator < 0) {
      _numerator = numerator * -1;
      _denominator = denominator * -1;
    } else {
      try { throw BadNumber("Denominator can't be 0!"); }
      catch(BadNumber& e) { std::cout << e;}
    }
  };
  
  Fraction<T>& operator=(const Fraction<T> &f) {
    if (this != &f) {
      _numerator = f._numerator;
      _denominator = f._denominator;
    }
    return *this;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f._numerator;
    
    if (f._denominator.getData() != 1) {
      os << "/" << f._denominator;
    }
    return os;
  }
  
  Fraction<T> operator +(const Fraction<T>& f) {
    T a = _numerator.getData();
    T b = _denominator.getData();
    T c = f._numerator.getData();
    T d = f._denominator.getData();
    return convert((a*d) + (b*c), b*d);
  }
  
  Fraction<T> operator -(const Fraction<T>& f) {
    T a = _numerator.getData();
    T b = _denominator.getData();
    T c = f._numerator.getData();
    T d = f._denominator.getData();
    return convert((a*d) - (b*c), b*d);
  }
  
  Fraction<T> operator /(const Fraction<T>& f) {
    T a = _numerator.getData();
    T b = _denominator.getData();
    T c = f._numerator.getData();
    T d = f._denominator.getData();
    return convert(a*d, b*c);
  }
  
  Fraction<T> operator *(const Fraction<T>& f) {
    T a = _numerator.getData();
    T b = _denominator.getData();
    T c = f._numerator.getData();
    T d = f._denominator.getData();
    return convert(a*c, b*d);
  }
  
private:
  Number<T> _numerator = NULL;
  Number<T> _denominator = NULL;
  
  T gcd(long x, long y) const {
    if (y == 0) return x;
    else return gcd(y, x%y);
  };
  
  Fraction<T> convert(T numerator, T denominator) {
    T divisor = gcd(numerator, denominator);
    return Fraction(numerator/divisor, denominator/divisor);
  };
};

#endif /* Number_h */
