#pragma once
#include <functional>
#include <algorithm>

namespace test
{
  template <typename ItType, typename Comparator = std::less<typename ItType::value_type>>
  bool isHeap(ItType start, ItType finish, Comparator compare = std::less<typename ItType::value_type>{})
  {
    auto heapSize = std::distance(start, finish);
    auto current = start;
    for(std::size_t i = 0; i < heapSize; ++i)
    {
      if(2*i + 1 >= heapSize)
        return true;
      auto leftChild = current;
      std::advance(leftChild, i+1);
      if(compare(*current, *leftChild))
        return false;

      if(2*i + 2 >= heapSize)
        return true;
      auto rightChild = current;
      std::advance(rightChild, i+2);
      if(compare(*current, *rightChild))
        return false;
    }
    return true;
  };
}