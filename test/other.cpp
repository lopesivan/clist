/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool other_test();

static bool other_test_internal();

bool other_test()
{
  std::cout << "========== CList Other Functions Test ==========\n";

  bool result = other_test_internal();

  if (result)
  std::cout << "PASS CList Other Functions ==========\n";

  else
  std::cout << "FAIL CList Other Functions ==========\n";

  return result;
}

bool other_test_internal()
{
  return true;
}
