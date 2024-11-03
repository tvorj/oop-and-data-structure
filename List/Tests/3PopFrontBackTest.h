#pragma once
#include "../List.h"
#include "Fixtures/CustomAsserts.h"

namespace test
{
  struct PopFrontBackTest
  {
    PopFrontBackTest()
    {
  	  List<int> lst(4, 42);
      for(std::size_t i = 1; i <= 5; ++i)
        lst.push_front(i);

      for(std::size_t i = 1; i <= 5; ++i)
        lst.push_back(i);

      for(std::size_t i = 5; i >= 1; --i)
      {
        assertEqual(lst.front(), i, __LINE__, __FILE__);
        lst.pop_front();
      }

      for(std::size_t i = 5; i >= 1; --i)
      {
        assertEqual(lst.back(), i, __LINE__, __FILE__);
        lst.pop_back();
      }
      
      for(std::size_t i = 0; i < 4; ++i)
      {
        assertEqual(lst.front(), 42, __LINE__, __FILE__);
        lst.pop_front();
      }
      
  	  assertBool(lst.empty(), __LINE__, __FILE__);
    }
  };
  
  static PopFrontBackTest PopFrontBackTest;
}