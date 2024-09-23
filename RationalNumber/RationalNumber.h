#pragma once
#include <iostream>
#include <numeric>
namespace yourname
{
  template <typename T>
  class RationalNumber
  {
  public:
    RationalNumber(T num = 0, T denom = 1);

    RationalNumber &operator+=(const RationalNumber<T> &other);
    RationalNumber &operator*=(const RationalNumber<T> &other);
    RationalNumber &operator/=(const RationalNumber<T> &other);
    RationalNumber &operator-=(const RationalNumber<T> &other);

    // prefix increment
    RationalNumber &operator++();
    // postfix increment
    RationalNumber operator++(int);

    RationalNumber operator+() const;
    RationalNumber operator-() const;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const RationalNumber<U> &obj);

    template <typename K>
    friend bool operator<(const RationalNumber<K> &lhs, const RationalNumber<K> &rhs);
    template <typename K>
    friend bool operator==(const RationalNumber<K> &lhs, const RationalNumber<K> &rhs);

    template <typename Q>
    operator Q() const;

  private:
    T numerator;
    T denominator;
    void simplify();
  };

  template <typename T>
  template <typename Q>
  RationalNumber<T>::operator Q() const
  {
    return static_cast<Q>(numerator) / static_cast<Q>(denominator);
  }

  template <typename T>
  RationalNumber<T>::RationalNumber(T num, T denom) : numerator(num), denominator(denom)
  {
    if (denom == 0)
    {
      throw std::invalid_argument("dividing by zero");
    }
    simplify();
  }

  template <typename T>
  void RationalNumber<T>::simplify()
  {
    if (denominator < 0)
    {
      denominator *= -1;
      numerator *= -1;
    }
    T tnum = numerator < 0 ? -numerator : numerator; // compiler was warning about std::abs(numerator)
    T temp = std::gcd(tnum, denominator);
    numerator /= temp;
    denominator /= temp;
  }

  template <typename T>
  RationalNumber<T> &RationalNumber<T>::operator+=(const RationalNumber<T> &other)
  {
    T temp = std::lcm(other.denominator, denominator);
    numerator = (temp / denominator) * numerator + (temp / other.denominator) * other.numerator;
    denominator = temp;
    simplify();
    return *this;
  }
  template <typename T>
  RationalNumber<T> &RationalNumber<T>::operator*=(const RationalNumber<T> &other)
  {
    T temp1 = std::gcd(numerator, other.denominator);
    T temp2 = std::gcd(other.numerator, denominator);
    numerator = (other.numerator / temp2) * (numerator / temp1);
    denominator = (other.denominator / temp1) * (denominator / temp2);
    simplify();
    return *this;
  }
  template <typename T>
  RationalNumber<T> &RationalNumber<T>::operator/=(const RationalNumber<T> &other)
  {
    RationalNumber<T> temp(other.denominator, other.numerator);
    *this *= temp;
    return *this;
  }
  template <typename T>
  RationalNumber<T> &RationalNumber<T>::operator-=(const RationalNumber<T> &other)
  {
    RationalNumber<T> temp(-other.numerator, other.denominator);
    *this += temp;
    return *this;
  }

  // prefix increment
  template <typename T>
  RationalNumber<T> &RationalNumber<T>::operator++()
  {
    numerator += denominator;
    simplify();
    return *this;
  }
  // postfix increment
  template <typename T>
  RationalNumber<T> RationalNumber<T>::operator++(int)
  {
    RationalNumber<T> old = *this;
    numerator += denominator;
    simplify();
    return old;
  }

  template <typename T>
  RationalNumber<T> RationalNumber<T>::operator+() const { return *this; }
  template <typename T>
  RationalNumber<T> RationalNumber<T>::operator-() const
  {
    RationalNumber<T> temp(numerator, denominator);
    temp.numerator *= -1;
    return temp;
  }

  template <typename T>
  RationalNumber<T> operator+(RationalNumber<T> lhs, const RationalNumber<T> &rhs)
  {
    lhs += rhs;
    return lhs;
  }
  template <typename T>
  RationalNumber<T> operator-(RationalNumber<T> lhs, const RationalNumber<T> &rhs)
  {
    lhs -= rhs;
    return lhs;
  }
  template <typename T>
  RationalNumber<T> operator*(RationalNumber<T> lhs, const RationalNumber<T> &rhs)
  {
    lhs *= rhs;
    return lhs;
  }
  template <typename T>
  RationalNumber<T> operator/(RationalNumber<T> lhs, const RationalNumber<T> &rhs)
  {
    lhs /= rhs;
    return lhs;
  }

  template <typename T>
  RationalNumber<T> operator+(T num, const RationalNumber<T> &other)
  {
    RationalNumber<T> res(num);
    res += other;
    return res;
  }
  template <typename T>
  RationalNumber<T> operator*(T num, const RationalNumber<T> &other)
  {
    RationalNumber<T> res(num);
    res *= other;
    return res;
  }
  template <typename T>
  RationalNumber<T> operator/(T num, const RationalNumber<T> &other)
  {
    RationalNumber<T> res(num);
    res /= other;
    return res;
  }
  template <typename T>
  RationalNumber<T> operator-(T num, const RationalNumber<T> &other)
  {
    RationalNumber<T> res(num);
    res -= other;
    return res;
  }

  template <typename T>
  std::ostream &operator<<(std::ostream &os, const RationalNumber<T> &obj)
  {
    os << obj.numerator << '/' << obj.denominator;
    return os;
  }

  template <typename T>
  bool operator<(const RationalNumber<T> &lhs, const RationalNumber<T> &rhs)
  {
    if (lhs.numerator * rhs.denominator < lhs.denominator * rhs.numerator)
    {
      return true;
    }
    return false;
  }
  template <typename T>
  bool operator>(const RationalNumber<T> &lhs, const RationalNumber<T> &rhs)
  {
    if (lhs < rhs || lhs == rhs)
    {
      return false;
    }
    return true;
  }
  template <typename T>
  bool operator<=(const RationalNumber<T> &lhs, const RationalNumber<T> &rhs)
  {
    if (lhs < rhs || lhs == rhs)
    {
      return true;
    }
    return false;
  }
  template <typename T>
  bool operator>=(const RationalNumber<T> &lhs, const RationalNumber<T> &rhs)
  {
    if (lhs > rhs || lhs == rhs)
    {
      return true;
    }
    return false;
  }
  template <typename T>
  bool operator==(const RationalNumber<T> &lhs, const RationalNumber<T> &rhs)
  {
    if (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator)
    {
      return true;
    }
    return false;
  }
  template <typename T>
  bool operator!=(const RationalNumber<T> &lhs, const RationalNumber<T> &rhs)
  {
    if (lhs == rhs)
    {
      return false;
    }
    return true;
  }

  namespace literals
  {
    RationalNumber<unsigned long long> operator""_r(unsigned long long literal)
    {
      return RationalNumber<unsigned long long>(literal);
    }
  } // namespace literals
} // namespace sana
// i think this kind of rational number is not bad. it could be helpful in certain cases.
// but if we dealing with big numbers and they cant be reduced in for examaple multiplication,
// it would be better using double/float numbers, because it could overflow.
// all in all, choice of realization type depends on the goal.