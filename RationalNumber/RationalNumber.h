// Your goal is to create a rational number class that would
// support each of the operations given in main.cpp.
//
// In this file you must declare only the interface of your class
// and implement the given functions separately from the class (at the bottom of
// this file inside the namespace).
// Notice that the RationalNumber is a class template, where the
// template parameter is an integer type for numerator and denominator.
//
// Note - Rename the namespace "yourname" to whatever you want, feel creative
// ( but not too much :) ).
//
// After you wrote RationalNumber class and the tests in the main function work
// - write at the bottom of the file the downsides of such rational numbers,
// what would you change/remove/add? Would you use such rational numbers instead
// of double/float numbers? There is no right/wrong answer, this question is
// more of a philosofical kind than technical.
#pragma once
#include <iostream>
#include <numeric>
namespace yourname
{
  template <typename T>
  class RationalNumber
  {
  public:
    // RationalNumber();
    // RationalNumber(T num, T denum): numerator(num), denumerator(denum){};
    // RationalNumber(T num): numerator(num), denumerator(1){};
    RationalNumber(T num = 0, T denum = 1) : numerator(num), denumerator(denum)
    {
      if (denum == 0)
      {
        throw std::invalid_argument("denumerator can't be 0");
      }
      simplify();
    }

    void simplify()
    {
      T temp = std::gcd(abs(numerator), abs(denumerator));
      numerator /= temp;
      denumerator /= temp;
      // if(numerator < 0 && denumerator < 0){
      //   numerator *= -1;
      //   denumerator *= - 1;
      // }
      if (denumerator < 0)
      {
        denumerator *= -1;
        numerator *= -1;
      }
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const RationalNumber<T> &obj)
    {
      os << obj.numerator << '/' << obj.denumerator;
      return os;
    }

    RationalNumber operator+(const RationalNumber<T> &other)
    {
      T temp = std::lcm(other.denumerator, denumerator);
      RationalNumber res;
      res.denumerator = temp;
      res.numerator = (temp / denumerator) * numerator +
                      (temp / other.denumerator) * other.numerator;
      res.simplify();
      return res;
    }
    RationalNumber operator-(const RationalNumber<T> &other)
    {
      T temp = std::lcm(other.denumerator, denumerator);
      RationalNumber res;
      res.denumerator = temp;
      res.numerator = (temp / denumerator) * numerator -
                      (temp / other.denumerator) * other.numerator;
      res.simplify();
      return res;
    }
    RationalNumber operator*(const RationalNumber<T> &other)
    {
      RationalNumber res;
      T temp1 = std::gcd(numerator, other.denumerator);
      T temp2 = std::gcd(other.numerator, denumerator);
      res.numerator = (other.numerator / temp2) * (numerator / temp1);
      res.denumerator = (other.denumerator / temp1) * (denumerator / temp2);
      res.simplify();
      return res;
    }
    RationalNumber operator/(const RationalNumber<T> &other)
    {
      RationalNumber res;
      res.numerator = numerator * other.denumerator;
      res.denumerator = denumerator * other.numerator;
      res.simplify();
      return res;
    }

    RationalNumber &operator+=(const RationalNumber<T> &other)
    {
      *this = *this + other;
      simplify();
      return *this;
    }
    RationalNumber &operator*=(const RationalNumber<T> &other)
    {
      *this = *this * other;
      simplify();
      return *this;
    }
    RationalNumber &operator/=(const RationalNumber<T> &other)
    {
      *this = *this / other;
      simplify();
      return *this;
    }
    RationalNumber &operator-=(const RationalNumber<T> &other)
    {
      *this = *this - other;
      simplify();
      return *this;
    }

    // prefix increment
    RationalNumber &operator++()
    {
      numerator += denumerator;
      simplify();
      return *this;
    }
    // postfix increment
    RationalNumber operator++(int)
    {
      RationalNumber old;
      numerator += denumerator;
      simplify();
      return old;
    }

    RationalNumber operator+() const { return *this; }
    RationalNumber operator-()
    {
      numerator *= -1;
      simplify();
      return *this;
    }

    friend RationalNumber operator+(T num, const RationalNumber &other)
    {
      RationalNumber res;
      res.numerator = num * other.denumerator + other.numerator;
      res.denumerator = other.denumerator;
      res.simplify();
      return res;
    }
    friend RationalNumber operator*(int num, const RationalNumber &other)
    {
      RationalNumber res;
      res.numerator = num * other.numerator;
      res.denumerator = other.denumerator;
      res.simplify();
      return res;
    }
    friend RationalNumber operator/(int num, const RationalNumber &other)
    {
      RationalNumber res;
      res.numerator = num * other.denumerator;
      res.denumerator = other.numerator;
      res.simplify();
      return res;
    }
    friend RationalNumber operator-(int num, const RationalNumber &other)
    {
      RationalNumber res;
      res.numerator = num * other.denumerator - other.numerator;
      res.denumerator = other.denumerator;
      res.simplify();
      return res;
    }

    bool operator<(const RationalNumber &other) const
    {
      if (numerator < 0 && other.numerator > 0)
      {
        return true;
      }
      if (numerator > 0 && other.numerator < 0)
      {
        return false;
      }
      if (numerator * other.denumerator < denumerator * other.numerator)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    bool operator>(const RationalNumber &other) const
    {
      if (numerator < 0 && other.numerator > 0)
      {
        return false;
      }
      if (numerator > 0 && other.numerator < 0)
      {
        return true;
      }
      if (numerator * other.denumerator < denumerator * other.numerator)
      {
        return false;
      }
      else
      {
        return true;
      }
    }
    bool operator<=(const RationalNumber &other) const
    {
      if (*this < other || *this == other)
      {
        return true;
      }
      return false;
    }
    bool operator>=(const RationalNumber &other) const
    {
      if (*this > other || *this == other)
      {
        return true;
      }
      return false;
    }
    bool operator==(const RationalNumber &other) const
    {
      if (numerator == other.numerator && denumerator == other.denumerator)
      {
        return true;
      }
      return false;
    }
    bool operator!=(const RationalNumber &other) const
    {
      if (*this == other)
      {
        return false;
      }
      return true;
    }

    template <typename Q>
    operator Q() const
    {
      return static_cast<Q>(numerator) / static_cast<Q>(denumerator);
    }

  private:
    T numerator;
    T denumerator;
  };
  namespace literals
  {
    // template<typename T>
    RationalNumber<unsigned long long> operator""_r(unsigned long long literal)
    {
      return RationalNumber(literal);
    }
  } // namespace literals
} // namespace yourname
