/*============================================================================*\
 *Other CList Classes. Supports additional functionality for CList. .         *
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
  This file is the header for other list classes and related objects:

  Associate: this binds arguments of 2 different types.  This class abides by
  the type rules of ListTypes.  By default, the comparison functions are based
  on the Key value.  If Key values are the same, then comparison is based on
  the Value values.

  KeyList: this class is a list of Associate objects.  Static functions are
  provided for creating new elements and for processing based on either Key
  or Value alone.  Duplicate keys are allowed.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2003-2004 Kevin P. Barry

//==============================================================================
#ifndef OTHER_LISTS_HPP
#define OTHER_LISTS_HPP LIST_HPP
#include "LIST.hpp"

namespace OTHER_LISTS_HPP
{

//Lists=========================================================================
//Struct Associate--------------------------------------------------------------
//Used as element for associative lists
template <class Type1, class Type2 = Type1>
struct Associate
{
        //Typedefs==============================================================
        typedef typename ListTypes <Type1> ::BASE_TYPE         BASE_TYPE1;
        typedef typename ListTypes <Type1> ::RETURN_TYPE       RETURN_TYPE1;
        typedef typename ListTypes <Type1> ::CONST_RETURN_TYPE CONST_RETURN_TYPE1;

        typedef typename ListTypes <Type2> ::BASE_TYPE         BASE_TYPE2;
        typedef typename ListTypes <Type2> ::RETURN_TYPE       RETURN_TYPE2;
        typedef typename ListTypes <Type2> ::CONST_RETURN_TYPE CONST_RETURN_TYPE2;
        //======================================================================

        //Constructors==========================================================
        Associate() {}

        template <class Type3, class Type4>
        Associate(const Type3&, const Type4&);

        Associate(const Associate&);
        //======================================================================

        //Return data===========================================================
                RETURN_TYPE1
        Key();
        //Returns key

                RETURN_TYPE2
        Value();
        //Returns value

                CONST_RETURN_TYPE1
        Key() const;
        //Returns key

                CONST_RETURN_TYPE2
        Value() const;
        //Returns value
        //======================================================================

        //Operators=============================================================
                Associate
        &operator = (const Associate&);

                bool
        operator == (const Associate&) const;

                bool
        operator < (const Associate&) const;

                bool
        operator > (const Associate&) const;
        //======================================================================

private:
                BASE_TYPE1
        KEY;
        //Key

                BASE_TYPE2
        VALUE;
        //Value
}; //END------------------------------------------------------------------------

//Struct KeyList----------------------------------------------------------------
//CList of Associate elements
template <class Type1, class Type2>
struct KeyList :
        public CList <Associate <Type1, Type2> >
{
        typedef Associate <Type1, Type2> ELEMENT;
        //Element typedef

        typedef typename ListTypes <Type1> ::CONST_RETURN_TYPE CONST_RETURN_TYPE1;
        typedef typename ListTypes <Type2> ::CONST_RETURN_TYPE CONST_RETURN_TYPE2;

        KeyList(unsigned int = 0);
        //Constructor
        //Max number of elements

        template <class Type3, class Type4> static
                ELEMENT
        NewElement(const Type3&, const Type4&);
        //Create new element

        static
                bool
        SORT_BY_KEY(const ELEMENT&, const ELEMENT&);
        //Function to sort by key

        static
                bool
        SORT_BY_VALUE(const ELEMENT&, const ELEMENT&);
        //Function to sort by value

        static
                bool
        FIND_BY_KEY(const ELEMENT&, CONST_RETURN_TYPE1);
        //Function to find by key

        static
                bool
        FIND_BY_VALUE(const ELEMENT&, CONST_RETURN_TYPE2);
        //Function to find by value

        static
                bool
        FIND_DUP_KEY(const ELEMENT&, const ELEMENT&);
        //Function to find duplicate key

        static
                bool
        FIND_DUP_VALUE(const ELEMENT&, const ELEMENT&);
        //Function to find duplicate value
}; //END------------------------------------------------------------------------
//==============================================================================
}

#endif
//==============================================================================
