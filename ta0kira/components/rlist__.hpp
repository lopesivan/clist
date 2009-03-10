/*============================================================================*\
 *rlist. Ring list with complex sorting.                                      *
 *Copyright (C) 2008 Kevin P. Barry (ta0kira)                                 *
 *                                                                            *
 *This library is free software; you can redistribute it and/or modify it     *
 *under the terms of the GNU Lesser General Public License as published by the*
 *Free Software Foundation; either version 2.1 of the License, or (at your    *
 *option) any later version.                                                  *
 *                                                                            *
 *This library is distributed in the hope that it will be useful, but WITHOUT *
 *ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
 *FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
 *for more details.                                                           *
 *                                                                            *
 *You should have received a copy of the GNU Lesser General Public License    *
 *along with this library; if not, write to the                               *
 *                                                                            *
 *    Free Software Foundation, Inc.,                                         *
 *    59 Temple Place, Suite 330,                                             *
 *    Boston, MA 02111-1307 USA                                               *
 *                                                                            *
 *Please contact ta0kira@users.sourceforge.net for feedback, questions, or    *
 *comments.                                                                   *
\*============================================================================*/

//CList_________________________________________________________________________
//(C) 2003-2005,2007-2008 Kevin P. Barry

//Header Section################################################################
#ifndef rlist___HPP
#define rlist___HPP CLIST_HPP
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include "list_types__.hpp"

namespace rlist___HPP
{

//Lists=========================================================================
//Class rlist-------------------------------------------------------------------
//Ring list class
template <class Type>
class rlist
{
public:
    //Typedefs==================================================================
    typedef typename internal_types <Type> ::base_type base_type;
    //Base type of elements

    typedef typename internal_types <Type> ::assign_type assign_type;
    //Assignable argument type

    typedef typename internal_types <Type> ::return_type return_type;
    //Return argument type

    typedef typename internal_types <Type> ::pointer_type pointer_type;
    //Pointer type

    typedef typename internal_types <Type> ::const_pointer_type
      const_pointer_type;
    //Constant pointer type

    typedef typename internal_types <Type> ::const_return_type
      const_return_type;
    //Constant return argument type

    typedef typename internal_types <Type> ::pull_type pull_type;
    //Return argument type for pull functions

    typedef unsigned char flag_value;
    //Option flag
    //==========================================================================

public:
    class locator;

    //Constructors--------------------------------------------------------------
    rlist(unsigned int = 0);
    //Constructor
    //Max size

    rlist(const rlist&);
    //Copy constructor
    //--------------------------------------------------------------------------

    //Copy data=================================================================

    /*____________________________________________________________________*
      -Copy Functions-

      copy_from: this function replaces the entire list with a sequence of
      elements from another list.

      copy_from(iterator): this function replaces the entire list with the
      number of elements provided by a pointer to an array of elements.

      f_copy_from: these functions allow copying of elements that are not
      the same as the list type by preprocessing them with a functor.
     *____________________________________________________________________*/

        rlist
    &copy_from(const rlist&);
    //Erase list and copy elements
    //List to copy from

    template <class Iterator2>
        rlist
    &copy_from(Iterator2, unsigned int);
    //Erase list and copy elements
    //Array of elements, size

    template <class Type2, class Function1>
        rlist
    &f_copy_from(const rlist <Type2>&, Function1);
    //Erase list and copy elements with functor pre-processing
    //List to copy from, pre-process functor

    template <class Iterator2, class Function1>
        rlist
    &f_copy_from(Iterator2, unsigned int, Function1);
    //Erase list and copy elements with functor pre-processing
    //Array of elements, size, pre-process functor
    //==========================================================================

    //List maintenance==========================================================

    /*____________________________________________________________________*
      -Add Functions-

      These functions add elements to the end of the list.
     *____________________________________________________________________*/

    //Add single element--------------------------------------------------------
    template <class Type2>
        bool
    add_element(const Type2&);
    //Add element
    //Element to add

        return_type
    add_element();
    //Increase size if possible
    //Returns reference to last element
    //--------------------------------------------------------------------------

    //Add multiple elements-----------------------------------------------------
        bool
    add_element(const rlist&, unsigned int = 1);
    //Add elements
    //List to copy from

    template <class Iterator2>
        bool
    add_element(Iterator2, unsigned int);
    //Add elements
    //Array of elements, size

    template <class Iterator2>
        unsigned int
    add_element(Iterator2, Iterator2);
    //Add elements
    //Begin iterator, end iterator

    template <class Type2, class Function1>
        bool
    f_add_element(const rlist <Type2>&, Function1, unsigned int = 1);
    //Add elements with functor pre-processing
    //List to copy from, pre-process functor

    template <class Iterator2, class Function1>
        bool
    f_add_element(Iterator2, unsigned int, Function1);
    //Add elements with functor pre-processing
    //Array of elements, size, pre-process functor

    template <class Iterator2, class Function1>
        unsigned int
    f_add_element(Iterator2, Iterator2, Function1);
    //Add elements using a functor to preprocess
    //Begin iterator, end iterator
    //--------------------------------------------------------------------------

    /*____________________________________________________________________*
      -Insert Functions-

      These functions insert elements at the given position.
     *____________________________________________________________________*/

    //Insert single element-----------------------------------------------------
    template <class Type2>
        bool
    insert_element(locator, const Type2&);
    //Insert element
    //Element to insert

        return_type
    insert_element(locator);
    //Insert default element
    //Returns element
    //--------------------------------------------------------------------------

    //Insert multiple elements--------------------------------------------------
        bool
    insert_element(locator, const rlist&, unsigned int = 1);
    //Insert multiple elements
    //Element list

    template <class Iterator2>
        bool
    insert_element(locator, Iterator2, unsigned int);
    //Insert multiple elements
    //Element array, number of elements

    template <class Iterator2>
        unsigned int
    insert_element(locator, Iterator2, Iterator2);
    //Insert multiple elements
    //Begin iterator, end iterator

    template <class Type2, class Function1>
        bool
    f_insert_element(locator, const rlist <Type2>&, Function1, unsigned int = 1);
    //Insert multiple elements with functor pre-processing
    //Element list, pre-process functor

    template <class Iterator2, class Function1>
        bool
    f_insert_element(locator, Iterator2, unsigned int, Function1);
    //Insert multiple elements with functor pre-processing
    //Element array, number of elements, pre-process functor

    template <class Iterator2, class Function1>
        unsigned int
    f_insert_element(locator, Iterator2, Iterator2, Function1);
    //Insert multiple elements with functor pre-processing
    //Begin iterator, end iterator
    //--------------------------------------------------------------------------

    //Remove elements-----------------------------------------------------------

    /*____________________________________________________________________*
      -Remove Functions-

      These functions remove elements based on their position, based on a
      list of positions, based on a range (endpoints are included), or
      based on the equality comparison with another element.
     *____________________________________________________________________*/

        rlist
    &remove_single(locator);
    //Remove specified element
    //List position

    template <class Type2>
        rlist
    &remove_list(rlist <Type2>&, int = first, int = last + 1);
    //Remove specified elements
    //List position list, list start position, list stop position

    template <class Iterator2>
        rlist
    &remove_list(Iterator2, unsigned int);
    //Remove specified elements
    //List position array, array size

        rlist
    &remove_range(locator, locator);
    //Remove elements in range
    //Start position, stop position

    template <class Type2>
        rlist
    &remove_pattern(const Type2&);
    //Remove matching elements
    //Pattern to remove

    template <class Type2, class Function2>
        rlist
    &f_remove_pattern(const Type2&, Function2);
    //Remove matching elements with functor comparison
    //Pattern to remove, functor

    template <class Function1>
        rlist
    &fe_remove_pattern(Function1);
    //Remove elements with functor evaluation
    //Functor
    //--------------------------------------------------------------------------

    //Keep elements-------------------------------------------------------------

    /*____________________________________________________________________*
      -Keep Functions-

      These functions keep elements based on their position, based on a
      list of positions, based on a range (endpoints are included), or
      based on the equality comparison with another element.
     *____________________________________________________________________*/

        rlist
    &keep_single(locator);
    //Keep specified element
    //List position

    template <class Type2>
        rlist
    &keep_list(rlist <Type2>&, int = first, int = last + 1);
    //Keep specified elements
    //List position list, list start position, list stop position

    template <class Iterator2>
        rlist
    &keep_list(Iterator2, unsigned int);
    //Keep specified elements
    //List position array, array size

        rlist
    &keep_range(locator, locator);
    //Keep elements in range
    //Start position, stop position

    template <class Type2>
        rlist
    &keep_pattern(const Type2&, int = first, int = last + 1);
    //Keep matching elements
    //Pattern to keep

    template <class Type2, class Function2>
        rlist
    &f_keep_pattern(const Type2&, Function2, int = first, int = last + 1);
    //Keep matching elements with functor comparison
    //Pattern to keep, functor

    template <class Function1>
        rlist
    &fe_keep_pattern(Function1, int = first, int = last + 1);
    //Keep elements with functor evaluation
    //Functor
    //--------------------------------------------------------------------------
    //==========================================================================

    /*____________________________________________________________________*
      -Retrieval Functions-

      first_element: these functions allow access to the first element.

      last_element: these functions allow access to the last element.

      current_element: these functions allow access to the element at the
      current index point.

      next_element: these functions allow access to the element at the
      current index point and post-increment the index position.

      previous_element: these functions pre-decrement the index position
      and then give access to the element at the current index point.
     *____________________________________________________________________*/

    //Random access=============================================================
    //Get first element---------------------------------------------------------
    inline
        const rlist
    &first_element(assign_type) const;
    //Get first element
    //Variable to set equal

    inline
        return_type
    first_element();
    //Get first element
    //Returns element reference

    inline
        const_return_type
    first_element() const;
    //Get first element
    //Returns element reference
    //--------------------------------------------------------------------------

    //Get last element----------------------------------------------------------
    inline
        const rlist
    &last_element(assign_type) const;
    //Get last element
    //Variable to set equal

    inline
        return_type
    last_element();
    //Get last element
    //Returns element reference

    inline
        const_return_type
    last_element() const;
    //Get last element
    //Returns element reference
    //--------------------------------------------------------------------------
  //============================================================================

    //Interated access==========================================================
    //Get current element-------------------------------------------------------
    inline
        const rlist
    &current_element(assign_type) const;
    //Get current element
    //Variable to set equal

    inline
        return_type
    current_element();
    //Get current element
    //Returns element reference

    inline
        const_return_type
    current_element() const;
    //Get current element
    //Returns element reference
    //--------------------------------------------------------------------------

    //Get current element, increment index--------------------------------------
    inline
        const rlist
    &next_element(assign_type);
    //Get current element
    //Variable to set equal

    inline
        return_type
    next_element();
    //Get current element
    //Returns element reference
    //--------------------------------------------------------------------------

    //Decrement index, get current element--------------------------------------
    inline
        const rlist
    &previous_element(assign_type);
    //Get previous element
    //Variable to set equal

    inline
        return_type
    previous_element();
    //Get previous element
    //Returns element reference
    //--------------------------------------------------------------------------
    //==========================================================================

    //Remove after access=======================================================

    /*____________________________________________________________________*
      -Pull Functions-

      These functions remove an element while returning it.
     *____________________________________________________________________*/

    //Remove and give first element---------------------------------------------
    inline
        rlist
    &p_first_element(assign_type);
    //Get and remove first element
    //Variable to set equal

    inline
        pull_type
    p_first_element();
    //Get and remove first element
    //Returns element
    //--------------------------------------------------------------------------

    //Remove and give last element----------------------------------------------
    inline
        rlist
    &p_last_element(assign_type);
    //Get and remove last element
    //Variable to set equal

    inline
        pull_type
    p_last_element();
    //Get and remove last element
    //Returns element
    //--------------------------------------------------------------------------

    //Remove and give current element-------------------------------------------
    inline
        rlist
    &p_current_element(assign_type);
    //Get and remove current element
    //Variable to set equal

    inline
        pull_type
    p_current_element();
    //Get and remove current element
    //Returns element
    //--------------------------------------------------------------------------
    //==========================================================================

    //Find functions============================================================
    //Normal find---------------------------------------------------------------
    template <class Type2> inline
        locator
    find(const Type2&) const;
    //Find first occurence only
    //Object to find, returns position

    template <class Type2, class Iterator2> inline
        locator
    find(const Type2&, Iterator2) const;
    //Find all occurences
    //Object to find, pointer for position array return, returns number found

    template <class Type2> inline
        locator
    count(const Type2&) const;
    //Find number of occurences
    //Object to find, returns number found

    template <class Type2, class Type3> inline
        locator
    rlist_find(const Type2&, rlist <Type3>&) const;
    //Find all occurences
    //Object to find, rlist to store positions, returns number found
    //--------------------------------------------------------------------------

    //Find with a comparison functor--------------------------------------------
    template <class Type2, class Function2> inline
        locator
    f_find(const Type2&, Function2) const;
    //Find first occurence only
    //Object to find, comparison functor, returns position

    template <class Type2, class Function2, class Iterator2> inline
        locator
    f_find(const Type2&, Iterator2, Function2) const;
    //Find all occurences
    //Object to find, pointer for position array return, comparison functor,
    //returns number found

    template <class Type2, class Function2> inline
        locator
    f_count(const Type2&, Function2) const;
    //Find number of occurences
    //Object to find, comparison functor, returns number found

    template <class Type2, class Function2, class Type3> inline
        locator
    f_rlist_find(const Type2&, rlist <Type3>&, Function2) const;
    //Find all occurences
    //Object to find, rlist to store positions, comparison functor, returns
    //number found
    //--------------------------------------------------------------------------

    //Find with an evaluation functor-------------------------------------------
    template <class Function1> inline
        locator
    fe_find(Function1) const;
    //Find first occurence only
    //Object to find, evaluation functor, returns position

    template <class Function1, class Iterator2> inline
        locator
    fe_find(Iterator2, Function1) const;
    //Find all occurences
    //Pointer for position array return, evaluation functor, returns number
    //found

    template <class Function1> inline
        locator
    fe_count(Function1) const;
    //Find number of occurences
    //Evaluation functor, returns number found

    template <class Function1, class Type2> inline
        locator
    fe_rlist_find(rlist <Type2>&, Function1) const;
    //Find all occurences
    //rlist to store positions, evaluation functor, returns number found
    //--------------------------------------------------------------------------
    //==========================================================================

    //List processing functions=================================================
    //sort functions------------------------------------------------------------
    //Intra-list sort...........................................................
        rlist
    &sort();
    //Sort list elements
    //Start position, stop position

