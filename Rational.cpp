//
// Created by gamef on 2026-11-19.
//

#include "Rational.h"
#include <cmath>
#include <string>
#include <cstdlib>
#include  <sstream>
using namespace std;

// ========================================= CONSTRUCTORS ========================================= //

Rational::Rational()
{
    cout<<"-- Rational Default constructor -- "<<endl;
    set_value(0, 1);
}

Rational::Rational(int wholeNumber)
{
    cout<<"-- Rational Whole Number constructor -- "<<endl;
    set_value(wholeNumber, 1);
}

Rational::Rational(int numer, int denom)
{
    cout<<"-- Rational Numerator and Denominator constructor -- "<<endl;
    set_value(numer, denom);
}

Rational::Rational(const string& text)
{
    cout<<" -- Rational String constructor -- "<<endl;

    if (!is_valid_number(text))
    {
        throw invalid_argument("Invalid number format");
    }
    size_t slash = text.find('/');

    // If it cannot find the slash
    if (slash == string::npos)
    {
        Rational(stoi(text));
    }
    else
    {
        int numer = stoi(text.substr(0, slash)); // Everything before the slash
        int denom = stoi(text.substr(slash + 1)); // Everything after the slash

        set_value(numer, denom);
    }
}

    Rational::~Rational()
    {

    }

// ========================================= OVERLOADS ========================================= //
    Rational operator+(const Rational& obj1,const Rational& obj2)
    {
        cout << " -- Operator Overload '+' -- " << endl;
        // brings upto same denominator equivalent for 'otherNumerator'
        int scaledNumer1 = obj1.numerator * obj2.denominator;

        //Gets other obj numerator to be brought upto a same denominator equivalent
        int scaledNumer2 = obj1.denominator * obj2.numerator;

        int denom = obj1.denominator * obj2.denominator;

        return Rational(scaledNumer1 + scaledNumer2, denom);
    }

    Rational operator-(const Rational& obj1, const Rational& obj2)
    {
        cout << " -- Operator Overload '-' -- " << endl;

        // brings upto same denominator equivalent for 'otherNumerator'
        int scaledNumer1 = obj1.numerator * obj2.denominator;

        //Gets other obj numerator to be brought upto a same denominator equivalent
        int scaledNumer2 = obj1.denominator * obj2.numerator;

        int denom = obj1.denominator * obj2.denominator;

        return Rational(scaledNumer1 - scaledNumer2, denom);
    }

    Rational operator*(const Rational& obj1, const Rational& obj2)
    {
        cout << " -- Operator Overload '*' -- " << endl;

        return Rational(obj1.numerator * obj2.numerator, obj1.denominator * obj2.denominator);
    }

    Rational operator/(const Rational& obj1, const Rational& obj2)
    {
        cout << " -- Operator Overload '/' -- " << endl;

        if (obj2.numerator == 0)
        {
            throw invalid_argument("Denominator cannot be zero: Devision operator");
        }

        return Rational(obj1 * Rational(obj2.denominator, obj2.numerator));
    }

    // Compares by cross-multiplying (no division, so no rounding or truncation).
    // Valid because denominators are always positive, so the inequality never flips.
    bool operator>(const Rational& obj1, const Rational& obj2)
    {
        cout << " -- Operator Overload '>' -- " << endl;

        // a * c
        int obj1Result = (obj1.numerator * obj2.denominator); // (a/b) * (b*d) = a·d (the bs cancel)

        // c * b
        int obj2Result = (obj2.numerator * obj1.denominator); // (c/d) * (b*d) = c·b (the ds cancel)
        return (obj1Result > obj2Result);
    }

    bool operator==(const Rational& obj1, const Rational& obj2)
    {
        cout << " -- Operator Overload '==' -- " << endl;

        int obj1Result = (obj1.numerator * obj2.denominator);
        int obj2Result = (obj2.numerator * obj1.denominator);
        return (obj1Result == obj2Result);
    }

    bool operator<(const Rational& obj1, const Rational& obj2)
    {
        cout << " -- Operator Overload '<' -- " << endl;

        return (obj2 > obj1);
    }

    ostream& operator<<(ostream& output, Rational& obj)
    {
        cout << " -- Operator Overload '<<' -- " << endl;

        obj.normalize();
        output << obj.numerator << "/" << obj.denominator << endl;
        return output;
    }

// ========================================= METHODS ========================================= //
void Rational::set_value(const int& numer, const int& denom)
{
    cout << "[DEBUG] Assigning Value to Rational number: " << numer << "/" << denom << endl;
    if (denom == 0)
    {
        throw invalid_argument("Denominator cannot be zero");
    }

    //Flips to make numerator possitive ans assigns appropriately
    if (numer > 0 && denom < 0)
    {
        denominator = abs(denom);
        numerator = numer * -1;
    } else if (numer < 0 && denom < 0)
    {
        numerator = abs(numer);
        denominator = abs(denom);
    } else
    {
        numerator = numer;
        denominator = denom;
    }
}

bool Rational::is_positive() const
{
    return numerator >= 0;
}

bool Rational::is_normalized() const
{
    return (get_GCF(numerator, denominator) == 1);
}

bool Rational::is_whole_number() const
{
    return (denominator == 1);
}

void Rational::normalize()
{
    int greatestFactor = get_GCF(numerator, denominator);
    if (greatestFactor != 1)
    {
        numerator = numerator / greatestFactor;
        denominator = denominator / greatestFactor;
    }
}

bool Rational::is_valid_number(const string& text)
{
    size_t slash = text.find('/');

    // if it does not find a /
    if (slash == string::npos)
    {
        return is_integer(text);
    }

    // only one slash allowed
    if (text.find('/', slash + 1) != string::npos)
    {
        return false;
    }

    string numer = text.substr(0, slash);
    string denom = text.substr(slash + 1);

    return is_integer(numer) && is_integer(denom);
}

bool Rational::is_fraction_input(const string& text)
{
    size_t slash = text.find('/');

    return (slash != string::npos);
}

bool Rational::is_integer(const string& text)
{
    if (text.empty())
        return false;

    try
    {
        size_t pos;
        stoi(text, &pos);
        return pos == text.size();
    }
    catch (...)
    {
        return false;
    }
}

bool Rational::is_dividing_by_zero(const Rational& r)
{
    return (r.denominator == 0);
}

int Rational::get_greatest_factor() const
{
    return (get_GCF(numerator, denominator));
}

int Rational::get_GCF(int numer, int denom)
{
    // make both possitive
    numer = abs(numer);
    denom = abs(denom);

    while (denom != 0) {
        int temp = denom;
        denom = numer % denom;
        numer = temp;
    }

    return numer;
}



