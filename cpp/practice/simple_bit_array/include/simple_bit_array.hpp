/*****************************************************************************
Title: simple_bit_array - Infinity Labs R&D 
Group: OL91
Description: simple_bit_array API
******************************************************************************/

#ifndef ILRD_OL91_BIT_ARRAY_HPP
#define ILRD_OL91_BIT_ARRAY_HPP

#include <cstddef>
#include <cstring>

using namespace std;

/*****************************************************************************/

namespace ilrd
{
class Bit
{
public:
    Bit(size_t *ba, size_t index)
        : m_ba(ba), m_index(index)
    {}
    Bit& operator=(bool status)
    {
        if (true == status)
        {
            SetBit();
        }
        else
        {
            ClearBit();
        }

        return *this;
    }
    operator bool() const
    {
        return GetBit();
    }
private:
    size_t *m_ba;
    size_t m_index;

    bool GetBit() const
    {
        return (*m_ba >> m_index) & 1;
    }
    void SetBit()
    {
        *m_ba |= (1 << m_index);
    }
    void ClearBit()
    {
        *m_ba &= ~(1 << m_index);
    }
};

class BitArray
{
public:
    BitArray()
        : m_ba(0)
    {}
    BitArray(const BitArray& other)
        : m_ba(other.m_ba)
    {}
    BitArray& operator=(const BitArray& other)
    {
        m_ba = other.m_ba;
        return *this;
    }
    Bit operator[](size_t index)
    {
        return Bit(&m_ba, index);
    }

private:
    size_t m_ba;
};
}

/*****************************************************************************/

#endif // ILRD_OL91_BIT_ARRAY_HPP

