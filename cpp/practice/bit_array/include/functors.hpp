/*****************************************************************************
Title: functors - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: functors
******************************************************************************/

class SetBitsInWord
{
public:
    SetBitsInWord(bool value) 
        : m_value(value) 
    {}
    void operator()(std::size_t &ba)
    {
        ba = (0 == m_value) ? 0 : ~0;
    }
private:
    bool m_value;
};

/*******************************/

class FlipBitsInWord
{
public:
    void operator()(std::size_t &ba)
    {
        ba = ~ba;
    }
};

/*******************************/

class CountBitsInByte
{
public:
    CountBitsInByte(std::size_t &count)
        : m_count(count)
    {}
    void operator()(const char &byte)
    {
        m_count += g_lut_set_bits[byte & 0xff];
    }
private:
    std::size_t &m_count;
};

class CountBitsInWord
{
public:
    CountBitsInWord(std::size_t &count) 
        : m_functor(count)
    {}
    void operator()(const std::size_t &word)
    {
        char buff[g_bytes_in_word];
        std::memcpy(buff, &word, g_bytes_in_word);
        std::for_each(buff, buff + g_bytes_in_word, m_functor);
    }
private:
    CountBitsInByte m_functor;
};

/*******************************/

template<std::size_t N>
class BitToString
{
public:
    BitToString(const BitArray<N>& ba) 
        : m_ba(ba), m_index(0) 
    {}
    void operator()(char &curr)
    {
        curr = m_ba[m_index] + 48;
        ++m_index;
    }
private:
    const BitArray<N>& m_ba;
    size_t m_index;
};

/*****************************************************************************/
