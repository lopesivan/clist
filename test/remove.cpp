/*============================================================================*\
 *'CList' test program.                                                       *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           *
 *Licensed under the GPL.                                                     *
\*============================================================================*/

#include <iostream>
#include <ta0kira/clist.hpp>

extern bool remove_test();

static bool remove_test_internal();

bool remove_test()
{
  std::cout << "========== CList Data Removal Functions Test ==========\n";

  bool result = remove_test_internal();

  if (result)
  std::cout << "PASS CList Data Removal Functions ==========\n";

  else
  std::cout << "FAIL CList Data Removal Functions ==========\n";

  return result;
}

bool alpha_check(int vVal1, char vVal2) { return vVal1 % 26 + 'a' == vVal2; }

bool three_multiple(int vVal1) { return !(vVal1 % 3); }

bool remove_test_internal()
{
  data::clist <int> TEST1, TEST2(30), VALUES1(10);
  data::clist_sequence(TEST2).random_order() %= 10;
  int VALUE, VALUES2[10];


  //remove----------------------------------------------------------------------

  std::cout << "remove_single...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.remove_single(56);
  if (TEST1.size() != 29) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST1[26] != TEST2[27]) return false; std::cout << "[2 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2) - TEST2[26]) return false; std::cout << "[3 pass]\n"; std::cout.flush();


  std::cout << "remove_list 1...\n"; std::cout.flush();

  TEST1 = TEST2;
  for (int I = 0; I < VALUES1.max_size(); I++) VALUES1.add_element(TEST2[TEST2[I]] + I * 3);

  (VALUES1 %= TEST1.size()).remove_duplicates() += 10;

  TEST1.remove_list(VALUES1);
  if (TEST1.size() != TEST2.size() - VALUES1.size()) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2) -
      data::f_clist_sigma(VALUES1, data::bind_convert_shadow(TEST2, VALUES1)))
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "remove_list 2...\n"; std::cout.flush();

  TEST1 = TEST2;
  for (int I = 0; I < VALUES1.size(); I++) VALUES2[I] = VALUES1[I];

  TEST1.remove_list(VALUES2, VALUES1.size());
  if (TEST1.size() != TEST2.size() - VALUES1.size()) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2) -
      data::f_clist_sigma(VALUES1, data::bind_convert_shadow(TEST2, VALUES1)))
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "remove_range...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.remove_range(25, 13);
  if (TEST1.size() != TEST2.size() - TEST2.section_size(25, 13)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2) - data::clist_sigma(TEST2, 25, 13))
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "remove_pattern...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.remove_pattern(5, 12, 8);
  VALUE = TEST2.count(5, 12, 8);
  std::cout << "data: " << TEST2 << " " << data::clist_sigma(TEST2) << "\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << " " << data::clist_sigma(TEST1) << "\n"; std::cout.flush();
  if (TEST1.size() != TEST2.size() - VALUE) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2) - 5 * VALUE)
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "f_remove_pattern...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.f_remove_pattern('c', &alpha_check, 12, 8);
  VALUE = TEST2.f_count('c', &alpha_check, 12, 8);
  std::cout << "data: " << TEST2 << " " << data::clist_sigma(TEST2) << "\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << " " << data::clist_sigma(TEST1) << "\n"; std::cout.flush();
  if (TEST1.size() != TEST2.size() - VALUE) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2) - 2 * VALUE)
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "fe_remove_pattern...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.fe_remove_pattern(&three_multiple, 12, 8);
  VALUE = TEST2.fe_count(&three_multiple, 12, 8);
  std::cout << "data: " << TEST2 << " " << data::clist_sigma(TEST2) << "\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << " " << data::clist_sigma(TEST1) << "\n"; std::cout.flush();
  if (TEST1.size() != TEST2.size() - VALUE) return false; std::cout << "[1 pass]\n"; std::cout.flush();

  //END remove------------------------------------------------------------------


  //keep------------------------------------------------------------------------

  TEST2.random_order();

  std::cout << "keep_single...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.keep_single(56);
  if (TEST1.size() != 1) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (TEST1[0] != TEST2[26]) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "keep_list 1...\n"; std::cout.flush();

  TEST1 = TEST2;
  for (int I = 0; I < VALUES1.max_size(); I++) VALUES1.add_element(TEST2[TEST2[I]] + I * 3);

  (VALUES1 %= 30).remove_duplicates() += 10;

  TEST1.keep_list(VALUES1);
  if (TEST1.size() != VALUES1.size()) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::f_clist_sigma(VALUES1, data::bind_convert_shadow(TEST2, VALUES1)))
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "keep_list 2...\n"; std::cout.flush();

  TEST1 = TEST2;
  for (int I = 0; I < VALUES1.size(); I++) VALUES2[I] = VALUES1[I];

  TEST1.keep_list(VALUES2, VALUES1.size());
  if (TEST1.size() != VALUES1.size()) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::f_clist_sigma(VALUES1, data::bind_convert_shadow(TEST2, VALUES1)))
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "keep_range...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.keep_range(25, 13);
  if (TEST1.size() != TEST2.section_size(25, 13)) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != data::clist_sigma(TEST2, 25, 13))
    return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "keep_pattern...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.keep_pattern(5, 12, 8);
  VALUE = TEST2.count(5, 12, 8);
  std::cout << "data: " << TEST2 << " " << data::clist_sigma(TEST2) << "\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << " " << data::clist_sigma(TEST1) << "\n"; std::cout.flush();
  if (TEST1.size() != VALUE) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != 5 * VALUE) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "f_keep_pattern...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.f_keep_pattern('c', &alpha_check, 12, 8);
  VALUE = TEST2.f_count('c', &alpha_check, 12, 8);
  std::cout << "data: " << TEST2 << " " << data::clist_sigma(TEST2) << "\n"; std::cout.flush();
  std::cout << "data: " << TEST1 << " " << data::clist_sigma(TEST1) << "\n"; std::cout.flush();
  if (TEST1.size() != VALUE) return false; std::cout << "[1 pass]\n"; std::cout.flush();
  if (data::clist_sigma(TEST1) != 2 * VALUE) return false; std::cout << "[2 pass]\n"; std::cout.flush();


  std::cout << "fe_keep_pattern...\n"; std::cout.flush();

  TEST1 = TEST2;

  TEST1.fe_keep_pattern(&three_multiple, 12, 8);
  VALUE = TEST2.fe_count(&three_multiple, 12, 8);
  std::cout << "data: " << TEST2 << " " << data::clist_sigma(TEST2) << "\n"; std::cout.flush(); std::cout.flush();
  std::cout << "data: " << TEST1 << " " << data::clist_sigma(TEST1) << "\n"; std::cout.flush(); std::cout.flush();
  if (TEST1.size() != VALUE) return false; std::cout << "[1 pass]\n"; std::cout.flush(); std::cout.flush();

  //END keep--------------------------------------------------------------------

  return true;
}
