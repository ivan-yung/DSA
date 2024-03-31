#ifndef QSORT_CPP
#define QSORT_CPP

#include <ctime>
#include <cstdlib>
#include "qsort.hpp"
#include "iostream"

template <typename RandomAccessIter, typename Comparator>
RandomAccessIter part(RandomAccessIter first, RandomAccessIter last, Comparator comparator)
{

    RandomAccessIter piv = last - 1;
    RandomAccessIter i = first - 1;
    for (RandomAccessIter j = first; j <= last - 1; ++j)
    {
        if (comparator(*j, *piv))
        {
            ++i;
            std::swap(*i, *j);
        }
    }
    std::swap(*(i + 1), *(last - 1));
    return i + 1;
}
template <typename RandomAccessIter, typename Comparator>
RandomAccessIter randpart(RandomAccessIter first, RandomAccessIter last, Comparator comparator)
{
    /*
    if (first == last){
        return last;
    }
    */
    int ipiv = std::rand() % std::distance(first, last);

    RandomAccessIter piv = first; //= first + std::rand() % (last - first);
    std::advance(piv, ipiv);
    if (first != last)
    {
        // std::swap(*(last - 1), *piv);
        std::swap(*piv, *(last - 1));
    }

    return part(first, last, comparator);
}

template <typename RandomAccessIter, typename Comparator>
void quick_sort(RandomAccessIter first, RandomAccessIter last, Comparator comparator)
{
    // Implement here
    // std::sort(first, last, comparator);
    // int size = std::distance(first, last);
    // std::cout << size << std::endl;
    /*
    if ((first == last) || (size == 1)){
        return;
    }*/
    if (first < last)
    {

        // srand(time(0));
        static bool seeded = false;
        if (!seeded)
        {
            std::srand(time(0));
            seeded = true;
        }
        RandomAccessIter piv = randpart(first, last, comparator);

        quick_sort(first, piv, comparator);
        quick_sort(piv + 1, last, comparator);
    }
}

#endif
