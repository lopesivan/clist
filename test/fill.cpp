/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool fill_test();

static bool fill_test_internal();

bool fill_test()
{
  std::cout << "========== CList Fill Functions Test ==========\n";

  bool result = fill_test_internal();

  if (result)
  std::cout << "PASS CList Fill Functions ==========\n";

  else
  std::cout << "FAIL CList Fill Functions ==========\n";

  return result;
}

int simple_convert(int vVal) { return (vVal + 5) % 10; }

bool fill_test_internal()
{
  data::clist <unsigned int> TEST1, TEST2(10);
  int TEST_RAW[10];


  //copy from-------------------------------------------------------------------

  std::cout << "copy_from 1...\n"; std::cout.flush();

  data::clist_sequence(TEST2);
  TEST2.set_max_size(0);
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();

  TEST1.copy_from(TEST2);
  if (TEST1 != TEST2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "copy_from 1 range...\n"; std::cout.flush();

  TEST1.reset_list();

  TEST1.copy_from(TEST2, 5, 5);
  if (TEST1 != (TEST2 << 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "copy_from 2...\n"; std::cout.flush();

  TEST1.reset_list();
  for (int I = 0; I < 10; I++) TEST_RAW[I] = TEST2[I];

  TEST1.copy_from(TEST_RAW, 10);
  if (TEST1 != TEST2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "f_copy_from 1...\n"; std::cout.flush();

  TEST1.reset_list();

  TEST1.f_copy_from(TEST2, &simple_convert);
  if (TEST1 != data::clist_inverted_shift(TEST2, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  std::cout << "f_copy_from 1 range...\n"; std::cout.flush();

  TEST1.reset_list();

  TEST1.f_copy_from(TEST2, &simple_convert, 5, 5);
  if (TEST1 != data::clist_inverted_shift(TEST2 << 5, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "f_copy_from 2...\n"; std::cout.flush();

  TEST1.reset_list();
  for (int I = 0; I < 10; I++) TEST_RAW[I] = TEST2[I];

  TEST1.f_copy_from(TEST_RAW, 10, &simple_convert);
  if (TEST1 != data::clist_inverted_shift(TEST2, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1.max_size() != 10) return false; std::cout << "[2 pass]\n"; std::cout.flush();

  //END copy from---------------------------------------------------------------


  //add element-----------------------------------------------------------------

  std::cout << "add_element 1...\n"; std::cout.flush();

  TEST1.reset_list(0);
  TEST2.reset_list(10);

  for (int I = 0; I < 10; I++)
  {
  if (!TEST1.add_element(I)) return false;
  if (!TEST2.add_element(I)) return false;
  }

  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1 != TEST2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (!TEST1.add_element(0)) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST2.add_element(0))  return false; std::cout << "[3 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();


  std::cout << "add_element 2...\n"; std::cout.flush();

  TEST1.reset_list(0);
  TEST2.reset_list(10);

  for (int I = 0; I < 10; I++)
  {
  TEST1.add_element() = I;
  TEST2.add_element() = I;
  }

  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1 != TEST2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  TEST1.add_element() = 0;
  TEST2.add_element() = 0;
  if (TEST1 == TEST2) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();


  std::cout << "add_element 3...\n"; std::cout.flush();

  if (!TEST1.add_element(TEST2)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.add_element(TEST1))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 21) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "add_element 3 range...\n"; std::cout.flush();

  if (!TEST1.add_element(TEST2, 5, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.add_element(TEST1, 5, 5))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 31) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "add_element 4...\n"; std::cout.flush();

  TEST1 = TEST2;
  TEST1.set_max_size(0);
  for (int I = 0; I < 10; I++) TEST_RAW[I] = TEST2[I];

  if (!TEST1.add_element(TEST_RAW, 10)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.add_element(TEST_RAW, 10))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1 != (TEST2 + TEST2)) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST1.size() != 20) return false; std::cout << "[4 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[5 pass]\n"; std::cout.flush();


  std::cout << "add_element 5...\n"; std::cout.flush();

  if (!TEST1.add_element(TEST_RAW, TEST_RAW + 10)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.add_element(TEST_RAW, TEST_RAW + 10))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1 != (TEST2 + TEST2 + TEST2)) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST1.size() != 30) return false; std::cout << "[4 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[5 pass]\n"; std::cout.flush();


  std::cout << "f_add_element 1...\n"; std::cout.flush();

  TEST1 = TEST2;
  TEST1.set_max_size(0);

  if (!TEST1.f_add_element(TEST2, &simple_convert)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_add_element(TEST1, &simple_convert))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 20) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_add_element 1 range...\n"; std::cout.flush();

  if (!TEST1.f_add_element(TEST2, &simple_convert, 5, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_add_element(TEST1, &simple_convert, 5, 5))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 30) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_add_element 2...\n"; std::cout.flush();

  TEST1 = TEST2;
  TEST1.set_max_size(0);
  for (int I = 0; I < 10; I++) TEST_RAW[I] = TEST2[I];

  if (!TEST1.f_add_element(TEST_RAW, 10, &simple_convert)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_add_element(TEST_RAW, 10, &simple_convert))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 20) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_add_element 3...\n"; std::cout.flush();

  if (!TEST1.f_add_element(TEST_RAW, TEST_RAW + 10, &simple_convert)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_add_element(TEST_RAW, TEST_RAW + 10, &simple_convert))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 30) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();

  //END add element-------------------------------------------------------------


  //insert element--------------------------------------------------------------

  std::cout << "insert_element 1...\n"; std::cout.flush();

  TEST1.reset_list(0);
  TEST2.reset_list(10);

  for (int I = 0; I < 10; I++)
  {
  if (!TEST1.insert_element(data::first, I)) return false;
  if (!TEST2.insert_element(data::first, I)) return false;
  }

  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1 != TEST2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (!TEST1.insert_element(data::first, 0)) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (TEST2.insert_element(data::first, 0))  return false; std::cout << "[3 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();


  std::cout << "insert_element 2...\n"; std::cout.flush();

  TEST1.reset_list(0);
  TEST2.reset_list(10);

  for (int I = 0; I < 10; I++)
  {
  TEST1.insert_element(data::first) = I;
  TEST2.insert_element(data::first) = I;
  }

  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  if (TEST1 != TEST2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  TEST1.insert_element(data::first) = 0;
  TEST2.insert_element(data::first) = 0;
  if (TEST1 == TEST2) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();


  std::cout << "insert_element 3...\n"; std::cout.flush();

  if (!TEST1.insert_element(5, TEST2)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.insert_element(5, TEST1))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 21) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "insert_element 3 range...\n"; std::cout.flush();

  if (!TEST1.insert_element(5, TEST2, 5, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.insert_element(5, TEST1, 5, 5))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 31) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "insert_element 4...\n"; std::cout.flush();

  TEST1 = TEST2;
  TEST1.set_max_size(0);
  for (int I = 0; I < 10; I++) TEST_RAW[I] = TEST2[I];

  if (!TEST1.insert_element(5, TEST_RAW, 10)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.insert_element(5, TEST_RAW, 10))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 20) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "insert_element 5...\n"; std::cout.flush();

  if (!TEST1.insert_element(5, TEST_RAW, TEST_RAW + 10)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.insert_element(5, TEST_RAW, TEST_RAW + 10))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 30) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_insert_element 1...\n"; std::cout.flush();

  TEST1 = TEST2;
  TEST1.set_max_size(0);

  if (!TEST1.f_insert_element(5, TEST2, &simple_convert)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_insert_element(5, TEST1, &simple_convert))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 20) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_insert_element 1 range...\n"; std::cout.flush();

  if (!TEST1.f_insert_element(5, TEST2, &simple_convert, 5, 5)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_insert_element(5, TEST1, &simple_convert, 5, 5))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 30) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_insert_element 2...\n"; std::cout.flush();

  TEST1 = TEST2;
  TEST1.set_max_size(0);
  for (int I = 0; I < 10; I++) TEST_RAW[I] = TEST2[I];

  if (!TEST1.f_insert_element(5, TEST_RAW, 10, &simple_convert)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_insert_element(5, TEST_RAW, 10, &simple_convert))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 20) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();


  std::cout << "f_insert_element 3...\n"; std::cout.flush();

  if (!TEST1.f_insert_element(5, TEST_RAW, TEST_RAW + 10, &simple_convert)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2.f_insert_element(5, TEST_RAW, TEST_RAW + 10, &simple_convert))  return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << "\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  if (TEST1.size() != 30) return false; std::cout << "[3 pass]\n"; std::cout.flush();
  if (TEST2.size() != 10) return false; std::cout << "[4 pass]\n"; std::cout.flush();

  //END insert element----------------------------------------------------------


  //out of place tests----------------------------------------------------------

  std::cout << "replace_element...\n"; std::cout.flush();

  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  TEST2.replace_element(15, 3);
  if (TEST2[5] != 3) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();


  std::cout << "switch_elements...\n"; std::cout.flush();

  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();
  TEST2.switch_elements(13, 7);
  if (TEST2[3] != 2) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST2[7] != 6) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();


  std::cout << "clear_all...\n"; std::cout.flush();

  TEST2.clear_all();
  if (data::clist_sigma(TEST2) != 0) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1 = data::clist_delta(TEST2)) != 0) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  std::cout << "data: " << TEST2 << "\n"; std::cout.flush();

  //END out of place tests------------------------------------------------------

  return true;
}
