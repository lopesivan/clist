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

//BasicComponents_______________________________________________________________
//(C) 2003-2004 Kevin P. Barry

//==============================================================================
#ifndef OTHER_LISTS_CPP
#define OTHER_LISTS_CPP OTHER_LISTS_HPP
#include "OTHER_LISTS.hpp"
#include "LIST.cpp"

namespace OTHER_LISTS_CPP
{

//Associate function bodies=====================================================
        //Constructors==========================================================
        template <class Type1, class Type2> template <class Type3, class Type4>
        Associate <Type1, Type2> ::Associate(const Type3 &kKey, const Type4 &vVal) :
        KEY(kKey), VALUE(vVal) {}

        template <class Type1, class Type2> Associate <Type1, Type2> ::
        Associate(const Associate &eEqual) :
        KEY(eEqual.KEY), VALUE(eEqual.VALUE) {}
        //======================================================================

        //Return data===========================================================
        template <class Type1, class Type2> typename Associate <Type1, Type2> ::
        RETURN_TYPE1 Associate <Type1, Type2> ::Key()
        //Returns key
        { return KEY; }

        template <class Type1, class Type2> typename Associate <Type1, Type2> ::
        RETURN_TYPE2 Associate <Type1, Type2> ::Value()
        //Returns value
        { return VALUE; }

        template <class Type1, class Type2> typename Associate <Type1, Type2> ::
        CONST_RETURN_TYPE1 Associate <Type1, Type2> ::Key() const
        //Returns key
        { return KEY; }

        template <class Type1, class Type2> typename Associate <Type1, Type2> ::
        CONST_RETURN_TYPE2 Associate <Type1, Type2> ::Value() const
        //Returns value
        { return VALUE; }
        //======================================================================

        //Operators=============================================================
        template <class Type1, class Type2> Associate <Type1, Type2>
        &Associate <Type1, Type2> ::operator = (const Associate &eEqual)
        {
        KEY = eEqual.KEY;
        VALUE = eEqual.VALUE;
        return *this;
        }

        template <class Type1, class Type2> bool Associate <Type1, Type2> ::
        operator == (const Associate &eEqual) const
        {
        if (KEY == eEqual.KEY) return VALUE == eEqual.VALUE;
        else return false;
        }

        template <class Type1, class Type2> bool Associate <Type1, Type2> ::
        operator < (const Associate &eEqual) const
        {
        if (KEY == eEqual.KEY) return VALUE < eEqual.VALUE;
        else return KEY < eEqual.KEY;
        }

        template <class Type1, class Type2> bool Associate <Type1, Type2> ::
        operator > (const Associate &eEqual) const
        {
        if (KEY == eEqual.KEY) return VALUE > eEqual.VALUE;
        else return KEY > eEqual.KEY;
        }
        //======================================================================
//==============================================================================

//KeyList function bodies=======================================================
        template <class Type1, class Type2>
        KeyList <Type1, Type2> ::KeyList(unsigned int mMax) :
        CList <Associate <Type1, Type2> > (mMax) {}
        //Constructor

        template <class Type1, class Type2> template <class Type3, class Type4>
        typename KeyList <Type1, Type2> ::ELEMENT
        KeyList <Type1, Type2> ::NewElement(const Type3 &kKey, const Type4 &vVal)
        { return Associate <Type1, Type2> (kKey, vVal); }

        template <class Type1, class Type2> bool
        KeyList <Type1, Type2> ::SORT_BY_KEY(const ELEMENT &eEl1, const ELEMENT &eEl2)
        { return eEl1.Key() < eEl2.Key(); }

        template <class Type1, class Type2> bool
        KeyList <Type1, Type2> ::SORT_BY_VALUE(const ELEMENT &eEl1, const ELEMENT &eEl2)
        { return eEl1.Value() < eEl2.Value(); }

        template <class Type1, class Type2> bool
        KeyList <Type1, Type2> ::FIND_BY_KEY(const ELEMENT &eEl,
        typename KeyList <Type1, Type2> ::CONST_RETURN_TYPE1 kKey)
        { return eEl.Key() == kKey; }

        template <class Type1, class Type2> bool
        KeyList <Type1, Type2> ::FIND_BY_VALUE(const ELEMENT &eEl,
        typename KeyList <Type1, Type2> ::CONST_RETURN_TYPE2 vVal)
        { return eEl.Value() == vVal; }

        template <class Type1, class Type2> bool
        KeyList <Type1, Type2> ::FIND_DUP_KEY(const ELEMENT &eEl1, const ELEMENT &eEl2)
        { return eEl1.Key() == eEl2.Key(); }

        template <class Type1, class Type2> bool
        KeyList <Type1, Type2> ::FIND_DUP_VALUE(const ELEMENT &eEl1, const ELEMENT &eEl2)
        { return eEl1.Value() == eEl2.Value(); }
//==============================================================================
}

#endif
//==============================================================================