    template <class Function2>
        rlist
    &f_sort(Function2);
    //Sort list elements with a functor for comparison
    //Comparison functor, start position, stop position
    //..........................................................................

    //Sorted order verification.................................................
        bool
    verify_order(int = first, int = last + 1) const;
    //Verify order
    //Start position, stop position

    template <class Function2>
        bool
    f_verify_order(Function2, int = first, int = last + 1) const;
    //Verify order with a comparison functor
    //Pre-comparison functor, start position, stop position
    //..........................................................................
    //--------------------------------------------------------------------------

    //Simple functions----------------------------------------------------------
        rlist
    &reverse_order(int = first, int = last + 1);
    //Reverse order of elements
    //Start position, stop position
    //--------------------------------------------------------------------------
    //==========================================================================

    //Basic operations==========================================================
    inline
        unsigned int
    size() const;
    //Get size of list
    //==========================================================================

    //Operators=================================================================
        rlist
    &operator = (const rlist&);
    //Assignment operator
    //rlist to copy from

        rlist
    &operator = (const_return_type);
    //Assignment operator
    //Replacement element

    inline
        return_type
    operator * ();
    //Dereference operator
    //Returns current element reference

    inline
        const_return_type
    operator * () const;
    //Dereference operator
    //Returns current element reference

    inline
        pointer_type
    operator -> ();
    //Dereference operator
    //Returns current element pointer

    inline
        const_pointer_type
    operator -> () const;
    //Dereference operator
    //Returns current element pointer

    inline
        rlist
    &operator >> (int);
    //Shift elements forward

    inline
        rlist
    &operator << (int);
    //Shift elements reverse

    inline
        int
    operator ++ (int);
    //Increment index (postfix)
    //Returns current index

    inline
        int
    operator ++ ();
    //Increment index (prefix)
    //Returns new index

    inline
        int
    operator -- (int);
    //Decrement index (postfix)
    //Returns current index

    inline
        int
    operator -- ();
    //Decrement index (prefix)
    //Returns new index
    //==========================================================================

    //Option flags==============================================================
    inline
        flag_value
    &o_reverse_process();
    //Reverse processing

    inline
        flag_value
    &o_reverse_equals();
    //Reverse equal elements against process direction

    inline
        flag_value
    &o_reverse_find();
    //Find in reverse
    //==========================================================================

    //Constant option flags=====================================================
    inline
        const flag_value
    &o_reverse_process() const;
    //Reverse processing

    inline
        const flag_value
    &o_reverse_equals() const;
    //Reverse equal elements against process direction

    inline
        const flag_value
    &o_reverse_find() const;
    //Find in reverse
    //==========================================================================

protected:
    //Sort/sort assist functions------------------------------------------------

    /*____________________________________________________________________*
      -Sort Functions-

      rlist_clm_sort_auto: a highly optimized circular linear merge sort
      function.

      f_rlist_clm_sort_auto: the functor version of the above.
     *____________________________________________________________________*/

    //Sort......................................................................
    template <class Iterator2> static
        void
    rlist_cim_sort_auto(Iterator2, Iterator2, unsigned int, unsigned int, bool,
      bool);
    //Circular insertion merge sort
    //Data start, data end, sort start position, sort end position, reverse
    //sorting flag, reverse equal elements flag

    template <class Function2, class Iterator2> static
        void
    f_rlist_cim_sort_auto(Iterator2, Iterator2, unsigned int, unsigned int,
      Function2, bool, bool);
    //Circular insertion merge sort with functor comparison
    //Data start, data end, sort start position, sort end position, functor,
    //reverse sorting flag, reverse equal elements flag

    template <class Iterator2> static
        void
    rlist_cim_sort(Iterator2, Iterator2, Iterator2, unsigned int, unsigned int,
      bool, bool);
    //Circular insertion merge sort
    //Data start, data end, temporary array, sort start position, sort end
    //position, reverse sorting flag, reverse equal elements flag

    template <class Function2, class Iterator2> static
        void
    f_rlist_cim_sort(Iterator2, Iterator2, Iterator2, unsigned int, unsigned int,
      Function2, bool, bool);
    //Circular insertion merge sort with functor comparison
    //Data start, data end, temporary array, sort start position, sort end
    //position, functor, reverse sorting flag, reverse equal elements flag
    //..........................................................................
    //--------------------------------------------------------------------------

protected:
    inline
        unsigned int
    allocate(unsigned int);
    //Allocation function

    //Converter-----------------------------------------------------------------
    template <class Type2> static inline
        const Type2
    &safety_convert(const Type2&);
    //Assists functor sorting by returning data as const
    //--------------------------------------------------------------------------

        internal_container
    internal_list_data;
    //Stores list of data

    static
        base_type
    reference_dummy;
    //Default element

    static
        const unsigned char
    number_flags = 5;
    //count of flags used

        mutable flag_value
    internal_flags[ number_flags ];
    //Flags for options
};
//END rlist---------------------------------------------------------------------
//END Header Section############################################################

//Source Section################################################################
//rlist function bodies=========================================================
  //Constructors----------------------------------------------------------------
  template <class Type>
  rlist <Type> ::rlist(unsigned int mMax)
  //Constructor
  {
  for (int I = 0; I < number_flags; I++) internal_flags[I] = false;
  reset_list(mMax);
  }

  template <class Type>
  rlist <Type> ::rlist(const rlist <Type> &eEqual)
  //Copy constructor
  {
  for (int I = 0; I < number_flags; I++) internal_flags[I] = eEqual.internal_flags[I];
  reset_list(eEqual.index.max_size());
  resize(eEqual.index.size());
  for (int I = 0; I < (signed) index.size(); I++)
  list_reference(I) = eEqual.list_reference(I);
  index = eEqual.index;
  }
  //----------------------------------------------------------------------------

  //Copy data===================================================================
  template <class Type> rlist <Type>
  &rlist <Type> ::copy_from(const rlist <Type> &eEqual, int sStart, int sStop)
  //Erase list and copy elements
  {
  int RS1, RS2, RSIZE = eEqual.set_range(RS1, RS2, sStart, sStop);
  reset_list(RSIZE);
  resize(RSIZE);
  for (int I = 0; I < (signed) index.size(); I++) list_reference(I) = eEqual[I + RS1];
  return *this;
  }

  template <class Type> template <class Iterator2> rlist <Type>
  &rlist <Type> ::copy_from(Iterator2 eEqual, unsigned int sSize)
  //Erase list and copy elements
  {
  reset_list(sSize);
  resize(sSize);
  for (int I = 0; I < (signed) index.size(); I++) list_reference(I) = *eEqual++;
  return *this;
  }

  template <class Type> template <class Type2, class Function1> rlist <Type>
  &rlist <Type> ::f_copy_from(const rlist <Type2> &eEqual, Function1 fFunction,
    int sStart, int sStop)
  //Erase list and copy elements with functor pre-processing
  {
  int RS1, RS2, RSIZE = eEqual.set_range(RS1, RS2, sStart, sStop);
  reset_list(RSIZE);
  resize(RSIZE);
  for (int I = 0; I < (signed) index.size(); I++)
  list_reference(I) = EVALUATE_1(fFunction, eEqual[I + RS1]);
  return *this;
  }

  template <class Type> template <class Iterator2, class Function1> rlist <Type>
  &rlist <Type> ::f_copy_from(Iterator2 eEqual, unsigned int sSize, Function1 fFunction)
  //Erase list and copy elements with functor pre-processing
  {
  reset_list(sSize);
  resize(sSize);
  for (int I = 0; I < (signed) index.size(); I++)
  list_reference(I) = EVALUATE_1(fFunction, *eEqual++);
  return *this;
  }
  //============================================================================

  //List maintenance============================================================
  //Add single element----------------------------------------------------------
  template <class Type> template <class Type2> bool
  rlist <Type> ::add_element(const Type2 &nNew)
  //Add element
  {
  if (!add_element_noshift(nNew)) return false;
  shift_elements(-1, -1 - index, last + 1);
  list_reference(short_modulo(last)) = nNew;
  return true;
  }

  template <class Type> typename rlist <Type> ::return_type
  rlist <Type> ::add_element()
  //Increase size if possible
  {
  if (!add_element(base_type())) return default_element();
  return get_element(last);
  }
  //----------------------------------------------------------------------------

  //Add multiple elements-------------------------------------------------------
  template <class Type> bool
  rlist <Type> ::add_element(const rlist <Type> &eEqual, int sStart, int sStop)
  //Add elements
  {
  if (!add_element_noshift(eEqual, sStart, sStop)) return false;
  shift_elements(- eEqual.section_size(sStart, sStop),
    - eEqual.section_size(sStart, sStop) - index, last + 1);
  return true;
  }

  template <class Type>  template <class Iterator2> bool
  rlist <Type> ::add_element(Iterator2 eEqual, unsigned int nNum)
  //Add elements
  {
  if (!add_element_noshift(eEqual, nNum)) return false;
  shift_elements(- nNum, - nNum - index, last + 1);
  return true;
  }

  template <class Type> template <class Iterator2> unsigned int
  rlist <Type> ::add_element(Iterator2 bBegin, Iterator2 eEnd)
  //Add elements
  {
  unsigned int S = add_element_noshift(bBegin, eEnd);

  if (S > 0) shift_elements(- (signed) S, - (signed) S - index, last + 1);

  return S;
  }

  template <class Type> template <class Type2, class Function1> bool
  rlist <Type> ::f_add_element(const rlist <Type2> &eEqual, Function1 fFunction,
    int sStart, int sStop)
  //Add elements
  {
  if (!f_add_element_noshift(eEqual, fFunction, sStart, sStop)) return false;
  shift_elements(- eEqual.section_size(sStart, sStop),
    - eEqual.section_size(sStart, sStop) - index, last + 1);
  return true;
  }

  template <class Type> template <class Iterator2, class Function1> bool
  rlist <Type> ::f_add_element(Iterator2 eEqual, unsigned int nNum, Function1 fFunction)
  //Add elements
  {
  if (!f_add_element_noshift(eEqual, nNum, fFunction)) return false;
  shift_elements(- nNum, - nNum - index, last + 1);
  return true;
  if (!increment_size(nNum)) return false;
  }

  template <class Type> template <class Iterator2, class Function1> unsigned int
  rlist <Type> ::f_add_element(Iterator2 bBegin, Iterator2 eEnd, Function1 fFunction)
  //Add elements using a functor to preprocess
  {
  unsigned int S = f_add_element_noshift(bBegin, eEnd, fFunction);

  if (S > 0) shift_elements(- (signed) S, - (signed) S - index, last + 1);

  return S;
  }
  //----------------------------------------------------------------------------

  //Insert single element-------------------------------------------------------
  template <class Type> template <class Type2> bool
  rlist <Type> ::insert_element(int pPos, const Type2 &aAdd)
  //Insert element at position
  {
  if (!add_element_noshift(aAdd)) return false;
  shift_elements(1, pPos, last - index + 1);
  if (index > list_modulo(pPos)) index++;
  return true;
  }

  template <class Type> typename rlist <Type> ::return_type
  rlist <Type> ::insert_element(int pPos)
  //Insert default element at position if possible
  {
  if (!add_element_noshift(base_type())) return default_element();
  shift_elements(1, pPos, last - index + 1);
  int position = list_modulo(pPos);
  if (index > list_modulo(pPos)) index++;
  return list_reference(position);
  }
  //----------------------------------------------------------------------------

  //Insert multiple elements----------------------------------------------------

  //Elements are added to the end of the list, then the list is shifted
  //the appropriate number of positions to move the added elements into
  //the correct position.

  template <class Type> bool
  rlist <Type> ::insert_element(int pPos, const rlist <Type> &lList, int sStart,
    int sStop)
  //Inserts multiple elements
  {
  int RS1, RS2, RSIZE = lList.set_range(RS1, RS2, sStart, sStop);
  if (RSIZE < 1) return true;
  if (!increment_size(RSIZE)) return false;
  for (int I = 0; I < RSIZE; I++)
  list_reference(index.size() - RSIZE + I) = lList[I + RS1];
  shift_elements(RSIZE, pPos, last - index + 1);
  if (index > list_modulo(pPos)) index += RSIZE;
  return true;
  }

  template <class Type> template <class Iterator2> bool
  rlist <Type> ::insert_element(int pPos, Iterator2 aAdd, unsigned int sSize)
  //Inserts multiple elements
  {
  if (sSize < 1) return true;
  if (!increment_size(sSize)) return false;
  for (int I = 0; I < (signed) sSize; I++)
  list_reference(index.size() - sSize + I) = *aAdd++;
  shift_elements(sSize, pPos, last - index + 1);
  if (index > list_modulo(pPos)) index += sSize;
  return true;
  }

  template <class Type> template <class Iterator2> unsigned int
  rlist <Type> ::insert_element(int pPos, Iterator2 bBegin, Iterator2 eEnd)
  //Insert multiple elements
  {
  int S = 0;
  shift_elements(S = add_element_noshift(bBegin, eEnd), pPos, last - index + 1);
  if (index > list_modulo(pPos)) index += S;
  return S;
  }

  template <class Type> template <class Type2, class Function1> bool
  rlist <Type> ::f_insert_element(int pPos, const rlist <Type2> &lList,
    Function1 fFunction, int sStart, int sStop)
  //Insert multiple elements with functor pre-processing
  {
  int RS1, RS2, RSIZE = lList.set_range(RS1, RS2, sStart, sStop);
  if (RSIZE < 1) return true;
  if (!increment_size(RSIZE)) return false;
  for (int I = 0; I < RSIZE; I++)
  list_reference(index.size() - RSIZE + I) = EVALUATE_1(fFunction, lList[I + RS1]);
  shift_elements(RSIZE, pPos, last - index + 1);
  if (index > list_modulo(pPos)) index += RSIZE;
  return true;
  }

  template <class Type> template <class Iterator2, class Function1> bool
  rlist <Type> ::f_insert_element(int pPos, Iterator2 aAdd, unsigned int sSize,
    Function1 fFunction)
  //Insert multiple elements with functor pre-processing
  {
  if (sSize < 1) return true;
  if (!increment_size(sSize)) return false;
  for (int I = 0; I < (signed) sSize; I++)
  list_reference(index.size() - sSize + I) = EVALUATE_1(fFunction, *aAdd++);
  shift_elements(sSize, pPos, last - index + 1);
  if (index > list_modulo(pPos)) index += sSize;
  return true;
  }

  template <class Type> template <class Iterator2, class Function1> unsigned int
  rlist <Type> ::f_insert_element(int pPos, Iterator2 bBegin, Iterator2 eEnd,
    Function1 fFunction)
  //Insert multiple elements using a functor to preprocess
  {
  int S = 0;
  shift_elements(S = f_add_element_noshift(bBegin, eEnd, fFunction), pPos,
    last - index + 1);
  if (index > list_modulo(pPos)) index += S;
  return S;
  }
  //----------------------------------------------------------------------------

