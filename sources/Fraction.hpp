#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <limits>
const int PRECISION = 1000;
namespace ariel
{
    class Fraction
    {
        int numerator;
        int denominator;
        static void reduce(int &numerator, int &denominator)
        {
            int div = gcd(abs(numerator), abs(denominator));
            numerator /= div;
            denominator /= div;
        }
        // greatest common divisor of num1 & num2
        static int gcd(int num1, int num2)
        {
            if (num2 == 0)
            {
                return num1;
            }

            return gcd(num2, num1 % num2);
        }
        void reduce()
        {
            if (denominator < 0)
            {
                denominator *= -1;
                numerator *= -1;
            }

            int div = gcd(abs(numerator), abs(denominator));
            numerator /= div;
            denominator /= div;
        }  

        
    public:
        // constructors of fraction class

        // Default constructor
        Fraction() : numerator(0), denominator(1) {}

        Fraction(float number);
        Fraction(int _numerator_, int _denominator_);

        // copy constructor
        Fraction(const Fraction &copy) : numerator(copy.numerator), denominator(copy.denominator) {}

        // move constructor
        Fraction(Fraction &&other) noexcept : numerator(other.numerator), denominator(other.denominator) {}

        // destructor
        ~Fraction() = default;

        // getters
        int getNumerator() const { return numerator; }
        int getDenominator() const { return denominator; }

        //setters
        void setNumerator(int numerator) {this->numerator=numerator;}
        void setDenominator(int denominator) {this->denominator=denominator;}

        // operator +
        Fraction operator+(const float &num) const;
        Fraction operator+(const Fraction &other) const;
        friend Fraction operator+(const float &num, const Fraction &other);

        // operator -
        Fraction operator-(const Fraction &other) const;
        Fraction operator-(const float &other) const;
        friend Fraction operator-(const float &num, const Fraction &other);

        // operator *
        Fraction operator*(const float &num) const;
        Fraction operator*(const Fraction &other) const;
        friend Fraction operator*(const float &num, const Fraction &other);

        // operator =
        Fraction &operator=(const Fraction &other);
        Fraction &operator=(Fraction&& other) noexcept;

        // operator /
        Fraction operator/(const float &num) const;
        Fraction operator/(const Fraction &other) const;
        friend Fraction operator/(const float &num, const Fraction &other);

        // compare ==
        bool operator==(const float &num) const;
        bool operator==(const Fraction &other) const;
        friend bool operator==(const float &num, const Fraction &other);
     //   friend bool operator==(const Fraction& num , const Fraction& other);

        // compare !=
        bool operator!=(const float &num) const;
        bool operator!=(const Fraction &other) const;
        friend bool operator!=(const float &num, const Fraction &other);

        // compare >
        bool operator>(const float &num) const;
        bool operator>(const Fraction &other) const;
        friend bool operator>(const float &num, const Fraction &other);

        // compare <
        bool operator<(const float &num) const;
        bool operator<(const Fraction &other) const;
        friend bool operator<(const float &num, const Fraction &other);

        // compare >=
        bool operator>=(const float &num) const;
        bool operator>=(const Fraction &other) const;
        friend bool operator>=(const float &num, const Fraction &other);

        // compare <=
        bool operator<=(const float &num) const;
        bool operator<=(const Fraction &other) const;
        friend bool operator<=(const float &num, const Fraction &other);

        // pre - increments 1 to the fraction
        Fraction &operator++();

        // post - increments 1 to the fraction
        Fraction operator++(int);

        // pre - decrements 1 to the fraction
        Fraction &operator--();

        // post - decrements 1 to the fraction
        Fraction operator--(int);

        // stream operators
        // return the output stream
        // operator <<
        friend std::ostream &operator<<(std::ostream &output, const Fraction &fraction)
        {
            output << fraction.numerator << '/' << fraction.denominator;
            return output;
        }

        // return the input stream
        // operator >>
        friend std::istream &operator>>(std::istream &input, Fraction &fraction);


    
    };
}
#endif