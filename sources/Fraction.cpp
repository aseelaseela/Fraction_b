#include "Fraction.hpp"
#include <cmath>
using namespace std;
namespace ariel
{
    int add_overflow_check(int num, int other ) {
        int result=num+other;
        bool is_pos_overflow = other >0 && num > numeric_limits<int>::max()-other; 
        bool is_neg_overflow = other <0 && num < numeric_limits<int>::min()-other;
        return (is_pos_overflow || is_neg_overflow)?throw std::overflow_error("add_overflow") : result;  
      } 

    int sub_overflow_check(int num, int other ) {
        int result=num-other;
        bool is_overflow = other<0 && num > (numeric_limits<int>::max()+other) || (other>0 && num <(numeric_limits<int>::min()+other));
        return is_overflow ? throw std::overflow_error("sub_overflow"):result;
      } 

    int mult_overflow_check(int num, int other ) {
        int result=num*other;
        bool is_overflow = other >0 && num > (numeric_limits<int>::max()/other) || (other <0 && num <(numeric_limits<int>::max()/other));
        return is_overflow ? throw std::overflow_error("mult_overflow"):result;
      } 

    int div_overflow_check(int num, int other ) {
        int result=num/other;
        bool is_overflow = (other ==0 || (num ==(numeric_limits<int>::min()) && (other ==-1 ) )) ;
        return is_overflow ? throw std::overflow_error("div_overflow"):result;
        } 


    Fraction::Fraction(int _numerator_, int _denominator_) : numerator(_numerator_), denominator(_denominator_)
    {
        if (_denominator_ == 0)
        {
            throw std ::invalid_argument(" can't divide by zero");
        }

        if (_denominator_ < 0)
        {
            _denominator_ *= -1;
            _numerator_ *= -1;
        }

        reduce();
    }

    Fraction::Fraction(float number) : numerator(number * PRECISION), denominator(PRECISION)
    {
        reduce();
    }

    // operator +
    Fraction Fraction ::operator+(const float &num) const
    {
        Fraction helper(num);
        helper = *this + helper;
        helper.reduce();
        return helper;
    }
    Fraction Fraction ::operator+(const Fraction &other) const
    {
        int _numerator=add_overflow_check(mult_overflow_check(numerator,other.denominator),mult_overflow_check(other.numerator,denominator));
        int _denominator=mult_overflow_check(denominator,other.denominator);
        reduce(_numerator,_denominator);
        return Fraction(_numerator,_denominator);
    }
    
    Fraction operator+(const float &num, const Fraction &other)
    {
        return Fraction(num) + other;
    }
    Fraction &Fraction ::operator++()
    {
        if (__builtin_add_overflow(numerator,denominator,&numerator))
        {
            throw std :: overflow_error("over flow error ");
        }
        return *this;
    }
    Fraction Fraction ::operator++(int)
    {
        Fraction helper(*this);
        if (__builtin_add_overflow(numerator,denominator,&numerator))
        {
            throw std :: overflow_error("over flow error ");
        }
        return helper;
    }

    // operator -
    Fraction Fraction ::operator-(const float &num) const
    {
        Fraction helper(num);
        helper = *this - helper;
        helper.reduce();
        return helper;
    }
    Fraction Fraction ::operator-(const Fraction &other) const
    {
        int _numerator=sub_overflow_check(mult_overflow_check(numerator,other.denominator),mult_overflow_check(other.numerator,denominator));
        int _denominator=mult_overflow_check(denominator,other.denominator);
        reduce(_numerator,_denominator);
        return Fraction(_numerator,_denominator);
    }
    Fraction operator-(const float &num, const Fraction &other)
    { 
        Fraction helper(num);
        helper = helper - other;
        helper.reduce();
        return helper;
    }
    Fraction &Fraction ::operator--()
    {
        if (__builtin_sub_overflow(numerator,denominator,&numerator))
        {
            throw std :: overflow_error("over flow error ");
        }
        return *this;
    }
    Fraction Fraction ::operator--(int)
    {
        Fraction helper(*this);
        if (__builtin_sub_overflow(numerator,denominator,&numerator))
        {
            throw std::overflow_error(" overflow error ! ");
        }
        return helper;
    }

