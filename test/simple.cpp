/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool simple_test();
static bool simple_test_internal();

bool simple_test()
{
  std::cout << "========== CList Simple Functions Test ==========\n";

  bool result = simple_test_internal();

  if (result)
  std::cout << "PASS CList Simple Functions ==========\n";

  else
  std::cout << "FAIL CList Simple Functions ==========\n";

  return result;
}

bool simple_test_internal()
{
  data::clist <int> TEST1, TEST2(10);

  std::cout << "initial size...\n"; std::cout.flush();
  if (TEST1.size() != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.size() != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "initial section size...\n"; std::cout.flush();
  if (TEST1.section_size(0, 9) != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.section_size(0, 9) != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "initial decrement...\n"; std::cout.flush();
  if (TEST1.decrement_size()) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.decrement_size()) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  TEST1.resize(10);
  TEST2.resize(10);

  std::cout << "resize...\n"; std::cout.flush();
  if (TEST1.size() != 10) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "resize section size...\n"; std::cout.flush();
  if (TEST1.section_size(0, 10) != 10) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.section_size(0, 10) != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.section_size(5, 5) != 10) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.section_size(5, 5) != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();

  std::cout << "resize max size...\n"; std::cout.flush();
  if (TEST1.max_size() != 0)  return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "resize increment size...\n"; std::cout.flush();
  if (!TEST1.increment_size()) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.increment_size())  return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "set max size...\n"; std::cout.flush();
  if (TEST1.set_max_size(5) != 5) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.set_max_size(0) != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "set max size max size...\n"; std::cout.flush();
  if (TEST1.max_size() != 5) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.max_size() != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "set max size size...\n"; std::cout.flush();
  if (TEST1.size() != 5)  return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  TEST1.reset_list(0);
  TEST2.reset_list(10);

  std::cout << "reset size...\n"; std::cout.flush();
  if (TEST1.size() != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.size() != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "reset max size...\n"; std::cout.flush();
  if (TEST1.max_size() != 0)  return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  return true;
}
