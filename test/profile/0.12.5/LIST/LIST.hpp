/*============================================================================*\
 *CList. Circular list with complex sorting.                                  *
 *Copyright (C) 2006 Kevin P. Barry (ta0kira)                                 *
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

/*____________________________________________________________________________*
  This file is the header for the class CList.  This is a list class that
  supports sorting, circular list positions, find functions, various functions
  with functor support, various sorting functions allowing sorting based on
  external references and sorting external arrays based on this list, and
  element iteration.

  -General Comments-

  Template Parameter: see LIST_TYPES.hpp for specifics on the type provided as
  the template argument.  The BASE_TYPE must have the following properties:
  publicly constructable, default constructable, copy constructable, and
  assignable.

  List Processing Functions: many of these functions require the argument type
  to be const comparable by < and ==.

  Process Ranges: When using ranges provided as arguments, they are first
  parsed for valid list positions.  For example; for a list of size 10, you
  give a range of -6 to 13.  These are parsed to be 4 to 3.  The list is
  processed from 4 to 3 crossing the end of the list.  Ranges always include
  the endpoints; removing elements X to Y will also remove X and Y, etc.  Even
  when RevProcess is set, ranges are taken as first arg to second arg.

  Index: Index manages the index point of the list.  It is mutable, therefore
  in a const CList it can be changed.  This allows easy iteration through a
  list that is const.

  Element Access Functions: when accessing an element, if the list size is 0,
  a reference is returned to an internal object that has the value of a
  BASE_TYPE object made equal to the result of the default constructor.  If
  a position is given when accessing an element, the position is parsed to a
  value within the range of elements.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2003-2005 Kevin P. Barry

//==============================================================================
#ifndef LIST_HPP
#define LIST_HPP BC
#include <iterator>
#include <cstdlib>
#include "../FUNCTOR/FUNCTOR.hpp"
#include "LIST_ASSIST.hpp"
#include "LIST_TYPES.hpp"
#include "INDEX.hpp"

namespace LIST_HPP
{
//Constant integers-------------------------------------------------------------
//Use with CList to obtain FIRST or LAST element
const int FIRST =  0; //Used for first position of list
const int LAST  = -1; //Used for last position of list

const int NOT_FOUND = -1; //Return value if find operation fails
//END---------------------------------------------------------------------------

//Lists=========================================================================
//Class CList-------------------------------------------------------------------
//Circular list class
template <class Type>
class CList
{
public:
        //Typedefs==============================================================
        typedef typename ListTypes <Type> ::BASE_TYPE         BASE_TYPE;
        //Base type of elements

        typedef typename ListTypes <Type> ::POINTER_TYPE      POINTER_TYPE;
        //Pointer to element base type

        typedef typename ListTypes <Type> ::ASSIGN_TYPE       ASSIGN_TYPE;
        //Assignable argument type

        typedef typename ListTypes <Type> ::RETURN_TYPE       RETURN_TYPE;
        //Return argument type

        typedef typename ListTypes <Type> ::CONST_RETURN_TYPE CONST_RETURN_TYPE;
        //Constant return argument type

        typedef typename ListTypes <Type> ::PULL_TYPE         PULL_TYPE;
        //Return argument type for pull functions

        typedef typename LIST_CONTAINER <BASE_TYPE> ::TYPE    Container;
        //Container type

        typedef char                                          Flag;
        //Option flag
        //======================================================================

        //Constructors----------------------------------------------------------
        CList(unsigned int = 0);
        //Constructor
        //Max size

        CList(const CList&);
        //Copy constructor
        //----------------------------------------------------------------------

        //Copy data=============================================================

        /*____________________________________________________________________*
          -Copy Functions-

          CopyFrom: this function replaces the entire list with a sequence of
          elements from another list.

          CopyFrom(iterator): this function replaces the entire list with the
          number of elements provided by a pointer to an array of elements.

          FCopyFrom: these functions allow copying of elements that are not
          the same as the list type by preprocessing them with a functor.
         *____________________________________________________________________*/

                CList
        &CopyFrom(const CList&, int = FIRST, int = LAST);
        //Erase list and copy elements
        //List to copy from, list start position, list stop position

        template <class Iterator2>
                CList
        &CopyFrom(Iterator2, unsigned int);
        //Erase list and copy elements
        //Array of elements, size

        template <class Type2, class Function1>
                CList
        &FCopyFrom(const CList <Type2>&, Function1, int = FIRST, int = LAST);
        //Erase list and copy elements with functor pre-processing
        //List to copy from, pre-process functor, list start position,
        //list stop position

        template <class Iterator2, class Function1>
                CList
        &FCopyFrom(Iterator2, unsigned int, Function1);
        //Erase list and copy elements with functor pre-processing
        //Array of elements, size, pre-process functor
        //======================================================================

        //List maintenance======================================================

        /*____________________________________________________________________*
          -Add Functions-

          These functions add elements to the end of the list.
         *____________________________________________________________________*/

        //Add single element----------------------------------------------------
        template <class Type2>
                bool
        Add(const Type2&);
        //Add element
        //Element

                RETURN_TYPE
        Add();
        //Increase size if possible
        //Returns reference to last element
        //----------------------------------------------------------------------

        //Add multiple elements-------------------------------------------------
                bool
        Add(const CList&, int = FIRST, int = LAST);
        //Add elements
        //List to copy from

        template <class Iterator2>
                bool
        Add(Iterator2, unsigned int);
        //Add elements
        //Array of elements, size

        template <class Iterator2>
                unsigned int
        Add(Iterator2, Iterator2);
        //Add elements
        //Begin iterator, end iterator

        template <class Type2, class Function1>
                bool
        FAdd(const CList <Type2>&, Function1, int = FIRST, int = LAST);
        //Add elements with functor pre-processing
        //List to copy from, pre-process functor

        template <class Iterator2, class Function1>
                bool
        FAdd(Iterator2, unsigned int, Function1);
        //Add elements with functor pre-processing
        //Array of elements, size, pre-process functor

        template <class Iterator2, class Function1>
                unsigned int
        FAdd(Iterator2, Iterator2, Function1);
        //Add elements using a functor to preprocess
        //Begin iterator, end iterator
        //----------------------------------------------------------------------

        /*____________________________________________________________________*
          -Insert Functions-

          These functions insert elements at the given position.
         *____________________________________________________________________*/

        //Insert single element-------------------------------------------------
        template <class Type2>
                bool
        Insert(int, const Type2&);
        //Insert element at position
        //Element position, element

                RETURN_TYPE
        Insert(int);
        //Insert default element at position if possible
        //Returns element at position specified
        //----------------------------------------------------------------------

        //Insert multiple elements----------------------------------------------
                bool
        Insert(int, const CList&, int = FIRST, int = LAST);
        //Insert multiple elements
        //Insert position, element list, list start position, list stop position

        template <class Iterator2>
                bool
        Insert(int, Iterator2, unsigned int);
        //Insert multiple elements
        //Insert position, element array, number of elements

        template <class Iterator2>
                unsigned int
        Insert(int, Iterator2, Iterator2);
        //Insert multiple elements
        //Insert position, begin iterator, end iterator

        template <class Type2, class Function1>
                bool
        FInsert(int, const CList <Type2>&, Function1, int = FIRST, int = LAST);
        //Insert multiple elements with functor pre-processing
        //Insert position, element list, list start position,
        //list stop position, pre-process functor

        template <class Iterator2, class Function1>
                bool
        FInsert(int, Iterator2, unsigned int, Function1);
        //Insert multiple elements with functor pre-processing
        //Insert position, element array, number of elements,
        //pre-process functor

        template <class Iterator2, class Function1>
                unsigned int
        FInsert(int, Iterator2, Iterator2, Function1);
        //Insert multiple elements with functor pre-processing
        //Insert position, begin iterator, end iterator
        //----------------------------------------------------------------------

        //Replace elements------------------------------------------------------

        /*____________________________________________________________________*
          -Replace Functions-

          Replace: this function replaces a single element with the given
          element.

          Clear: this function replaces all elements with the default element.
         *____________________________________________________________________*/

        template <class Type2>
                CList
        &Replace(int, const Type2&);
        //Replace element
        //Element position, element

                CList
        &Clear();
        //Set all elements equal to a default
        //----------------------------------------------------------------------

        //Remove elements-------------------------------------------------------

        /*____________________________________________________________________*
          -Remove Functions-

          These functions remove elements based on their position, based on a
          list of positions, based on a range (endpoints are included), or
          based on the equality comparison with another element.
         *____________________________________________________________________*/

                CList
        &Remove(int);
        //Remove specified element
        //Element position

        template <class Type2>
                CList
        &Remove(CList <Type2>&, int = FIRST, int = LAST);
        //Remove specified elements
        //Element position list, list start position, list stop position

        template <class Iterator2>
                CList
        &Remove(Iterator2, unsigned int);
        //Remove specified elements
        //Element position array, array size

                CList
        &Remove(int, int);
        //Remove elements in range
        //Start position, stop position

        template <class Type2>
                CList
        &RemoveElement(const Type2&);
        //Remove matching elements
        //Element to remove

        template <class Type2, class Function2>
                CList
        &FRemoveElement(const Type2&, Function2);
        //Remove matching elements with functor comparison
        //Element to remove, functor
        //----------------------------------------------------------------------

        //Keep elements---------------------------------------------------------

        /*____________________________________________________________________*
          -Keep Functions-

          These functions keep elements based on their position, based on a
          list of positions, based on a range (endpoints are included), or
          based on the equality comparison with another element.
         *____________________________________________________________________*/

                CList
        &Keep(int);
        //Keep specified element
        //Element position

        template <class Type2>
                CList
        &Keep(CList <Type2>&, int = FIRST, int = LAST);
        //Keep specified elements
        //Element position list, list start position, list stop position

        template <class Iterator2>
                CList
        &Keep(Iterator2, unsigned int);
        //Keep specified elements
        //Element position array, array size

                CList
        &Keep(int, int);
        //Keep elements in range
        //Start position, stop position

        template <class Type2>
                CList
        &KeepElement(const Type2&);
        //Keep matching elements
        //Element to remove

        template <class Type2, class Function2>
                CList
        &FKeepElement(const Type2&, Function2);
        //Keep matching elements with functor comparison
        //Element to remove, functor
        //----------------------------------------------------------------------
        //======================================================================

        /*____________________________________________________________________*
          -Retrieval Functions-

          Get: these functions allow access to an element at the given
          position.

          Hold: these functions allow access to an element at the given
          position and set the index point to the given position.

          First: these functions allow access to the first element.

          HoldFirst: these functions allow access to the first element and
          set the index point to the beginning of the list.

          Last: these functions allow access to the last element.

          HoldLast: these functions allow access to the last element and set
          the index point to the end of the list.

          Current: these functions allow access to the element at the current
          index point.

          Next: these functions allow access to the element at the current
          index point and post-increment the index position.

          Previous: these functions pre-decrement the index position and then
          give access to the element at the current index point.
         *____________________________________________________________________*/

        //Get values (if size == 0 default element is given)====================
        //Provide position------------------------------------------------------
        inline
                const CList
        &Get(int, ASSIGN_TYPE) const;
        //Get element
        //Element position, variable to set equal

        inline
                RETURN_TYPE
        Get(int);
        //Get element
        //Element position, returns element reference

        inline
                CONST_RETURN_TYPE
        Get(int) const;
        //Get element
        //Element position, returns element reference

        inline
                const CList
        &Hold(int, ASSIGN_TYPE) const;
        //Get element, set index
        //Element position, variable to set equal

        inline
                RETURN_TYPE
        Hold(int);
        //Get element, set index
        //Element position, returns element reference

        inline
                CONST_RETURN_TYPE
        Hold(int) const;
        //Get element, set index
        //Element position, returns element reference
        //----------------------------------------------------------------------

        //Get first element-----------------------------------------------------
        inline
                const CList
        &First(ASSIGN_TYPE) const;
        //Get first element
        //Variable to set equal

        inline
                RETURN_TYPE
        First();
        //Get first element
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        First() const;
        //Get first element
        //Returns element reference

        inline
                const CList
        &HoldFirst(ASSIGN_TYPE) const;
        //Get first element, set index
        //Variable to set equal

        inline
                RETURN_TYPE
        HoldFirst();
        //Get first element, set index
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        HoldFirst() const;
        //Get first element, set index
        //Returns element reference
        //----------------------------------------------------------------------

        //Get last element------------------------------------------------------
        inline
                const CList
        &Last(ASSIGN_TYPE) const;
        //Get last element
        //Variable to set equal

        inline
                RETURN_TYPE
        Last();
        //Get last element
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        Last() const;
        //Get last element
        //Returns element reference

        inline
                const CList
        &HoldLast(ASSIGN_TYPE) const;
        //Get last element, set index
        //Variable to set equal

        inline
                RETURN_TYPE
        HoldLast();
        //Get last element, set index
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        HoldLast() const;
        //Get last element, set index
        //Returns element reference
        //----------------------------------------------------------------------

        //Get current element---------------------------------------------------
        inline
                const CList
        &Current(ASSIGN_TYPE) const;
        //Get current element
        //Variable to set equal

        inline
                RETURN_TYPE
        Current();
        //Get current element
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        Current() const;
        //Get current element
        //Returns element reference
        //----------------------------------------------------------------------

        //Get current element, increment index----------------------------------
        inline
                const CList
        &Next(ASSIGN_TYPE) const;
        //Get current element
        //Variable to set equal

        inline
                RETURN_TYPE
        Next();
        //Get current element
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        Next() const;
        //Get current element
        //Returns element reference
        //----------------------------------------------------------------------

        //Decrement index, get current element----------------------------------
        inline
                const CList
        &Previous(ASSIGN_TYPE) const;
        //Get previous element
        //Variable to set equal

        inline
                RETURN_TYPE
        Previous();
        //Get previous element
        //Returns element reference

        inline
                CONST_RETURN_TYPE
        Previous() const;
        //Get previous element
        //Returns element reference
        //----------------------------------------------------------------------
        //======================================================================

        //Get value and remove element (if size == 0 default element is given)==

        /*____________________________________________________________________*
          -Pull Functions-

          Pull: these functions remove and return the element at the given
          position.

          PullFirst: these functions remove and return the first element.

          PullLast: these functions remove and return the last element.

          PullCurrent: these functions remove and return the element at the
          current index position.

          PullHold: these functions remove and return the element at the given
          position and set the index position.
         *____________________________________________________________________*/

        //Remove and give element at given position-----------------------------
        inline
                CList
        &Pull(int, ASSIGN_TYPE);
        //Get and remove element
        //Element position, variable to set equal

        inline
                PULL_TYPE
        Pull(int);
        //Get and remove element
        //Element position, returns element
        //----------------------------------------------------------------------

        //Remove and give first element-----------------------------------------
        inline
                CList
        &PullFirst(ASSIGN_TYPE);
        //Get and remove first element
        //Variable to set equal

        inline
                PULL_TYPE
        PullFirst();
        //Get and remove first element
        //Returns element
        //----------------------------------------------------------------------

        //Remove and give last element------------------------------------------
        inline
                CList
        &PullLast(ASSIGN_TYPE);
        //Get and remove last element
        //Variable to set equal

        inline
                PULL_TYPE
        PullLast();
        //Get and remove last element
        //Returns element
        //----------------------------------------------------------------------

        //Remove and give current element---------------------------------------
        inline
                CList
        &PullCurrent(ASSIGN_TYPE);
        //Get and remove current element
        //Variable to set equal

        inline
                PULL_TYPE
        PullCurrent();
        //Get and remove current element
        //Returns element
        //----------------------------------------------------------------------

        //Remove and give current element, set index----------------------------
        inline
                CList
        &PullHold(int, ASSIGN_TYPE);
        //Get and remove element, set index
        //Variable to set equal

        inline
                PULL_TYPE
        PullHold(int);
        //Get and remove element, set index
        //Returns element
        //----------------------------------------------------------------------
        //======================================================================

        //Find functions========================================================

        /*____________________________________________________________________*
          -Find Functions-

          FindFrom: this function returns the position of the given element.
          If it isn't found, -1 is returned.

          FindFrom(iterator): this function places the positions of all found
          occurences of the given element in the given array.  This array must
          be allocated to the correct size first by using NumberFrom.

          NumberFrom: this function returns the number of elements matching
          the given element.

          Find/Number: these functions correspond to FindFrom/NumberFrom.  If
          RevFind is true, these functions find/number from the end to the
          beginning.
         *____________________________________________________________________*/

        //Find from position functions------------------------------------------
        template <class Type2>
                int
        FindFrom(const Type2&, int) const;
        //Finds first occurence starting at given position
        //Object to find, start position, returns position

        template <class Type2, class Iterator2>
                int
        FindFrom(const Type2&, int, Iterator2) const;
        //Finds all occurences from given position
        //Object to find, start position, pointer for position array return,
        //returns number found

        template <class Type2>
                int
        NumberFrom(const Type2&, int) const;
        //Finds number of occurences starting at given position
        //Object to find, start position, returns number found
        //----------------------------------------------------------------------

        //Overloads for find from end-------------------------------------------
        template <class Type2> inline
                int
        Find(const Type2&) const;
        //Finds first occurence
        //Object to find, returns position

        template <class Type2, class Iterator2> inline
                int
        Find(const Type2&, Iterator2) const;
        //Finds all occurences
        //Object to find, pointer for position array return,
        //returns number found

        template <class Type2> inline
                int
        Number(const Type2&) const;
        //Finds number of occurences
        //Object to find, returns number found
        //----------------------------------------------------------------------

        /*____________________________________________________________________*
          -Functor Find Functions-

          These functions correspond to the find functions above using a
          functor to preprocess the list elements.  A functor is added as the
          last argument.
         *____________________________________________________________________*/

        //Functor pre-processing find from position functions-------------------
        template <class Type2, class Function2>
                int
        FFindFrom(const Type2&, int, Function2) const;
        //Finds first occurence starting at given position
        //Object to find, start position, comparison functor, returns position

        template <class Type2, class Function2, class Iterator2>
                int
        FFindFrom(const Type2&, int, Iterator2, Function2) const;
        //Finds all occurences
        //Object to find, start position, pointer for position array return,
        //pre-process functor, returns number found

        template <class Type2, class Function2>
                int
        FNumberFrom(const Type2&, int, Function2) const;
        //Finds number of occurences starting at given position
        //Object to find, start position, comparison functor, returns number
        //found
        //----------------------------------------------------------------------

        //Overloads for functor find from end-----------------------------------
        template <class Type2, class Function2> inline
                int
        FFind(const Type2&, Function2) const;
        //Finds first occurence
        //Object to find, comparison functor, returns position

        template <class Type2, class Function2, class Iterator2> inline
                int
        FFind(const Type2&, Iterator2, Function2) const;
        //Finds all occurences
        //Object to find, pointer for position array return, comparison functor,
        //returns number found

        template <class Type2, class Function2> inline
                int
        FNumber(const Type2&, Function2) const;
        //Finds number of occurences
        //Object to find, comparison functor, returns number found
        //----------------------------------------------------------------------
        //======================================================================

        //List processing functions=============================================

        /*____________________________________________________________________*
          -Sort Functions-

          Sort: this places elements in order based on comparison.

          FSort: this sorts elements based on the results of functor
          preprocessing of elements.

          RSort: this uses an external iterator as a reference for sorting;
          the element swaps that would take place to sort the reference will
          be applied to the list, but the reference will not be changed.

          CSort: this operates the same as RSort, however if there are not
          enough elements in the reference list then no action will be taken.
          an offset can be provided after the range arguments.

          FRSort/FCSort: functor versions of RSort and CSort.

          RMasterSort/CMasterSort: like RSort/CSort except in this case the
          reference is sorted based on this list.

          FRMasterSort/FCMasterSort: functor versions of RMasterSort and
          CMasterSort.
         *____________________________________________________________________*/

        //Sort functions--------------------------------------------------------
        //Default sort..........................................................
                CList
        &Sort(int = FIRST, int = LAST);
        //Sorts using linear merge sort
        //Start position, stop position

        template <class Function2>
                CList
        &FSort(Function2, int = FIRST, int = LAST);
        //Sorts using linear merge sort using functor pre-comparison
        //Pre-comparison functor, start position, stop position
        //......................................................................

        //Sort with external references.........................................
        template <class Iterator2>
                CList
        &RSort(Iterator2, int = FIRST, int = LAST);
        //Sorts using linear merge sort based on reference
        //Sort reference, start position, stop position

        template <class Type2>
                CList
        &CSort(const CList <Type2>&, int = FIRST, int = LAST, int = 0);
        //Sorts using linear merge sort based on reference
        //Sort reference, start position, stop position,
        //reference start position

        template <class Function2, class Iterator2>
                CList
        &FRSort(Iterator2, Function2, int = FIRST, int = LAST);
        //Sorts using linear merge sort based on reference using functor
        //Sort reference, start position, stop position

        template <class Function2, class Type2>
                CList
        &FCSort(const CList <Type2>&, Function2, int = FIRST, int = LAST,
                int = 0);
        //Sorts using linear merge sort based on reference using functor
        //Sort reference, start position, stop position,
        //reference start position
        //......................................................................

        //Master sorting functions..............................................
        template <class Iterator2>
                const CList
        &RMasterSort(Iterator2, int = FIRST, int = LAST) const;
        //Sorts reference using this as a reference
        //Array to sort, start position, stop position

        template <class Type2>
                const CList
        &CMasterSort(CList <Type2>&, int = FIRST, int = LAST, int = 0) const;
        //Sorts reference using this as a reference
        //Sort reference, start position, stop position,
        //reference start position

        template <class Function2, class Iterator2>
                const CList
        &FRMasterSort(Iterator2, Function2, int = FIRST, int = LAST) const;
        //Sorts reference using this as a reference using functor
        //Array to sort, start position, stop position

        template <class Function2, class Type2>
                const CList
        &FCMasterSort(CList <Type2>&, Function2, int = FIRST, int = LAST,
                      int = 0) const;
        //Sorts reference using this as a reference using functor
        //Sort reference, start position, stop position,
        //reference start position
        //......................................................................

        //Verify order..........................................................
                bool
        Verify(int = FIRST, int = LAST) const;
        //Verifies order
        //Start position, stop position

        template <class Function2>
                bool
        FVerify(Function2, int = FIRST, int = LAST) const;
        //Verifies order using functor
        //Pre-comparison functor, start position, stop position
        //......................................................................
        //----------------------------------------------------------------------

        /*____________________________________________________________________*
          -Other List Process Functions-

          Reverse: this reverses the order of elements.

          Randomize: this randomizes the order of elements.

          Shift: this shifts elements.

          RemoveDuplicates: this removes duplicate elements based on equality
          comparison.

          RemoveDuplicates(list): this does the same as RemoveDuplicates, but
          records the  positions of the removed elements.

          FRemoveDuplicates: these functions correspond to RemoveDuplicates
          with functor pre-comparisons.
         *____________________________________________________________________*/

        //Reverse elements------------------------------------------------------
                CList
        &Reverse(int = FIRST, int = LAST);
        //Reverses order of elements
        //Start position, stop position
        //----------------------------------------------------------------------

        //Randomize order-------------------------------------------------------
                CList
        &Randomize(int = FIRST, int = LAST);
        //Randomizes order of items
        //Start position, stop position
        //----------------------------------------------------------------------

        //Shift elements--------------------------------------------------------
                CList
        &Shift(int, int = FIRST, int = LAST);
        //Shifts elements
        //Number of moves, start position, stop position
        //----------------------------------------------------------------------

        //Remove duplicate elements---------------------------------------------
                CList
        &RemoveDuplicates(int = FIRST, int = LAST);
        //Removes all duplicate elements
        //Start position, stop position

        template <class Type2>
                CList
        &RemoveDuplicates(CList <Type2>&, int = FIRST, int = LAST);
        //Removes all duplicate elements, stores positions of removed elements
        //Element return list, start position, stop position

        template <class SortFunction2, class FindFunction2>
                CList
        &FRemoveDuplicates(SortFunction2, FindFunction2, int = FIRST,
                           int = LAST);
        //Removes all duplicate elements
        //Sort functor, find functor

        template <class SortFunction2, class FindFunction2, class Type2>
                CList
        &FRemoveDuplicates(CList <Type2>&, SortFunction2, FindFunction2,
                           int = FIRST, int = LAST);
        //Removes all duplicate elements, stores positions of removed elements
        //Element return list, sort functor, find functor
        //----------------------------------------------------------------------
        //======================================================================

        //Size operations=======================================================
        inline
                unsigned int
        Size() const;
        //Returns size of list
        //Returns size

        inline
                int
        SectionSize(int = FIRST, int = LAST) const;
        //Returns size of element range
        //Start position, stop position

        inline
                unsigned int
        Resize(unsigned int = 0);
        //Sets size of list
        //Size, returns new size

                bool
        Increment(unsigned int = 1);
        //Increments size if possible
        //Returns true if size is changed

                bool
        Decrement(unsigned int = 1);
        //Decrements size if possible
        //Returns true if size is changed

        inline
                unsigned int
        Max() const;
        //Return max size
        //Returns max

        inline
                unsigned int
        NewMax(unsigned int = 0);
        //Sets new max size
        //Max, returns new max

                CList
        &Reset(unsigned int = 0);
        //Clears list, sets max size
        //Max size (0 = open ended)
        //======================================================================

        //Operators=============================================================
                CList
        &operator = (const CList&);
        //Assignment operator
        //CList to copy from

                CList
        &operator = (CONST_RETURN_TYPE);
        //Assignment operator
        //Replacement element

        inline
                RETURN_TYPE
        operator [] (int);
        //Returns element reference
        //Position, returns element reference

        inline
                CONST_RETURN_TYPE
        operator [] (int) const;
        //Returns element reference
        //Position, returns element reference

        inline
                CList
        &operator >> (int);
        //Shift elements forward

        inline
                CList
        &operator << (int);
        //Shift elements reverse

        inline
                int
        operator ++ (int);
        //Increments index (postfix)
        //Returns current index

        inline
                int
        operator ++ ();
        //Increments index (prefix)
        //Returns new index

        inline
                int
        operator -- (int);
        //Decrements index (postfix)
        //Returns current index

        inline
                int
        operator -- ();
        //Decrements index (prefix)
        //Returns new index
        //======================================================================

        //Flags=================================================================

        /*____________________________________________________________________*
          -Option Flags-

          RevProcess: this makes list processing functions process in reverse.

          RevEquals: this makes sorting functions reverse the order of like
          elements against the direction given by RevProcess.

          RevFind: this makes search functions process in reverse. (mutable.)

          CrossEndsFind: this allows FindFrom functions to cross the ends of
          the list.  If false, these functions stop at the end. (mutable.)

          IteratorProcess: this makes processing functions process iterators
          first, then transpose the actual elements.

          RefIteratorProcess: this makes processing functions process
          iterators for given references instead of copying elements.

          InvertedSortMode: this allows for inverted mode.  See documentation
          for use.
         *____________________________________________________________________*/

        inline
                Flag
        &RevProcess();
        //Reverse processing flag

        inline
                Flag
        &RevEquals();
        //Reverse equal elements against process direction flag

        inline
                Flag
        &RevFind() const;
        //Find in reverse flag

        inline
                Flag
        &CrossEndsFind() const;
        //Cross begin/end points when searching flag

        inline
                Flag
        &IteratorProcess();
        //Process iterators instead of values flag

        inline
                Flag
        &RefIteratorProcess();
        //Process iterators of reference data instead of values flag

        inline
                Flag
        &InvertedSortMode();
        //Sets inverted mode
        //======================================================================

        //Constant flags========================================================
        inline
                const Flag
        &RevProcess() const;
        //Reverse processing flag

        inline
                const Flag
        &RevEquals() const;
        //Reverse equal elements against process direction flag

        inline
                const Flag
        &IteratorProcess() const;
        //Process iterators instead of values flag

        inline
                const Flag
        &RefIteratorProcess() const;
        //Process iterators of reference data instead of values flag

        inline
                const Flag
        &InvertedSortMode() const;
        //Sets inverted mode
        //======================================================================

        //Index reference=======================================================
                mutable IndexManager
        Index;
        //Circular index reference
        //======================================================================

