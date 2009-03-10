/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool external_test();

static bool external_test_internal();

bool external_test()
{
  std::cout << "========== CList External Functions Test ==========\n";

  bool result = external_test_internal();

  if (result)
  std::cout << "PASS CList External Functions ==========\n";

  else
  std::cout << "FAIL CList External Functions ==========\n";

  return result;
}

bool external_test_internal()
{
  return true;
}
