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
    numerator = 0;
    denominator = 1;
    greatestFactor = 1;
    isPositive = true;
    isNormalized = true;
    isWholeNumber = true;
}

Rational::Rational(int wholeNumber)
{
    cout<<"-- Rational Whole Number constructor -- "<<endl;
    numerator = wholeNumber;
    denominator = 1;
    greatestFactor = 1;
    isNormalized = true;
    isWholeNumber = true;

    if (is_positive_number(wholeNumber))
    {
        isPositive = true;
    } else
    {
        isPositive = false;
    }
}

Rational::Rational(int numer, int denom)
{
    cout<<"-- Rational Numerator and Denominator constructor -- "<<endl;

    numerator = numer;
    denominator = denom;
    isNormalized = false;

    if (is_whole_number(denom))
    {
        isWholeNumber = true;
    } else
    {
        isWholeNumber = false;
    }

    greatestFactor = get_GCF(numer, denom);
    if (greatestFactor == 1)
    {
        isNormalized = true;
    }

    if (is_rational_num_positive(numer, denom))
    {
        isPositive = true;
    } else
    {
        isPositive = false;
    }
}

Rational::Rational(string text)
{
    if (!text.find('/') == string::npos)
    {
        numerator = stoi(text);
        denominator = 1;
        isNormalized = true;
        isWholeNumber = true;
        isPositive = true;
        if (text.find('-') == string::npos)
        {
            isPositive = false;
        }

    }

    stringstream ss(text);
    string token;
    //
    // // Extract tokens separated by commas
    // for (int i = 0; i < 1; i++)
    //     getline(ss, token, '/')
    //     token 
    // }

}

Rational::~Rational()
{

}

// ========================================= OVERLOADS ========================================= //

// ========================================= METHODS ========================================= //
bool Rational::is_dividing_by_zero(const Rational& obj)
{

}

bool Rational::is_valid_number(const string& str)
{

}

bool Rational::is_positive_number(const int& number)
{
    if (number >= 0) { return true; } return false;
}

bool Rational::is_rational_num_positive(const int& numer, const int& denom)
{
    if (numer < 0 && denom < 0)
    {
        return true;
    }
    if (numer >= 0 && denom >= 0)
    {
        return true;
    }
    return false;
}

bool Rational::is_whole_number(const int& denom)
{
    if (denom == 0) { return true; } return false;
}

int Rational::get_GCF(int& numerator, int& denominator)
{
    // make both possitive
    numerator = abs(numerator);
    denominator = abs(denominator);

    while (denominator != 0) {
        int temp = denominator;
        denominator = numerator % denominator;
        numerator = temp;
    }
    
    return numerator;
}

void Rational::normalize()
{

}