  //Replace elements------------------------------------------------------------
  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::replace_element(int pPos, const Type2 &eEqual)
  //Replace element
  {
  if (!index.at_min()) list_reference(list_modulo(pPos)) = eEqual;
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::switch_elements(int pPos1, int pPos2)
  //Switch element positions
  {
  if (index.at_min()) return *this;
  typename internal_container::interim_type Temp =
    *list_element(list_modulo(pPos1));
  *list_element(list_modulo(pPos1)) = *list_element(list_modulo(pPos2));
  *list_element(list_modulo(pPos2)) = Temp;
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::clear_all()
  //Sets all elements equal to  a default
  {
  //We cast to the return type to prevent this function from being used
  //for const element lists
  for (int I = 0; I < (signed) index.size(); I++)
  const_cast <return_type> (list_reference(I)) = base_type();
  return *this;
  }
  //----------------------------------------------------------------------------

  //Remove elements-------------------------------------------------------------
  template <class Type> rlist <Type>
  &rlist <Type> ::remove_single(int pPos)
  //Remove specified element
  {
  if (!index.at_min())
   {
  shift_elements(-1, pPos, last - index + 1);
  if (index == short_modulo(last)) index = first;
  else if (pPos != first) index--;
  decrement_size();
   }
  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::remove_list(rlist <Type2> &lList, int sStart, int sStop)
  //Remove specified elements
  {
  //The list of elements to remove is copied, then sorted by position,
  //then the fast removal function removes the elements.
  if (index.at_min()) return *this;
  int RS1, RS2, RSIZE = lList.set_range(RS1, RS2, sStart, sStop);
  if (RSIZE < 1) return *this;

  position_container Temp;
  if (!check_capacity(Temp, RSIZE)) return *this;
  Temp.resize(RSIZE);

  for (int I = 0; I < RSIZE; I++) Temp[I] = list_modulo(lList[I + RS1]);
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + RSIZE, 0, RSIZE, false,
    false);
  fast_remove(Temp.begin(), RSIZE);
  return *this;
  }

  template <class Type> template <class Iterator2> rlist <Type>
  &rlist <Type> ::remove_list(Iterator2 pPos, unsigned int sSize)
  //Remove specified elements
  {
  //The array of elements to remove is copied, then sorted by position,
  //then the fast removal function removes the elements.
  if (index.at_min()) return *this;
  if (sSize < 1) return *this;

  position_container Temp;
  if (!check_capacity(Temp, sSize)) return *this;
  Temp.resize(sSize);

  for (int I = 0; I < (signed) sSize; I++) Temp[I] = list_modulo(*pPos++);
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + sSize, 0, sSize, false,
    false);
  fast_remove(Temp.begin(), sSize);
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::remove_range(int sStart, int sStop)
  //Remove elements in range
  {
  if (index.at_min()) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 1) return *this;

  position_container Temp;
  if (!check_capacity(Temp, SIZE)) return *this;
  Temp.resize(SIZE);

  for (int I = 0; I < SIZE; I++)  Temp[I] = list_modulo(I + S1);
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE, false, false);
  fast_remove(Temp.begin(), SIZE);
  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::remove_pattern(const Type2 &fFind, int sStart, int sStop)
  //Remove matching elements
  {
  if (index.at_min()) return *this;
  int Num = count(fFind, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, Num)) return *this;
  Temp.resize(Num);

  remove_list(Temp.begin(), find(fFind, Temp.begin(), sStart, sStop));
  return *this;
  }

  template <class Type> template <class Type2, class Function2> rlist <Type>
  &rlist <Type> ::f_remove_pattern(const Type2 &fFind, Function2 fFunction,
    int sStart, int sStop)
  //Remove matching elements with functor comparison
  {
  if (index.at_min()) return *this;
  int Num = f_count(fFind, fFunction, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, Num)) return *this;
  Temp.resize(Num);

