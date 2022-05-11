/*****************************************************************************
Title: simple_string - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Nour
Description: simple_string API
******************************************************************************/

#include <cstring> // size_t, strlen, memcpy

#include "simple_string.hpp" // api 

/**************************** HELPER FUNCS ***********************************/

static void SetStr(char*& dest, const char *src)
{
    std::size_t size = strlen(src) + 1;

    dest = new char[size];
    memcpy(dest, src, size);
}

static int IsSameStr(const char *lhs, const char *rhs)
{
    return (0 == strcmp(lhs, rhs));
}

static int IsBiggerStr(const char *lhs, const char *rhs)
{
    return (strcmp(lhs, rhs) > 0);
}

static int IsSmallerStr(const char *lhs, const char *rhs)
{
    return (strcmp(lhs, rhs) < 0);
}

/*****************************************************************************/

String::String(const char *str_)
    : m_cstr(NULL)
{
    SetStr(m_cstr, str_);
}

/*****************************************************************************/

String::String(const String& str_)
    : m_cstr(NULL)
{
    SetStr(m_cstr, str_.CStr());
}

/*****************************************************************************/

String& String::operator=(const String& str_)
{
    if (this == &str_)
    {
        return *this;
    }

    char *to_delete = m_cstr; 

    SetStr(m_cstr, str_.CStr());

    delete[] to_delete;

    return *this; 
}

/*****************************************************************************/

String::~String()
{
    delete[] m_cstr;
    m_cstr = NULL;
}

/*****************************************************************************/

std::size_t String::Length() const
{
    return strlen(m_cstr);
}

/*****************************************************************************/

char *String::CStr() const
{
    return m_cstr;
}

/*****************************************************************************/

std::ostream& operator<<(std::ostream& os_, const String& str_)
{
    return os_ << str_.CStr();
}

/*****************************************************************************/

bool String::operator==(const String& str_) const
{
    return IsSameStr(this->CStr(), str_.CStr());
}

bool String::operator==(const char *str_) const
{
    return IsSameStr(this->CStr(), str_);
}

bool operator==(const char *lhs, const String& rhs)
{
    return IsSameStr(lhs, rhs.CStr());
}

/*****************************************************************************/

bool String::operator!=(const String& str_) const
{
    return !IsSameStr(this->CStr(), str_.CStr());
}

bool String::operator!=(const char *str_) const
{
    return !IsSameStr(this->CStr(), str_);
}

bool operator!=(const char *lhs, const String& rhs)
{
    return !IsSameStr(lhs, rhs.CStr());
}

/*****************************************************************************/

bool String::operator>(const String& str_) const
{
    return IsBiggerStr(this->CStr(), str_.CStr());
}

bool String::operator>(const char *str_) const
{
    return IsBiggerStr(this->CStr(), str_);
}

bool operator>(const char *lhs, const String& rhs)
{
    return IsBiggerStr(lhs, rhs.CStr());
}

/*****************************************************************************/

bool String::operator<(const String& str_) const
{
    return IsSmallerStr(this->CStr(), str_.CStr());
}

bool String::operator<(const char *str_) const
{
    return IsSmallerStr(this->CStr(), str_);
}

bool operator<(const char *lhs, const String& rhs)
{
    return IsSmallerStr(lhs, rhs.CStr());
}

/*****************************************************************************/

bool String::operator>=(const String& str_) const
{
    return !IsSmallerStr(this->CStr(), str_.CStr());
}

bool String::operator>=(const char *str_) const
{
    return !IsSmallerStr(this->CStr(), str_);
}

bool operator>=(const char *lhs, const String& rhs)
{
    return !IsSmallerStr(lhs, rhs.CStr());
}

/*****************************************************************************/

bool String::operator<=(const String& str_) const
{
    return !IsBiggerStr(this->CStr(), str_.CStr());
}

bool String::operator<=(const char *str_) const
{
    return !IsBiggerStr(this->CStr(), str_);
}

bool operator<=(const char *lhs, const String& rhs)
{
    return !IsBiggerStr(lhs, rhs.CStr());
}

/*****************************************************************************/

