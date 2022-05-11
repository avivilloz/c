/****************************************************************************
Title: RCString - Infinity Labs R&D 
Group: OL91
Description: RCString API
*****************************************************************************/

#ifndef ILRD_OL91_REFERENCE_COUNTING_STRING_HPP
#define ILRD_OL91_REFERENCE_COUNTING_STRING_HPP

#include <cstddef> //size_t
#include <iostream> //ostream

namespace ilrd
{
struct StrObject;
class RCString
{
public:
    RCString(const char *p_ = "");
    RCString(const RCString& str_);
    ~RCString();

    RCString& operator=(const RCString& str_);
    const char& operator[](size_t index) const;
    char& operator[](size_t index);

    const char *GetStr() const;

private:
    struct StrObject *m_s;
};

std::ostream& operator<<(std::ostream& os_, const RCString& str_);
bool operator==(const RCString& str1_, const RCString& str2_);
bool operator>(const RCString& str1_, const RCString& str2_);
bool operator<(const RCString& str1_, const RCString& str2_);
}

#endif //ILRD_OL91_REFERENCE_COUNTING_STRING_HPP