protected:
        //Assist functions------------------------------------------------------

        /*____________________________________________________________________*
          -Assist Functions-

          MOD: this returns a valid array position, or 0 if the list contains
          no elements.

          SET_RANGE: this sets the range based on 2 given arguments.  Both low
          and high variables are included in the range.

          FIND_RANGE: this sets a range for find functions.  A start point is
          given, and the range is established based on RevFind and
          CrossEndsFind.  The low range variable is included in the range,
          however the high range variable is one past the end of the range.

          COPY_SAVER: when using C_MSORT_, a copy of the data to be sorted is
          required for every other power of 2.  Provide the size to this
          function and it will return true if you do not need to precopy the
          data into the temporary list.

          CHECK_CAPACITY: checks a container for maximum capacity.
         *____________________________________________________________________*/

        inline
                int
        MOD(int) const;
        //Returns valid array pos from int
        //Unformatted position, returns position in bounds or 0

        inline
                int
        SET_RANGE(int&, int&, int, int) const;
        //Sets range
        //Lo variable, hi variable, value 1, value 2

        inline
                int
        FIND_RANGE(int&, int&, int) const;
        //Set find range
        //Lo variable, hi variable, start position

        inline
                bool
        COPY_SAVER(unsigned int) const;
        //Predicts if copy is needed prior to sorting

        template <class Type2> inline
                bool
        CHECK_CAPACITY(const Type2&, unsigned int) const;
        //Check for total space
        //Container, desired total space
        //----------------------------------------------------------------------

        //Sort/sort assist functions--------------------------------------------

        /*____________________________________________________________________*
          -Sort Functions-

          C_MSORT_: this is a highly optimized circular linear merge sort
          function.  This was created by me as a result of this class (not the
          merge sort concept; but the circular and linear adaptations of it).
          This allows data to be sorted crossing the upper boundary of the
          array back around to the beginning of the array.  This is done with
          an extremely trivial amount of extra time (I know because I
          originally had a non-circular version in the class as well),
          therefore this is used for all sorting, even that which is never
          going to be circular.  See .cpp for notes.

          FC_MSORT_: the functor version of the above.
         *____________________________________________________________________*/

        //Sort..................................................................
        template <class Iterator2> static
                void
        C_MSORT_(Iterator2, Iterator2, Iterator2, unsigned int, unsigned int,
                 bool = false, bool = false);
        //Circular linear merge sort
        //Data start, data end, temporary data, sort start position, sort end
        //position, reverse sorting flag, reverse equal elements flag

        template <class Function2, class Iterator2> static
                void
        FC_MSORT_(Iterator2, Iterator2, Iterator2, unsigned int, unsigned int,
                  Function2, bool = false, bool = false);
        //Circular linear merge sort with functor processing
        //Data start, data end, temporary data, sort start position, sort end
        //position, functor, reverse sorting flag, reverse equal elements flag
        //......................................................................

