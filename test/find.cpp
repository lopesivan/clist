/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool find_test();

static bool find_test_internal();

bool find_test()
{
  std::cout << "========== CList Find Functions Test ==========\n";

  bool result = find_test_internal();

  if (result)
  std::cout << "PASS CList Find Functions ==========\n";

  else
  std::cout << "FAIL CList Find Functions ==========\n";

  return result;
}

bool find_test_internal()
{
  return true;
}
