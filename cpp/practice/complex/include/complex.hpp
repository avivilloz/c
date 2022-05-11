/****************************************************************************
Title: Complex Number - Infinity Labs R&D 
Group: Ol91
Description: Complex number  API
*****************************************************************************/

#ifndef ILRD_OL91_COMPLEX_NUMBER_HPP
#define ILRD_OL91_COMPLEX_NUMBER_HPP

#include <iostream>

namespace ilrd
{
class Complex 
{
public:
    Complex(double real_= 0, double imag_ = 0);

    void SetReal (double new_value);
    void SetImaginary (double new_value);
    double GetReal() const;
    double GetImaginary() const;
    
    Complex& operator+=(const Complex& cnum_);
    Complex& operator-=(const Complex& cnum_);
    Complex& operator*=(const Complex& cnum_);
    Complex& operator/=(const Complex& cnum_);

private:
    double m_real;
    double m_imaginary;
};

bool operator==(const Complex& lhs_cnum_, const Complex& rhs_cnum_);
bool operator!=(const Complex& lhs_cnum_, const Complex& rhs_cnum_);
const Complex operator/(const Complex& lhs_cnum_, const Complex& rhs_cnum_); 
const Complex operator*(const Complex& lhs_cnum_, const Complex& rhs_cnum_);
const Complex operator-(const Complex& lhs_cnum_, const Complex& rhs_cnum_);
const Complex operator+(const Complex& lhs_cnum_, const Complex& rhs_cnum_);

std::ostream& operator<<(std::ostream& os_, const Complex& cnum_);
std::istream& operator>>(std::istream& is_, Complex& cnum_);
} // end of namespace ilrd

#endif //ILRD_OL91_COMPLEX_NUMBER_HPP