  remove_list(Temp.begin(), f_find(fFind, Temp.begin(), fFunction, sStart, sStop));
  return *this;
  }

  template <class Type> template <class Function1> rlist <Type>
  &rlist <Type> ::fe_remove_pattern(Function1 fFunction, int sStart, int sStop)
  //Remove elements with functor evaluation
  {
  if (index.at_min()) return *this;
  int Num = fe_count(fFunction, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, Num)) return *this;
  Temp.resize(Num);

  remove_list(Temp.begin(), fe_find(Temp.begin(), fFunction, sStart, sStop));
  return *this;
  }
  //----------------------------------------------------------------------------

  //Keep elements---------------------------------------------------------------
  template <class Type> rlist <Type>
  &rlist <Type> ::keep_single(int pPos)
  //Keep specified element
  {
  if (index.at_min()) return *this;
  if (list_modulo(pPos) != 0)
   {
  release_element(0);
  *list_element(0) = *list_element(list_modulo(pPos));
  clear_element(list_modulo(pPos));
   }
  resize(1);
  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::keep_list(rlist <Type2> &lList, int sStart, int sStop)
  //Keep specified elements
  {
  //The list of elements to keep is first copied, then sorted by list
  //position.  The appropriate elements are moved to the beginning of the
  //list, then the list size is parsed.
  if (index.at_min()) return *this;
  int RS1, RS2, RSIZE = lList.set_range(RS1, RS2, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, RSIZE)) return *this;
  Temp.resize(RSIZE);

  for (int I = 0; I < RSIZE; I++) Temp[I] = list_modulo(lList[I + RS1]);
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + RSIZE, 0, RSIZE, false,
    false);
  fast_keep(Temp.begin(), RSIZE);
  return *this;
  }

  template <class Type> template <class Iterator2> rlist <Type>
  &rlist <Type> ::keep_list(Iterator2 pPos, unsigned int sSize)
  //Keep specified elements
  {
  //The list of elements to keep is first copied, then sorted by list
  //position.  The appropriate elements are moved to the beginning of the
  //list, then the list size is parsed.
  if (index.at_min()) return *this;

  position_container Temp;
  if (!check_capacity(Temp, sSize)) return *this;
  Temp.resize(sSize);

  for (int I = 0; I < (signed) sSize; I++) Temp[I] = list_modulo(*pPos++);
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + sSize, 0, sSize, false,
    false);
  fast_keep(Temp.begin(), sSize);
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::keep_range(int sStart, int sStop)
  //Keep elements in range
  {
  //This essentially reverses the range and calls the range remove
  //function.  The endpoints are removed from the range so that the range
  //of kept elements includes the endpoints.
  if (index.at_min()) return *this;
  int T1, T2;
  if (index.size() - set_range(T1, T2, sStart, sStop) < 1) return *this;
  int S1, S2, SIZE = set_range(S1, S2, T2, T1);
  if (SIZE < 1) return *this;

  position_container Temp;
  if (!check_capacity(Temp, SIZE)) return *this;
  Temp.resize(SIZE);

  for (int I = 0; I < SIZE; I++)  Temp[I] = short_modulo(I + S1);
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE, false, false);
  fast_remove(Temp.begin(), SIZE);
  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::keep_pattern(const Type2 &fFind, int sStart, int sStop)
  //Keep matching elements
  {
  if (index.at_min()) return *this;
  int Num = count(fFind, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, Num)) return *this;
  Temp.resize(Num);

  keep_list(Temp.begin(), find(fFind, Temp.begin(), sStart, sStop));
  return *this;
  }

  template <class Type> template <class Type2, class Function2> rlist <Type>
  &rlist <Type> ::f_keep_pattern(const Type2 &fFind, Function2 fFunction,
    int sStart, int sStop)
  //Keep matching elements with functor comparison
  {
  if (index.at_min()) return *this;
  int Num = f_count(fFind, fFunction, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, Num)) return *this;
  Temp.resize(Num);

  keep_list(Temp.begin(), f_find(fFind, Temp.begin(), fFunction, sStart, sStop));
  return *this;
  }

  template <class Type> template <class Function1> rlist <Type>
  &rlist <Type> ::fe_keep_pattern(Function1 fFunction, int sStart, int sStop)
  //Keep elements with functor evaluation
  {
  if (index.at_min()) return *this;
  int Num = fe_count(fFunction, sStart, sStop);

  position_container Temp;
  if (!check_capacity(Temp, Num)) return *this;
  Temp.resize(Num);

  keep_list(Temp.begin(), fe_find(Temp.begin(), fFunction, sStart, sStop));
  return *this;
  }
  //----------------------------------------------------------------------------
  //============================================================================

  //Random access===============================================================
  //Provide position------------------------------------------------------------
  template <class Type> inline const rlist <Type>
  &rlist <Type> ::get_element(int pPos, assign_type rReturn) const
  //Get element
  {
  rReturn = index.at_min()? base_type() : list_reference(list_modulo(pPos));
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::get_element(int pPos)
  //Get element
  { return index.at_min()? default_element() : list_reference(list_modulo(pPos)); }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::get_element(int pPos) const
  //Get element
  { return index.at_min()? default_element() : list_reference(list_modulo(pPos)); }

  template <class Type> inline const rlist <Type>
  &rlist <Type> ::h_get_element(int pPos, assign_type rReturn)
  //Get element, set index
  {
  rReturn = index.at_min()? base_type() : list_reference(index = list_modulo(pPos));
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::h_get_element(int pPos)
  //Get element, set index
  { return index.at_min()? default_element() : list_reference(index = list_modulo(pPos)); }
  //----------------------------------------------------------------------------

  //Get first element-----------------------------------------------------------
  template <class Type> inline const rlist <Type>
  &rlist <Type> ::first_element(assign_type rReturn) const
  //Get first element
  {
  rReturn = index.at_min()? base_type() : list_reference(first);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::first_element()
  //Get first element
  { return index.at_min()? default_element() : list_reference(first); }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::first_element() const
  //Get first element
  { return index.at_min()? default_element() : list_reference(first); }

  template <class Type> inline const rlist <Type>
  &rlist <Type> ::h_first_element(assign_type rReturn)
  //Get first element, set index
  {
  rReturn = index.at_min()? base_type() : list_reference(index = first);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::h_first_element()
  //Get first element, set index
  { return index.at_min()? default_element() : list_reference(index = first); }
  //----------------------------------------------------------------------------

  //Get last element------------------------------------------------------------
  template <class Type> inline const rlist <Type>
  &rlist <Type> ::last_element(assign_type rReturn) const
  //Get last element
  {
  rReturn = index.at_min()? base_type() : list_reference(short_modulo(last));
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::last_element()
  //Get last element
  { return index.at_min()? default_element() : list_reference(short_modulo(last)); }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::last_element() const
  //Get last element
  { return index.at_min()? default_element() : list_reference(short_modulo(last)); }

  template <class Type> inline const rlist <Type>
  &rlist <Type> ::h_last_element(assign_type rReturn)
  //Get last element, set index
  {
  rReturn = index.at_min()? base_type() : list_reference(index = last);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::h_last_element()
  //Get last element, set index
  { return index.at_min()? default_element() : list_reference(index = last); }
  //----------------------------------------------------------------------------
  //============================================================================

  //Interated access============================================================
  //Get current element---------------------------------------------------------
  template <class Type> inline const rlist <Type>
  &rlist <Type> ::current_element(assign_type rReturn) const
  //Get current element
  {
  rReturn = index.at_min()? base_type() : list_reference(index);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::current_element()
  //Get current element
  { return index.at_min()? default_element() : list_reference(index); }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::current_element() const
  //Get current element
  { return index.at_min()? default_element() : list_reference(index); }
  //----------------------------------------------------------------------------

  //Get current element, increment index----------------------------------------
  template <class Type> inline const rlist <Type>
  &rlist <Type> ::next_element(assign_type rReturn)
  //Get current element
  {
  rReturn = index.at_min()? base_type() : list_reference(index++);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::next_element()
  //Get current element
  { return index.at_min()? default_element() : list_reference(index++); }
  //----------------------------------------------------------------------------

  //Decrement index, get current element----------------------------------------
  template <class Type> inline const rlist <Type>
  &rlist <Type> ::previous_element(assign_type rReturn)
  //Get previous element
  {
  rReturn = index.at_min()? base_type() : list_reference(--index);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::previous_element()
  //Get previous element
  { return index.at_min()? default_element() : list_reference(--index); }
  //----------------------------------------------------------------------------
  //============================================================================

  //Remove after access=========================================================
  //Remove and give element at given position-----------------------------------
  template <class Type> inline rlist <Type>
  &rlist <Type> ::p_get_element(int pPos, assign_type rReturn)
  //Get and remove element
  {
  if (!index.at_min())
   {
  rReturn = list_reference(list_modulo(pPos));
  remove_single(pPos);
   }
  else rReturn = base_type();

  return *this;
  }

  template <class Type> inline typename rlist <Type> ::pull_type
  rlist <Type> ::p_get_element(int pPos)
  //Get and remove element
  {
  base_type Temp;
  p_get_element(pPos, Temp);
  return Temp;
  }
  //----------------------------------------------------------------------------

  //Remove and give first element-----------------------------------------------
  template <class Type> inline rlist <Type>
  &rlist <Type> ::p_first_element(assign_type rReturn)
  //Get and remove first element
  {
  if (!index.at_min())
   {
  rReturn = list_reference(first);
  remove_single(first - index);
   }
  else rReturn = base_type();

  return *this;
  }

  template <class Type> inline typename rlist <Type> ::pull_type
  rlist <Type> ::p_first_element()
  //Get and remove first element
  {
  base_type Temp;
  p_first_element(Temp);
  return Temp;
  }
  //----------------------------------------------------------------------------

  //Remove and give last element------------------------------------------------
  template <class Type> inline rlist <Type>
  &rlist <Type> ::p_last_element(assign_type rReturn)
  //Get and remove last element
  {
  if (!index.at_min())
   {
  rReturn = list_reference(short_modulo(last));
  remove_single(last - index);
   }
  else rReturn = base_type();

  return *this;
  }

  template <class Type> inline typename rlist <Type> ::pull_type
  rlist <Type> ::p_last_element()
  //Get and remove last element
  {
  base_type Temp;
  p_last_element(Temp);
  return Temp;
  }
  //----------------------------------------------------------------------------

  //Remove and give current element---------------------------------------------
  template <class Type> inline rlist <Type>
  &rlist <Type> ::p_current_element(assign_type rReturn)
  //Get and remove current element
  { return p_get_element(first, rReturn); }

  template <class Type> inline typename rlist <Type> ::pull_type
  rlist <Type> ::p_current_element()
  //Get and remove current element
  { return p_get_element(first); }
  //----------------------------------------------------------------------------

  //Remove and give current element, set index----------------------------------
  template <class Type> inline rlist <Type>
  &rlist <Type> ::hp_get_element(int pPos, assign_type rReturn)
  //Get and remove element, set index
  {
  if (!index.at_min())
   {
  rReturn = list_reference(list_modulo(pPos));
  remove_single(pPos);
   }
  else rReturn = base_type();

  index = pPos;

  return *this;
  }

  template <class Type> inline typename rlist <Type> ::pull_type
  rlist <Type> ::hp_get_element(int pPos)
  //Get and remove element, set index
  {
  base_type Temp;
  hp_get_element(pPos, Temp);
  return Temp;
  }
  //----------------------------------------------------------------------------
  //============================================================================

  //Find functions==============================================================
  //Normal find-----------------------------------------------------------------
  template <class Type> template <class Type2> inline int
  rlist <Type> ::find(const Type2 &fFind, int sStart, int sStop) const
  //Find first occurence only
  {
  if (index.at_min()) return not_found;

  int S1, S2, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if (list_reference(short_modulo(S1)) == fFind)
  return short_modulo(short_modulo(S1) - index);

  return not_found;
  }

  template <class Type> template <class Type2, class Iterator2> inline int
  rlist <Type> ::find(const Type2 &fFind, Iterator2 pPos, int sStart, int sStop) const
  //Find all occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if (list_reference(short_modulo(S1)) == fFind)
  *(pPos + N++) = short_modulo(short_modulo(S1) - index);

  return N;
  }

  template <class Type> template <class Type2> inline int
  rlist <Type> ::count(const Type2 &fFind, int sStart, int sStop) const
  //Find number of occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if (list_reference(short_modulo(S1)) == fFind) N++;

  return N;
  }

  template <class Type> template <class Type2, class Type3> inline int
  rlist <Type> ::rlist_find(const Type2 &fFind, rlist <Type3> &lList, int sStart,
    int sStop) const
  //Find all occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if (list_reference(short_modulo(S1)) == fFind)
  if (!lList.add_element(short_modulo(short_modulo(S1) - index))) return N;
  else N++;

  return N;
  }
  //----------------------------------------------------------------------------

  //Find with a comparison functor----------------------------------------------
  template <class Type> template <class Type2, class Function2> inline int
  rlist <Type> ::f_find(const Type2 &fFind, Function2 fFunction, int sStart, int sStop) const
  //Find first occurence only
  {
  if (index.at_min()) return not_found;

  int S1, S2, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_2(fFunction, list_reference(short_modulo(S1)), fFind) )
  return short_modulo(short_modulo(S1) - index);

  return not_found;
  }

  template <class Type> template <class Type2, class Function2, class Iterator2>
    inline int
  rlist <Type> ::f_find(const Type2 &fFind, Iterator2 pPos, Function2 fFunction,
    int sStart, int sStop) const
  //Find all occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_2(fFunction, list_reference(short_modulo(S1)), fFind) )
  *(pPos + N++) = short_modulo(short_modulo(S1) - index);

  return N;
  }

  template <class Type> template <class Type2, class Function2> inline int
  rlist <Type> ::f_count(const Type2 &fFind, Function2 fFunction, int sStart, int sStop) const
  //Find number of occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_2(fFunction, list_reference(short_modulo(S1)), fFind) ) N++;

  return N;
  }

  template <class Type> template <class Type2, class Function2, class Type3>
    inline int
  rlist <Type> ::f_rlist_find(const Type2 &fFind, rlist <Type3> &lList,
    Function2 fFunction, int sStart, int sStop) const
  //Find all occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_2(fFunction, list_reference(short_modulo(S1)), fFind) )
  if (!lList.add_element(short_modulo(short_modulo(S1) - index))) return N;
  else N++;

  return N;
  }
  //----------------------------------------------------------------------------

  //Find with an evaluation functor---------------------------------------------
  template <class Type> template <class Function1> inline int
  rlist <Type> ::fe_find(Function1 fFunction, int sStart, int sStop) const
  //Find first occurence only
  {
  if (index.at_min()) return not_found;

  int S1, S2, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_1(fFunction, list_reference(short_modulo(S1))) )
    return short_modulo(S1);

  return not_found;
  }

  template <class Type> template <class Function1, class Iterator2>
    inline int
  rlist <Type> ::fe_find(Iterator2 pPos, Function1 fFunction, int sStart, int sStop) const
  //Find all occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_1(fFunction, list_reference(short_modulo(S1))) )
    *(pPos + N++) = short_modulo(S1);

  return N;
  }

  template <class Type> template <class Function1> inline int
  rlist <Type> ::fe_count(Function1 fFunction, int sStart, int sStop) const
  //Find number of occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_1(fFunction, list_reference(short_modulo(S1))) ) N++;

  return N;
  }

  template <class Type> template <class Function1, class Type2>
    inline int
  rlist <Type> ::fe_rlist_find(rlist <Type2> &lList,
    Function1 fFunction, int sStart, int sStop) const
  //Find all occurences
  {
  if (index.at_min()) return 0;

  int S1, S2, N = 0, SIZE = find_range(S1, S2, sStart, sStop);

  for (int I = 0; I < SIZE; I++, o_reverse_find()? S1-- : S1++)
  if ( EVALUATE_1(fFunction, list_reference(short_modulo(S1))) )
  if (!lList.add_element(short_modulo(S1))) return N;
  else N++;

  return N;
  }
  //----------------------------------------------------------------------------
  //============================================================================

  //List processing functions===================================================
  //sort functions--------------------------------------------------------------
  //Intra-list sort.............................................................
  template <class Type> rlist <Type>
  &rlist <Type> ::sort(int sStart, int sStop)
  //Sort list elements
  {
  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  if (!o_inverted_sort_mode())
  //If we aren't in inverted mode then we can just call the sort function
   {
  internal_container Temp(SIZE);
  copy_data(Temp, sStart, sStop);

  rlist_clm_sort(list_element(0), list_element(index.size()), Temp.element(0),
    S1, S2, o_reverse_process(), o_reverse_equals());
   }

  else
  //We are in inverted mode, therefore we must pre-sort and then transpose
   {
  transposer_container TRANS;

  if (!pre_sort_data <shell_type, i_shell_type> (list_element(0), TRANS, S1, S2,
        internal_container::is_virtual, true, o_inverted_sort_mode(), true,
        o_reverse_process(), o_reverse_equals()))
  return *this;

  pre_order_data(TRANS.begin(), SIZE);
  n_internal_order_data(list_element(0), TRANS.begin(), S1, S2);
   }

  return *this;
  }

  template <class Type> template <class Function2> rlist <Type>
  &rlist <Type> ::f_sort(Function2 fFunction, int sStart, int sStop)
  //Sort list elements with a functor for comparison
  {
  //This is identical to the sort function except we use the functor versions
  //of the functions called

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  if (!o_inverted_sort_mode())
   {
  internal_container Temp(SIZE);
  copy_data(Temp, sStart, sStop);

  f_rlist_clm_sort(list_element(0), list_element(index.size()), Temp.element(0),
    S1, S2, fFunction, o_reverse_process(), o_reverse_equals());
   }

   else
   {
  transposer_container TRANS;

  if (!f_pre_sort_data <shell_type, i_shell_type> (list_element(0), TRANS, S1,
        o_reverse_equals(), S2, internal_container::is_virtual, true,
        o_inverted_sort_mode(), true, o_reverse_process(), fFunction))
  return *this;

  pre_order_data(TRANS.begin(), SIZE);
  n_internal_order_data(list_element(0), TRANS.begin(), S1, S2);
   }

  return *this;
  }
  //............................................................................

  //Inter-data master sort functions............................................
  template <class Type> template <class Iterator2> rlist <Type>
  &rlist <Type> ::ref_sort(Iterator2 rRef, int sStart, int sStop)
  //Sort a reference based on list elements
  {
  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  //Here we presort the reference then transpose our own elements

  transposer_container TRANS;

  if (!pre_sort_data <n_shell <typename std::iterator_traits <Iterator2> ::
          value_type>, i_n_shell <Iterator2> > (rRef, TRANS, 0, SIZE,
        o_ref_iterator_process(), false, o_inverted_sort_mode(), true,
        o_reverse_process(), o_reverse_equals()))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);
  n_internal_order_data(list_element(0), TRANS.begin(), S1, S2);

  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::rlist_ref_sort(const rlist <Type2> &rRef, int sStart, int sStop,
    int rRefStart)
  //Sort a rlist reference based on list elements
  {
  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  //First we check to see that there are enough elements in the reference

  int RS1, RS2, RSIZE = rRef.set_range(RS1, RS2, rRefStart,
                           rRefStart + SIZE);
  if (RSIZE != SIZE) return *this;

  transposer_container TRANS;

  //Here we call the reference list's own presorting function while using our
  //own option flags

  if (!rRef.pre_sort_data <typename rlist <Type2> ::shell_type,
          typename rlist <Type2> ::i_shell_type> (rRef.list_element(0), TRANS,
        RS1, RS2, rlist <Type2> ::internal_container::is_virtual, true,
        o_inverted_sort_mode(), false, o_reverse_process(), o_reverse_equals()))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);
  n_internal_order_data(list_element(0), TRANS.begin(), S1, S2);

  return *this;
  }

  template <class Type> template <class Function2, class Iterator2> rlist <Type>
  &rlist <Type> ::f_ref_sort(Iterator2 rRef, Function2 fFunction, int sStart, int sStop)
  //Sort list elements based on a reference with a comparison functor
  {
  //Identical to ref_sort but with a functor

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  typedef typename std::iterator_traits <Iterator2> ::value_type Type2;

  transposer_container TRANS;

  if (!f_pre_sort_data <n_shell <typename std::iterator_traits <Iterator2> ::
          value_type>, i_n_shell <Iterator2> > (rRef, TRANS, 0, SIZE,
         o_ref_iterator_process(), false, o_inverted_sort_mode(), true,
         o_reverse_process(), o_reverse_equals(), fFunction))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);
  n_internal_order_data(list_element(0), TRANS.begin(), S1, S2);

  return *this;
  }

  template <class Type> template <class Function2, class Type2> rlist <Type>
  &rlist <Type> ::f_rlist_ref_sort(const rlist <Type2> &rRef, Function2 fFunction,
    int sStart, int sStop, int rRefStart)
  //Sort list elements based on a rlist reference with a comparison functor
  {
  //Identical to rlist_ref_sort but with a functor

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  int RS1, RS2, RSIZE = rRef.set_range(RS1, RS2, rRefStart,
                           rRefStart + SIZE);
  if (RSIZE != SIZE) return *this;

  transposer_container TRANS;

  if (!rRef.f_pre_sort_data <typename rlist <Type2> ::shell_type,
          typename rlist <Type2> ::i_shell_type> (rRef.list_element(0), TRANS,
        RS1, RS2, rlist <Type2> ::internal_container::is_virtual, true,
        o_inverted_sort_mode(), false, o_reverse_process(), o_reverse_equals(),
        fFunction))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);
  n_internal_order_data(list_element(0), TRANS.begin(), S1, S2);

  return *this;
  }
  //............................................................................

  //Master sorting functions....................................................
  template <class Type> template <class Iterator2> const rlist <Type>
  &rlist <Type> ::ref_master_sort(Iterator2 rRef, int sStart, int sStop) const
  //Sort a reference based on list elements
  {
  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  transposer_container TRANS;

  //Here we presort our own elements

  if (!pre_sort_data <shell_type, i_shell_type> (list_element(0), TRANS, S1, S2,
        internal_container::is_virtual, true, o_inverted_sort_mode(), false,
        o_reverse_process(), o_reverse_equals()))
  return *this;

  //If we are not inverting then the transposer needs pre_order_data in order to
  //sort the external data

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);

  //Regardless of the mode we call n_order_data to order the reference

  n_order_data(rRef, TRANS.begin(), 0, SIZE);

  return *this;
  }

  template <class Type> template <class Type2> const rlist <Type>
  &rlist <Type> ::rlist_ref_master_sort(rlist <Type2> &rRef, int sStart,
    int sStop, int rRefStart) const
  //Sort a rlist reference based on list elements
  {
  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  //First we check to see that there are enough elements in the reference

  int RS1, RS2, RSIZE = rRef.set_range(RS1, RS2, rRefStart, rRefStart + SIZE);
  if (RSIZE != SIZE) return *this;

  transposer_container TRANS;

  //Here we call the presorting function

  if (!pre_sort_data <shell_type, i_shell_type> (list_element(0), TRANS, S1, S2,
         internal_container::is_virtual, true, o_inverted_sort_mode(), false,
         o_reverse_process(), o_reverse_equals()))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);

  //Here we call the reference list's own order_data function

  rRef.n_internal_order_data(rRef.list_element(0), TRANS.begin(), RS1, RS2);

  return *this;
  }

  template <class Type> template <class Function2, class Iterator2> const rlist <Type>
  &rlist <Type> ::f_ref_master_sort(Iterator2 rRef, Function2 fFunction,
    int sStart, int sStop) const
  //Sort a reference based on list elements with a comparison functor
  {
  //Identical to ref_master_sort but with a functor

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  transposer_container TRANS;

  if (!f_pre_sort_data <shell_type, i_shell_type> (list_element(0), TRANS, S1,
        S2, internal_container::is_virtual,true,  o_inverted_sort_mode(),
        o_reverse_equals(), false, o_reverse_process(), fFunction))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);

  n_order_data(rRef, TRANS.begin(), 0, SIZE);

  return *this;
  }

  template <class Type> template <class Function2, class Type2> const rlist <Type>
  &rlist <Type> ::f_rlist_ref_master_sort(rlist <Type2> &rRef, Function2 fFunction,
    int sStart, int sStop, int rRefStart) const
  //Sort a rlist reference based on list elements with a comparison functor
  {
  //Identical to rlist_ref_sort but with a functor

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  int RS1, RS2, RSIZE = rRef.set_range(RS1, RS2, rRefStart, rRefStart + SIZE);
  if (RSIZE != SIZE) return *this;

  transposer_container TRANS;

  if (!f_pre_sort_data <shell_type, i_shell_type> (list_element(0), TRANS, S1,
        S2, internal_container::is_virtual, true, o_inverted_sort_mode(), false,
        o_reverse_process(), o_reverse_equals(), fFunction))
  return *this;

  if (!o_inverted_sort_mode()) pre_order_data(TRANS.begin(), SIZE);
  rRef.n_internal_order_data(rRef.list_element(0), TRANS.begin(), RS1, RS2);

  return *this;
  }
  //............................................................................

  //Sorted order verification...................................................
  template <class Type> bool
  rlist <Type> ::verify_order(int sStart, int sStop) const
  //Verify order
  {
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);

  for (int I = S1; I < S2 - 1; I++)
   {
  const_return_type VAL1( list_reference(short_modulo(I    )) );
  const_return_type VAL2( list_reference(short_modulo(I + 1)) );

  if (o_reverse_process())
    {
  if (VAL1 < VAL2) return false;
    }
  else
    {
  if (VAL2 < VAL1) return false;
    }
   }

  return true;
  }

  template <class Type> template <class Function2> bool
  rlist <Type> ::f_verify_order(Function2 fFunction, int sStart, int sStop) const
  //Verify order with a comparison functor
  {
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);

  for (int I = S1; I < S2 - 1; I++)
   {
  if (o_reverse_process())
    {
  if ( EVALUATE_2( fFunction, safety_convert(list_reference( short_modulo(I) )),
         safety_convert(list_reference( short_modulo(I + 1) )) ) )
  return false;
    }
  else
    {
  if ( EVALUATE_2( fFunction, safety_convert(list_reference( short_modulo(I + 1) )),
         safety_convert(list_reference( short_modulo(I) )) ) )
  return false;
    }
   }

  return true;
  }
  //............................................................................
  //----------------------------------------------------------------------------

    //Simple functions----------------------------------------------------------
  template <class Type> rlist <Type>
  &rlist <Type> ::reverse_order(int sStart, int sStop)
  //Reverse order of elements
  {
  //Here we start by finding the range.  Then we make a reference array
  //the same size as the range with values numbered from one less than the
  //Size to 0.  We then order the range of elements based on this
  //reference.

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  position_container TRANS;
  if (!check_capacity(TRANS, SIZE)) return *this;
  TRANS.resize(SIZE);

  for (int I = SIZE - 1; I > -1; I--) TRANS[SIZE - I - 1] = I;
  internal_order_data(list_element(0), TRANS.begin(), S1, S2);
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::random_order(int sStart, int sStop)
  //Randomize order of elements
  {
  //Here we create a reference array of random numbers.  We then sort
  //this reference, and order the list based on the reference.

  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;

  typename list_container <n_shell <int> > ::type Temp;
  if (!check_capacity(Temp, SIZE)) return *this;
  Temp.resize(SIZE);

  srand(time(NULL) + rand());

  for (int I = 0; I < SIZE; I++)
   {
  Temp[I] << (int) rand() + ((int) rand() << sizeof(short));
  Temp[I] = I;
   }

  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE, false, false);
  n_internal_order_data(list_element(0), Temp.begin(), S1, S2);
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::shift_elements(int nNum, int sStart, int sStop)
  //Shift elements
  {
  //Given the number of elements being shifted N: we start our iteration
  //by subtracting parsed N from the size of the range.  We then number a
  //reference starting with that number, incrementing it each time.  The
  //element at the -Nth position of the range will now be at position 0 of
  //the range, therefore we order the list using this reference.

  if (nNum == 0) return *this;
  if (index.size() < 2) return *this;
  int S1, S2, SIZE = set_range(S1, S2, sStart, sStop);
  if (SIZE < 2) return *this;
  int N = ( (nNum > 0)? (-nNum % SIZE + SIZE) : (-nNum % SIZE) );

  position_container Temp(SIZE);
  if (!check_capacity(Temp, SIZE)) return *this;
  Temp.resize(SIZE);

  for (int I = 0; I < SIZE; I++)
  Temp[(I + N >= SIZE)? I + N - SIZE : I + N] = I;
  internal_order_data(list_element(0), Temp.begin(), S1, S2);
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::remove_duplicates(int sStart, int sStop)
  //Remove all duplicate elements
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = find_duplicates(Temp, sStart, sStop, false);
  fast_remove(Temp.begin(), P);
  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::remove_duplicates(rlist <Type2> &pPos, int sStart, int sStop)
  //Remove all duplicate elements and record positions
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = find_duplicates(Temp, sStart, sStop, false);
  pPos.copy_from(fast_remove(Temp.begin(), P), P);
  return *this;
  }

  template <class Type> template <class SortFunction2, class FindFunction2>
    rlist <Type>
  &rlist <Type> ::f_remove_duplicates(SortFunction2 sSort, FindFunction2 fFind,
    int sStart, int sStop)
  //Remove all duplicate elements with functors
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = f_find_duplicates(Temp, sStart, sStop, sSort, fFind, false);
  fast_remove(Temp.begin(), P);
  return *this;
  }

  template <class Type> template <class SortFunction2, class FindFunction2, class Type2>
    rlist <Type>
  &rlist <Type> ::f_remove_duplicates(rlist <Type2> &pPos, SortFunction2 sSort,
    FindFunction2 fFind, int sStart, int sStop)
  //Remove all duplicate elements and record positions with functors
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = f_find_duplicates(Temp, sStart, sStop, sSort, fFind, false);
  pPos.copy_from(fast_remove(Temp.begin(), P), P);
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::keep_only_duplicated(int sStart, int sStop)
  //Keep only duplicated elements
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = find_duplicates(Temp, sStart, sStop, true);
  fast_remove(Temp.begin(), P);
  return *this;
  }

  template <class Type> template <class Type2> rlist <Type>
  &rlist <Type> ::keep_only_duplicated(rlist <Type2> &pPos, int sStart, int sStop)
  //Keep only duplicated elements and record positions
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = find_duplicates(Temp, sStart, sStop, true);
  pPos.copy_from(fast_remove(Temp.begin(), P), P);
  return *this;
  }

  template <class Type> template <class SortFunction2, class FindFunction2>
    rlist <Type>
  &rlist <Type> ::f_keep_only_duplicated(SortFunction2 sSort, FindFunction2 fFind,
    int sStart, int sStop)
  //Keep only duplicated elements with functors
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = f_find_duplicates(Temp, sStart, sStop, sSort, fFind, true);
  fast_remove(Temp.begin(), P);
  return *this;
  }

  template <class Type> template <class SortFunction2, class FindFunction2, class Type2>
    rlist <Type>
  &rlist <Type> ::f_keep_only_duplicated(rlist <Type2> &pPos, SortFunction2 sSort,
    FindFunction2 fFind, int sStart, int sStop)
  //Keep only duplicated elements and record positions with functors
  {
  if (index.size() == 0) return *this;
  position_container Temp;
  int P = f_find_duplicates(Temp, sStart, sStop, sSort, fFind, true);
  pPos.copy_from(fast_remove(Temp.begin(), P), P);
  return *this;
  }
  //----------------------------------------------------------------------------
  //============================================================================

    //Basic operations==========================================================
  template <class Type> inline unsigned int
  rlist <Type> ::size() const
  //Get size of list
  { return index.size(); }

  template <class Type> inline int
  rlist <Type> ::section_size(int sStart, int sStop) const
  //Get size of element range
  {
  int B, E, SIZE = set_range(B, E, sStart, sStop);
  return SIZE;
  }

  template <class Type> inline unsigned int
  rlist <Type> ::resize(unsigned int sSize)
  //Set size of list
  {
  (sSize < index.size())? decrement_size(index.size() - sSize) :
                          increment_size(sSize - index.size());
  return index.size();
  }

  template <class Type> bool
  rlist <Type> ::increment_size(unsigned int sSize)
  //Increment size if possible
  {
  bool Unlimited = !index.max_size();

  if (Unlimited && !check_capacity(internal_list_data, index.size() + sSize)) return false;
  if (!Unlimited && (index.max_size() < index.size() + sSize)) return false;

  if (Unlimited) index.set_size(allocate(index.size() + sSize));
  else index.set_size(index.size() + sSize);

  for (unsigned int I = index.size() - sSize; I < index.size(); I++)
  internal_list_data.utilize(I);

  return true;
  }

  template <class Type> bool
  rlist <Type> ::decrement_size(unsigned int sSize)
  //Decrement size if possible
  {
  bool Unlimited = !index.max_size();
  if (index.size() < sSize) return false;

  for (int I = (signed) index.size() - 1; I > (signed) index.size() - (signed) sSize - 1; I--)
  internal_list_data.unutilize(I);

  //Here we allocate to the new size to erase/destruct the old elements
  allocate(index.size() - sSize);

  //Here we re-allocate the max size if necessary
  if (!Unlimited) allocate(index.max_size());

  //The new size becomes what was requested
  index.set_size(index.size() - sSize);

  return true;
  }

  template <class Type> inline unsigned int
  rlist <Type> ::max_size() const
  //Get max size
  { return index.max_size(); }

  template <class Type> inline unsigned int
  rlist <Type> ::set_max_size(unsigned int mMax)
  //Set new max size
  {
  if (mMax) return allocate(index.set_max(mMax));
  index.set_max(mMax);
  allocate(index.size());
  return mMax;
  }

  template <class Type> rlist <Type> &rlist <Type> ::
  reset_list(unsigned int mMax)
  //Clear list and max size
  {
  //Here we erase all data and set the size to 0
  index.set_size(allocate(0));

  //If we are limiting the size, we allocate the entire list...
  if (mMax) index.set_max(allocate(mMax));
  //...otherwise we set the max to unlimited
  else index.set_max(0);

  return *this;
  }
  //============================================================================

  //Operators===================================================================
  template <class Type> bool
  rlist <Type> ::operator == (const rlist <Type> &eEqual) const
  //Comparison operator
  {
  if (index.size() != eEqual.index.size()) return false;
  //using 'list_modulo' on the left forces the index to be taken into account
  for (int I = 0; I < (signed) index.size(); I++)
    if (!list_reference(list_modulo(I)) == eEqual[I]) return false;
  return true;
  }

  template <class Type> bool
  rlist <Type> ::operator != (const rlist <Type> &eEqual) const
  //Comparison operator
  { return !(*this == eEqual); }

  template <class Type> rlist <Type>
  &rlist <Type> ::operator = (const rlist <Type> &eEqual)
  //Assignment operator
  {
  //We do not copy flags here; we just copy capacity, index, and data
  reset_list(eEqual.index.max_size());
  for (int I = 0; I < (signed) eEqual.index.size(); I++) add_element(eEqual[I]);
  index = eEqual.index;
  return *this;
  }

  template <class Type> rlist <Type>
  &rlist <Type> ::operator = (typename internal_types <Type> ::const_return_type eEqual)
  //Assignment operator
  {
  //We cast to the return type to prevent this function from being used
  //for const element lists
  for (int I = 0; I < (signed) index.size(); I++)
  //using 'list_modulo' on the left forces the index to be taken into account
  const_cast <return_type> (list_reference(list_modulo(I))) = eEqual;
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::operator [] (int pPos)
  //Returns element reference
  {
  if (index.at_min()) return default_element();
  return list_reference(list_modulo(pPos));
  }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::operator [] (int pPos) const
  //Returns element reference
  {
  if (index.at_min()) return default_element();
  return list_reference(list_modulo(pPos));
  }

  template <class Type> inline typename rlist <Type> ::return_type
  rlist <Type> ::operator * ()
  //Dereference operator
  { return current_element(); }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::operator * () const
  //Dereference operator
  { return current_element(); }

  template <class Type> inline typename rlist <Type> ::pointer_type
  rlist <Type> ::operator -> ()
  //Dereference operator
  { return &current_element(); }

  template <class Type> inline typename rlist <Type> ::const_pointer_type
  rlist <Type> ::operator -> () const
  //Dereference operator
  { return &current_element(); }

  template <class Type> inline rlist <Type>
  &rlist <Type> ::operator >> (int sShift)
  //Shift elements forward
  { return shift_elements(sShift, first, last + 1); }

  template <class Type> inline rlist <Type>
  &rlist <Type> ::operator << (int sShift)
  //Shift elements reverse
  { return shift_elements(-sShift, first, last + 1); }

  template <class Type> inline int
  rlist <Type> ::operator ++ (int)
  //Increment index (postfix)
  { return index++; }

  template <class Type> inline int
  rlist <Type> ::operator ++ ()
  //Increment index (prefix)
  { return ++index; }

  template <class Type> inline int
  rlist <Type> ::operator -- (int)
  //Decrement index (postfix)
  { return index--; }

  template <class Type> inline int
  rlist <Type> ::operator -- ()
  //Decrement index (prefix)
  { return --index; }
  //============================================================================

  //Option flags================================================================
  template <class Type> inline typename rlist <Type> ::flag_value
  &rlist <Type> ::o_reverse_process()
  //Reverse processing
  { return internal_flags[0]; }

  template <class Type> inline typename rlist <Type> ::flag_value
  &rlist <Type> ::o_reverse_equals()
  //Reverse equal elements against process direction
  { return internal_flags[1]; }

  template <class Type> inline typename rlist <Type> ::flag_value
  &rlist <Type> ::o_reverse_find()
  //Find in reverse flag
  { return internal_flags[2]; }

  template <class Type> inline typename rlist <Type> ::flag_value
  &rlist <Type> ::o_ref_iterator_process()
  //Process iterators of reference data instead of values
  { return internal_flags[3]; }

  template <class Type> inline typename rlist <Type> ::flag_value
  &rlist <Type> ::o_inverted_sort_mode()
  //Set inverted mode
  { return internal_flags[4]; }
  //============================================================================

  //Constant option flags=======================================================
  template <class Type> inline const typename rlist <Type> ::flag_value
  &rlist <Type> ::o_reverse_process() const
  //Reverse processing
  { return internal_flags[0]; }

  template <class Type> inline const typename rlist <Type> ::flag_value
  &rlist <Type> ::o_reverse_equals() const
  //Reverse equal elements against process direction
  { return internal_flags[1]; }

  template <class Type> inline const typename rlist <Type> ::flag_value
  &rlist <Type> ::o_reverse_find() const
  //Find in reverse
  { return internal_flags[2]; }

  template <class Type> inline const typename rlist <Type> ::flag_value
  &rlist <Type> ::o_ref_iterator_process() const
  //Process iterators of reference data instead of values
  { return internal_flags[3]; }

  template <class Type> inline const typename rlist <Type> ::flag_value
  &rlist <Type> ::o_inverted_sort_mode() const
  //Set inverted mode
  { return internal_flags[4]; }
  //============================================================================

  //Assist functions------------------------------------------------------------
  template <class Type> inline int
  rlist <Type> ::list_modulo(int pPos) const
  //Returns valid array pos from int
  { return index[pPos + index]; }

  template <class Type> inline int
  rlist <Type> ::set_range(int &lLo, int &hHi, int sStart, int sStop) const
  //Sets range
  {
  if (index.size() < 1) return lLo = hHi = 0;
  lLo = list_modulo(sStart);
  hHi = list_modulo(sStop);
  if (lLo >= hHi) hHi += index.size();
  return hHi - lLo;
  }

  template <class Type> inline int
  rlist <Type> ::find_range(int &lLo, int &hHi, int sStart, int sStop) const
  //Sets range
  {
  return o_reverse_find()? set_range(hHi, lLo, sStart - 1, sStop - 1) :
    set_range(lLo, hHi, sStart, sStop);
  }

  template <class Type> template <class Type2> inline
  bool rlist <Type> ::check_capacity(const Type2 &cCont, unsigned int sSize)
  //Check for total space
  { return cCont.max_size() >= sSize; }
  //----------------------------------------------------------------------------
  //Add single element----------------------------------------------------------
  template <class Type> template <class Type2> bool
  rlist <Type> ::add_element_noshift(const Type2 &nNew)
  //Add element
  {
  if (!increment_size()) return false;
  list_reference(short_modulo(last)) = nNew;
  return true;
  }

  template <class Type> bool
  rlist <Type> ::add_element_noshift(const rlist <Type> &eEqual, int sStart,
    int sStop)
  //Add elements
  {
  int RS1, RS2, RSIZE = eEqual.set_range(RS1, RS2, sStart, sStop);
  if (RSIZE < 1) return true;
  if (!increment_size(RSIZE)) return false;
  for (int I = 0; I < RSIZE; I++)
  list_reference(index.size() - RSIZE + I) = eEqual[I + RS1];
  return true;
  }

  template <class Type>  template <class Iterator2> bool
  rlist <Type> ::add_element_noshift(Iterator2 eEqual, unsigned int nNum)
  //Add elements
  {
  if (!increment_size(nNum)) return false;
  for (int I = 0; I < (signed) nNum; I++)
  list_reference(index.size() - nNum + I) = *eEqual++;
  return true;
  }

  template <class Type> template <class Iterator2> unsigned int
  rlist <Type> ::add_element_noshift(Iterator2 bBegin, Iterator2 eEnd)
  //Add elements
  {
  unsigned int S = 0;
  bool Continue = true;

  while (bBegin < eEnd && Continue)
  if (add_element_noshift(*bBegin++)) S++;
  else Continue = false;

  return S;
  }

  template <class Type> template <class Type2, class Function1> bool
  rlist <Type> ::f_add_element_noshift(const rlist <Type2> &eEqual,
    Function1 fFunction, int sStart, int sStop)
  //Add elements
  {
  int RS1, RS2, RSIZE = eEqual.set_range(RS1, RS2, sStart, sStop);
  if (RSIZE < 1) return true;
  if (!increment_size(RSIZE)) return false;
  for (int I = 0; I < RSIZE; I++)
  list_reference(index.size() - RSIZE + I) = EVALUATE_1(fFunction, eEqual[I + RS1]);
  return true;
  }

  template <class Type> template <class Iterator2, class Function1> bool
  rlist <Type> ::f_add_element_noshift(Iterator2 eEqual, unsigned int nNum,
    Function1 fFunction)
  //Add elements
  {
  if (!increment_size(nNum)) return false;
  for (int I = 0; I < (signed) nNum; I++)
  list_reference(index.size() - nNum + I) = EVALUATE_1(fFunction, *eEqual++);
  return true;
  }

  template <class Type> template <class Iterator2, class Function1> unsigned int
  rlist <Type> ::f_add_element_noshift(Iterator2 bBegin, Iterator2 eEnd,
    Function1 fFunction)
  //Add elements using a functor to preprocess
  {
  unsigned int S = 0;
  bool Continue = true;

  while (bBegin < eEnd && Continue)
  if ( add_element( EVALUATE_1(fFunction, *bBegin++) ) ) S++;
  else Continue = false;

  return S;
  }
  //----------------------------------------------------------------------------

  //Sort/sort assist functions--------------------------------------------------
//Circular linear merge sort****************************************************
//(C) 2003-2005,2007-2008 Kevin P. Barry

  //Sort........................................................................
  template <class Type> template <class Iterator2> void
  rlist <Type> ::rlist_clm_sort_auto(Iterator2 lListBegin, Iterator2 lListEnd,
    unsigned int sStart, unsigned int sStop, bool rRev, bool eEqual)
  //Circular insertion merge sort
  {
  int DataSize = sStop - sStart, TotalSize = lListEnd - lListBegin;

  typename list_container <typename std::iterator_traits <Iterator2> ::value_type> ::type Temp;
  if (!check_capacity(Temp, DataSize)) return;
  Temp.resize(DataSize);

  int RequiredSection = 1;
  bool Direction = false;
  while ((RequiredSection *= 2) < DataSize) Direction = !Direction;

  if (!Direction)
  for (int I = 0; I < DataSize; I++)
  Temp[I] = lListBegin[ (I + sStart) % TotalSize ];

  rlist_clm_sort(lListBegin, lListEnd, Temp.begin(), sStart, sStop, rRev, eEqual);
  }

  template <class Type> template <class Iterator2> void
  rlist <Type> ::rlist_clm_sort(Iterator2 lListBegin, Iterator2 lListEnd,
    Iterator2 tTemp, unsigned int sStart, unsigned int sStop, bool rRev, bool eEqual)
  //Circular insertion merge sort
  {
  //Instantiate iterators and integers==========================================
  //Fixed values----------------------------------------------------------------
  int DataSize = sStop - sStart;
  //----------------------------------------------------------------------------

  //Each cycle------------------------------------------------------------------
  Iterator2 ReadMin,  ReadMax,  ReadStart,
    WriteMin, WriteMax, WriteStart;

  int ReadSection  = 1, ReadSize,
      WriteSection = 2, WriteSize;
  //----------------------------------------------------------------------------

  //Each iteration--------------------------------------------------------------
  Iterator2 ReadLeft, ReadRight, Write;

  int ReadLeftCount, ReadRightCount;
  //----------------------------------------------------------------------------
  //============================================================================

  //Determine initial read/write lists==========================================
  int RequiredSection = 1;
  bool Direction = false;
  while ((RequiredSection *= 2) < DataSize) Direction = !Direction;
  //Predict sort iterations (Direction is about = !(ceil(log2(size)) % 2))
  //============================================================================

  //sort========================================================================
  while (ReadSection < RequiredSection)
   {
  //Set cycle limits------------------------------------------------------------
  //processes about log2(size) times
  if (Direction)
    {
  //The read data points are set to the actual data and the write data
  //points are set to the temporary data.
  ReadStart  = lListBegin + sStart;     WriteStart = tTemp;
  ReadMin    = lListBegin;              WriteMin   = tTemp;
  ReadMax    = lListEnd;                WriteMax   = tTemp + DataSize;
    }

  else
    {
  //The read data points are set to the temporary data and the write data
  //points are set to the actual data.
  ReadStart  = tTemp;                   WriteStart = lListBegin + sStart;
  ReadMin    = tTemp;                   WriteMin   = lListBegin;
  ReadMax    = tTemp + DataSize;        WriteMax   = lListEnd;
    }

  //The read and write sizes are found by subtracting the ranges.
  ReadSize  = ReadMax  - ReadMin;      WriteSize = WriteMax - WriteMin;

  //Of course, we need to make sure to switch the next time around.
  Direction = !Direction;
  //----------------------------------------------------------------------------

  //Linear processing of sort sections------------------------------------------
  //processes about size x log2(size) / 2 times
  for (int I = 0; I < DataSize; I += WriteSection)
    {
  //Set iteration parameters based on cycle limits..............................

  //These assignments were nice and neat, however in an effort to make
  //them as fast as possible I've 'optimized' the statements as much as
  //possible.  No, it isn't very graceful.

  //Here we set the left read section to the next section of read data.
  //If the start of the section crosses the endpoint of the read data, we
  //subtract the read data size to wrap the read point around to the
  //beginning.
  if ((ReadLeft = ReadStart + I) >= ReadMax) ReadLeft -= ReadSize;

  //Here we set the right read section much like above, except the right
  //section is one data section ahead of the left read section.  Again,
  //if we are past the endpoint we subtract the read data size to wrap
  //the read point around to the beginning.
  if ((ReadRight = ReadLeft + ReadSection) >= ReadMax) ReadRight -= ReadSize;

  //Here we set the write section to the next section of write data.  If
  //we are past the write data endpoint we subtract the write data size
  //to wrap around to the beginning.
  if ((Write = WriteStart + I) >= WriteMax) Write -= WriteSize;

  //Now that the iterators are set, we need a counter set that isn't
  //dependent on comparing read positions with the data endpoint.  We
  //set the left counter to the section size.  If there is not enough
  //read data left we set this counter to whatever is left.
  if ((ReadLeftCount = ReadSection) + I > DataSize)
     {
  ReadLeftCount  = DataSize - I;

  //While we are at it, we will set the right section to 0 since there is
  //not enough left to make even a partial section.
  ReadRightCount = 0;
     }

  //If there was enough room for the left section, we set the right
  //section to the section size and check to see if it is too large. If
  //it is too large, we set it to whatever is left of the read data.
  else if ((ReadRightCount = ReadSection) > DataSize - I - ReadLeftCount)
  ReadRightCount = DataSize - I - ReadLeftCount;
  //............................................................................

  //Compare and transpose.......................................................
  //processes about size x log2(size) times
  while (ReadLeftCount && ReadRightCount)
     {
  if (eEqual)

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( rRev ^  ( safety_convert(ReadLeft[0]) <
                 safety_convert(ReadRight[0]) ) )
      {
  *Write = *ReadLeft;
  if (++ReadLeft >= ReadMax)  ReadLeft = ReadMin;
  if (++Write    >= WriteMax) Write    = WriteMin;
  --ReadLeftCount;
      }

  else
      {
  *Write = *ReadRight;
  if (++ReadRight >= ReadMax)  ReadRight = ReadMin;
  if (++Write     >= WriteMax) Write     = WriteMin;
  --ReadRightCount;
      }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  else

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( rRev ^  ( safety_convert(ReadRight[0]) <
                 safety_convert(ReadLeft[0]) ) )
      {
  *Write = *ReadRight;
  if (++ReadRight >= ReadMax)  ReadRight = ReadMin;
  if (++Write     >= WriteMax) Write     = WriteMin;
  --ReadRightCount;
      }

  else
      {
  *Write = *ReadLeft;
  if (++ReadLeft >= ReadMax)  ReadLeft = ReadMin;
  if (++Write    >= WriteMax) Write    = WriteMin;
  --ReadLeftCount;
      }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     }
  //............................................................................

  //Fill in excess elements.....................................................
  while (ReadLeftCount)
     {
  *Write = *ReadLeft;
  if (++ReadLeft >= ReadMax)  ReadLeft = ReadMin;
  if (++Write    >= WriteMax) Write    = WriteMin;
  --ReadLeftCount;
     }

  while (ReadRightCount)
     {
  *Write = *ReadRight;
  if (++ReadRight >= ReadMax)  ReadRight = ReadMin;
  if (++Write     >= WriteMax) Write     = WriteMin;
  --ReadRightCount;
     }
  //............................................................................
    }
  //----------------------------------------------------------------------------

  WriteSection += (ReadSection = WriteSection);
   }
  //============================================================================
  }

  template <class Type> template <class Function2, class Iterator2> void
  rlist <Type> ::f_rlist_clm_sort_auto(Iterator2 lListBegin, Iterator2 lListEnd,
    unsigned int sStart, unsigned int sStop, Function2 fFunction, bool rRev,
    bool eEqual)
  //Circular insertion merge sort with functor comparison
  {
  int DataSize = sStop - sStart, TotalSize = lListEnd - lListBegin;

  typename list_container <typename std::iterator_traits <Iterator2> ::value_type> ::type Temp;
  if (!check_capacity(Temp, DataSize)) return;
  Temp.resize(DataSize);

  int RequiredSection = 1;
  bool Direction = false;
  while ((RequiredSection *= 2) < DataSize) Direction = !Direction;

  if (!Direction)
  for (int I = 0; I < DataSize; I++)
  Temp[I] = lListBegin[ (I + sStart) % TotalSize ];

  f_rlist_clm_sort(lListBegin, lListEnd, Temp.begin(), sStart, sStop, fFunction,
    rRev, eEqual);
  }

  template <class Type> template <class Function2, class Iterator2> void
  rlist <Type> ::f_rlist_clm_sort(Iterator2 lListBegin, Iterator2 lListEnd,
    Iterator2 tTemp, unsigned int sStart, unsigned int sStop, Function2 fFunction,
    bool rRev, bool eEqual)
  //Circular insertion merge sort with functor comparison
  {
  //This is identical to the other rlist_clm_sort except here we run the
  //elements through a functor before we compare them.  I purposely didn't
  //duplicate the notes because if I revise them I don't want to change
  //them twice.

  //Instantiate iterators and integers==========================================
  //Fixed values----------------------------------------------------------------
  int DataSize  = sStop - sStart;
  //----------------------------------------------------------------------------

  //Each cycle------------------------------------------------------------------
  Iterator2 ReadMin,  ReadMax,  ReadStart,
    WriteMin, WriteMax, WriteStart;

  int ReadSection  = 1, ReadSize,
      WriteSection = 2, WriteSize;
  //----------------------------------------------------------------------------

  //Each iteration--------------------------------------------------------------
  Iterator2 ReadLeft, ReadRight, Write;

  int ReadLeftCount, ReadRightCount;
  //----------------------------------------------------------------------------
  //============================================================================

  //Determine initial read/write lists==========================================
  int RequiredSection = 1;
  bool Direction = false;
  while ((RequiredSection *= 2) < DataSize) Direction = !Direction;
  //============================================================================

  //sort========================================================================
  while (ReadSection < RequiredSection)
   {
  //Set cycle limits------------------------------------------------------------
  //processes about log2(size) times
  if (Direction)
    {
  //The read data points are set to the actual data and the write data
  //points are set to the temporary data.
  ReadStart  = lListBegin + sStart;     WriteStart = tTemp;
  ReadMin    = lListBegin;              WriteMin   = tTemp;
  ReadMax    = lListEnd;                WriteMax   = tTemp + DataSize;
    }

  else
    {
  //The read data points are set to the temporary data and the write data
  //points are set to the actual data.
  ReadStart  = tTemp;                   WriteStart = lListBegin + sStart;
  ReadMin    = tTemp;                   WriteMin   = lListBegin;
  ReadMax    = tTemp + DataSize;        WriteMax   = lListEnd;
    }

  //The read and write sizes are found by subtracting the ranges.
  ReadSize  = ReadMax  - ReadMin;      WriteSize = WriteMax - WriteMin;

  //Of course, we need to make sure to switch the next time around.
  Direction = !Direction;
  //----------------------------------------------------------------------------

  //Linear processing of sort sections------------------------------------------
  for (int I = 0; I < DataSize; I += WriteSection)
    {
  //Set iteration parameters based on cycle limits..............................
  if ((ReadLeft = ReadStart + I) >= ReadMax) ReadLeft -= ReadSize;

  if ((ReadRight = ReadLeft + ReadSection) >= ReadMax) ReadRight -= ReadSize;

  if ((Write = WriteStart + I) >= WriteMax) Write -= WriteSize;

  if ((ReadLeftCount = ReadSection) + I > DataSize)
     {
  ReadLeftCount  = DataSize - I;

  ReadRightCount = 0;
     }

  else if ((ReadRightCount = ReadSection) > DataSize - I - ReadLeftCount)
  ReadRightCount = DataSize - I - ReadLeftCount;
  //............................................................................

  //Compare and transpose.......................................................
  while (ReadLeftCount && ReadRightCount)
     {
  if (eEqual)

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( rRev ^  EVALUATE_2( fFunction, safety_convert(ReadLeft[0]),
                                      safety_convert(ReadRight[0]) ) )
      {
  *Write = *ReadLeft;
  if (++ReadLeft >= ReadMax)  ReadLeft = ReadMin;
  if (++Write    >= WriteMax) Write    = WriteMin;
  --ReadLeftCount;
      }

  else
      {
  *Write = *ReadRight;
  if (++ReadRight >= ReadMax)  ReadRight = ReadMin;
  if (++Write     >= WriteMax) Write     = WriteMin;
  --ReadRightCount;
      }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  else

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( rRev ^  EVALUATE_2( fFunction, safety_convert(ReadRight[0]),
                                      safety_convert(ReadLeft[0]) ) )
      {
  *Write = *ReadRight;
  if (++ReadRight >= ReadMax)  ReadRight = ReadMin;
  if (++Write     >= WriteMax) Write     = WriteMin;
  --ReadRightCount;
      }

  else
      {
  *Write = *ReadLeft;
  if (++ReadLeft >= ReadMax)  ReadLeft = ReadMin;
  if (++Write    >= WriteMax) Write    = WriteMin;
  --ReadLeftCount;
      }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     }
  //............................................................................

  //Fill in excess elements.....................................................
  while (ReadLeftCount)
     {
  *Write = *ReadLeft;
  if (++ReadLeft >= ReadMax)  ReadLeft = ReadMin;
  if (++Write    >= WriteMax) Write    = WriteMin;
  --ReadLeftCount;
     }

  while (ReadRightCount)
     {
  *Write = *ReadRight;
  if (++ReadRight >= ReadMax)  ReadRight = ReadMin;
  if (++Write     >= WriteMax) Write     = WriteMin;
  --ReadRightCount;
     }
  //............................................................................
    }
  //----------------------------------------------------------------------------

  WriteSection += (ReadSection = WriteSection);
   }
  //============================================================================
  }
  //............................................................................

  //Copy elements...............................................................
  template <class Type> void
  rlist <Type> ::copy_data(internal_container &cCopy, int sStart, int sStop) const
  //Copy elements directly from list data
  {
  int S1, S2;
  int SIZE = set_range(S1, S2, sStart, sStop), RequiredSection = 1;

  bool Direction = false;
  while ((RequiredSection *= 2) < SIZE) Direction = !Direction;

  if(!Direction) for (int I = 0; I < SIZE; I++)
  cCopy.actual_value(I) = internal_list_data.actual_value(short_modulo(I + S1));
  }
  //............................................................................

  //Order by reference..........................................................
  template <class Type> template <class Iterator2> void
  rlist <Type> ::pre_order_data(Iterator2 pPos, int sSize) const
  //Transposes reference list before using it to sort data
  {
  //For this to perform correctly, the n_shell array must contain all
  //numbers from 0 through 1 less than the number of elements as their object
  //values (which is why it is a private function.)  Here we start with
  //the first element and switch it with whatever element is at the
  //position given by the object value.  Once the first element has 0 as its
  //object value, we move to the 2nd element and do the same thing until it
  //has an element with an object value of 1, etc.  This performs no more
  //than one switch per each element in the array.  This function
  //basically undoes the sort operation.  After this function is complete,
  //the position value of each n_shell tells us where the element at that given
  //position should be on the sorted list.
  int P = 0;
  typename std::iterator_traits <Iterator2> ::value_type Temp;
  while (P < sSize - 1)
   {
  while (P != pPos[P].object)
    {
  Temp = pPos[pPos[P].object];
  pPos[pPos[P].object] = pPos[P];
  pPos[P] = Temp;
    }
  P++;
   }
  }

  //Order functions perform similar to pre_order_data, however we are looking
  //at position values here, and we also move the reference elements every time
  //we move a n_shell element.  This means that there will be no more
  //element switches than there are elements.

  template <class Type> template <class Iterator2, class Iterator3> void
  rlist <Type> ::n_order_data(Iterator2 lList, Iterator3 pPos, int sStart,
    int sStop) const
  //Orders list by reference positions
  {
  int P = 0, S;
  typename std::iterator_traits <Iterator2> ::value_type Temp;
  while (P < sStop - sStart - 1)
   {
  while (P != pPos[P].position)
    {
  Temp = *(lList + short_modulo(sStart + pPos[P].position));
  *(lList + short_modulo(sStart + pPos[P].position)) = *(lList + short_modulo(sStart + P));
  *(lList + short_modulo(sStart + P)) = Temp;

  S = pPos[pPos[P].position].position;
  pPos[pPos[P].position].position = pPos[P].position;
  pPos[P].position = S;
    }
  P++;
   }
  }

  template <class Type> template <class Iterator2, class Iterator3> void
  rlist <Type> ::n_internal_order_data(Iterator2 lList, Iterator3 pPos, int sStart,
    int sStop) const
  //Orders list by reference positions
  {
  int P = 0, S;
  typename internal_container::interim_type Temp;
  while (P < sStop - sStart - 1)
   {
  while (P != pPos[P].position)
    {
  Temp = *(lList + short_modulo(sStart + pPos[P].position));
  *(lList + short_modulo(sStart + pPos[P].position)) = *(lList + short_modulo(sStart + P));
  *(lList + short_modulo(sStart + P)) = Temp;

  S = pPos[pPos[P].position].position;
  pPos[pPos[P].position].position = pPos[P].position;
  pPos[P].position = S;
    }
  P++;
   }
  }

  template <class Type> template <class Iterator2, class Iterator3> void
  rlist <Type> ::internal_order_data(Iterator2 lList, Iterator3 pPos, int sStart,
    int sStop) const
  //Orders list by reference positions
  {
  int P = 0, S;
  typename internal_container::interim_type Temp;
  while (P < sStop - sStart - 1)
   {
  while (P != pPos[P])
    {
  Temp = *(lList + short_modulo(sStart + pPos[P]));
  *(lList + short_modulo(sStart + pPos[P])) = *(lList + short_modulo(sStart + P));
  *(lList + short_modulo(sStart + P)) = Temp;

  S = pPos[pPos[P]];
  pPos[pPos[P]] = pPos[P];
  pPos[P] = S;
    }
  P++;
   }
  }
  //............................................................................

  //Pre-sorting functions.......................................................
  template <class Type> template <class Shell, class IShell, class Iterator2>
    bool
  rlist <Type> ::pre_sort_data(Iterator2 iIterator, rlist <Type> ::
      transposer_container &tTrans, unsigned int bBegin, unsigned int eEnd,
    bool iIter, bool oOrig, bool iInv, bool sSelf, bool rRev, bool eEqual) const
  //Pre-sort reference data for transposing other data
  {
  //This function handles all pre-sorting operations for front-end
  //functions.  This takes into account sorting iterators, whether we are
  //sorting data from this list,  if the calling function intends to use
  //the results for an inverting operation, and whether the intended
  //operation will be used on the data in this list or not.
  int Size = eEnd - bBegin;
  if (!Size) return true;

  typename list_container <IShell> ::type I_Temp;
  typename list_container <Shell> ::type  Temp;

  if (iIter)
  //If we are sorting iterators we resize the iterator containers...
   {
  if (!check_capacity(I_Temp, Size)) return false;
  I_Temp.resize(Size);
   }

  else
  //...otherwise we resize the object containers.
   {
  if (!check_capacity(Temp, Size)) return false;
  Temp.resize(Size);
   }

  //Here we fill temporary containers with the data provided.  We also
  //sequentially number the containers so that we can find out where each
  //container moved after sorting.
  for (int I = 0; I < Size; I++)
   {
  if (iIter)
    {
  I_Temp[I] << (iIterator + (oOrig? short_modulo(I + bBegin) : (I + bBegin)));
  I_Temp[I] = I;
    }

  else
    {
  Temp[I] << *(iIterator + (oOrig? short_modulo(I + bBegin) : (I + bBegin)));
  Temp[I] = I;
    }
   }

  //We presort the lists of containers by the data value.
  if (iIter)
  rlist_clm_sort_auto(I_Temp.begin(), I_Temp.begin() + Size, 0, Size, rRev, eEqual);

  else
  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + Size, 0, Size, rRev, eEqual);

  //We set the size of the transposer.
  if (!check_capacity(tTrans, Size)) return false;
  tTrans.resize(Size);

  if (!oOrig && !iInv) for (int I = 0; I < Size; I++)
  //If we are not in inverted mode and are not using the original list
  //data then we copy the results into the transposer and also
  //sequentially number it.
   {
  if (iIter) tTrans[I] << I_Temp[I].position;
  else       tTrans[I] << Temp[I].position;
  tTrans[I] = I;
   }

  else if (!oOrig)
  //If we aren't using the original data, that means we are in inverted
  //mode, therefore we just copy the results into the transposer.
  if (iIter) for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].position;
  else       for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].position;

  else if (iInv && !sSelf)
  //If we are in inverted mode and are not performing this to change the
  //order of the data in this list then we just copy the results into
  //the transposer.
  if (iIter) for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].position;
  else       for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].position;

  else
  //If the other conditions were not met, that means that either we are
  //using this data to sort in normal mode, or we are sorting this list
  //in inverted mode.  In either case, we copy the results into the
  //transposer.
   {
  for (int I = 0; I < Size; I++)
    {
  if (iIter) tTrans[I] << I_Temp[I].position;
  else       tTrans[I] << Temp[I].position;
  tTrans[I] = I;
    }

  if (iInv)
  //If we are in inverted mode, that means we are inverting this list,
  //therefore we pre_order_data and refill the transposer with the
  //results.
    {
  pre_order_data(tTrans.begin(), Size);
  if (iIter) for (int I = 0; I < Size; I++) tTrans[I] << I_Temp[I].position;
  else       for (int I = 0; I < Size; I++) tTrans[I] << Temp[I].position;
    }
   }

  return true;
  }

  template <class Type> template <class Shell, class IShell, class Function2,
    class Iterator2>
    bool
  rlist <Type> ::f_pre_sort_data(Iterator2 iIterator, rlist <Type> ::
    transposer_container &tTrans, unsigned int bBegin, unsigned int eEnd,
    bool iIter, bool oOrig, bool iInv, bool sSelf, bool rRev, bool eEqual,
    Function2 fFunction) const
  //Pre-sort reference data for transposing other data using functor
  {
  //This is identical to pre_sort_data except where noted.
  int Size = eEnd - bBegin;
  if (!Size) return true;

  typename list_container <IShell> ::type I_Temp;
  typename list_container <Shell> ::type  Temp;

  if (iIter)
   {
  if (!check_capacity(I_Temp, Size)) return false;
  I_Temp.resize(Size);
   }

  else
   {
  if (!check_capacity(Temp, Size)) return false;
  Temp.resize(Size);
   }

  for (int I = 0; I < Size; I++)
   {
  if (iIter)
    {
  I_Temp[I] << (iIterator + (oOrig? short_modulo(I + bBegin) : (I + bBegin)));
  I_Temp[I] = I;
    }

  else
    {
  Temp[I] << *(iIterator + (oOrig? short_modulo(I + bBegin) : (I + bBegin)));
  Temp[I] = I;
    }
   }

  //We presort the containers with the functor.
  if (iIter)
  f_rlist_clm_sort_auto(I_Temp.begin(), I_Temp.begin() + Size, 0, Size, fFunction,
    rRev, eEqual);

  else
  f_rlist_clm_sort_auto(Temp.begin(), Temp.begin() + Size, 0, Size, fFunction,
    rRev, eEqual);

  if (!check_capacity(tTrans, Size)) return false;
  tTrans.resize(Size);

  if (!oOrig && !iInv) for (int I = 0; I < Size; I++)
   {
  if (iIter)  tTrans[I] << I_Temp[I].position;
  else        tTrans[I] << Temp[I].position;
  tTrans[I] = I;
   }

  else if (!oOrig)
  if (iIter)  for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].position;
  else        for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].position;

  else if (iInv && !sSelf)
  if (iIter)  for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].position;
  else        for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].position;

  else
   {
  for (int I = 0; I < Size; I++)
    {
  if (iIter)  tTrans[I] << I_Temp[I].position;
  else        tTrans[I] << Temp[I].position;
  tTrans[I] = I;
    }

  if (iInv)
    {
  pre_order_data(tTrans.begin(), Size);
  if (iIter)  for (int I = 0; I < Size; I++) tTrans[I] << I_Temp[I].position;
  else        for (int I = 0; I < Size; I++) tTrans[I] << Temp[I].position;
    }
   }

  return true;
  }
  //............................................................................
  //----------------------------------------------------------------------------

  //Duplicate removal assist functions------------------------------------------

  //First we find the range, then we copy either elements into d_n_shell or
  //iterators into id_n_shell.  Initially the comparison functions for these
  //objects base the comparison on the value of the object.  The d_n_shell or
  //id_n_shell are sorted first, therefore are put in order by element value.
  //We then start with the first element of the sorted list and compare the
  //object value with that of the next element.  If the elements pass the
  //equality comparison, the deletable flag is set for the second element.  The
  //second element position is incremented until an element different than the
  //first element is found, then that element becomes the first element, and the
  //second becomes the element following it.  This happens until the entire
  //array of d_n_shell or id_n_shell has been analyzed.  During analysis, the
  //sorting flag is set for each element.  After analysis, the list is sorted.
  //Since the sorting flag is set, they are sorted first by the deletable flag,
  //and then by the position value.  The resulting list gives us all of the
  //elements flagged for deleting at the beginning, which are in the order of
  //their position in the actual list of elements.  The container provided is
  //filled with the positions of the elements to be removed, and the number of
  //elements to be removed is returned.

  template <class Type> unsigned int
  rlist <Type> ::find_duplicates(position_container &pPos, int sStart, int sStop,
    bool eExclusive)
  //Finds duplicate elements
  {
  if (index.size() < 2) return 0;
  int S1, S2;
  int SIZE = set_range(S1, S2, sStart, sStop);
  if (S2 == S1) return 0;

  typename list_container <d_shell_type> ::type Temp;

  if (!check_capacity(Temp, SIZE)) return 0;
  Temp.resize(SIZE);

  for (int I = 0; I < SIZE; I++)
   {
  Temp[I] << *list_element(short_modulo(S1 + I));
  Temp[I] = short_modulo(S1 + I);
   }

  rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE,
    o_reverse_process(), false);

  int P1 = 0, P2 = 1;

  while (P2 < SIZE)
   {
  if (eExclusive && !(Temp[P2] == Temp[P1])) Temp[P1].deletable = true;

  while (Temp[P2] == Temp[P1])
    {
  Temp[P2].deletable = true;
  if (++P2 >= SIZE) break;
    }

  if (eExclusive && P2 == SIZE - 1) Temp[P2].deletable = true;
  P1 = P2++;
   }

  for (int I = 0; I < SIZE; I++) Temp[I].sorting = true;

  f_rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE,
    d_shell_type::final_sort, false, false);

  int P = 0;

  while ((P < SIZE) && Temp[P].deletable) P++;

  if (P == 0) return 0;

  if (!check_capacity(pPos, P)) return 0;
  pPos.resize(P);

  for (int I = 0; I < P; I++) pPos[I] = Temp[I].position;
  return P;
  }

  template <class Type> template <class SortFunction2, class FindFunction2> int
  rlist <Type> ::f_find_duplicates(position_container &pPos, int sStart, int sStop,
    SortFunction2 sSort, FindFunction2 fFind, bool eExclusive)
  //Finds duplicate elements
  {
  if (index.size() < 2) return 0;
  int S1, S2;
  int SIZE = set_range(S1, S2, sStart, sStop);
  if (S2 == S1) return 0;

  typename list_container <d_shell_type> ::type Temp;

  if (!check_capacity(Temp, SIZE)) return 0;
  Temp.resize(SIZE);

  for (int I = 0; I < SIZE; I++)
   {
  Temp[I] << *list_element(short_modulo(S1 + I));
  Temp[I] = short_modulo(S1 + I);
   }

  f_rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE, sSort,
    o_reverse_process(), false);

  int P1 = 0, P2 = 1;

  while (P2 < SIZE)
   {
  if (eExclusive && !EVALUATE_2(fFind, safety_convert(Temp[P2]), safety_convert(Temp[P1])))
  Temp[P1].deletable = true;

  while (EVALUATE_2(fFind, safety_convert(Temp[P2]), safety_convert(Temp[P1])))
    {
  Temp[P2].deletable = true;
  if (++P2 >= SIZE) break;
    }

  if (eExclusive && P2 == SIZE - 1) Temp[P2].deletable = true;
  P1 = P2++;
   }

  for (int I = 0; I < SIZE; I++) Temp[I].sorting = true;

  //NOTE: use of 'final_sort' prevents < comparison of actual elements
  f_rlist_clm_sort_auto(Temp.begin(), Temp.begin() + SIZE, 0, SIZE,
    d_shell_type::final_sort, false, false);

  int P = 0;

  while ((P < SIZE) && Temp[P].deletable) P++;

  if (P == 0) return 0;

  if (!check_capacity(pPos, P)) return 0;
  pPos.resize(P);

  for (int I = 0; I < P; I++) pPos[I] = Temp[I].position;
  return P;
  }

  template <class Type> template <class Iterator2> Iterator2
  rlist <Type> ::fast_remove(Iterator2 pPos, unsigned int sSize)
  //Removes elements
  {
  //Here we start with the first element to be removed as the read and
  //write positions.  We then increment the read position until we reach
  //the first element to be kept.  Once the element is found, we write and
  //increment the write position and find the next element to be kept.
  //Once we are done, the list size is set to the number of elements kept.
  if (sSize < 1) return pPos;
  int Write, Read, Remove = 0;
  Read = Write = pPos[Remove];
  int SIZE = index.size(), NewSize = SIZE - sSize, Offset = 0;

  while (Write < NewSize)
   {

  while (Read == pPos[Remove])
    {
  if (pPos[Remove] < index) Offset++;
  if (++Read >= SIZE) break;
  if (++Remove >= (signed) sSize) break;

  if (Remove != (signed) sSize - 1)
  while (pPos[Remove] == pPos[Remove - 1])
  if ((++NewSize >= SIZE) || (++Remove >= (signed) sSize - 1)) break;
  if (Read < index) Offset++;
    }

  if (Read >= SIZE) break;

  if (Write != Read)
    {
  release_element(Write);
  *list_element(Write) = *list_element(Read);
  clear_element(Read);
    }

  Write++;
  Read++;
   }

  index -= Offset;
  resize(NewSize);
  return pPos;
  }

  template <class Type> template <class Iterator2> Iterator2
  rlist <Type> ::fast_keep(Iterator2 pPos, unsigned int sSize)
  //Keeps elements
  {
  //Here we start with the first element as the write position.  Then we
  //go through and move the elements to be kept to the beginning of the
  //list and set the list size.
  int Write = 0, Keep = 0;
  int NewSize = sSize, Offset = 0;

  for (int I = 0; I < NewSize && Keep < (signed) sSize; I++)
   {
  if (pPos[Keep] <= index) Offset++;

  if (Keep < (signed) sSize - 1)
  while (pPos[Keep] == pPos[Keep + 1])
    {
  if (++Keep >= (signed) sSize - 1) break;
  NewSize--;
    }

  if (Write != pPos[Keep])
    {
  release_element(Write);
  *list_element(Write) = *list_element(pPos[Keep]);
  clear_element(pPos[Keep]);
    }

  Write++;
  Keep++;
   }

  index = Offset;
  resize(NewSize);
  return pPos;
  }
  //----------------------------------------------------------------------------

  template <class Type> inline unsigned int
  rlist <Type> ::allocate(unsigned int sSize)
  //Allocation function
  {
  unsigned int Size = sSize;

  if (!check_capacity(internal_list_data, Size))
  Size = internal_list_data.max_size();

  return internal_list_data.resize(Size);
  }

  //Access functions============================================================
  //Iterator access-------------------------------------------------------------
  template <class Type> inline typename rlist <Type> ::iterator
  rlist <Type> ::list_element(unsigned int pPos)
  //Random access function
  { return internal_list_data.element(pPos); }

  template <class Type> inline typename rlist <Type> ::const_iterator
  rlist <Type> ::list_element(unsigned int pPos) const
  //Random access function
  { return internal_list_data.element(pPos); }

  template <class Type> inline void
  rlist <Type> ::release_element(unsigned int pPos)
  //Element-releasing function
  { internal_list_data.release_element(pPos); }

  template <class Type> inline void
  rlist <Type> ::clear_element(unsigned int pPos)
  //Element-clearing function
  { internal_list_data.clear_element(pPos); }
  //----------------------------------------------------------------------------

  //Reference access------------------------------------------------------------
  template <class Type> inline typename rlist <Type> ::assign_type
  rlist <Type> ::list_reference(unsigned int pPos)
  //Random access function
  { return internal_list_data[pPos]; }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::list_reference(unsigned int pPos) const
  //Random access function
  { return internal_list_data[pPos]; }

  template <class Type> inline typename rlist <Type> ::assign_type
  rlist <Type> ::default_element()
  //Returns default element
  { return reference_dummy = base_type(); }

  template <class Type> inline typename rlist <Type> ::const_return_type
  rlist <Type> ::default_element() const
  //Returns default element
  { return reference_dummy = base_type(); }
  //----------------------------------------------------------------------------
  //============================================================================

  //Converters------------------------------------------------------------------
  template <class Type> template <class Type2> inline const Type2
  &rlist <Type> ::safety_convert(const Type2 &oObj)
  //Assists functor sorting by returning data as const
  { return oObj; }
  //----------------------------------------------------------------------------

  template <class Type> inline int
  rlist <Type> ::short_modulo(int pPos) const
  //Returns valid array pos from int
  {
  //This version is slightly faster than list_modulo because here we don't use
  //the % operator.  The position argument must be between the negative of the
  //Size of the list to one less than twice the size of the list (which is
  //the reason this is a private function.)  For this reason this is only
  //used internally after parsing range arguments with list_modulo.
  if (pPos >= 0)
  if (pPos >= (signed) index.size()) return pPos - index.size();
  else                               return pPos;
  else                               return pPos + index.size();
  }
