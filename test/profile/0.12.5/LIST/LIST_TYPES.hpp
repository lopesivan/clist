/*============================================================================*\
 *CList Argument Types. Supports const and reference types for CList.         *
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
  This file is the header for the class ListTypes.  This class is a 'traits'
  class for use by CList.  The types included are; the base type with const
  and reference qualifiers removed, various argument types, and various return
  types.

  -General Comments-

  Constant Types: if a type is const, all return types will be const, and
  elements cannot be changed except with Replace.  They can, however, be added,
  removed, sorted, etc.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2005 Kevin P. Barry

//==============================================================================
#ifndef LIST_TYPES_HPP
#define LIST_TYPES_HPP LIST_HPP

//Definitions___________________________________________________________________

        /*____________________________________________________________________*
          To override the container type used to manage the data in CList you
          must redefine three macros:

          CLIST_CONTAINER_TYPE(Type): the 'Type' parameter is expected to be
          the element type when the declaration is done.  This definition must
          result in an instantiable type that has these functions:
              resize(unsigned int): resizes the container
              size(): returns the number of elements
              begin(): returns the first element iterator
              end(): returns the end element iterator
              max_size(): returns the capacity of the container
              insert(iterator, Type): insert an element in the list
              pop_back(): remove the last element
              operator []: return a reference to the element given
              (iterators returned must be convertible to 'Type*' via &[])

          CELL_FRIENDS_DECLARATIONS: this should take the form of a forward
          declaration of classes as needed.

          CELL_FRIENDS: this is the friend declaration to allow your class to
          create the helper objects that CList uses.
         *____________________________________________________________________*/


#ifndef CLIST_CONTAINER_TYPE
#define CLIST_CONTAINER_TYPE(Type) std::vector < Type >
#include <vector>

#undef  CELL_FRIENDS_DECLARATIONS
#define CELL_FRIENDS_DECLARATIONS

#undef  CELL_FRIENDS
#define CELL_FRIENDS template <class> friend class std::vector;
#endif

#ifndef CELL_FRIENDS_DECLARATIONS
#define CELL_FRIENDS_DECLARATIONS
#endif

#ifndef CELL_FRIENDS
#define CELL_FRIENDS
#endif
//______________________________________________________________________________

namespace LIST_TYPES_HPP
{

/*____________________________________________________________________________*

        //Base type-----------------------------------------------------------
        BASE_TYPE         Always 'Type' without const qualifier
                          Used to create elements/objects internally

        //Argument types------------------------------------------------------
        POINTER_TYPE      Always a pointer to 'BASE_TYPE', never const
                          Not used by CList

        ASSIGN_TYPE       Always a reference to 'BASE_TYPE', never const
                          Used as an argument to assign a value to

        //Return types--------------------------------------------------------
        PULL_TYPE         Always by value, const only if 'Type' is
                          Used to return an element by value

        RETURN_TYPE       Always by reference, const only if 'Type' is
                          Used to return an element

        CONST_RETURN_TYPE Always by reference and const
                          Used to return an element in a const list

 *____________________________________________________________________________*/

//Struct ListTypes--------------------------------------------------------------
//Stores typedefs for list classes
//Specialized for object________________________________________________________
template <class Type>
struct ListTypes
{
        typedef Type             BASE_TYPE,   *POINTER_TYPE, &ASSIGN_TYPE;
        typedef BASE_TYPE       &RETURN_TYPE,  PULL_TYPE;
        typedef const BASE_TYPE &CONST_RETURN_TYPE;
};

//Specialized for constant______________________________________________________
template <class Type>
struct ListTypes <const Type>
{
        typedef Type             BASE_TYPE,   *POINTER_TYPE, &ASSIGN_TYPE;
        typedef const BASE_TYPE &RETURN_TYPE,  PULL_TYPE; //<- const
        typedef const BASE_TYPE &CONST_RETURN_TYPE;
};
//END---------------------------------------------------------------------------

//Struct LIST_CONTAINER---------------------------------------------------------
//Contains typedef for list container types
template <class Type>
struct LIST_CONTAINER
{
        typedef CLIST_CONTAINER_TYPE(Type) TYPE;
}; //END------------------------------------------------------------------------
}

#endif
//==============================================================================