    // operator *
    Fraction Fraction ::operator*(const float &num) const
    {
        Fraction helper(num);
        helper = *this * helper;
        helper.reduce();
        return helper;
    }
    Fraction Fraction ::operator*(const Fraction &other) const
    {
        return Fraction(mult_overflow_check(numerator,other.numerator),mult_overflow_check(denominator,other.denominator));
    }
    Fraction operator*(const float &num, const Fraction &other)
    {
        Fraction helper(num);
        helper = helper * other;
        helper.reduce();
        return helper;
    }

    // operator /
    Fraction Fraction ::operator/(const float &num) const
    {
        if (num == 0)
        {
            throw runtime_error("can't divide by zero");
        }
        Fraction helper(num);
        helper = *this / helper;
        helper.reduce();
        return helper;
    }
    Fraction Fraction ::operator/(const Fraction &other) const
    {
        if (other.numerator == 0)
        {
            throw std::runtime_error("can't divide by zero");
        }
        int _numerator= mult_overflow_check(numerator,other.denominator);
        int _denominator= mult_overflow_check(denominator,other.numerator);
        reduce(_numerator,_denominator);
        return Fraction(_numerator,_denominator);

    }
    Fraction operator/(const float &num, const Fraction &other)
    {
        if (other.numerator == 0)
        {
            throw std::runtime_error("can't divide by zero");
        }
        Fraction helper(num);
        helper = helper / other;
        helper.reduce();
        return helper;
    }
    
    // operator =
    Fraction &Fraction ::operator=(const Fraction &other)
    {
        if (this != &other)
        {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }
    Fraction &Fraction ::operator=(Fraction &&other) noexcept
    {
        if (this != &other)
        {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }

    // compare ==
    bool Fraction ::operator==(const float &num) const
    {
        Fraction helper(num);
        return *this == helper;
    }
    bool Fraction ::operator==(const Fraction &other) const
    {
        return (this->numerator == other.numerator && this->denominator == other.denominator);
    }
    bool operator==(const float &num, const Fraction &other)
    {
        return Fraction(num) == other;
    }
    // compare !=
    bool Fraction ::operator!=(const float &num) const
    {
        return !(*this == Fraction(num));
    }
    bool Fraction ::operator!=(const Fraction &other) const
    {
        return !(*this == other);
    }
    bool operator!=(const float &num, const Fraction &other)
    {
        return !(Fraction(num) == other);
    }

    // compare >
    bool Fraction ::operator>(const float &num) const
    {
        return *this > Fraction(num);
    }
    bool Fraction ::operator>(const Fraction &other) const
    {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }
    bool operator>(const float &num, const Fraction &other)
    {
        return Fraction(num) > other;
    }

    // compare <
    bool Fraction ::operator<(const float &num) const
    {
        return *this < Fraction(num);
    }
    bool Fraction ::operator<(const Fraction &other) const
    {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }
    bool operator<(const float &num, const Fraction &other)
    {
        return Fraction(num) < other;
    }

    bool Fraction ::operator>=(const float &num) const
    {
        return !(*this < Fraction(num));
    }

    bool Fraction ::operator>=(const Fraction &other) const
    {
        return !(*this < other);
    }
    bool operator>=(const float &num, const Fraction &other)
    {
        return !(Fraction(num) < other);
    }

    bool Fraction ::operator<=(const float &num) const
    {
        return !(*this > Fraction(num));
    }

    bool Fraction ::operator<=(const Fraction &other) const
    {
        return !(*this > other);
    }

    bool operator<=(const float &num, const Fraction &other)
    {
        return !(Fraction(num) > other);
    }

    std::istream &operator>>(std::istream &input, Fraction &fraction)
    {
        int numerator=0, denominator=0;
        input >> numerator >> denominator;

        if (!input)
        {
            throw std::runtime_error("invalid input");
        }

        if (denominator == 0)
        {
            throw std::runtime_error("denominator can't be 0");
        }

        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }

        fraction.numerator = numerator;
        fraction.denominator = denominator;
        fraction.reduce();
        return input;
    }

}