//==============================================================================

//internal_index function bodies================================================
  //Information=================================================================
  template <class Type> inline unsigned int
  rlist <Type> ::internal_index::size() const
  //Returns size
  { return size_value; }

  template <class Type> inline unsigned int
  rlist <Type> ::internal_index::max_size() const
  //Returns max size
  { return max_value; }
  //============================================================================

  //Limit information===========================================================
  template <class Type> inline bool
  rlist <Type> ::internal_index::at_min() const
  //Returns true if size is 0
  { return !size_value; }

  template <class Type> inline bool
  rlist <Type> ::internal_index::at_max() const
  //Returns true if size is equal to max
  { return max_value && size_value == max_value; }

  template <class Type> inline bool
  rlist <Type> ::internal_index::at_begin() const
  //Returns true if index is at beginning
  { return size_value? !index_value : false; }

  template <class Type> inline bool
  rlist <Type> ::internal_index::at_end() const
  //Returns true if index is at end
  { return index_value >= size_value - 1; }
  //============================================================================

  //Endpoint functions==========================================================
  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::set_to_begin()
  //Sets index to beginning
  {
  index_value = 0;
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::set_to_end()
  //Sets index to end
  {
  index_value = short_modulo(-1);
  return *this;
  }
  //============================================================================

  //Index operators=============================================================
  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator = (int iIndex)
  //Sets index
  {
  index_value = list_modulo(iIndex);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator = (const internal_index &iIndex)
  //Sets index
  {
  //The above operator will work fine in this case, however we define this
  //operator so that the default operator does not overwrite our size/max
  index_value = list_modulo(iIndex.index_value);
  return *this;
  }

  template <class Type> inline int
  rlist <Type> ::internal_index::operator ++ (int)
  //Increments index (postfix)
  {
  if (size_value == 0) return 0;
  index_value = short_modulo(index_value + 1);
  return short_modulo(index_value - 1);
  }

  template <class Type> inline int
  rlist <Type> ::internal_index::operator ++ ()
  //Increments index (prefix)
  {
  if (size_value == 0) return 0;
  return (index_value = short_modulo(index_value + 1));
  }

  template <class Type> inline int
  rlist <Type> ::internal_index::operator -- (int)
  //Decrements index (postfix)
  {
  if (size_value == 0) return 0;
  index_value = short_modulo(index_value - 1);
  return short_modulo(index_value + 1);
  }

  template <class Type> inline int
  rlist <Type> ::internal_index::operator -- ()
  //Decrements index (prefix)
  {
  if (size_value == 0) return 0;
  return (index_value = short_modulo(index_value - 1));
  }
  //============================================================================

  //Arithmetic operators========================================================
  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator += (int vVal)
  //Add, correct, and equal
  {
  index_value = list_modulo(index_value + vVal);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator -= (int vVal)
  //Subtract, correct, and equal
  {
  index_value = list_modulo(index_value - vVal);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator *= (int vVal)
  //Multiply, correct, and equal
  {
  index_value = list_modulo(index_value * vVal);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator /= (int vVal)
  //Divide, correct, and equal
  {
  index_value = (vVal == 0)? 0 : list_modulo(index_value / vVal);
  return *this;
  }

  template <class Type> inline typename rlist <Type> ::internal_index
  &rlist <Type> ::internal_index::operator %= (int vVal)
  //Modulus, correct, and equal
  {
  index_value = (vVal == 0)? 0 : list_modulo(index_value % vVal);
  return *this;
  }
  //============================================================================

  //Other operators=============================================================
  template <class Type> inline int
  rlist <Type> ::internal_index::operator [] (int vVal) const
  //Returns valid index position
  { return list_modulo(vVal); }

  template <class Type> inline
  rlist <Type> ::internal_index::operator int() const
  //Conversion operator
  { return index_value; }
  //============================================================================

  template <class Type>
  rlist <Type> ::internal_index::internal_index(unsigned int mMax) :
  index_value(0), size_value(0), max_value(mMax)  { }
  //Constructor

  template <class Type>
  rlist <Type> ::internal_index::internal_index(const internal_index &eEqual) :
  index_value(eEqual.index_value), size_value(eEqual.size_value),
  max_value(eEqual.max_value) { }
  //Constructor

  //Private functions-----------------------------------------------------------
  template <class Type> inline unsigned int
  rlist <Type> ::internal_index::set_size(unsigned int sSize)
  //Sets size, adjusts index
  {
  //If the requested size is less than the max then we set the new size to
  //the max.  If the max is 0, we set the new size to that requested.  If
  //the index falls out of the range of the size we set it to the new
  //endpoint.  In case we set the size to 0, we set the index to 0 also.
  size_value = max_value? LO(max_value, (int) sSize) : (int) sSize;
  *this = index_value;
  return size_value;
  }

  template <class Type> inline unsigned int
  rlist <Type> ::internal_index::set_max(unsigned int mMax)
  //Sets max size
  {
  //If the max is less than the current size, we reduce the current size
  //to the max.  We adjust the index as above.
  max_value = mMax;
  LTME(size_value, (max_value? max_value : size_value));
  *this = index_value;
  return max_value;
  }

  template <class Type> inline int
  rlist <Type> ::internal_index::list_modulo(int iIndex) const
  //Returns valid array position (for mod of externally provided values)
  {
  if (size_value <= 1) return 0;
  while (iIndex < 0) iIndex += size_value;
  return iIndex % size_value;
  }

  template <class Type> inline int
  rlist <Type> ::internal_index::short_modulo(int iIndex) const
  //Returns valid array position (shortened for internal use)
  {
  //If the value is greater than 0 and greater than the size, we just
  //subtract the size.  It is greater than zero otherwise then we just
  //return the value.  If it is less than zero we just add the size.
  if (iIndex >= 0)
  if (iIndex >= size_value) return iIndex - size_value;
  else return iIndex;
  else return iIndex + size_value;
  }
  //----------------------------------------------------------------------------

template <class Type> typename rlist <Type> ::base_type
rlist <Type> ::reference_dummy;
//==============================================================================
}

#endif
//END Source Section############################################################
