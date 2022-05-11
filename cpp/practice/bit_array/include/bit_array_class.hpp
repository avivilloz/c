/*****************************************************************************
Title: bit_array - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: bit_array
******************************************************************************/

#include "bit_class.hpp"
#include "functors.hpp"

template<std::size_t N>
BitArray<N>::BitArray()
{
    std::memset(m_ba, 0, GetBytesInArray(N));
}

template<std::size_t N>
class BitArray<N>::Bit BitArray<N>::operator[](std::size_t position)
{
    if (position >= N)
    {
        throw std::out_of_range("out of range");
    }

    return Bit(m_ba[GetArrayIndex(position)], GetBitPosition(position));
}

template<std::size_t N>
bool BitArray<N>::operator[](std::size_t position) const
{
    if (position >= N)
    {
        throw std::out_of_range("out of range");
    }

    return Bit(const_cast<std::size_t&>(m_ba[GetArrayIndex(position)]),
               GetBitPosition(position));
}

template<std::size_t N>
BitArray<N>& BitArray<N>::operator|=(const BitArray<N>& other_)
{
    std::transform(m_ba, m_ba + NUM_OF_WORDS(N), other_.m_ba, m_ba,
                   std::bit_or<std::size_t>()); 
    return *this;
}

template<std::size_t N>
BitArray<N>& BitArray<N>::operator&=(const BitArray<N>& other_)
{
    std::transform(m_ba, m_ba + NUM_OF_WORDS(N), other_.m_ba, m_ba,
                   std::bit_and<std::size_t>()); 
    return *this;
}

template<std::size_t N>
BitArray<N>& BitArray<N>::operator^=(const BitArray<N>& other_)
{
    std::transform(m_ba, m_ba + NUM_OF_WORDS(N), other_.m_ba, m_ba,
                   std::bit_xor<std::size_t>()); 
    return *this;
}

template<std::size_t N>
void BitArray<N>::Flip(std::size_t position)
{
    if (position >= N)
    {
        throw std::out_of_range("out of range");
    }

    FlipBit(m_ba[GetArrayIndex(position)], GetBitPosition(position));
}

template<std::size_t N>
void BitArray<N>::SetAll(bool value)
{
    std::for_each(m_ba, m_ba + NUM_OF_WORDS(N), SetBitsInWord(value));
    ShiftLastWord(m_ba + NUM_OF_WORDS(N) - 1, N);
}

template<std::size_t N>
void BitArray<N>::FlipAll()
{
    std::for_each(m_ba, m_ba + NUM_OF_WORDS(N), FlipBitsInWord());
    ShiftLastWord(m_ba + NUM_OF_WORDS(N) - 1, N);
}

template<std::size_t N>
std::size_t BitArray<N>::CountSetBits() const
{
    std::size_t count = 0;
    std::for_each(m_ba, m_ba + NUM_OF_WORDS(N), CountBitsInWord(count));
    return count;
}

template<std::size_t N>
std::string BitArray<N>::ToString() const
{
    char buff[N + 1];
    std::for_each(buff, buff + N, BitToString<N>(*this));
    buff[N] = '\0';
    return buff;
}

/*****************************************************************************/
// boolian operators
template<std::size_t M>
bool operator==(const BitArray<M>& lhs, const BitArray<M>& rhs)
{
    return (0 == std::memcmp(lhs.m_ba, rhs.m_ba, NUM_OF_WORDS(M)));
}

template<std::size_t M>
bool operator!=(const BitArray<M>& lhs, const BitArray<M>& rhs)
{
    return (0 != std::memcmp(lhs.m_ba, rhs.m_ba, NUM_OF_WORDS(M)));
}

/*****************************************************************************/
// helper functions
template<std::size_t N>
std::size_t BitArray<N>::GetBytesInArray(std::size_t num_of_bits) const
{
    return (NUM_OF_WORDS(num_of_bits) * g_bytes_in_word);
}

template<std::size_t N>
std::size_t BitArray<N>::GetArrayIndex(std::size_t position) const
{
    return (position / g_bits_in_word);
}

template<std::size_t N>
std::size_t BitArray<N>::GetBitPosition(std::size_t position) const
{
    return (position % g_bits_in_word);
}

template<std::size_t N>
std::size_t BitArray<N>::GetLastWordOffset(std::size_t num_of_bits) const
{
    return (g_bits_in_word - (GetBitPosition(num_of_bits) % g_bits_in_word));
}

template<std::size_t N>
void BitArray<N>::FlipBit(std::size_t &ba, std::size_t position)
{
    ba ^= (1ul << position); 
}

template<std::size_t N>
void BitArray<N>::ShiftLastWord(std::size_t *end, std::size_t num_of_bits)
{
    std::size_t offset = GetLastWordOffset(num_of_bits);
    *end = (*end << offset) >> offset;
}

/*****************************************************************************/
