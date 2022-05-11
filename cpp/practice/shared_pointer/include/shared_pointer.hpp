/****************************************************************************
Title: Shared Pointer Infinity Labs R&D 
Group: RD91
Description: shared pointer API 
*****************************************************************************/

#ifndef CPP_SHARED_POINTER_INFINITY_RD_91
#define CPP_SHARED_POINTER_INFINITY_RD_91

#include <cstddef>

namespace ilrd
{

template <class T>
class SharedPointer
{
public:
    explicit SharedPointer(T *ptr_ = NULL)
        : m_ptr(ptr_), m_count(new std::size_t(1))
    {}

    ~SharedPointer()
    {
        --(*m_count);
        if (0 == *m_count)
        {
            delete m_ptr;
            m_ptr = NULL;
            delete m_count;
            m_count = NULL;
        }
    }

    SharedPointer(const SharedPointer& other_)
        : m_ptr(other_.m_ptr), m_count(other_.m_count)
    {
        ++(*m_count);
    }

    template <class U> 
    SharedPointer(const SharedPointer<U>& other_)
        : m_ptr(other_.m_ptr), m_count(other_.m_count)
    {
        ++(*m_count);
    }
    
    SharedPointer& operator=(const SharedPointer& other_)
    {
        return AssignPtr(other_);
    }

    template <class U> 
    SharedPointer& operator=(const SharedPointer<U>& other_)
    {
        return AssignPtr(other_);
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    T* Get() const
    {
        return m_ptr;
    }

    std::size_t Count() {return *m_count;} /* temporary */

private:
    T *m_ptr;
    std::size_t *m_count;

    template<class U>
    friend class SharedPointer;

    template<class V>
    SharedPointer& AssignPtr(const SharedPointer<V>& other_)
    {
        T *temp_ptr = other_.m_ptr;
        std::size_t *temp_count = other_.m_count;
        ++(*temp_count);

        --(*m_count);
        if (0 == *m_count)
        {
            delete m_ptr;
            delete m_count;
        }

        m_ptr = temp_ptr;
        m_count = temp_count;

        return *this;
    }
};

}

#endif // CPP_SHARED_POINTER_INFINITY_RD_91
