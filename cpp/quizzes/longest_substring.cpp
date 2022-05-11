/*****************************************************************************
Title: longest_substring 
Description: learn longest_substring
******************************************************************************/

#include <iostream> // cout

using namespace std;

/*****************************************************************************/

std::size_t LongestSubstring(std::string s1, std::string s2)
{
    std::size_t s1Len = s1.length();
    std::size_t s2Len = s2.length();
    std::size_t count = 0;

    for (std::size_t i = 0; i < s1Len; ++i)
    {
        std::size_t currCount = 0;
        std::size_t k = i;
        for (std::size_t j = 0; j < s2Len; ++j)
        {
            if (s1[k] == s2[j])
            {
                ++currCount;
                ++k;
            }
            else
            {
                currCount = 0;
                k = i;
            }

            if (currCount > count)
            {
                count = currCount;
            }
        }
    }

    return count;
}

int main()
{
    std::cout << LongestSubstring(std::string("infinityLabs"), std::string("infinity")) << std::endl;

    return 0;
}

/*****************************************************************************/

