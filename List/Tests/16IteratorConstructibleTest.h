#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"
#include <vector>

namespace test
{
  struct IteratorConstructibleTest
  {
    IteratorConstructibleTest()
    {
      std::vector<int> vec{9, 5, 1, 4, 3, 2};
  	  List<int> lst1(vec.begin(), vec.end());

      auto vec_it = vec.cbegin();
      auto lst1_it = lst1.cbegin(); // cbegin() returns a constant iterator to the beginning.

      while(vec_it != vec.cend() && lst1_it != lst1.cend())
        assertEqual(*(vec_it++), *(lst1_it++), __LINE__, __FILE__);

      assertBool(vec_it == vec.end(), __LINE__, __FILE__);
      assertBool(lst1_it == lst1.end(), __LINE__, __FILE__);

      auto container = {8, 8, 0, 0, 5, 5, 5, 3, 5, 3, 5};
      List<int> lst2(container.begin(), container.end());

      auto container_it = container.begin();
      auto lst2_it = lst2.cbegin();

      while(container_it != container.end() && lst2_it != lst2.cend())
        assertEqual(*(container_it++), *(lst2_it++), __LINE__, __FILE__);

      assertBool(container_it == container.end(), __LINE__, __FILE__);
      assertBool(lst2_it == lst2.end(), __LINE__, __FILE__);
    }
  };
  
  static IteratorConstructibleTest iteratorConstructibleTest;
}