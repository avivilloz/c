/****************************************************************************
Title: Simple String - Infinity Labs R&D 
Group: Ol91
Description: Simple String API
*****************************************************************************/

#ifndef ILRD_OL91_SIMPLE_STRING_HPP
#define ILRD_OL91_SIMPLE_STRING_HPP

#include <iostream> // std::ostream

class String
{
public:
	String(const char *str_);
	String(const String& str_);
	String& operator=(const String& str_);
	~String();

	std::size_t Length() const;
	char *CStr() const;

    //operators for comparison between String and char *, starting from String
    bool operator==(const String& str_) const;
    bool operator==(const char *str_) const;

    bool operator!=(const String& str_) const;
    bool operator!=(const char *str_) const;

    bool operator>(const String& str_) const;
    bool operator>(const char *str_) const;

    bool operator<(const String& str_) const;
    bool operator<(const char *str_) const;

    bool operator>=(const String& str_) const;
    bool operator>=(const char *str_) const;

    bool operator<=(const String& str_) const;
    bool operator<=(const char *str_) const;

private:
	char *m_cstr;
};

std::ostream& operator<<(std::ostream& os_, const String& str_);

// operators for comparison between String and char *, starting from char*
bool operator==(const char *lhs, const String& rhs);
bool operator!=(const char *lhs, const String& rhs);
bool operator>(const char *lhs, const String& rhs);
bool operator<(const char *lhs, const String& rhs);
bool operator>=(const char *lhs, const String& rhs);
bool operator<=(const char *lhs, const String& rhs);

#endif // ILRD_OL91_SIMPLE_STRING_HPP
