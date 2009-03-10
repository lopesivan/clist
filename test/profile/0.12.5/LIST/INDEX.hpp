/*============================================================================*\
 *IndexManager. Supporting class for CList.                                   *
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
  This file is the header for the class IndexManager.  IndexManager provides
  an index point for CList, as well as list size/capacity tracking and
  positional parsing.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2003-2005 Kevin P. Barry

//==============================================================================
#ifndef INDEX_HPP
#define INDEX_HPP BC

namespace INDEX_HPP
{

//Class IndexManager------------------------------------------------------------
//Manages circular index point
template <class Type> class CList;
//Pre-declaration for use as friend

class IndexManager
{
public:
        //Information===========================================================
        inline
                unsigned int
        Size() const;
        //Returns size

        inline
                unsigned int
        Max() const;
        //Returns max size
        //======================================================================

        //Limit information=====================================================

        /*____________________________________________________________________*
          -Other Information Functions-

          AtMin: this function returns true if the size of the list is 0.

          AtMax: this function returns true if the size of the list is equal
          to the max size allocated.

          AtBegin: this function returns true if the index point is at the
          beginning of the list.

          AtEnd:  this function returns true if the index point is at the end
          of the list.
         *____________________________________________________________________*/

        inline
                bool
        AtMin() const;
        //Returns true if size is 0

        inline
                bool
        AtMax() const;
        //Returns true if size is equal to max

        inline
                bool
        AtBegin() const;
        //Returns true if index is at beginning

        inline
                bool
        AtEnd() const;
        //Returns true if index is at end
        //======================================================================

        //Index functions=======================================================

        /*____________________________________________________________________*
          -Index Setting Functions-

          SetBegin: this function sets the index point at the beginning of the
          list.

          SetEnd: this function sets the index point at the end of the list.
         *____________________________________________________________________*/

        inline
                IndexManager
        &SetBegin();
        //Sets index to beginning

        inline
                IndexManager
        &SetEnd();
        //Sets index to end
        //======================================================================

        //Index operators=======================================================
        inline
                IndexManager
        &operator = (int);
        //Sets index
        //Unformatted index, returns new index

        inline
                IndexManager
        &operator = (const IndexManager&);
        //Sets index
        //Index to copy

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

        //Arithmetic operators (based on index)=================================
        inline
                IndexManager
        &operator += (int);
        //Add, correct, and equal
        //Value, returns total corrected index

        inline
                IndexManager
        &operator -= (int);
        //Subtract, correct, and equal
        //Value, returns total corrected index

        inline
                IndexManager
        &operator *= (int);
        //Multiply, correct, and equal
        //Value, returns total corrected index

        inline
                IndexManager
        &operator /= (int);
        //Divide, correct, and equal
        //Value, returns total index

        inline
                IndexManager
        &operator %= (int);
        //Modulus, correct, and equal
        //Value, returns total index
        //======================================================================

        //Other operators=======================================================

        /*____________________________________________________________________*
          -Other Operators-

          operator []: this operator returns a valid list position (based on
          modulus by the list size.)

          operator int: this is a conversion operator that returns the
          current index position.
         *____________________________________________________________________*/

        inline
                int
        operator [] (int) const;
        //Returns valid index position
        //Value, returns corrected index

        inline
        operator int() const;
        //Conversion operator
        //Returns current index
        //======================================================================

private:
        IndexManager(unsigned int = 0);
        //Constructor
        //Max size

        ~IndexManager() {}
        //Destructor
        //Prevents instantiation

        //Private functions-----------------------------------------------------
        inline
                unsigned int
        SET_SIZE(unsigned int);
        //Sets size, adjusts index
        //Size, returns corrected size

        inline
                IndexManager
        &SET_MAX(unsigned int);
        //Sets max size
        //Max size

        inline
                int
        MOD(int) const;
        //Returns valid array position (for mod of externally provided values)
        //Value, returns corrected index

        inline
                int
        S_MOD(int) const;
        //Returns valid array position (shortened for internal use)
        //Value, returns corrected index
        //----------------------------------------------------------------------

                int
        INDEX, SIZE, MAX;
        //Index, total size, maximum size

        template <class Type> friend class CList;
        //Friend class
}; //---------------------------------------------------------------------------
}

#endif
//==============================================================================
