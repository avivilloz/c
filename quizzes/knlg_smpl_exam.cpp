/*****************************************************************************
Title: know_smpl_exam 
Description: learn know_smpl_exam
******************************************************************************/

#include <iostream> // cout
#include <string.h>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

/*****************************************************************************/

class String
{
public:
    String(const char *s) : m_s(new char[strlen(s) + 1])
    {
        strcpy(m_s, s);
    }
    String(const String& other) : m_s()
    {
        CpyStr(other.m_s);
    }
    String& operator=(const String& other)
    {
        CpyStr(other.m_s);
        return *this;
    }
    ~String()
    {
        delete[] m_s;
        m_s = NULL;
    }   

    friend ostream& operator<<(ostream& out, const String& s);

private:
    char *m_s;

    void CpyStr(const char *s)
    {
        char *temp_s = new char[strlen(s) + 1];
        strcpy(temp_s, s);
        delete[] m_s;
        m_s = temp_s;
    }
};

ostream& operator<<(ostream& out, const String& s)
{
    return out << s.m_s;
}

template<class T>
class Singleton : boost::noncopyable
{
public:
    static T *GetInstance()
    {
        m_mutex.lock();
        if (!m_exists)
        {
            m_object = new T;
            m_exists = true;
        }
        m_mutex.unlock();

        return m_object;
    }

private:
    static T *m_object;
    static bool m_exists;
    static boost::mutex m_mutex;
};

template<class T>
T *Singleton<T>::m_object;
template<class T>
bool Singleton<T>::m_exists = 0;
template<class T>
boost::mutex Singleton<T>::m_mutex;

class A
{
};

int main()
{
    /* string */

    String s1("hey bro");
    String s2(s1);
    cout << s2 << endl;

    String s3("heeey");
    s2 = s3;
    cout << s2 << endl;

    /* singleton */

    A *a1 = Singleton<A>::GetInstance();
    A *a2 = Singleton<A>::GetInstance();

    cout << (a1 == a2) << endl;

    return 0;
}

/*****************************************************************************/

