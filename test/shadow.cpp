/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool shadow_test();

static bool shadow_test_internal();

bool shadow_test()
{
  std::cout << "========== CList Shadow Test ==========\n";

  bool result = shadow_test_internal();

  if (result)
  std::cout << "PASS CList Shadow ==========\n";

  else
  std::cout << "FAIL CList Shadow ==========\n";

  return result;
}

bool shadow_test_internal()
{
  return true;
}
