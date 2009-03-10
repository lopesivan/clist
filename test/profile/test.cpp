/*============================================================================*\
 *'CList' profiler program.                                                   *
 *Copyright (C) 2008 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <cstdlib>

#ifdef USER_TYPE

  #ifdef USER_FILE
  #include USER_FILE
  #endif

typedef USER_TYPE Type;

#else

const unsigned int HUGE_SIZE = T_SIZE;

struct huge
{
  huge()
  {
  for (int I = 0; I < HUGE_SIZE; I++)
  internal[I] = rand();
  }

  huge &operator = (const huge &eEqual)
  {
  for (int I = 0; I < HUGE_SIZE; I++)
  internal[I] = eEqual.internal[I];
  return *this;
  }

  bool operator < (const huge &eEqual) const
  {
  for (int I = 0; I < HUGE_SIZE; I++)
  if (eEqual.internal[I] < internal[I]) return false;
  return false;
  }

  char internal[HUGE_SIZE];
};

typedef huge Type;

#endif


#if T_TYPE == 0
  #include "0.12.5/CList.h"
  typedef BC::CList <Type> LIST;
  #define FILL Add
  #define SORT Sort
  #define VERIFY Verify
  #define SORT_TYPE "CList 0.12.5"


#elif T_TYPE == 1
  #include FILE_NAME1
  typedef data::clist <Type> LIST;
  #define FILL add_element
  #define SORT sort
  #define VERIFY verify_order
  #define SORT_TYPE "CList CURRENT / default VAS"

#elif T_TYPE == 2
  #include FILE_NAME1
  DISABLE_VIRT_ARRAY(Type)
  typedef data::clist <Type> LIST;
  #define FILL add_element
  #define SORT sort
  #define VERIFY verify_order
  #define SORT_TYPE "CList CURRENT / disable VAS"

#elif T_TYPE == 3
  #include FILE_NAME1
  ENABLE_VIRT_ARRAY(Type)
  typedef data::clist <Type> LIST;
  #define FILL add_element
  #define SORT sort
  #define VERIFY verify_order
  #define SORT_TYPE "CList CURRENT / enable VAS"


#elif (T_TYPE == -1) || (T_TYPE == -2)
  #include <vector>
  #include <algorithm>

  template <class Type>
  struct list_shell
  {
    unsigned int limit;
    std::vector <Type> internal;

    list_shell(unsigned int lLimit) : limit(lLimit) {}

    bool add(const Type &aAdd)
    {
    if (!limit) return false;
    limit--;
    internal.push_back(aAdd);
    return true;
    }

    inline void sort()
  #if T_TYPE == -1
    #define SORT_TYPE "std::sort"
    { std::sort(internal.begin(), internal.end()); }
  #elif  T_TYPE == -2
    #define SORT_TYPE "std::stable_sort"
    { std::stable_sort(internal.begin(), internal.end()); }
  #endif

    bool verify() const
    {
    for (int I = 0; I < internal.size() - 1; I++)
    if (internal[I + 1] < internal[I]) return false;
    return true;
    }
  };

  typedef list_shell <Type> LIST;
  #define FILL add
  #define SORT sort
  #define VERIFY verify

#endif

int main()
{
#ifdef FILL

  srand(time(NULL));

  const unsigned int NUMBER = T_FACTOR * 1024 * 1024;

  LIST TEST(NUMBER);

#ifdef USER_TYPE
  while (TEST.FILL(rand()));
#else
  while (TEST.FILL(Type()));
#endif


  std::cout << "--press enter to start [type: " << SORT_TYPE << "]--\n"; std::cin.get();
  clock_t T1 = clock();
  TEST.SORT();
  clock_t T2 = clock();
  if (!TEST.VERIFY()) std::cout << "FAILED!\n";


  std::cout << ((double) (T2 - T1) / CLOCKS_PER_SEC) << "s\n";

  return 0;

#endif

  return 1;
}
