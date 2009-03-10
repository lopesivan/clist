/*============================================================================*\
 *CList Assist Functions/Classes.                                             *
 *Copyright (C) 2005 Kevin P. Barry (ta0kira)                                 *
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
  This file contains assist objects for CList and external operators/functions
  for use with some types of CList.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2003-2005 Kevin P. Barry

//==============================================================================
#ifndef LIST_ASSIST_HPP
#define LIST_ASSIST_HPP LIST_HPP
#include <iterator>
#include <iostream>
#include "LIST_TYPES.hpp"

namespace LIST_ASSIST_HPP
{

//External CList operators======================================================
template <class Type> class CList;
//Pre-declaration

/*____________________________________________________________________________*
  -External List Operators-

  operator +=: this operator adds an argument to all elements in a list.

  operator -=: this operator subtracts an argument from all elements in a list.

  operator *=: this operator multiplies all elements in a list by an argument.

  operator /=: this operator divides all elements in a list by an argument.

  operator %=: this operator moduluses all elements in a list by an argument.

  operator <<: sequentially submits list elements to std::ostream
 *____________________________________________________________________________*/

template <class Type1, class Type2>
        CList <Type1>
&operator += (CList <Type1>&, const Type2&);

template <class Type1, class Type2>
        CList <Type1>
&operator -= (CList <Type1>&, const Type2&);

template <class Type1, class Type2>
        CList <Type1>
&operator *= (CList <Type1>&, const Type2&);

template <class Type1, class Type2>
        CList <Type1>
&operator /= (CList <Type1>&, const Type2&);

template <class Type1, class Type2>
        CList <Type1>
&operator %= (CList <Type1>&, const Type2&);
}

template <class Type>
        std::ostream
&operator << (std::ostream&, const LIST_ASSIST_HPP::CList <Type>&);

namespace LIST_ASSIST_HPP
{
//==============================================================================

//Other external CList functions================================================

/*____________________________________________________________________________*
  -External List Functions-

  DELTA: this function subtracts all elements from the next element.  If the
  RevProcess flag is set in the list then elements will be subtracted from the
  previous element.

  SIGMA: this function totals all elements in a list.

  INVERTED_SHIFT: this function allows shifting of inverted lists.  Please see
  documentation for use.

  SEQUENCE: this function adds the current list size until the list is full,
  creating a sequence.  If the list capacity is unlimited then no action is
  taken.
 *____________________________________________________________________________*/

template <class Type>
        CList <Type>
&DELTA(CList <Type>&);
//Subtracts elements from next elements

template <class Type>
        typename CList <Type> ::PULL_TYPE
SIGMA(CList <Type>&);
//Calculates sum of all elements

template <class Type1, class Type2>
        CList <Type1>
&INVERTED_SHIFT(CList <Type1>&, const Type2&);
//Complimentary shift operation for inverted list

template <class Type>
        CList <Type>
&SEQUENCE(CList <Type>&);
//Adds sequential elements to list
//==============================================================================

//Assist objects================================================================
CELL_FRIENDS_DECLARATIONS
//Declarations for friends of cell types

//Structure for sorting objects.................................................
template <class Iterator> class I_CELL;
//Pre-declaration for use as friend

template <class Type> class D_CELL;
//Pre-declaration for use as friend

template <class Iterator> class ID_CELL;
//Pre-declaration for use as friend

template <class Type>
class CELL
{
                void
        operator << (Type);
        //Set object
        //Object

                void
        operator = (int);
        //Set position reference
        //Position

        inline
        operator const Type&() const;
        //Returns value

        /*____________________________________________________________________*
          -Comparison Operators-

          These operators compare based on the object value.
         *____________________________________________________________________*/

        //Comparison operators (based on value)---------------------------------
                bool
        operator < (const CELL&) const;

                bool
        operator == (const CELL&) const;

                bool
        operator > (const CELL&) const;
        //----------------------------------------------------------------------

                int
        POS;
        //Position reference

                Type
        OBJ;
        //Object

        template <class Type2> friend class CList;
        //Friend class

        template <class Iterator> friend class I_CELL;
        //Friend class

        template <class Type2> friend class D_CELL;
        //Friend class

        template <class Iterator> friend class ID_CELL;
        //Friend class

        CELL_FRIENDS
        //Declaration of other friends
};
//..............................................................................

//Structure for sorting iterators...............................................
template <class Iterator>
class I_CELL :
        public CELL <Iterator>
{
        typedef typename std::iterator_traits <Iterator> ::value_type Type;
        //Typedef for value type

                void
        operator << (Iterator);
        //Set pointer
        //Pointer

                void
        operator = (int);
        //Set position reference
        //Position

        inline
        operator const Type&() const;
        //Returns value

        /*____________________________________________________________________*
          -Comparison Operators-

          These operators compare based on the object value.
         *____________________________________________________________________*/

        //Comparison operators (based on value)---------------------------------
                bool
        operator < (const I_CELL&) const;

                bool
        operator == (const I_CELL&) const;

                bool
        operator > (const I_CELL&) const;
        //----------------------------------------------------------------------

        template <class Type2> friend class CList;
        //Friend class

        CELL_FRIENDS
        //Declaration of other friends
};
//..............................................................................

//Structure deletion flagging of objects........................................
template <class Type>
class D_CELL :
        public CELL <Type>
{
        D_CELL();
        //Constructor

                void
        operator << (Type);
        //Set pointer
        //Pointer

                void
        operator = (int);
        //Set position reference
        //Position

        inline
        operator const Type&() const;
        //Returns value

        /*____________________________________________________________________*
          -Comparison Operators-

          These operators compare based on the object value if SORT is false.
          If SORT is true, comparison is based on the DEL flag.  If the DEL
          flags are equal, comparison is based on the positional value.
         *____________________________________________________________________*/

        //Comparison operators (based on value)---------------------------------
                bool
        operator < (const D_CELL&) const;

                bool
        operator == (const D_CELL&) const;

                bool
        operator > (const D_CELL&) const;
        //----------------------------------------------------------------------

                char
        DEL, SORT;
        //Delete flag, sort phase

        template <class Type2> friend class CList;
        //Friend class

        CELL_FRIENDS
        //Declaration of other friends
};
//..............................................................................

//Structure deletion flagging of iterators......................................
template <class Iterator>
class ID_CELL :
        public I_CELL <Iterator>
{
        typedef typename std::iterator_traits <Iterator> ::value_type Type;
        //Typedef for value type

        ID_CELL();
        //Constructor

                void
        operator << (Iterator);
        //Set pointer
        //Pointer

                void
        operator = (int);
        //Set position reference
        //Position

        inline
        operator const Type&() const;
        //Returns value

        /*____________________________________________________________________*
          -Comparison Operators-

          These operators compare based on the object value if SORT is false.
          If SORT is true, comparison is based on the DEL flag.  If the DEL
          flags are equal, comparison is based on the positional value.
         *____________________________________________________________________*/

        //Comparison operators (based on value)---------------------------------
                bool
        operator < (const ID_CELL&) const;

                bool
        operator == (const ID_CELL&) const;

                bool
        operator > (const ID_CELL&) const;
        //----------------------------------------------------------------------

                char
        DEL, SORT;
        //Delete flag, sort phase

        template <class Type2> friend class CList;
        //Friend class

        CELL_FRIENDS
        //Declaration of other friends
};
//..............................................................................
//==============================================================================
}

#endif
//==============================================================================