private:
        typedef BASE_TYPE *Iterator;
        //Iterator typedef

        typedef BASE_TYPE const *ConstIterator;
        //Constant iterator typedef

        //Copy elements.........................................................
                void
        EQUAL(Iterator, int, int) const;
        //Copy elements directly from list data
        //Start position, stop position, returns array
        //......................................................................

        //Order by reference....................................................
                void
        PRE_ORDER(CELL <int> *const, int) const;
        //Transposes reference list before using it to sort data
        //Array of cells, total size

        template <class Iterator2, class T>
                void
        ORDER(Iterator2, CELL <T> *const, int, int) const;
        //Orders list by reference positions
        //Array, array of cells, start position, stop position

        template <class Iterator2>
                void
        ORDER(Iterator2, int*, int, int) const;
        //Orders list by reference positions
        //Array, array of positions, start position, stop position
        //......................................................................

        //Pre-sorting functions.................................................
        typedef typename LIST_CONTAINER <CELL <int> > ::TYPE Transposer;
        //Typedef for container of elements used in transposing

        template <class Iterator2>
                bool
        PRE_SORT(Iterator2, Transposer&, unsigned int, unsigned int, bool, bool,
                 bool, bool, bool, bool) const;
        //Pre-sort reference data for transposing other data
        //Iterator, Transposer, start point, end point, sort iterators,
        //using this list data, inverted mode, using to transpose this list
        //data, reverse sort, reverse equals

        template <class Function2, class Iterator2>
                bool
        FPRE_SORT(Iterator2, Transposer&, unsigned int, unsigned int, bool,
                  bool, bool, bool, bool, bool, Function2) const;
        //Pre-sort reference data for transposing other data using functor
        //Iterator, Transposer, start point, end point, sort iterators,
        //using this list data, inverted mode, using to transpose this list
        //data, reverse sort, reverse equals, processing functor
        //......................................................................
        //----------------------------------------------------------------------


