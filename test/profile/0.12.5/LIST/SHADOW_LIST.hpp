/*============================================================================*\
 *Shadow Lists. Shadow list support for CList.                                *
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
  This file is the header for shadow list supporting classes/functions.  Do
  not use the classes directly; use only the global functions.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2005-2006 Kevin P. Barry

//==============================================================================
#ifndef SHADOW_LIST_HPP
#define SHADOW_LIST_HPP LIST_HPP
#include "FUNCTOR/FUNCTOR.hpp"
#include "LIST_ASSIST.hpp"
#include "LIST.hpp"

namespace SHADOW_LIST_HPP
{

//Typedef ListShadow------------------------------------------------------------
//List for use with shadow operations
typedef CList <int> ListShadow; //END-------------------------------------------

//Functions=====================================================================
template <class Type1, class Type2>
struct ShadowSortBinder;
//Pre-declaration

template <class Type1, class Type2>
struct ShadowFindBinder;
//Pre-declaration

template <class Type1, class Type2>
struct ShadowDupBinder;
//Pre-declaration

template <class Type1, class Type2, class Function>
class FShadowInternBinder;
//Pre-declaration

template <class Type1, class Type2, class Function>
class FShadowExternBinder;
//Pre-declaration

//Function CreateBlankShadow----------------------------------------------------
//Creates a blank shadow list
template <class Type1, class Type2> inline
        Type2
&CreateBlankShadow(const Type1&, Type2&);
//Original list, shadow list

//Function BindSortShadow-------------------------------------------------------
//Automatically binds a list to a shadow for sorting
template <class Type1, class Type2> inline
        ShadowSortBinder <Type1, Type2>
BindSortShadow(Type1&, Type2&);
//Original list, shadow list

//Function BindFindShadow-------------------------------------------------------
//Automatically binds a list to a shadow for finding
template <class Type1, class Type2> inline
        ShadowFindBinder <Type1, Type2>
BindFindShadow(Type1&, Type2&);
//Original list, shadow list

//Function BindDupShadow--------------------------------------------------------
//Automatically binds a list to a shadow for finding duplicates
template <class Type1, class Type2> inline
        ShadowDupBinder <Type1, Type2>
BindDupShadow(Type1&, Type2&);
//Original list, shadow list

//Function FBindInternShadow----------------------------------------------------
//Automatically binds a list to a shadow and a functor for internal comparison
template <class Type1, class Type2, class Function> inline
        FShadowInternBinder <Type1, Type2, Function>
FBindInternShadow(Type1&, Type2&, Function);
//Original list, shadow list, functor

//Function FBindExternShadow----------------------------------------------------
//Automatically binds a list to a shadow and a functor for external comparison
template <class Type1, class Type2, class Function> inline
        FShadowExternBinder <Type1, Type2, Function>
FBindExternShadow(Type1&, Type2&, Function);
//Original list, shadow list, functor
//==============================================================================

//Classes=======================================================================
//Class ShadowSortBinder--------------------------------------------------------
template <class Type1, class Type2>
struct ShadowSortBinder
{
public:
        typedef bool F2_RETURN;

        typedef typename Type2::CONST_RETURN_TYPE F2_ARG1, F2_ARG2;

        ShadowSortBinder(Type1&);

                F2_RETURN
        operator () (F2_ARG1, F2_ARG2);

private:
                Type1
        *List;
}; //END------------------------------------------------------------------------

//Class ShadowFindBinder--------------------------------------------------------
template <class Type1, class Type2>
struct ShadowFindBinder
{
public:
        typedef bool F2_RETURN;

        typedef typename Type2::CONST_RETURN_TYPE F2_ARG1;
        typedef typename Type1::CONST_RETURN_TYPE F2_ARG2;

        ShadowFindBinder(Type1&);

                F2_RETURN
        operator () (F2_ARG1, F2_ARG2);

private:
                Type1
        *List;
};
//END---------------------------------------------------------------------------

//Class ShadowDupBinder---------------------------------------------------------
template <class Type1, class Type2>
struct ShadowDupBinder
{
public:
        typedef bool F2_RETURN;

        typedef typename Type2::CONST_RETURN_TYPE F2_ARG1, F2_ARG2;

        ShadowDupBinder(Type1&);

                F2_RETURN
        operator () (F2_ARG1, F2_ARG2);

private:
                Type1
        *List;
}; //END------------------------------------------------------------------------

//Class FShadowInternBinder-----------------------------------------------------
//Creates a functor that binds an original list to a shadow and a functor
template <class Type1, class Type2, class Function>
class FShadowInternBinder
{
public:
        typedef bool F2_RETURN;

        typedef typename Type2::CONST_RETURN_TYPE F2_ARG1, F2_ARG2;

        FShadowInternBinder(Type1&, Function);

                F2_RETURN
        operator () (F2_ARG1, F2_ARG2);

private:
                Type1
        *List;

                Function
        Functor;
}; //END------------------------------------------------------------------------

//Class FShadowExternBinder-----------------------------------------------------
//Creates a functor that binds an original list to a shadow and a functor
template <class Type1, class Type2, class Function>
class FShadowExternBinder
{
public:
        typedef bool F2_RETURN;

        typedef typename Type2::CONST_RETURN_TYPE     F2_ARG1;
        typedef typename FUNCTION_2 <Function> ::ARG2 F2_ARG2;

        FShadowExternBinder(Type1&, Function);

                F2_RETURN
        operator () (F2_ARG1, F2_ARG2);

private:
                Type1
        *List;

                Function
        Functor;
}; //END------------------------------------------------------------------------
//==============================================================================
}

#endif
//==============================================================================
