/*****************************************************************************
Title: primorial 
Description: learn primorial
******************************************************************************/

#include <iostream> // cout
#include <map>

using namespace std;

/*****************************************************************************/

class Primorial
{
public:
    Primorial() : m_primes() {}
    unsigned long GetPrimorial(std::size_t n)
    {
        std::map<std::size_t, std::pair<unsigned int, unsigned long> >::iterator it;
        it = m_primes.find(n);
        if (it != m_primes.end())
        {
            return it->second.second;
        }

        std::size_t i = n;
        for (; i > 0; --i)
        {
            it = m_primes.find(i);
            if (it != m_primes.end())
            {
                break;
            }
        }

        unsigned int j = 2;

        if (i)
        {
            j = it->second.first + 1;
        }
        else
        {
            m_primes[++i] = std::make_pair(j, j);
            it = m_primes.find(i);
            ++j;
        }

        while (i < n)
        {
            if (IsPrime(j))
            {
                m_primes[++i] = std::make_pair(j, it->second.second * j);
                it = m_primes.find(i);
            }

            ++j;
        }

        return it->second.second;
    }

private:
    std::map<std::size_t, std::pair<unsigned int, unsigned long> > m_primes;

    bool IsPrime(int num)
    {
         if (num <= 1) 
         {
             return 0;
         }

         if (num % 2 == 0 && num > 2) 
         {
             return 0;
         }

         for (int i = 3; i < num / 2; i+= 2)
         {
             if (num % i == 0)
             {
                 return 0;
             }
         }

         return 1;
    }
};

int main()
{
    Primorial p;

    cout << p.GetPrimorial(1) << endl;
    cout << p.GetPrimorial(3) << endl;
    cout << p.GetPrimorial(5) << endl;
    cout << p.GetPrimorial(8) << endl;
    cout << p.GetPrimorial(6) << endl;
    cout << p.GetPrimorial(7) << endl;

    return 0;
}

/*****************************************************************************/

