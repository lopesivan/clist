/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool sort_test();
static bool sort_test_internal();

bool sort_test()
{
  std::cout << "========== CList Sort Functions Test ==========\n";

  bool result = sort_test_internal();

  if (result)
  std::cout << "PASS CList Sort Functions ==========\n";

  else
  std::cout << "FAIL CList Sort Functions ==========\n";

  return result;
}

bool sort_test_internal()
{
  return true;
}
