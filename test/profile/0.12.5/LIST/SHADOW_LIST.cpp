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

//BasicComponents_______________________________________________________________
//(C) 2005-2006 Kevin P. Barry

//==============================================================================
#ifndef SHADOW_LIST_CPP
#define SHADOW_LIST_CPP SHADOW_LIST_HPP
#include "SHADOW_LIST.hpp"
#include "FUNCTOR/FUNCTOR.cpp"
#include "LIST_ASSIST.cpp"
#include "LIST.cpp"

namespace SHADOW_LIST_CPP
{

//Function CreateBlankShadow----------------------------------------------------
//Creates a blank shadow list
template <class Type1, class Type2> inline Type2
&CreateBlankShadow(const Type1 &lList, Type2 &sShadow)
{
        SEQUENCE( sShadow.Reset(lList.Size()) ).NewMax();
        return sShadow;
} //END-------------------------------------------------------------------------

//Function BindSortShadow-------------------------------------------------------
//Automatically binds a list to a shadow for sorting
template <class Type1, class Type2> inline ShadowSortBinder <Type1, Type2>
BindSortShadow(Type1 &lList, Type2&)
{ return ShadowSortBinder <Type1, Type2> (lList); } //END-----------------------

//Function BindFindShadow-------------------------------------------------------
//Automatically binds a list to a shadow for finding
template <class Type1, class Type2> inline ShadowFindBinder <Type1, Type2>
BindFindShadow(Type1 &lList, Type2&)
{ return ShadowFindBinder <Type1, Type2> (lList); } //END-----------------------

//Function BindFindShadow-------------------------------------------------------
//Automatically binds a list to a shadow for finding duplicates
template <class Type1, class Type2> inline ShadowDupBinder <Type1, Type2>
BindDupShadow(Type1 &lList, Type2&)
{ return ShadowDupBinder <Type1, Type2> (lList); } //END------------------------

//Function FBindInternShadow----------------------------------------------------
//Automatically binds a list to a shadow and a functor for internal comparison
template <class Type1, class Type2, class Function> inline
FShadowInternBinder <Type1, Type2, Function>
FBindInternShadow(Type1 &lList, Type2&, Function fFunction)
{ return FShadowInternBinder <Type1, Type2, Function> (lList, fFunction); }
//END---------------------------------------------------------------------------

//Function FBindExternShadow----------------------------------------------------
//Automatically binds a list to a shadow and a functor for external comparison
template <class Type1, class Type2, class Function> inline
FShadowExternBinder <Type1, Type2, Function>
FBindExternShadow(Type1 &lList, Type2&, Function fFunction)
{ return FShadowExternBinder <Type1, Type2, Function> (lList, fFunction); }
//END---------------------------------------------------------------------------

//ShadowSortBinder function bodies==============================================
        template <class Type1, class Type2> ShadowSortBinder <Type1, Type2> ::
        ShadowSortBinder(Type1 &lList) : List(&lList) {}

        template <class Type1, class Type2>
        typename ShadowSortBinder <Type1, Type2> ::F2_RETURN
        ShadowSortBinder <Type1, Type2> ::
        operator () (typename ShadowSortBinder <Type1, Type2> ::F2_ARG1 vVal1,
        typename ShadowSortBinder <Type1, Type2> ::F2_ARG2 vVal2)
        { return List->Get(vVal1) < List->Get(vVal2); }
//==============================================================================

//ShadowFindBinder function bodies==============================================
        template <class Type1, class Type2> ShadowFindBinder <Type1, Type2> ::
        ShadowFindBinder(Type1 &lList) : List(&lList) {}

        template <class Type1, class Type2>
        typename ShadowFindBinder <Type1, Type2> ::F2_RETURN
        ShadowFindBinder <Type1, Type2> ::
        operator () (typename ShadowFindBinder <Type1, Type2> ::F2_ARG1 vVal1,
        typename ShadowFindBinder <Type1, Type2> ::F2_ARG2 vVal2)
        { return List->Get(vVal1) == vVal2; }
//==============================================================================

//ShadowDupBinder function bodies===============================================
        template <class Type1, class Type2> ShadowDupBinder <Type1, Type2> ::
        ShadowDupBinder(Type1 &lList) : List(&lList) {}

        template <class Type1, class Type2>
        typename ShadowDupBinder <Type1, Type2> ::F2_RETURN
        ShadowDupBinder <Type1, Type2> ::
        operator () (typename ShadowDupBinder <Type1, Type2> ::F2_ARG1 vVal1,
        typename ShadowDupBinder <Type1, Type2> ::F2_ARG2 vVal2)
        { return List->Get(vVal1) == List->Get(vVal2); }
//==============================================================================

//FShadowInternBinder function bodies===========================================
        template <class Type1, class Type2, class Function>
        FShadowInternBinder <Type1, Type2, Function> ::
        FShadowInternBinder(Type1 &lList, Function fFunction) :
        List(&lList), Functor(fFunction) {}

        template <class Type1, class Type2, class Function>
        typename FShadowInternBinder <Type1, Type2, Function> ::F2_RETURN
        FShadowInternBinder <Type1, Type2, Function> ::
        operator () (typename FShadowInternBinder <Type1, Type2, Function> ::F2_ARG1 vVal1,
        typename FShadowInternBinder <Type1, Type2, Function> ::F2_ARG2 vVal2)
        { return EVALUATE_2( Functor, List->Get(vVal1), List->Get(vVal2) ); }
//==============================================================================

//FShadowExternBinder function bodies===========================================
        template <class Type1, class Type2, class Function>
        FShadowExternBinder <Type1, Type2, Function> ::
        FShadowExternBinder(Type1 &lList, Function fFunction) :
        List(&lList), Functor(fFunction) {}

        template <class Type1, class Type2, class Function>
        typename FShadowExternBinder <Type1, Type2, Function> ::F2_RETURN
        FShadowExternBinder <Type1, Type2, Function> ::
        operator () (typename FShadowExternBinder <Type1, Type2, Function> ::F2_ARG1 vVal1,
        typename FShadowExternBinder <Type1, Type2, Function> ::F2_ARG2 vVal2)
        { return EVALUATE_2( Functor, List->Get(vVal1), vVal2 ); }
//==============================================================================
}

#endif
//==============================================================================
