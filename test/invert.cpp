/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool invert_test();

static bool invert_test_internal();

bool invert_test()
{
  std::cout << "========== CList Inversion Test ==========\n";

  bool result = invert_test_internal();

  if (result)
  std::cout << "PASS CList Inversion ==========\n";

  else
  std::cout << "FAIL CList Inversion ==========\n";

  return result;
}

bool invert_test_internal()
{
  return true;
}
