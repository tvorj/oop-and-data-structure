#pragma once
#include "../HeapFunctions.h"
#include "Fixtures/CustomAsserts.h"
#include "Fixtures/CheckHeap.h"
#include <vector>
#include <cmath>

namespace test
{
  struct ComparisoncomparisonsTest
  {
    ComparisoncomparisonsTest()
    {
      static constexpr auto c_numberOfIterations = 1000000;
      static const std::size_t c_logNumberOfIterations = std::log(c_numberOfIterations) / std::log(2) + 1;
      std::size_t comparisons = 0;
      auto isGreater = [&comparisons](int a, int b)
      {++comparisons; return a > b; };

      std::vector<int> vectorHeap;
      for (std::size_t i = c_numberOfIterations; i > 0; --i)
      {
        vectorHeap.push_back(i);
        pushHeap(vectorHeap.begin(), vectorHeap.end(), isGreater);
      }
      assertLess(comparisons, c_numberOfIterations * c_logNumberOfIterations, __LINE__, __FILE__);

      for (std::size_t i = 0; i < c_numberOfIterations; ++i)
        vectorHeap[i] = c_numberOfIterations - i;
      // seg fault
      comparisons = 0;
      makeHeap(vectorHeap.begin(), vectorHeap.end(), isGreater);
      assertLess(comparisons, 3 * c_numberOfIterations, __LINE__, __FILE__);
      // seg fault
      comparisons = 0;
      for (std::size_t i = 0; i < c_numberOfIterations; ++i)
      {
        popHeap(vectorHeap.begin(), vectorHeap.end(), isGreater);
        vectorHeap.pop_back();
      }

      assertLess(comparisons, 2 * c_numberOfIterations * c_logNumberOfIterations, __LINE__, __FILE__);
    }
  };

  static ComparisoncomparisonsTest comparisoncomparisonsTest;
}
