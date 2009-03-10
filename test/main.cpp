/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool external_test();
extern bool fill_test();
extern bool find_test();
extern bool invert_test();
extern bool other_test();
extern bool remove_test();
extern bool retrieve_test();
extern bool shadow_test();
extern bool simple_test();
extern bool sort_test();

int main()
{
  std::cout << "BEGIN FULL TEST ++++++++++++++++++++\n";

  if (!simple_test())   return 1;
  if (!fill_test())     return 1;
  if (!retrieve_test()) return 1;
  if (!remove_test())   return 1;
//  if (!find_test())     return 1;
//  if (!sort_test())     return 1;
//  if (!invert_test())   return 1;
//  if (!shadow_test())   return 1;
//  if (!other_test())    return 1;
//  if (!external_test()) return 1;

  std::cout << "PASS FULL TEST ++++++++++++++++++++\n";

  return 0;
}