protected:
        //RemoveDuplicates assist functions-------------------------------------

        /*____________________________________________________________________*
          -Find Duplicate Functions-

          FIND_D: these functions find all duplicate elements in the list.
          Ranges are raw, therefore are converted using SET_RANGE before
          processing.  RevProcess is taken into account here.  Of any pair of
          elements evaluating as equal, the particular element deemed as being
          duplicate is based on 1) the start point of the range, 2) the state
          of RevProcess.  The first element of a given value (based on
          the equality operator) is kept while the remaining elements that
          pass the equality test are removed.

          FFIND_D: functor version of FIND_D.
         *____________________________________________________________________*/

        typedef typename LIST_CONTAINER <int> ::TYPE PosContainer;
        //Position container type

                unsigned int
        FIND_D(PosContainer&, int, int) const;
        //Finds duplicate elements
        //Position array, start position, stop position,
        //returns number of elements

        template <class SortFunction2, class FindFunction2>
                int
        FFIND_D(PosContainer&, int, int, SortFunction2, FindFunction2) const;
        //Finds duplicate elements
        //Position array, start position, stop position, sort functor,
        //find functor, returns number of elements

private:
                int
        *FAST_REM(int*, unsigned int);
        //Removes elements
        //Sorted element array, number of elements

                int
        *FAST_KEEP(int*, unsigned int);
        //Keeps elements
        //Sorted element array, number of elements
        //----------------------------------------------------------------------

        inline
                size_t
        Allocate(size_t);
        //Allocation function

        //Access functions======================================================
        //Iterator access-------------------------------------------------------
        inline
                Iterator
        Element(unsigned int);
        //Random access function

        inline
                ConstIterator
        Element(unsigned int) const;
        //Random access function
        //----------------------------------------------------------------------

        //Reference access------------------------------------------------------
        inline
                ASSIGN_TYPE
        Reference(unsigned int);
        //Random access function

        inline
                CONST_RETURN_TYPE
        Reference(unsigned int) const;
        //Random access function

        inline
                ASSIGN_TYPE
        Default();
        //Returns default element

        inline
                CONST_RETURN_TYPE
        Default() const;
        //Returns default element
        //----------------------------------------------------------------------
        //======================================================================

        //Converter-------------------------------------------------------------
        template <class Type2> static inline
                const Type2
        &Convert(const Type2&);
        //Assists functor sorting by returning data as const
        //----------------------------------------------------------------------

        inline
                int
        S_MOD(int) const;
        //Returns valid array pos from int
        //Unformatted position, returns position in bounds or 0

                Container
        LIST;
        //Stores list of data

                mutable BASE_TYPE
        ELEMENT_;
        //Default element

        static
                const unsigned char
        FLAGS_USED = 7;
        //Number of flags used

                mutable Flag
        Flags[ FLAGS_USED ];
        //Flags for options

        template <class Type2> friend class CList;
        //Friend class
}; //END------------------------------------------------------------------------
//==============================================================================
}

#endif
//==============================================================================
