/*============================================================================*\
 *CList Assist Functions/Classes.                                             *
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
//(C) 2003-2005 Kevin P. Barry

//==============================================================================
#ifndef LIST_ASSIST_CPP
#define LIST_ASSIST_CPP LIST_ASSIST_HPP
#include "LIST_ASSIST.hpp"
#include "../MISC/MISC.cpp"

namespace LIST_ASSIST_CPP
{

//External CList operators======================================================
template <class Type1, class Type2> CList <Type1> &operator += (CList <Type1> &lList,
const Type2 &vVal)
{
        for (int I = 0; I < (signed) lList.Size(); I++) lList[I] += vVal;
        return lList;
}

template <class Type1, class Type2> CList <Type1> &operator -= (CList <Type1> &lList,
const Type2 &vVal)
{
        for (int I = 0; I < (signed) lList.Size(); I++) lList[I] -= vVal;
        return lList;
}

template <class Type1, class Type2> CList <Type1> &operator *= (CList <Type1> &lList,
const Type2 &vVal)
{
        for (int I = 0; I < (signed) lList.Size(); I++) lList[I] *= vVal;
        return lList;
}

template <class Type1, class Type2> CList <Type1> &operator /= (CList <Type1> &lList,
const Type2 &vVal)
{
        for (int I = 0; I < (signed) lList.Size(); I++) lList[I] /= vVal;
        return lList;
}

template <class Type1, class Type2> CList <Type1> &operator %= (CList <Type1> &lList,
const Type2 &vVal)
{
        for (int I = 0; I < (signed) lList.Size(); I++) lList[I] %= vVal;
        return lList;
}
}

template <class Type> std::ostream &operator << (std::ostream &oOut,
const LIST_ASSIST_CPP::CList <Type> &lList)
{
        for (int I = 0; I < (signed) lList.Size(); I++) oOut << lList[I];
        return oOut;
}

namespace LIST_ASSIST_HPP
{
//==============================================================================

//Other external CList functions================================================
template <class Type> CList <Type> &DELTA(CList <Type> &lList)
//Subtracts elements from next elements
{
        int SIZE = lList.Size();
        if (SIZE <= 1) return lList;

        CList <Type> Temp(lList);

        for (int I = 0; I < SIZE - 1; I++) lList[I] = lList.RevProcess()?
                                           (Temp[I] - Temp[I + 1]) :
                                           (Temp[I] - Temp[I - 1]);

        return lList;
}

template <class Type> typename CList <Type> ::PULL_TYPE
SIGMA(CList <Type> &lList)
//Calculates sum of all elements
{
        int SIZE = lList.Size();
        typename CList <Type> ::BASE_TYPE Temp(lList.First());
        for (int I = 1; I < SIZE; I++) Temp += lList[I];
        return Temp;
}

template <class Type1, class Type2> CList <Type1> &INVERTED_SHIFT(CList <Type1> &lList,
const Type2 &sShift)
//Complimentary shift operation for inverted list
{
        int SIZE = lList.Size();
        if (SIZE <= 0) return lList;
        typename CList <Type1> ::BASE_TYPE SHIFT = sShift % SIZE;
        if (SHIFT < 0) SHIFT += SIZE;
        return (lList += SHIFT) %= SIZE;
}

template <class Type> CList <Type> &SEQUENCE(CList <Type> &lList)
//Adds sequential elements to list
{
        if (lList.Max() == 0) return lList;
        while (lList.Add(lList.Size()));
        return lList;
}
//==============================================================================

//Assist object function bodies=================================================
//Structure for sorting objects.................................................
        template <class Type> void CELL <Type> ::operator << (Type oObj)
        //Set object
        { OBJ = oObj; }

        template <class Type> void CELL <Type> ::operator = (int pPos)
        //Set position reference
        { POS = pPos; }

        template <class Type> CELL <Type> ::operator const Type&() const
        //Set position reference
        { return OBJ; }

        //Comparison operators (based on value)---------------------------------
        template <class Type> bool CELL <Type> ::
        operator < (const CELL &eEqual) const
        { return OBJ < eEqual.OBJ; }

        template <class Type> bool CELL <Type> ::
        operator == (const CELL &eEqual) const
        { return OBJ == eEqual.OBJ; }

        template <class Type> bool CELL <Type> ::
        operator > (const CELL &eEqual) const
        { return OBJ > eEqual.OBJ; }
        //----------------------------------------------------------------------
//..............................................................................

//Structure for sorting iterators...............................................
        template <class Iterator> void I_CELL <Iterator> ::
        operator << (Iterator oObj)
        //Set pointer
        { CELL <Iterator> ::OBJ = oObj; }

        template <class Iterator> void I_CELL <Iterator> ::operator = (int pPos)
        //Set position reference
        { CELL <Iterator> ::POS = pPos; }

        template <class Iterator> I_CELL <Iterator> ::operator const typename
        I_CELL <Iterator> ::Type&() const
        //Set position reference
        { return *CELL <Iterator> ::OBJ; }

        //Comparison operators (based on value)---------------------------------
        template <class Iterator> bool I_CELL <Iterator> ::
        operator < (const I_CELL &eEqual) const
        { return *CELL <Iterator> ::OBJ < *eEqual.OBJ; }

        template <class Iterator> bool I_CELL <Iterator> ::
        operator == (const I_CELL &eEqual) const
        { return *CELL <Iterator> ::OBJ == *eEqual.OBJ; }

        template <class Iterator> bool I_CELL <Iterator> ::
        operator > (const I_CELL &eEqual) const
        { return *CELL <Iterator> ::OBJ > *eEqual.OBJ; }
        //----------------------------------------------------------------------
//..............................................................................

//Structure deletion flagging of objects........................................
        template <class Type> D_CELL <Type> ::D_CELL() :
        DEL(false),
        SORT(false) {}

        template <class Type> void D_CELL <Type> ::operator << (Type oObj)
        //Set pointer
        { CELL <Type> ::OBJ = oObj; }

        template <class Type> void D_CELL <Type> ::operator = (int pPos)
        //Set position reference
        { CELL <Type> ::POS = pPos; }

        template <class Type> D_CELL <Type> ::operator const Type&() const
        //Set position reference
        { return CELL <Type> ::OBJ; }

        //Comparison operators (based on value)---------------------------------
        template <class Type> bool D_CELL <Type> ::
        operator < (const D_CELL &eEqual) const
        {
        if (!SORT) return CELL <Type> ::OBJ < eEqual.OBJ;
        if (DEL ^ eEqual.DEL) return DEL;
        return CELL <Type> ::POS < eEqual.POS;
        }

        template <class Type> bool D_CELL <Type> ::
        operator == (const D_CELL &eEqual) const
        {
        if (!SORT) return CELL <Type> ::OBJ == eEqual.OBJ;
        if (DEL ^ eEqual.DEL) return false;
        return CELL <Type> ::POS == eEqual.POS;
        }

        template <class Type> bool D_CELL <Type> ::
        operator > (const D_CELL &eEqual) const
        {
        if (!SORT) return CELL <Type> ::OBJ > eEqual.OBJ;
        if (DEL ^ eEqual.DEL) return eEqual.DEL;
        return CELL <Type> ::POS > eEqual.POS;
        }
        //----------------------------------------------------------------------
//..............................................................................

//Structure deletion flagging of iterators......................................
        template <class Iterator> ID_CELL <Iterator> ::ID_CELL() :
        DEL(false),
        SORT(false) {}

        template <class Iterator> void ID_CELL <Iterator> ::
        operator << (Iterator oObj)
        //Set pointer
        { CELL <Iterator> ::OBJ = oObj; }

        template <class Iterator> void ID_CELL <Iterator> ::
        operator = (int pPos)
        //Set position reference
        { CELL <Iterator> ::POS = pPos; }

        template <class Iterator> ID_CELL <Iterator> ::operator const typename
        ID_CELL <Iterator> ::Type&() const
        //Set position reference
        { return *CELL <Iterator> ::OBJ; }

        //Comparison operators (based on value)---------------------------------
        template <class Iterator> bool ID_CELL <Iterator> ::
        operator < (const ID_CELL &eEqual) const
        {
        if (!SORT) return *CELL <Iterator> ::OBJ < *eEqual.OBJ;
        if (DEL ^ eEqual.DEL) return DEL;
        return CELL <Iterator> ::POS < eEqual.POS;
        }

        template <class Iterator> bool ID_CELL <Iterator> ::
        operator == (const ID_CELL &eEqual) const
        {
        if (!SORT) return *CELL <Iterator> ::OBJ == *eEqual.OBJ;
        if (DEL ^ eEqual.DEL) return false;
        return CELL <Iterator> ::POS == eEqual.POS;
        }

        template <class Iterator> bool ID_CELL <Iterator> ::
        operator > (const ID_CELL &eEqual) const
        {
        if (!SORT) return *CELL <Iterator> ::OBJ > *eEqual.OBJ;
        if (DEL ^ eEqual.DEL) return eEqual.DEL;
        return CELL <Iterator> ::POS > eEqual.POS;
        }
        //----------------------------------------------------------------------
//..............................................................................
//==============================================================================
}

#endif
//==============================================================================
