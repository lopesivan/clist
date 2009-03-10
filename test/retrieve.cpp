/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool retrieve_test();

static bool retrieve_test_internal();

bool retrieve_test()
{
  std::cout << "========== CList Data Retrieval Functions Test ==========\n";

  bool result = retrieve_test_internal();

  if (result)
  std::cout << "PASS CList Data Retrieval Functions ==========\n";

  else
  std::cout << "FAIL CList Data Retrieval Functions ==========\n";

  return result;
}

bool retrieve_test_internal()
{
  data::clist <const int> TEST1, TEST2(10);
  data::clist_sequence(TEST2);
  TEST1 = TEST2;
  int VALUE;


  //get element-----------------------------------------------------------------

  std::cout << "get_element 1...\n"; std::cout.flush();

  TEST1.get_element(13, VALUE);
  if (VALUE != 3) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  TEST1.get_element(-3, VALUE);
  if (VALUE != 7) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "get_element 2...\n"; std::cout.flush();

  if (TEST1.get_element(13) != 3) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST1.get_element(-3) != 7) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1).get_element(13) != 3) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1).get_element(-3) != 7) return false; std::cout << "[4 pass]\n"; std::cout.flush();
  if (TEST1[13] != 3) return false; std::cout << "[5 pass]\n"; std::cout.flush();
  if (TEST1[-3] != 7) return false; std::cout << "[6 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1)[13] != 3) return false; std::cout << "[7 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1)[-3] != 7) return false; std::cout << "[8 pass]\n"; std::cout.flush();


  std::cout << "h_get_element 1...\n"; std::cout.flush();

  TEST1.h_get_element(13, VALUE);
  if (VALUE != 3) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 3) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  TEST1.h_get_element(-5, VALUE);
  if (VALUE != 8) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 8) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "h_get_element 2...\n"; std::cout.flush();

  if (TEST1.h_get_element(15) != 3) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 3) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.h_get_element(-4) != 9) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 9) return false; std::cout << "[4 pass]\n"; std::cout.flush();

  //END get element-------------------------------------------------------------


  //first element---------------------------------------------------------------

  std::cout << "first_element 1...\n"; std::cout.flush();

  TEST1.first_element(VALUE);
  if (VALUE != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();


  std::cout << "first_element 2...\n"; std::cout.flush();

  if (TEST1.first_element() != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1).first_element() != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "h_first_element 1...\n"; std::cout.flush();

  TEST1.index = data::last;
  TEST1.h_first_element(VALUE);
  if (VALUE != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "h_first_element 2...\n"; std::cout.flush();

  TEST1.index = data::last;
  if (TEST1.h_first_element() != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  TEST1.index = data::last;

  //END first element-----------------------------------------------------------


  //last element----------------------------------------------------------------

  std::cout << "last_element 1...\n"; std::cout.flush();

  TEST1.last_element(VALUE);
  if (VALUE != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();


  std::cout << "last_element 2...\n"; std::cout.flush();

  if (TEST1.last_element() != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1).last_element() != 9) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "h_last_element 1...\n"; std::cout.flush();

  TEST1.index = data::first;
  TEST1.h_last_element(VALUE);
  if (VALUE != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 9) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "h_last_element 2...\n"; std::cout.flush();

  TEST1.index = data::first;
  if (TEST1.h_last_element() != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.index != 9) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  TEST1.index = data::first;

  //END last element------------------------------------------------------------


  //current element-------------------------------------------------------------

  std::cout << "current_element 1...\n"; std::cout.flush();

  TEST1.index = 8;

  TEST1.current_element(VALUE);
  if (VALUE != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();


  std::cout << "current_element 2...\n"; std::cout.flush();

  if (TEST1.current_element() != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (((const data::clist <const int>&) TEST1).current_element() != 8) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "operator *...\n"; std::cout.flush();

  if (*TEST1 != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (*((const data::clist <const int>&) TEST1) != 8) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  //END current element---------------------------------------------------------


  //next element----------------------------------------------------------------

  std::cout << "next_element 1...\n"; std::cout.flush();

  TEST1.next_element(VALUE);
  if (VALUE != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();


  std::cout << "next_element 2...\n"; std::cout.flush();

  if (TEST1.next_element() != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();

  //END next element------------------------------------------------------------


  //previous element------------------------------------------------------------

  std::cout << "previous_element 1...\n"; std::cout.flush();

  TEST1.previous_element(VALUE);
  if (VALUE != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();


  std::cout << "previous_element 2...\n"; std::cout.flush();

  if (TEST1.previous_element() != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();

  //END previous element--------------------------------------------------------


  //pull element----------------------------------------------------------------
  TEST1.index.set_to_begin();

  std::cout << "p_get_element 1...\n"; std::cout.flush();

  if (TEST1.p_get_element(4) != 4) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1[4] != 5) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 9) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  std::cout << "p_get_element 2...\n"; std::cout.flush();

  TEST1.p_get_element(4, VALUE);
  if (VALUE != 5) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1[4] != 6) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 8) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  TEST1 = TEST2;
  TEST1.index = rand();


  std::cout << "p_first_element 1...\n"; std::cout.flush();

  if (TEST1.p_first_element() != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.first_element() != 1) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 9) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  std::cout << "p_first_element 2...\n"; std::cout.flush();

  TEST1.p_first_element(VALUE);
  if (VALUE != 1) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.first_element() != 2) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 8) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  TEST1 = TEST2;
  TEST1.index = rand();


  std::cout << "p_last_element 1...\n"; std::cout.flush();

  if (TEST1.p_last_element() != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.last_element() != 8) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 9) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  std::cout << "p_last_element 2...\n"; std::cout.flush();

  TEST1.p_last_element(VALUE);
  if (VALUE != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.last_element() != 7) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 8) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  TEST1 = TEST2;
  TEST1.index = 8;


  std::cout << "p_current_element 1...\n"; std::cout.flush();

  if (TEST1.p_current_element() != 8) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.current_element() != 9) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 9) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  std::cout << "p_current_element 2...\n"; std::cout.flush();

  TEST1.p_current_element(VALUE);
  if (VALUE != 9) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.current_element() != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 8) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  TEST1 = TEST2;
  TEST1.index.set_to_begin();


  std::cout << "hp_get_element 1...\n"; std::cout.flush();

  if (TEST1.hp_get_element(6) != 6) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.current_element() != 7) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 9) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  std::cout << "hp_get_element 2...\n"; std::cout.flush();

  TEST1.index = data::first;
  TEST1.hp_get_element(6, VALUE);
  if (VALUE != 7) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.current_element() != 8) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST1.size() != 8) return false; std::cout << "[3 pass]\n"; std::cout.flush();

  //END pull element------------------------------------------------------------

  return true;
}
