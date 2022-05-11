/*****************************************************************************
Title: bit - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: bit
******************************************************************************/

template<std::size_t N>
BitArray<N>::Bit::Bit(std::size_t &ba, std::size_t index)
    : m_ba(ba), m_index(index)
{}

template<std::size_t N>
class BitArray<N>::Bit& BitArray<N>::Bit::operator=(bool value)
{
    if (1 == value)
    {
        SetBit(m_ba, m_index);
    }
    else
    {
        ClearBit(m_ba, m_index);  
    }

    return *this;
}

template<std::size_t N>
class BitArray<N>::Bit& BitArray<N>::Bit::operator=(const Bit& other_)
{
    if (1 == GetBit(other_.m_ba, other_.m_index))
    {
        SetBit(m_ba, other_.m_index);
    }
    else
    {
        ClearBit(m_ba, other_.m_index);  
    }

    return *this;
}

template<std::size_t N>
BitArray<N>::Bit::operator bool() const
{
    return GetBit(m_ba, m_index);
}

/*****************************************************************************/
// helper functions
template<std::size_t N>
void BitArray<N>::Bit::SetBit(std::size_t &ba, std::size_t position)
{
    ba |= (1ul << position); 
}

template<std::size_t N>
void BitArray<N>::Bit::ClearBit(std::size_t &ba, std::size_t position)
{
    ba &= ~(1ul << position); 
}

template<std::size_t N>
bool BitArray<N>::Bit::GetBit(std::size_t &ba, std::size_t position) const
{
    return ((ba >> position) & 1ul);
}

/*****************************************************************************/

