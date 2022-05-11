/*****************************************************************************
Title: complex - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Nathan
Description: complex API
******************************************************************************/

#include <iostream> // cin, cout
#include <cmath> // pow

#include "complex.hpp" // api

using namespace ilrd;

/**************************** HELPER FUNCS ***********************************/

static double GetMultReal(const Complex& lhs, const Complex& rhs)
{
    return ((lhs.GetReal() * rhs.GetReal()) - 
           (lhs.GetImaginary() * rhs.GetImaginary()));
}

static double GetMultImaginary(const Complex& lhs, const Complex& rhs)
{
    return ((lhs.GetReal() * rhs.GetImaginary()) + 
           (lhs.GetImaginary() * rhs.GetReal()));
}

static double GetDivisor(const Complex& rhs)
{
    return (pow(rhs.GetReal(), 2) + pow(rhs.GetImaginary(), 2));
}

static double GetDivReal(const Complex& lhs, const Complex& rhs)
{
    return (((lhs.GetReal() * rhs.GetReal()) +
           (lhs.GetImaginary() * rhs.GetImaginary())) / GetDivisor(rhs));
}

static double GetDivImaginary(const Complex& lhs, const Complex& rhs)
{
    return (((lhs.GetImaginary() * rhs.GetReal()) -
           (lhs.GetReal() * rhs.GetImaginary())) / GetDivisor(rhs));
}

/*****************************************************************************/

Complex::Complex(double real_, double imag_)
    : m_real(real_), m_imaginary(imag_)
{}

/*****************************************************************************/

void Complex::SetReal (double new_value)
{
    m_real = new_value;
}

void Complex::SetImaginary (double new_value)
{
    m_imaginary = new_value;
}

double Complex::GetReal() const
{
    return m_real;
}

double Complex::GetImaginary() const
{
    return m_imaginary;
}

/*****************************************************************************/

Complex& Complex::operator+=(const Complex& cnum_)
{
    m_real += cnum_.GetReal();
    m_imaginary += cnum_.GetImaginary();

    return *this;
}

Complex& Complex::operator-=(const Complex& cnum_)
{
    m_real -= cnum_.GetReal();
    m_imaginary -= cnum_.GetImaginary();

    return *this;
}

Complex& Complex::operator*=(const Complex& cnum_)
{
    double temp_real = GetMultReal(*this, cnum_);
    m_imaginary = GetMultImaginary(*this, cnum_);
    m_real = temp_real;

    return *this;
}

Complex& Complex::operator/=(const Complex& cnum_)
{
    double temp_real = GetDivReal(*this, cnum_);
    m_imaginary = GetDivImaginary(*this, cnum_); 
    m_real = temp_real;

    return *this;
}

/*****************************************************************************/

bool operator==(const Complex& lhs_cnum_, const Complex& rhs_cnum_)
{
    return (lhs_cnum_.GetReal() == rhs_cnum_.GetReal()) && 
           (lhs_cnum_.GetImaginary() == rhs_cnum_.GetImaginary()); 
}

bool operator!=(const Complex& lhs_cnum_, const Complex& rhs_cnum_)
{
    return (lhs_cnum_.GetReal() != rhs_cnum_.GetReal()) || 
           (lhs_cnum_.GetImaginary() != rhs_cnum_.GetImaginary()); 
}

/*****************************************************************************/

const Complex ilrd::operator/(const Complex& lhs_cnum_, const Complex& rhs_cnum_)
{
    return Complex(GetDivReal(lhs_cnum_, rhs_cnum_), 
                   GetDivImaginary(lhs_cnum_, rhs_cnum_));
}

const Complex ilrd::operator*(const Complex& lhs_cnum_, const Complex& rhs_cnum_)
{
    return Complex(GetMultReal(lhs_cnum_, rhs_cnum_), 
                   GetMultImaginary(lhs_cnum_, rhs_cnum_));
}

const Complex ilrd::operator-(const Complex& lhs_cnum_, const Complex& rhs_cnum_)
{
    return Complex((lhs_cnum_.GetReal() - rhs_cnum_.GetReal()),
                   (lhs_cnum_.GetImaginary() - rhs_cnum_.GetImaginary()));
}

const Complex ilrd::operator+(const Complex& lhs_cnum_, const Complex& rhs_cnum_)
{
    return Complex((lhs_cnum_.GetReal() + rhs_cnum_.GetReal()),
                   (lhs_cnum_.GetImaginary() + rhs_cnum_.GetImaginary()));
}

/*****************************************************************************/

std::ostream& ilrd::operator<<(std::ostream& os_, const Complex& cnum_)
{
    return os_ << cnum_.GetReal() << " + " << cnum_.GetImaginary() << 'i' << std::endl; 
}

std::istream& ilrd::operator>>(std::istream& is_, Complex& cnum_)
{
    double input;

    std::cout << "real: ";
    is_ >> input;
    cnum_.SetReal(input);

    std::cout << "imaginary: ";
    is_ >> input;
    cnum_.SetImaginary(input);

    return is_;
}

/*****************************************************************************/
