#ifndef QSORT_HPP
#define QSORT_HPP

/// @brief Sorts the elements in the range [first, last) using an order determined by comparator.
/// @tparam RandomAccessIter Random access iterator
/// @tparam Comparator function or callable object that can be called with 2 argument(s) and a return value convertible to bool
/// @param first the iterator referencing the first element in the range (included) to be sorted
/// @param last the iterator referencing the last element in the range (excluded) to be sorted
/// @param comparator when called, returns truthy value if the first argument should be placed before the second and falsy value otherwise
template <typename RandomAccessIter, typename Comparator>
void quick_sort(RandomAccessIter first, RandomAccessIter last, Comparator comparator);

#endif
