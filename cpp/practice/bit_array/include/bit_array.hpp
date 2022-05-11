/*****************************************************************************
Title: bit_array - Infinity Labs R&D 
Group: OL91
Description: bit_array API
******************************************************************************/

#ifndef ILRD_OL91_BIT_ARRAY_HPP
#define ILRD_OL91_BIT_ARRAY_HPP

#include <cstddef>
#include <climits> 
#include <string>
#include <cstring>
#include <algorithm>

namespace ilrd
{
#include "globals.hpp"

template<std::size_t N>  
class BitArray
{
public:
    BitArray();

    class Bit;
    Bit operator[](std::size_t position);
    bool operator[](std::size_t position) const;

    BitArray& operator|=(const BitArray& other_);
    BitArray& operator&=(const BitArray& other_);
    BitArray& operator^=(const BitArray& other_);

    BitArray& operator<<=(std::size_t position);
    BitArray& operator>>=(std::size_t position);

    void SetAll(bool value);
    void FlipAll();
    void Flip(std::size_t position);
    std::size_t CountSetBits() const;
    std::string ToString() const;

    template<std::size_t M>
    friend bool operator==(const BitArray<M>& lhs, const BitArray<M>& rhs);
    template<std::size_t M>
    friend bool operator!=(const BitArray<M>& lhs, const BitArray<M>& rhs);
private:
    std::size_t m_ba[NUM_OF_WORDS(N)];

    std::size_t GetBytesInArray(std::size_t num_of_bits) const;
    std::size_t GetArrayIndex(std::size_t position) const;
    std::size_t GetBitPosition(std::size_t position) const;
    std::size_t GetLastWordOffset(std::size_t num_of_bits) const;
    void FlipBit(std::size_t &ba, std::size_t position);
    void ShiftLastWord(std::size_t *end, std::size_t num_of_bits);
};

template<std::size_t N>
class BitArray<N>::Bit
{
public:
    Bit(std::size_t &ba, std::size_t index);
    Bit& operator=(bool value);
    Bit& operator=(const Bit& other_);
    operator bool() const;
private:
    std::size_t &m_ba;
    std::size_t m_index;

    void SetBit(std::size_t &ba, std::size_t position);
    void ClearBit(std::size_t &ba, std::size_t position);
    bool GetBit(std::size_t &ba, std::size_t position) const;
};

template<std::size_t M>
bool operator==(const BitArray<M>& lhs, const BitArray<M>& rhs);
template<std::size_t M>
bool operator!=(const BitArray<M>& lhs, const BitArray<M>& rhs);

#include "bit_array_class.hpp"

} // end of namespace ilrd

#endif // ILRD_OL91_BIT_ARRAY_HPP

/*****************************************************************************/
