/*****************************************************************************
Title: rc_string - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: 
Description: rc_string API
******************************************************************************/

#define ASSERT_CHAR_SIZE_1(condition) enum {x = (1/(condition))}

#include <cstdlib> // exit
#include <cstring> // strlen, memcpy, strcmp

#include "rc_string.hpp" // api 

/*****************************************************************************/

namespace ilrd
{

struct StrObject
{
    size_t m_ref_count;
    char m_string[1];
};

static StrObject *Create(const char *src);
static StrObject *Copy(StrObject *str);
static void Delete(StrObject*& str);

RCString::RCString(const char *p_)
    : m_s(Create(p_))
{} 

RCString::RCString(const RCString& str_)
    : m_s(Copy(str_.m_s))
{}

RCString::~RCString()
{
    Delete(m_s);
}

RCString& RCString::operator=(const RCString& str_)
{
    if (this == &str_)
    {
        return *this;
    }

    Delete(m_s);
    m_s = Copy(str_.m_s);

    return *this;
}

const char& RCString::operator[](size_t index) const
{
    return m_s->m_string[index];
}

char& RCString::operator[](size_t index)
{
    if (1 == m_s->m_ref_count)
    {
        return m_s->m_string[index];
    }

    --m_s->m_ref_count;
    m_s = Create(m_s->m_string);

    return m_s->m_string[index];
}

const char *RCString::GetStr() const
{
    return m_s->m_string;
}

std::ostream& operator<<(std::ostream& os_, const RCString& str_)
{
    return os_ << str_.GetStr();
}

bool operator==(const RCString& str1_, const RCString& str2_)
{
    return (0 == strcmp(str1_.GetStr(), str2_.GetStr()));
}

bool operator>(const RCString& str1_, const RCString& str2_)
{
    return (0 < strcmp(str1_.GetStr(), str2_.GetStr()));
}

bool operator<(const RCString& str1_, const RCString& str2_)
{
    return (0 > strcmp(str1_.GetStr(), str2_.GetStr()));
}

static StrObject *Create(const char *src)
{
    size_t offset = offsetof(StrObject, m_string);
    size_t size = strlen(src) + 1;

    StrObject *dest;
    try
    {
        dest = static_cast<StrObject*>(operator new(offset + size));
    }
    catch(std::bad_alloc&)
    {
        std::cerr << "not enough memory"; 
        exit(1);
    }

    memcpy(dest->m_string, src, size);

    dest->m_ref_count = 1;

    return dest;
}

static void Delete(StrObject*& str)
{
    --str->m_ref_count;
    if (0 == str->m_ref_count)
    {
        operator delete(str);
    }
}

static StrObject *Copy(StrObject *str)
{
    ++str->m_ref_count;
    return str;
}

}

/*****************************************************************************/
