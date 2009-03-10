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

//BasicComponents_______________________________________________________________
//(C) 2003-2005 Kevin P. Barry

//==============================================================================
#ifndef LIST_CPP
#define LIST_CPP LIST_HPP
#include "LIST.hpp"
#include "../FUNCTOR/FUNCTOR.cpp"
#include "LIST_ASSIST.cpp"

#ifndef CLIST_SEPARATE_INDEX

/*     DEFINE THIS TO COMPILE INDEX SEPARATELY (USED WHEN MULTIPLE OBJECT     *\
\*                        FILESUSING CLIST ARE LINKED)                        */

#include "INDEX.cpp"
#endif

namespace LIST_CPP
{

//CList function bodies=========================================================
        //Constructors----------------------------------------------------------
        template <class Type> CList <Type> ::CList(unsigned int mMax)
        //Constructor
        {
        for (int I = 0; I < FLAGS_USED; I++) Flags[I] = false;
        Reset(mMax);
        }

        template <class Type> CList <Type> ::CList(const CList <Type> &eEqual)
        //Copy constructor
        {
        for (int I = 0; I < FLAGS_USED; I++) Flags[I] = eEqual.Flags[I];
        Reset(eEqual.Index.Max());
        Resize(eEqual.Index.Size());
        for (int I = 0; I < (signed) Index.Size(); I++) Reference(I) = eEqual[I];
        Index = eEqual.Index;
        }
        //----------------------------------------------------------------------

        //Copy data=============================================================
        template <class Type> CList <Type> &CList <Type> ::
        CopyFrom(const CList <Type> &eEqual, int sStart, int sStop)
        //Erase list and copy elements
        {
        int RS1, RS2, RSIZE = eEqual.SET_RANGE(RS1, RS2, sStart, sStop);
        Reset(RSIZE);
        Resize(RSIZE);
        for (int I = 0; I < (signed) Index.Size(); I++) Reference(I) = eEqual[I + RS1];
        return *this;
        }

        template <class Type> template <class Iterator2> CList <Type> &CList <Type> ::
        CopyFrom(Iterator2 eEqual, unsigned int sSize)
        //Erase list and copy elements
        {
        Reset(sSize);
        Resize(sSize);
        for (int I = 0; I < (signed) Index.Size(); I++) Reference(I) = *eEqual++;
        return *this;
        }

        template <class Type> template <class Type2, class Function1>
        CList <Type> &CList <Type> ::FCopyFrom(const CList <Type2> &eEqual,
        Function1 fFunction, int sStart, int sStop)
        //Erase list and copy elements with functor pre-processing
        {
        int RS1, RS2, RSIZE = eEqual.SET_RANGE(RS1, RS2, sStart, sStop);
        Reset(RSIZE);
        Resize(RSIZE);
        for (int I = 0; I < (signed) Index.Size(); I++)
        Reference(I) = EVALUATE_1(fFunction, eEqual[I + RS1]);
        return *this;
        }

        template <class Type> template <class Iterator2, class Function1>
        CList <Type> &CList <Type> ::FCopyFrom(Iterator2 eEqual, unsigned int sSize,
        Function1 fFunction)
        //Erase list and copy elements with functor pre-processing
        {
        Reset(sSize);
        Resize(sSize);
        for (int I = 0; I < (signed) Index.Size(); I++)
        Reference(I) = EVALUATE_1(fFunction, *eEqual++);
        return *this;
        }
        //======================================================================

        //List maintenance======================================================
        //Add single element----------------------------------------------------
        template <class Type> template <class Type2> bool CList <Type> ::
        Add(const Type2 &nNew)
        //Add element
        {
        if (!Increment()) return false;
        Reference(S_MOD(LAST)) = nNew;
        return true;
        }

        template <class Type> typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Add()
        //Increase size if possible
        {
        if (Increment())
         {
        Reference(S_MOD(LAST)) = BASE_TYPE();
        return Reference(S_MOD(LAST));
         }
        else return Default();
        }
        //----------------------------------------------------------------------

        //Add multiple elements-------------------------------------------------
        template <class Type> bool CList <Type> ::
        Add(const CList <Type> &eEqual, int sStart, int sStop)
        //Add elements
        {
        int RS1, RS2, RSIZE = eEqual.SET_RANGE(RS1, RS2, sStart, sStop);
        if (RSIZE < 1) return true;
        if (!Increment(RSIZE)) return false;
        for (int I = 0; I < RSIZE; I++)
        Reference(Index.Size() - RSIZE + I) = eEqual[I + RS1];
        return true;
        }

        template <class Type>  template <class Iterator2> bool CList <Type> ::
        Add(Iterator2 eEqual, unsigned int nNum)
        //Add elements
        {
        if (!Increment(nNum)) return false;
        for (int I = 0; I < (signed) nNum; I++)
        Reference(Index.Size() - nNum + I) = *eEqual++;
        return true;
        }

        template <class Type> template <class Iterator2> unsigned int
        CList <Type> ::Add(Iterator2 bBegin, Iterator2 eEnd)
        //Add elements
        {
        unsigned int S = 0;
        bool Continue = true;

        while (bBegin < eEnd && Continue)
        if (Add(*bBegin++)) S++;
        else                Continue = false;

        return S;
        }

        template <class Type> template <class Type2, class Function1>
        bool CList <Type> ::FAdd(const CList <Type2> &eEqual,
        Function1 fFunction, int sStart, int sStop)
        //Add elements
        {
        int RS1, RS2, RSIZE = eEqual.SET_RANGE(RS1, RS2, sStart, sStop);
        if (RSIZE < 1) return true;
        if (!Increment(RSIZE)) return false;
        for (int I = 0; I < RSIZE; I++)
        Reference(Index.Size() - RSIZE + I) = EVALUATE_1(fFunction, eEqual[I + RS1]);
        return true;
        }

        template <class Type> template <class Iterator2, class Function1>
        bool CList <Type> ::FAdd(Iterator2 eEqual, unsigned int nNum,
        Function1 fFunction)
        //Add elements
        {
        if (!Increment(nNum)) return false;
        for (int I = 0; I < (signed) nNum; I++)
        Reference(Index.Size() - nNum + I) = EVALUATE_1(fFunction, *eEqual++);
        return true;
        }

        template <class Type> template <class Iterator2, class Function1>
        unsigned int CList <Type> ::FAdd(Iterator2 bBegin, Iterator2 eEnd,
        Function1 fFunction)
        //Add elements using a functor to preprocess
        {
        unsigned int S = 0;
        bool Continue = true;

        while (bBegin < eEnd && Continue)
        if ( Add( EVALUATE_1(fFunction, *bBegin++) ) ) S++;
        else                                           Continue = false;

        return S;
        }
        //----------------------------------------------------------------------

        //Insert single element-------------------------------------------------
        template <class Type> template <class Type2> bool CList <Type> ::
        Insert(int pPos, const Type2 &aAdd)
        //Insert element at position
        {
        if (!Add(aAdd)) return false;
        Shift(1, pPos);
        if (Index >= MOD(pPos)) Index++;
        return true;
        }

        template <class Type> typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Insert(int pPos)
        //Insert default element at position if possible
        {
        if (!Add(BASE_TYPE())) return Default();
        Shift(1, pPos);
        if (Index >= MOD(pPos)) Index++;
        return Reference(MOD(pPos));
        }
        //----------------------------------------------------------------------

        //Insert multiple elements----------------------------------------------

        //Elements are added to the end of the list, then the list is shifted
        //the appropriate number of positions to move the added elements into
        //the correct position.

        template <class Type> bool CList <Type> ::Insert(int pPos,
        const CList <Type> &lList, int sStart, int sStop)
        //Inserts multiple elements
        {
        int RS1, RS2, RSIZE = lList.SET_RANGE(RS1, RS2, sStart, sStop);
        if (RSIZE < 1) return true;
        if (!Increment(RSIZE)) return false;
        for (int I = 0; I < RSIZE; I++)
        Reference(Index.Size() - RSIZE + I) = lList[I + RS1];
        Shift(RSIZE, pPos);
        return true;
        }

        template <class Type> template <class Iterator2> bool CList <Type> ::
        Insert(int pPos, Iterator2 aAdd, unsigned int sSize)
        //Inserts multiple elements
        {
        if (sSize < 1) return true;
        if (!Increment(sSize)) return false;
        for (int I = 0; I < (signed) sSize; I++)
        Reference(Index.Size() - sSize + I) = *aAdd++;
        Shift(sSize, pPos);
        return true;
        }

        template <class Type> template <class Iterator2> unsigned int
        CList <Type> ::Insert(int pPos, Iterator2 bBegin, Iterator2 eEnd)
        //Insert multiple elements
        {
        int S = 0;
        Shift(S = Add(bBegin, eEnd), pPos);
        return S;
        }

        template <class Type> template <class Type2, class Function1>
        bool CList <Type> ::FInsert(int pPos, const CList <Type2> &lList,
        Function1 fFunction, int sStart, int sStop)
        //Inserts multiple elements with functor pre-processing
        {
        int RS1, RS2, RSIZE = lList.SET_RANGE(RS1, RS2, sStart, sStop);
        if (RSIZE < 1) return true;
        if (!Increment(RSIZE)) return false;
        for (int I = 0; I < RSIZE; I++)
        Reference(Index.Size() - RSIZE + I) = EVALUATE_1(fFunction, lList[I + RS1]);
        Shift(RSIZE, pPos);
        return true;
        }

        template <class Type> template <class Iterator2, class Function1>
        bool CList <Type> ::FInsert(int pPos, Iterator2 aAdd, unsigned int sSize,
        Function1 fFunction)
        //Inserts multiple elements with functor pre-processing
        {
        if (sSize < 1) return true;
        if (!Increment(sSize)) return false;
        for (int I = 0; I < (signed) sSize; I++)
        Reference(Index.Size() - sSize + I) = EVALUATE_1(fFunction, *aAdd++);
        Shift(sSize, pPos);
        return true;
        }

        template <class Type> template <class Iterator2, class Function1>
        unsigned int CList <Type> ::FInsert(int pPos, Iterator2 bBegin,
        Iterator2 eEnd, Function1 fFunction)
        //Insert multiple elements using a functor to preprocess
        {
        int S = 0;
        Shift(S = FAdd(bBegin, eEnd, fFunction), pPos);
        return S;
        }
        //----------------------------------------------------------------------

        //Replace elements------------------------------------------------------
        template <class Type> template <class Type2> CList <Type>
        &CList <Type> ::Replace(int pPos, const Type2 &eEqual)
        //Replace element
        {
        if (!Index.AtMin()) Reference(MOD(pPos)) = eEqual;
        return *this;
        }

        template <class Type> CList <Type> &CList <Type> ::Clear()
        //Sets all elements equal to  a default
        {
        //We cast to the return type to prevent this function from being used
        //for const element lists
        for (int I = 0; I < (signed) Index.Size(); I++)
        const_cast <RETURN_TYPE> (Reference(I)) = BASE_TYPE();
        return *this;
        }
        //----------------------------------------------------------------------

        //Remove elements-------------------------------------------------------
        template <class Type> CList <Type> &CList <Type> ::Remove(int pPos)
        //Remove specified element
        {
        if (!Index.AtMin())
         {
        Shift(-1, pPos);
        Decrement();
         }
        return *this;
        }

        template <class Type> template <class Type2> CList <Type> &CList <Type> ::
        Remove(CList <Type2> &lList, int sStart, int sStop)
        //Remove specified elements
        {
        //The list of elements to remove is copied, then sorted by position,
        //then the fast removal function removes the elements.
        if (Index.AtMin()) return *this;
        int RS1, RS2, RSIZE = lList.SET_RANGE(RS1, RS2, sStart, sStop);
        if (RSIZE < 1) return *this;

        PosContainer Temp;
        PosContainer TEMP;
        if (!CHECK_CAPACITY(Temp, RSIZE)) return *this;
        Temp.resize(RSIZE);
        if (!CHECK_CAPACITY(TEMP, RSIZE)) return *this;
        TEMP.resize(RSIZE);

        for (int I = 0; I < RSIZE; I++) TEMP[I] = Temp[I] = MOD(lList[I + RS1]);
        C_MSORT_(&Temp[0], &Temp[RSIZE], &TEMP[0], 0, RSIZE - 1);
        FAST_REM(&Temp[0], RSIZE);
        return *this;
        }

        template <class Type> template <class Iterator2> CList <Type>
        &CList <Type> ::Remove(Iterator2 pPos, unsigned int sSize)
        //Remove specified elements
        {
        //The array of elements to remove is copied, then sorted by position,
        //then the fast removal function removes the elements.
        if (Index.AtMin()) return *this;
        if (sSize < 1) return *this;

        PosContainer Temp;
        PosContainer TEMP;
        if (!CHECK_CAPACITY(Temp, sSize)) return *this;
        Temp.resize(sSize);
        if (!CHECK_CAPACITY(TEMP, sSize)) return *this;
        TEMP.resize(sSize);

        for (int I = 0; I < (signed) sSize; I++) TEMP[I] = Temp[I] = MOD(*pPos++);
        C_MSORT_(&Temp[0], &Temp[sSize], &TEMP[0], 0, sSize - 1);
        FAST_REM(&Temp[0], sSize);
        return *this;
        }

        template <class Type> CList <Type> &CList <Type> :: Remove(int sStart,
        int sStop)
        //Remove elements in range
        {
        if (Index.AtMin()) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 1) return *this;

        PosContainer Temp;
        PosContainer TEMP;
        if (!CHECK_CAPACITY(Temp, SIZE)) return *this;
        Temp.resize(SIZE);
        if (!CHECK_CAPACITY(TEMP, SIZE)) return *this;
        TEMP.resize(SIZE);

        for (int I = 0; I < SIZE; I++)  TEMP[I] = Temp[I] = MOD(I + S1);
        C_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1);
        FAST_REM(&Temp[0], SIZE);
        return *this;
        }

        template <class Type> template <class Type2>CList <Type>
        &CList <Type> ::RemoveElement(const Type2 &fFind)
        //Remove matching elements
        {
        if (Index.AtMin()) return *this;
        int Num = Number(fFind);

        PosContainer Temp;
        if (!CHECK_CAPACITY(Temp, Num)) return *this;
        Temp.resize(Num);

        Remove(&Temp[0], Find(fFind, &Temp[0]));
        return *this;
        }

        template <class Type> template <class Type2, class Function2>
        CList <Type> &CList <Type> ::FRemoveElement(const Type2 &fFind,
        Function2 fFunction)
        //Remove matching elements with functor comparison
        {
        if (Index.AtMin()) return *this;
        int Num = FNumber(fFind, fFunction);

        PosContainer Temp;
        if (!CHECK_CAPACITY(Temp, Num)) return *this;
        Temp.resize(Num);

        Remove(&Temp[0], FFind(fFind, &Temp[0], fFunction));
        return *this;
        }
        //----------------------------------------------------------------------

        //Keep elements---------------------------------------------------------
        template <class Type> CList <Type> &CList <Type> ::Keep(int pPos)
        //Keep specified element
        {
        if (Index.AtMin()) return *this;
        Reference(0) = Reference(MOD(pPos));
        Resize(1);
        return *this;
        }

        template <class Type> template <class Type2> CList <Type> &CList <Type> ::
        Keep(CList <Type2> &lList, int sStart, int sStop)
        //Keep specified elements
        {
        //The list of elements to keep is first copied, then sorted by list
        //position.  The appropriate elements are moved to the beginning of the
        //list, then the list size is parsed.
        if (Index.AtMin()) return *this;
        int RS1, RS2, RSIZE = lList.SET_RANGE(RS1, RS2, sStart, sStop);

        PosContainer Temp;
        PosContainer TEMP;
        if (!CHECK_CAPACITY(Temp, RSIZE)) return *this;
        Temp.resize(RSIZE);
        if (!CHECK_CAPACITY(TEMP, RSIZE)) return *this;
        TEMP.resize(RSIZE);

        for (int I = 0; I < RSIZE; I++) TEMP[I] = Temp[I] = MOD(lList[I + RS1]);
        C_MSORT_(&Temp[0], &Temp[RSIZE], &TEMP[0], 0, RSIZE - 1);
        FAST_KEEP(&Temp[0], RSIZE);
        return *this;
        }

        template <class Type> template <class Iterator2>
        CList <Type> &CList <Type> ::Keep(Iterator2 pPos, unsigned int sSize)
        //Keep specified elements
        {
        //The list of elements to keep is first copied, then sorted by list
        //position.  The appropriate elements are moved to the beginning of the
        //list, then the list size is parsed.
        if (Index.AtMin()) return *this;

        PosContainer Temp;
        PosContainer TEMP;
        if (!CHECK_CAPACITY(Temp, sSize)) return *this;
        Temp.resize(sSize);
        if (!CHECK_CAPACITY(TEMP, sSize)) return *this;
        TEMP.resize(sSize);

        for (int I = 0; I < (signed) sSize; I++) TEMP[I] = Temp[I] = MOD(*pPos++);
        C_MSORT_(&Temp[0], &Temp[sSize], &TEMP[0], 0, sSize - 1);
        FAST_KEEP(&Temp[0], sSize);
        return *this;
        }

        template <class Type> CList <Type> &CList <Type> ::Keep(int sStart,
        int sStop)
        //Keep elements in range
        {
        //This essentially reverses the range and calls the range Remove
        //function.  The endpoints are removed from the range so that the range
        //of kept elements includes the endpoints.
        if (Index.AtMin()) return *this;
        int T1, T2;
        if (Index.Size() - SET_RANGE(T1, T2, sStart, sStop) < 1) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, T2 + 1, T1 - 1);
        if (SIZE < 1) return *this;

        PosContainer Temp;
        PosContainer TEMP;
        if (!CHECK_CAPACITY(Temp, SIZE)) return *this;
        Temp.resize(SIZE);
        if (!CHECK_CAPACITY(TEMP, SIZE)) return *this;
        TEMP.resize(SIZE);

        for (int I = 0; I < SIZE; I++)  TEMP[I] = Temp[I] = S_MOD(I + S1);
        C_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1);
        FAST_REM(&Temp[0], SIZE);
        return *this;
        }

        template <class Type> template <class Type2> CList <Type>
        &CList <Type> ::KeepElement(const Type2 &fFind)
        //Keep matching elements
        {
        if (Index.AtMin()) return *this;
        int Num = Number(fFind);

        PosContainer Temp;
        if (!CHECK_CAPACITY(Temp, Num)) return *this;
        Temp.resize(Num);

        Keep(&Temp[0], Find(fFind, &Temp[0]));
        return *this;
        }

        template <class Type> template <class Type2, class Function2>
        CList <Type> &CList <Type> ::FKeepElement(const Type2 &fFind,
        Function2 fFunction)
        //Keep matching elements with functor comparison
        {
        if (Index.AtMin()) return *this;
        int Num = FNumber(fFind, fFunction);

        PosContainer Temp;
        if (!CHECK_CAPACITY(Temp, Num)) return *this;
        Temp.resize(Num);

        Keep(&Temp[0], FFind(fFind, &Temp[0], fFunction));
        return *this;
        }
        //----------------------------------------------------------------------
        //======================================================================

        //Get values  (if size == 0 default element is given)===================
        //Provide position------------------------------------------------------
        template <class Type> inline const CList <Type> &CList <Type> ::
        Get(int pPos, ASSIGN_TYPE rReturn) const
        //Get element
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(MOD(pPos));
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Get(int pPos)
        //Get element
        { return Index.AtMin()? Default() : Reference(MOD(pPos)); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Get(int pPos) const
        //Get element
        { return Index.AtMin()? Default() : Reference(MOD(pPos)); }

        template <class Type> inline const CList <Type> &CList <Type> ::
        Hold(int pPos, ASSIGN_TYPE rReturn) const
        //Get element, set Index
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(MOD(Index = pPos));
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Hold(int pPos)
        //Get element, set Index
        { return Index.AtMin()? Default() : Reference(MOD(Index = pPos)); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Hold(int pPos) const
        //Get element, set Index
        { return Index.AtMin()? Default() : Reference(MOD(Index = pPos)); }
        //----------------------------------------------------------------------

        //Get first element-----------------------------------------------------
        template <class Type> inline const CList <Type> &CList <Type> ::
        First(ASSIGN_TYPE rReturn) const
        //Get first element
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(FIRST);
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::First()
        //Get first element
        { return Index.AtMin()? Default() : Reference(FIRST); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::First() const
        //Get first element
        { return Index.AtMin()? Default() : Reference(FIRST); }

        template <class Type> inline const CList <Type> &CList <Type> ::
        HoldFirst(ASSIGN_TYPE rReturn) const
        //Get first element, set Index
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(MOD(Index = FIRST));
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::HoldFirst()
        //Get first element, set Index
        { return Index.AtMin()? Default() : Reference(MOD(Index = FIRST)); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::HoldFirst() const
        //Get first element, set Index
        { return Index.AtMin()? Default() : Reference(MOD(Index = FIRST)); }
        //----------------------------------------------------------------------

        //Get last element------------------------------------------------------
        template <class Type> inline const CList <Type> &CList <Type> ::
        Last(ASSIGN_TYPE rReturn) const
        //Get last element
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(S_MOD(LAST));
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Last()
        //Get last element
        { return Index.AtMin()? Default() : Reference(S_MOD(LAST)); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Last() const
        //Get last element
        { return Index.AtMin()? Default() : Reference(S_MOD(LAST)); }

        template <class Type> inline const CList <Type> &CList <Type> ::
        HoldLast(ASSIGN_TYPE rReturn) const
        //Get last element, set Index
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(Index = LAST);
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::HoldLast()
        //Get last element, set Index
        { return Index.AtMin()? Default() : Reference(Index = LAST); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::HoldLast() const
        //Get last element, set Index
        { return Index.AtMin()? Default() : Reference(Index = LAST); }
        //----------------------------------------------------------------------

        //Get current element---------------------------------------------------
        template <class Type> inline const CList <Type> &CList <Type> ::
        Current(ASSIGN_TYPE rReturn) const
        //Get current element
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(Index);
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Current()
        //Get current element
        { return Index.AtMin()? Default() : Reference(Index); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Current() const
        //Get current element
        { return Index.AtMin()? Default() : Reference(Index); }
        //----------------------------------------------------------------------

        //Get current element, increment Index----------------------------------
        template <class Type> inline const CList <Type> &CList <Type> ::
        Next(ASSIGN_TYPE rReturn) const
        //Get current element
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(Index++);
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Next()
        //Get current element
        { return Index.AtMin()? Default() : Reference(Index++); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Next() const
        //Get current element
        { return Index.AtMin()? Default() : Reference(Index++); }
        //----------------------------------------------------------------------

        //Decrement Index, get current element----------------------------------
        template <class Type> inline const CList <Type> &CList <Type> ::
        Previous(ASSIGN_TYPE rReturn) const
        //Get previous element
        {
        rReturn = Index.AtMin()? BASE_TYPE() : Reference(--Index);
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::Previous()
        //Get previous element
        { return Index.AtMin()? Default() : Reference(--Index); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Previous() const
        //Get previous element
        { return Index.AtMin()? Default() : Reference(--Index); }
        //----------------------------------------------------------------------
        //======================================================================

        //Get value and remove element (if size == 0 default element is given)==
        //Remove and give element at given position-----------------------------
        template <class Type> inline CList <Type> &CList <Type> ::
        Pull(int pPos, ASSIGN_TYPE rReturn)
        //Get and remove element
        {
        if (!Index.AtMin())
         {
        rReturn = Reference(MOD(pPos));
        Remove(pPos);
         }
        else rReturn = BASE_TYPE();

        return *this;
        }

        template <class Type> inline typename CList <Type> ::PULL_TYPE
        CList <Type> ::Pull(int pPos)
        //Get and remove element
        {
        BASE_TYPE Temp;
        Pull(pPos, Temp);
        return Temp;
        }
        //----------------------------------------------------------------------

        //Remove and give first element-----------------------------------------
        template <class Type> inline CList <Type> &CList <Type> ::
        PullFirst(ASSIGN_TYPE rReturn)
        //Get and remove first element
        { return Pull(FIRST, rReturn); }

        template <class Type> inline typename CList <Type> ::PULL_TYPE
        CList <Type> ::PullFirst()
        //Get and remove first element
        { return Pull(FIRST); }
        //----------------------------------------------------------------------

        //Remove and give last element------------------------------------------
        template <class Type> inline CList <Type> &CList <Type> ::
        PullLast(ASSIGN_TYPE rReturn)
        //Get and remove last element
        { return Pull(LAST, rReturn); }

        template <class Type> inline typename CList <Type> ::PULL_TYPE
        CList <Type> ::PullLast()
        //Get and remove last element
        { return Pull(LAST); }
        //----------------------------------------------------------------------

        //Remove and give current element---------------------------------------
        template <class Type> inline CList <Type> &CList <Type> ::
        PullCurrent(ASSIGN_TYPE rReturn)
        //Get and remove current element
        { return Pull(Index, rReturn); }

        template <class Type> inline typename CList <Type> ::PULL_TYPE
        CList <Type> ::PullCurrent()
        //Get and remove current element
        { return Pull(Index); }
        //----------------------------------------------------------------------

        //Remove and give current element, set Index----------------------------
        template <class Type> inline CList <Type> &CList <Type> ::
        PullHold(int pPos, ASSIGN_TYPE rReturn)
        //Get and remove element, set Index
        {
        Pull(Index = pPos, rReturn);
        return *this;
        }

        template <class Type> inline typename CList <Type> ::PULL_TYPE
        CList <Type> ::PullHold(int pPos)
        //Get and remove element, set Index
        { return Pull(Index = pPos); }
        //----------------------------------------------------------------------
        //======================================================================

        //Find functions========================================================
        //Find from position functions------------------------------------------
        template <class Type> template <class Type2> int CList <Type> ::
        FindFrom(const Type2 &fFind, int pPos) const
        //Finds first occurence starting at given position
        {
        if (Index.AtMin()) return NOT_FOUND;

        int S1, S2;
        FIND_RANGE(S1, S2, pPos);
        for (int I = S1; RevFind()? (I > S2) : (I < S2); RevFind()? I-- : I++)
        if (Reference(S_MOD(I)) == fFind) return S_MOD(I);

        return NOT_FOUND;
        }

        template <class Type> template <class Type2, class Iterator2> int
        CList <Type> ::FindFrom(const Type2 &fFind, int pPos,
        Iterator2 pPos2) const
        //Finds all occurences from given position
        {
        if (Index.AtMin()) return 0;

        int S1, S2, N = 0;
        FIND_RANGE(S1, S2, pPos);
        for (int I = S1; RevFind()? (I > S2) : (I < S2); RevFind()? I-- : I++)
        if (Reference(S_MOD(I)) == fFind) *(pPos2 + N++) = S_MOD(I);

        return N;
        }

        template <class Type> template <class Type2> int CList <Type> ::
        NumberFrom(const Type2 &fFind, int pPos) const
        //Finds number of occurences starting at given position
        {
        if (Index.AtMin()) return 0;

        int S1, S2, N = 0;
        FIND_RANGE(S1, S2, pPos);
        for (int I = S1; RevFind()? (I > S2) : (I < S2); RevFind()? I-- : I++)
        if (Reference(S_MOD(I)) == fFind) N++;

        return N;
        }
        //----------------------------------------------------------------------

        //Overloads for find from end-------------------------------------------
        template <class Type> template <class Type2> inline int CList <Type> ::
        Find(const Type2 &fFind) const
        //Finds first occurence
        { return FindFrom(fFind, RevFind()? LAST : FIRST); }

        template <class Type> template <class Type2, class Iterator2> inline int
        CList <Type> ::Find(const Type2 &fFind, Iterator2 pPos) const
        //Finds all occurences
        { return FindFrom(fFind, RevFind()? LAST : FIRST, pPos); }

        template <class Type> template <class Type2> inline int CList <Type> ::
        Number(const Type2 &fFind) const
        //Finds number of occurences
        { return NumberFrom(fFind, RevFind()? LAST : FIRST); }
        //----------------------------------------------------------------------

        //Functor pre-processing find from position functions-------------------
        template <class Type> template <class Type2, class Function2>
        int CList <Type> ::FFindFrom(const Type2 &fFind, int pPos,
        Function2 fFunction) const
        //Finds first occurence starting at given position
        {
        if (Index.AtMin()) return NOT_FOUND;

        int S1, S2;
        FIND_RANGE(S1, S2, pPos);
        for (int I = S1; RevFind()? (I > S2) : (I < S2); RevFind()? I-- : I++)
        if ( EVALUATE_2(fFunction, Reference(S_MOD(I)), fFind) ) return S_MOD(I);

        return NOT_FOUND;
        }

        template <class Type>
        template <class Type2, class Function2, class Iterator2>
        int CList <Type> ::FFindFrom(const Type2 &fFind, int pPos, Iterator2 pPos2,
        Function2 fFunction) const
        //Finds all occurences
        {
        if (Index.AtMin()) return 0;

        int S1, S2, N = 0;
        FIND_RANGE(S1, S2, pPos);
        for (int I = S1; RevFind()? (I > S2) : (I < S2); RevFind()? I-- : I++)
        if ( EVALUATE_2(fFunction, Reference(S_MOD(I)), fFind) )
        *(pPos2 + N++) = S_MOD(I);

        return N;
        }

        template <class Type> template <class Type2, class Function2>
        int CList <Type> ::FNumberFrom(const Type2 &fFind, int pPos,
        Function2 fFunction) const
        //Finds number of occurences starting at given position
        {
        if (Index.AtMin()) return 0;

        int S1, S2, N = 0;
        FIND_RANGE(S1, S2, pPos);
        for (int I = S1; RevFind()? (I > S2) : (I < S2); RevFind()? I-- : I++)
        if ( EVALUATE_2(fFunction, Reference(S_MOD(I)), fFind) ) N++;

        return N;
        }
        //----------------------------------------------------------------------

        //Overloads for functor find from end-----------------------------------
        template <class Type> template <class Type2, class Function2>
        inline int CList <Type> ::FFind(const Type2 &fFind, Function2 fFunction) const
        //Finds first occurence
        { return FFindFrom(fFind, RevFind()? LAST : FIRST, fFunction); }

        template <class Type>
        template <class Type2, class Function2, class Iterator2>
        inline int CList <Type> ::FFind(const Type2 &fFind, Iterator2 pPos,
        Function2 fFunction) const
        //Finds all occurences
        { return FFindFrom(fFind, RevFind()? LAST : FIRST, pPos, fFunction); }

        template <class Type> template <class Type2, class Function2>
        inline int CList <Type> ::FNumber(const Type2 &fFind, Function2 fFunction) const
        //Finds number of occurences
        { return FNumberFrom(fFind, RevFind()? LAST : FIRST, fFunction); }
        //----------------------------------------------------------------------
        //======================================================================

        //List processing functions=============================================
        //Sort functions--------------------------------------------------------
        //Default sort..........................................................
        template <class Type> CList <Type> &CList <Type> ::
        Sort(int sStart, int sStop)
        //Sorts using linear merge sort
        {
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        //If we aren't sorting iterators first and we aren't in inverted mode
        //then we can just call the sort function.
        if (!IteratorProcess() && !InvertedSortMode())
         {
        Container TEMP;
        if (!CHECK_CAPACITY(TEMP, SIZE)) return *this;
        TEMP.resize(SIZE);

        if (!COPY_SAVER(SIZE)) EQUAL(&TEMP[0], S1, S2);

        C_MSORT_(Element(0), Element(Index.Size()), &TEMP[0], S1, S2,
        RevProcess(), RevEquals());
         }

        else
        //Either the sort iterators flag is set or we are in inverted mode,
        //therefore we must pre-sort and then transpose.
         {
        Transposer TRANS;

        if (!PRE_SORT(Element(0), TRANS, S1, S2, true, true, InvertedSortMode(),
                      true, RevProcess(), RevEquals()))
        return *this;

        PRE_ORDER(&TRANS[0], SIZE);
        ORDER(Element(0), &TRANS[0], S1, S2);
         }

        return *this;
        }

        template <class Type> template <class Function2> CList <Type>
        &CList <Type> ::FSort(Function2 fFunction, int sStart, int sStop)
        //Sorts using linear merge sort using functor pre-comparison
        {
        //This is identical to the Sort function except we use the functor
        //versions of the functions called.
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        if (!IteratorProcess() && !InvertedSortMode())
         {
        Container TEMP;
        if (!CHECK_CAPACITY(TEMP, SIZE)) return *this;
        TEMP.resize(SIZE);

        if (!COPY_SAVER(SIZE)) EQUAL(&TEMP[0], S1, S2);

        FC_MSORT_(Element(0), Element(Index.Size()), &TEMP[0], S1, S2, fFunction,
        RevProcess(), RevEquals());
         }

         else
         {
        Transposer TRANS;

        if (!FPRE_SORT(Element(0), TRANS, S1, S2, IteratorProcess(), true,
                       InvertedSortMode(), true, RevProcess(), RevEquals(),
                       fFunction))
        return *this;

        PRE_ORDER(&TRANS[0], SIZE);
        ORDER(Element(0), &TRANS[0], S1, S2);
         }

        return *this;
        }
        //......................................................................

        //Sort with external reference..........................................
        template <class Type> template <class Iterator2> CList <Type>
        &CList <Type> ::RSort(Iterator2 rRef, int sStart, int sStop)
        //Sorts using linear merge sort based on reference
        {
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        //Here we presort the reference then transpose our own elements.
        Transposer TRANS;

        if (!PRE_SORT(rRef, TRANS, 0, SIZE - 1, RefIteratorProcess(), false,
                      InvertedSortMode(), true, RevProcess(), RevEquals()))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);
        ORDER(Element(0), &TRANS[0], S1, S2);

        return *this;
        }

        template <class Type> template <class Type2> CList <Type> &CList <Type> ::
        CSort(const CList <Type2> &rRef, int sStart, int sStop, int rRefStart)
        //Sorts using linear merge sort based on reference
        {
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        //First we check to see that there are enough elements in the reference.
        int RS1, RS2, RSIZE = rRef.SET_RANGE(RS1, RS2, rRefStart,
                                             rRefStart + SIZE - 1);
        if (RSIZE != SIZE) return *this;

        Transposer TRANS;

        //Here we call the reference list's own presorting function while
        //using our own flags.
        if (!rRef.PRE_SORT(rRef.Element(0), TRANS, RS1, RS2, rRef.IteratorProcess(),
                           true, InvertedSortMode(), false, RevProcess(), RevEquals()))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);
        ORDER(Element(0), &TRANS[0], S1, S2);

        return *this;
        }

        template <class Type> template <class Function2, class Iterator2>
        CList <Type> &CList <Type> ::FRSort(Iterator2 rRef, Function2 fFunction,
        int sStart, int sStop)
        //Sorts using linear merge sort based on reference using functor
        {
        //Identical to RSort but with a functor
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        Transposer TRANS;

        if (!FPRE_SORT(rRef, TRANS, 0, SIZE - 1, RefIteratorProcess(), false,
                       InvertedSortMode(), true, RevProcess(), RevEquals(),
                       fFunction))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);
        ORDER(Element(0), &TRANS[0], S1, S2);

        return *this;
        }

        template <class Type> template <class Function2, class Type2>
        CList <Type> &CList <Type> ::FCSort(const CList <Type2> &rRef,
        Function2 fFunction, int sStart, int sStop, int rRefStart)
        //Sorts using linear merge sort based on reference using functor
        {
        //Identical to CSort but with a functor
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        int RS1, RS2, RSIZE = rRef.SET_RANGE(RS1, RS2, rRefStart,
                                             rRefStart + SIZE - 1);
        if (RSIZE != SIZE) return *this;

        Transposer TRANS;

        if (!rRef.FPRE_SORT(rRef.Element(0), TRANS, RS1, RS2, rRef.IteratorProcess(),
                            true, InvertedSortMode(), false, RevProcess(), RevEquals(),
                            fFunction))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);
        ORDER(Element(0), &TRANS[0], S1, S2);

        return *this;
        }
        //......................................................................

        //Master sorting functions..............................................
        template <class Type>
        template <class Iterator2> const CList <Type>
        &CList <Type> ::RMasterSort(Iterator2 rRef, int sStart, int sStop) const
        //Sorts reference using this as a reference
        {
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        Transposer TRANS;

        //Here we presort our own elements.
        if (!PRE_SORT(Element(0), TRANS, S1, S2, IteratorProcess(), true,
                      InvertedSortMode(), false, RevProcess(), RevEquals()))
        return *this;

        //If we are not inverting then the Transposer needs PRE_ORDER in order
        //to sort the external data.
        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);

        //Regardless of the mode we call ORDER to order the reference.
        ORDER(rRef, &TRANS[0], 0, SIZE - 1);

        return *this;
        }

        template <class Type> template <class Type2> const CList <Type> &CList <Type> ::
        CMasterSort(CList <Type2> &rRef, int sStart, int sStop, int rRefStart) const
        //Sorts reference using this as a reference
        {
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        //First we check to see that there are enough elements in the reference.
        int RS1, RS2, RSIZE = rRef.SET_RANGE(RS1, RS2, rRefStart,
                                             rRefStart + SIZE - 1);
        if (RSIZE != SIZE) return *this;

        Transposer TRANS;

        //Here we call the presorting function.
        if (!PRE_SORT(Element(0), TRANS, S1, S2, IteratorProcess(), true,
                      InvertedSortMode(), false, RevProcess(), RevEquals()))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);

        //Here we call the reference list's own ORDER function.
        rRef.ORDER(rRef.Element(0), &TRANS[0], RS1, RS2);

        return *this;
        }

        template <class Type> template <class Function2, class Iterator2>
        const CList <Type> &CList <Type> ::FRMasterSort(Iterator2 rRef,
        Function2 fFunction, int sStart, int sStop) const
        //Sorts reference using this as a reference using functor
        {
        //This is identical to the MasterSort function except we use the functor
        //versions of the functions called.
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        Transposer TRANS;

        if (!FPRE_SORT(Element(0), TRANS, S1, S2, IteratorProcess(), true,
                       InvertedSortMode(), false, RevProcess(), RevEquals(),
                       fFunction))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);

        ORDER(rRef, &TRANS[0], 0, SIZE - 1);

        return *this;
        }

        template <class Type> template <class Function2, class Type2>
        const CList <Type> &CList <Type> ::FCMasterSort(CList <Type2> &rRef,
        Function2 fFunction, int sStart, int sStop, int rRefStart) const
        //Sorts reference using this as a reference using functor
        {
        //Identical to CSort but with a functor
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        int RS1, RS2, RSIZE = rRef.SET_RANGE(RS1, RS2, rRefStart,
                                             rRefStart + SIZE - 1);
        if (RSIZE != SIZE) return *this;

        Transposer TRANS;

        if (!FPRE_SORT(Element(0), TRANS, S1, S2, IteratorProcess(), true,
                       InvertedSortMode(), false, RevProcess(), RevEquals(),
                       fFunction))
        return *this;

        if (!InvertedSortMode()) PRE_ORDER(&TRANS[0], SIZE);
        rRef.ORDER(rRef.Element(0), &TRANS[0], RS1, RS2);

        return *this;
        }
        //......................................................................

        //Verify order..........................................................
        template <class Type> bool CList <Type> ::Verify(int sStart,
        int sStop) const
        //Verifies ascending order
        {
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);

        for (int I = S1; I < S2; I++)
         {
        CONST_RETURN_TYPE VAL1( Reference(S_MOD(I    )) );
        CONST_RETURN_TYPE VAL2( Reference(S_MOD(I + 1)) );

        if (RevProcess()) if (VAL1 < VAL2) return false;
        else; else        if (VAL2 < VAL1) return false;
         }

        return true;
        }

        template <class Type> template <class Function2> bool CList <Type> ::
        FVerify(Function2 fFunction, int sStart, int sStop) const
        //Verifies ascending order using functor
        {
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);

        for (int I = S1; I < S2; I++)
         {
        if (RevProcess())
        if ( EVALUATE_2( fFunction, Convert(Reference( S_MOD(I) )),
                                    Convert(Reference( S_MOD(I + 1) )) ) )
        return false;

        else; else
        if ( EVALUATE_2( fFunction, Convert(Reference( S_MOD(I + 1) )),
                                    Convert(Reference( S_MOD(I) ))      ) )
        return false;
         }

        return true;
        }
        //......................................................................
        //----------------------------------------------------------------------

        //Reverse elements------------------------------------------------------
        template <class Type> CList <Type> &CList <Type> ::
        Reverse(int sStart, int sStop)
        //Reverses order of elements
        {
        //Here we start by finding the range.  Then we make a reference array
        //the same size as the range with values numbered from one less than the
        //size to 0.  We then ORDER the range of elements based on this
        //reference.
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;

        PosContainer TRANS;
        if (!CHECK_CAPACITY(TRANS, SIZE)) return *this;
        TRANS.resize(SIZE);

        for (int I = SIZE - 1; I > -1; I--) TRANS[SIZE - I - 1] = I;
        ORDER(Element(0), &TRANS[0], S1, S2);
        return *this;
        }
        //----------------------------------------------------------------------

        //Randomize order-------------------------------------------------------
        template <class Type> CList <Type> &CList <Type> ::
        Randomize(int sStart, int sStop)
        //Randomizes order of items
        {
        //Here we create a reference array of random numbers.  We then sort
        //this reference, and ORDER the list based on the reference.
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;
        bool PreCopy = !COPY_SAVER(SIZE);

        typename LIST_CONTAINER <CELL <int> > ::TYPE Temp;
        typename LIST_CONTAINER <CELL <int> > ::TYPE TEMP;
        if (!CHECK_CAPACITY(Temp, SIZE)) return *this;
        Temp.resize(SIZE);
        if (!CHECK_CAPACITY(TEMP, SIZE)) return *this;
        TEMP.resize(SIZE);

        for (int I = 0; I < SIZE; I++)
         {
        Temp[I] << rand() * rand();
        Temp[I] = I;
        if (PreCopy) TEMP[I] = Temp[I];
         }

        C_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1);
        ORDER(Element(0), &Temp[0], S1, S2);
        return *this;
        }
        //----------------------------------------------------------------------

        //Shift elements--------------------------------------------------------
        template <class Type> CList <Type> &CList <Type> ::
        Shift(int nNum, int sStart, int sStop)
        //Shifts elements
        {
        //Given the number of elements being shifted N: we start our iteration
        //by subtracting parsed N from the size of the range.  We then number a
        //reference starting with that number, incrementing it each time.  The
        //element at the -Nth position of the range will now be at position 0 of
        //the range, therefore we ORDER the list using this reference.
        if (nNum == 0) return *this;
        if (Index.Size() < 2) return *this;
        int S1, S2, SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (SIZE < 2) return *this;
        int N = ( (nNum > 0)? (-nNum % SIZE + SIZE) : (-nNum % SIZE) );

        PosContainer Temp(SIZE);
        if (!CHECK_CAPACITY(Temp, SIZE)) return *this;
        Temp.resize(SIZE);

        for (int I = 0; I < SIZE; I++)
        Temp[(I + N >= SIZE)? I + N - SIZE : I + N] = I;
        ORDER(Element(0), &Temp[0], S1, S2);
        return *this;
        }
        //----------------------------------------------------------------------

        //Remove duplicate elements---------------------------------------------
        template <class Type> CList <Type> &CList <Type> ::
        RemoveDuplicates(int sStart, int sStop)
        //Removes all duplicate elements
        {
        if (Index.Size() == 0) return *this;
        PosContainer Temp;
        int P = FIND_D(Temp, sStart, sStop);
        FAST_REM(&Temp[0], P);
        return *this;
        }

        template <class Type> template <class Type2> CList <Type> &CList <Type> ::
        RemoveDuplicates(CList <Type2> &pPos, int sStart, int sStop)
        //Removes all duplicate elements, stores positions of removed elements
        {
        if (Index.Size() == 0) return *this;
        PosContainer Temp;
        int P = FIND_D(Temp, sStart, sStop);
        pPos.CopyFrom(FAST_REM(&Temp[0], P), P);
        return *this;
        }

        template <class Type> template <class SortFunction2, class FindFunction2>
        CList <Type> &CList <Type> ::FRemoveDuplicates(SortFunction2 sSort,
        FindFunction2 fFind, int sStart, int sStop)
        //Removes all duplicate elements
        {
        if (Index.Size() == 0) return *this;
        PosContainer Temp;
        int P = FFIND_D(Temp, sStart, sStop, sSort, fFind);
        FAST_REM(&Temp[0], P);
        return *this;
        }

        template <class Type> template <class SortFunction2, class FindFunction2, class Type2>
        CList <Type> &CList <Type> ::FRemoveDuplicates(CList <Type2> &pPos,
        SortFunction2 sSort, FindFunction2 fFind, int sStart, int sStop)
        //Removes all duplicate elements, stores positions of removed elements
        {
        if (Index.Size() == 0) return *this;
        PosContainer Temp;
        int P = FFIND_D(Temp, sStart, sStop, sSort, fFind);
        pPos.CopyFrom(FAST_REM(&Temp[0], P), P);
        return *this;
        }
        //----------------------------------------------------------------------
        //======================================================================

        //Size operations=======================================================
        template <class Type> inline unsigned int CList <Type> ::Size() const
        //Return size of list
        { return Index.Size(); }

        template <class Type> inline unsigned int CList <Type> ::
        Resize(unsigned int sSize)
        //Sets size of list
        {
        (sSize < Index.Size())? Decrement(Index.Size() - sSize) :
                                Increment(sSize - Index.Size());
        return Index.Size();
        }

        template <class Type> inline int CList <Type> ::SectionSize(int sStart,
        int sStop) const
        //Returns size of element range
        {
        int B, E, SIZE = SET_RANGE(B, E, sStart, sStop);
        return SIZE;
        }

        template <class Type> bool CList <Type> ::Increment(unsigned int sSize)
        //Increments size if possible
        {
        bool Unlimited = !Index.Max();

        if (Unlimited && !CHECK_CAPACITY(LIST, Index.Size() + sSize)) return false;
        if (!Unlimited && (Index.Max() < Index.Size() + sSize)) return false;

        if (Unlimited) Index.SET_SIZE(Allocate(Index.Size() + sSize));
        else Index.SET_SIZE(Index.Size() + sSize);

        return true;
        }

        template <class Type> bool CList <Type> ::Decrement(unsigned int sSize)
        //Decrements size if possible
        {
        bool Unlimited = !Index.Max();
        if (Index.Size() < sSize) return false;

        //Here we allocate to the new size to erase/destruct the old elements
        Allocate(Index.Size() - sSize);

        //Here we re-allocate the max size if necessary
        if (!Unlimited) Allocate(Index.Max());

        //The new size becomes what was requested
        Index.SET_SIZE(Index.Size() - sSize);
        return true;
        }

        template <class Type> inline unsigned int CList <Type> ::Max() const
        //Return max size
        { return Index.Max(); }

        template <class Type> inline unsigned int CList <Type> ::
        NewMax(unsigned int mMax)
        //Sets new max size
        {
        if (mMax) return Index.SET_MAX(Allocate(mMax));
        Index.SET_MAX(0);
        Allocate(Index.Size());
        return 0;
        }
        template <class Type> CList <Type> &CList <Type> ::
        Reset(unsigned int mMax)
        //Clears list, sets max size
        {
        //Here we erase all data and set the size to 0
        Index.SET_SIZE(Allocate(0));

        //If we are limiting the size, we allocate the entire list...
        if (mMax) Index.SET_MAX(Allocate(mMax));
        //...otherwise we set the max to unlimited
        else Index.SET_MAX(0);

        return *this;
        }
        //======================================================================

        //Operators=============================================================
        template <class Type> CList <Type> &CList <Type> ::
        operator = (const CList <Type> &eEqual)
        //Assignment operator
        {
        //We do not copy flags here; we just copy size, capacity, and data
        Reset(eEqual.Index.Max());
        Resize(eEqual.Index.Size());
        for (int I = 0; I < (signed) eEqual.Index.Size(); I++) Reference(I) = eEqual[I];
        Index = eEqual.Index;
        return *this;
        }

        template <class Type> CList <Type> &CList <Type> ::
        operator = (typename ListTypes <Type> ::CONST_RETURN_TYPE eEqual)
        //Assignment operator
        {
        //We cast to the return type to prevent this function from being used
        //for const element lists
        for (int I = 0; I < (signed) Index.Size(); I++)
        const_cast <RETURN_TYPE> (Reference(I)) = eEqual;
        return *this;
        }

        template <class Type> inline typename CList <Type> ::RETURN_TYPE
        CList <Type> ::operator [] (int pPos)
        //Returns element reference
        {
        if (Index.AtMin()) return Default();
        return Reference(MOD(pPos));
        }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::operator [] (int pPos) const
        //Returns element reference
        {
        if (Index.AtMin()) return Default();
        return Reference(MOD(pPos));
        }

        template <class Type> inline CList <Type> &CList <Type> ::
        operator >> (int sShift)
        //Shift elements forward
        { return Shift(sShift, FIRST, LAST); }

        template <class Type> inline CList <Type> &CList <Type> ::
        operator << (int sShift)
        //Shift elements reverse
        { return Shift(-sShift, FIRST, LAST); }

        template <class Type> inline int CList <Type> ::operator ++ (int)
        //Increments index (postfix)
        { return Index++; }

        template <class Type> inline int CList <Type> ::operator ++ ()
        //Increments index (prefix)
        { return ++Index; }

        template <class Type> inline int CList <Type> ::operator -- (int)
        //Decrements index (postfix)
        { return Index--; }

        template <class Type> inline int CList <Type> ::operator -- ()
        //Decrements index (prefix)
        { return --Index; }
        //======================================================================

        //Flags=================================================================
        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> ::RevProcess()
        //Reverse processing flag
        { return Flags[0]; }

        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> ::RevEquals()
        //Reverse equal elements against process direction flag
        { return Flags[1]; }

        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> ::RevFind() const
        //Find in reverse flag
        { return Flags[2]; }

        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> :: CrossEndsFind() const
        //Cross begin/end points when searching flag
        { return Flags[3]; }

        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> ::IteratorProcess()
        //Process iterators instead of values flag
        { return Flags[4]; }

        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> ::RefIteratorProcess()
        //Process iterators of reference data instead of values flag
        { return Flags[5]; }

        template <class Type> inline typename CList <Type> ::
        Flag &CList <Type> ::InvertedSortMode()
        //Sets inverted mode
        { return Flags[6]; }
        //======================================================================

        //Constant flags========================================================
        template <class Type> inline const typename CList <Type> ::
        Flag &CList <Type> ::RevProcess() const
        //Reverse processing flag
        { return Flags[0]; }

        template <class Type> inline const typename CList <Type> ::
        Flag &CList <Type> ::RevEquals() const
        //Reverse equal elements against process direction flag
        { return Flags[1]; }

        template <class Type> inline const typename CList <Type> ::
        Flag &CList <Type> ::IteratorProcess() const
        //Process iterators instead of values flag
        { return Flags[4]; }

        template <class Type> inline const typename CList <Type> ::
        Flag &CList <Type> ::RefIteratorProcess() const
        //Process iterators of reference data instead of values flag
        { return Flags[5]; }

        template <class Type> inline const typename CList <Type> ::
        Flag &CList <Type> ::InvertedSortMode() const
        //Sets inverted mode
        { return Flags[6]; }
        //======================================================================

        //Assist functions------------------------------------------------------
        template <class Type> inline int CList <Type> ::
        MOD(int pPos) const
        //Returns valid array pos from int
        { return Index[pPos]; }

        template <class Type> inline int CList <Type> ::SET_RANGE(int &lLo,
        int &hHi, int sStart, int sStop) const
        //Sets range
        {
        if (Index.Size() < 1) return lLo = hHi = 0;
        lLo = MOD(sStart);
        hHi = MOD(sStop);
        if (lLo > hHi) hHi += Index.Size();
        return hHi - lLo + 1;
        }

        template <class Type> inline int CList <Type> ::
        FIND_RANGE(int &bBegin, int &eEnd, int pPos) const
        //Set find range
        {
        bBegin = MOD(pPos);

        if (CrossEndsFind())
        if (RevFind())       eEnd = bBegin - (signed) Index.Size();
        else                 eEnd = bBegin + (signed) Index.Size();
        else if (RevFind())  eEnd = -1;
        else                 eEnd = Index.Size();

        return eEnd - bBegin;
        }

        template <class Type> inline bool CList <Type> ::
        COPY_SAVER(unsigned int sSize) const
        //Predicts if copy is needed prior to sorting
        {
        unsigned int CC = 1;
        bool IT = false;
        while ((CC += CC) < sSize) IT = !IT;
        return IT;
        }

        template <class Type> template <class Type2> inline bool CList <Type> ::
        CHECK_CAPACITY(const Type2 &cCont, unsigned int sSize) const
        //Check for total space
        { return cCont.max_size() >= sSize; }
        //----------------------------------------------------------------------

        //Sort/sort assist functions--------------------------------------------
        //Sort..................................................................
//Circular linear merge sort****************************************************
//(C) 2003-2005 Kevin P. Barry

        template <class Type> template <class Iterator2> void CList <Type> ::
        C_MSORT_(Iterator2 lListBegin, Iterator2 lListEnd, Iterator2 tTemp,
        unsigned int sStart, unsigned int sStop, bool rRev, bool eEqual)
        //Circular linear merge sort
        {
        //Instantiate iterators and integers====================================
        //Fixed values----------------------------------------------------------
        int DataSize  = sStop - sStart + 1,
            TotalSize = lListEnd - lListBegin;
        //----------------------------------------------------------------------

        //Each cycle------------------------------------------------------------
        Iterator2 ReadMin,  ReadMax,  ReadStart,
                  WriteMin, WriteMax, WriteStart;

        int ReadSection  = 1, ReadSize,
            WriteSection = 2, WriteSize;
        //----------------------------------------------------------------------

        //Each iteration--------------------------------------------------------
        Iterator2 ReadLeft, ReadRight, Write;

        int ReadLeftCount, ReadRightCount;
        //----------------------------------------------------------------------
        //======================================================================

        //Determine initial read/write lists====================================
        int RequiredSection = 1;
        bool Direction = false;
        while ((RequiredSection *= 2) < DataSize) Direction = !Direction;
        //Predict sort iterations (Direction is about = !(ceil(log2(Size)) % 2))
        //======================================================================

        //Sort==================================================================
        while (ReadSection < RequiredSection)
         {
        //Set cycle limits------------------------------------------------------
        //processes about log2(Size) times
        if (Direction)
          {
        //The read data points are set to the actual data and the write data
        //points are set to the temporary data.
        ReadStart  = lListBegin + sStart;    WriteStart = tTemp;
        ReadMin    = lListBegin;             WriteMin   = tTemp;
        ReadMax    = lListEnd;               WriteMax   = tTemp + DataSize;
          }

        else
          {
        //The read data points are set to the temporary data and the write data
        //points are set to the actual data.
        ReadStart  = tTemp;                  WriteStart = lListBegin + sStart;
        ReadMin    = tTemp;                  WriteMin   = lListBegin;
        ReadMax    = tTemp + DataSize;       WriteMax   = lListEnd;
          }

        //The read and write sizes are found by subtracting the ranges.
        ReadSize  = ReadMax  - ReadMin;      WriteSize = WriteMax - WriteMin;

        //Of course, we need to make sure to switch the next time around.
        Direction = !Direction;
        //----------------------------------------------------------------------

        //Linear processing of sort sections------------------------------------
        //processes about Size x log2(Size) / 2 times
        for (int I = 0; I < DataSize; I += WriteSection)
          {
        //Set iteration parameters based on cycle limits........................

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
        //......................................................................

        //Compare and transpose.................................................
        //processes about Size x log2(Size) times
        while (ReadLeftCount && ReadRightCount)
           {
        if (eEqual)

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (rRev ^ ( Convert(*ReadLeft) < Convert(*ReadRight) ))
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
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        else

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (rRev ^ ( Convert(*ReadRight) < Convert(*ReadLeft) ))
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
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           }
        //......................................................................

        //Fill in excess elements...............................................
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
        //......................................................................
          }
        //----------------------------------------------------------------------

        WriteSection += (ReadSection = WriteSection);
         }
        //======================================================================
        }

        template <class Type> template <class Function2, class Iterator2>
        void CList <Type> ::FC_MSORT_(Iterator2 lListBegin, Iterator2 lListEnd,
        Iterator2 tTemp, unsigned int sStart, unsigned int sStop,
        Function2 fFunction, bool rRev, bool eEqual)
        //Circular linear merge sort with functor processing
        {
        //This is identical to the other C_MSORT_ except here we run the
        //elements through a functor before we compare them.  I purposely didn't
        //duplicate the notes because if I revise them I don't want to change
        //them twice.

        //Instantiate iterators and integers====================================
        //Fixed values----------------------------------------------------------
        int DataSize  = sStop - sStart + 1,
            TotalSize = lListEnd - lListBegin;
        //----------------------------------------------------------------------

        //Each cycle------------------------------------------------------------
        Iterator2 ReadMin,  ReadMax,  ReadStart,
                  WriteMin, WriteMax, WriteStart;

        int ReadSection  = 1, ReadSize,
            WriteSection = 2, WriteSize;
        //----------------------------------------------------------------------

        //Each iteration--------------------------------------------------------
        Iterator2 ReadLeft, ReadRight, Write;

        int ReadLeftCount, ReadRightCount;
        //----------------------------------------------------------------------
        //======================================================================

        //Determine initial read/write lists====================================
        int RequiredSection = 1;
        bool Direction = false;
        while ((RequiredSection *= 2) < DataSize) Direction = !Direction;
        //======================================================================

        //Sort==================================================================
        while (ReadSection < RequiredSection)
         {
        //Set cycle limits------------------------------------------------------
        if (Direction)
          {
        ReadStart  = lListBegin + sStart;    WriteStart = tTemp;
        ReadMin    = lListBegin;             WriteMin   = tTemp;
        ReadMax    = lListEnd;               WriteMax   = tTemp + DataSize;
          }

        else
          {
        ReadStart  = tTemp;                  WriteStart = lListBegin + sStart;
        ReadMin    = tTemp;                  WriteMin   = lListBegin;
        ReadMax    = tTemp + DataSize;       WriteMax   = lListEnd;
          }

        ReadSize  = ReadMax  - ReadMin;      WriteSize = WriteMax - WriteMin;

        Direction = !Direction;
        //----------------------------------------------------------------------

        //Linear processing of sort sections------------------------------------
        for (int I = 0; I < DataSize; I += WriteSection)
          {
        //Set iteration parameters based on cycle limits........................
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
        //......................................................................

        //Compare and transpose.................................................
        while (ReadLeftCount && ReadRightCount)
           {
        if (eEqual)

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if ( rRev ^ EVALUATE_2( fFunction, Convert(*ReadLeft),
                                           Convert(*ReadRight) ) )
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
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        else

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if ( rRev ^ EVALUATE_2( fFunction, Convert(*ReadRight),
                                           Convert(*ReadLeft)   ) )
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
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           }
        //......................................................................

        //Fill in excess elements...............................................
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
        //......................................................................
          }
        //----------------------------------------------------------------------

        WriteSection += (ReadSection = WriteSection);
         }
        //======================================================================
        }

//******************************************************************************
        //......................................................................

        //Copy elements.........................................................
        template <class Type> void CList <Type> ::EQUAL(Iterator iIter,
        int sStart, int sStop) const
        //Copy elements directly from list data
        {
        int S1, S2;
        int SIZE = SET_RANGE(S1, S2, sStart, sStop);
        for (int I = 0; I < SIZE; I++) *(iIter + I) = Reference(S_MOD(I + S1));
        }
        //......................................................................

        //Order by reference....................................................
        template <class Type> void CList <Type> ::
        PRE_ORDER(CELL <int> *const pPos, int sSize) const
        //Transposes reference list before using it to sort data
        {
        //For this to perform correctly, the CELL array must contain all
        //numbers from 0 through 1 less than the number of elements as their OBJ
        //values (which is why it is a private function.)  Here we start with
        //the first element and switch it with whatever element is at the
        //position given by the OBJ value.  Once the first element has 0 as its
        //OBJ value, we move to the 2nd element and do the same thing until it
        //has an element with an OBJ value of 1, etc.  This performs no more
        //than one switch per each element in the array.  This function
        //basically undoes the sort operation.  After this function is complete,
        //the POS value of each CELL tells us where the element at that given
        //position should be on the sorted list.
        int P = 0;
        CELL <int> Temp;
        while (P < sSize - 1)
         {
        while (P != pPos[P].OBJ)
          {
        Temp = pPos[pPos[P].OBJ];
        pPos[pPos[P].OBJ] = pPos[P];
        pPos[P] = Temp;
          }
        P++;
         }
        }

        //ORDER functions perform similar to PRE_ORDER, however we are looking
        //at POS values here, and we also move the reference elements every time
        //we move a CELL element.  This means that there will be no more
        //element switches than there are elements.  This gives us the benifit
        //of using IteratorProcess for large objects: sorting by object will
        //copy the elements at most 2log[2](N) where N is the number of elements
        //therefore we use iterators for the sort, then ORDER to actually move
        //the elements.  This is also how we sort elements based on the order of
        //a reference.

        template <class Type> template <class Iterator2, class T> void
        CList <Type> ::ORDER(Iterator2 lList, CELL <T> *const pPos, int sStart,
        int sStop) const
        //Orders list by reference positions
        {
        int P = 0, S;
        typename std::iterator_traits <Iterator2> ::value_type Temp;
        while (P < sStop - sStart)
         {
        while (P != pPos[P].POS)
          {
        Temp = lList[S_MOD(sStart + pPos[P].POS)];
        lList[S_MOD(sStart + pPos[P].POS)] = lList[S_MOD(sStart + P)];
        lList[S_MOD(sStart + P)] = Temp;

        S = pPos[pPos[P].POS].POS;
        pPos[pPos[P].POS].POS = pPos[P].POS;
        pPos[P].POS = S;
          }
        P++;
         }
        }

        template <class Type> template <class Iterator2> void CList <Type> ::
        ORDER(Iterator2 lList, int *pPos, int sStart, int sStop) const
        //Orders list by reference positions
        {
        int P = 0, S;
        typename std::iterator_traits <Iterator2> ::value_type Temp;
        while (P < sStop - sStart)
         {
        while (P != pPos[P])
          {
        Temp = lList[S_MOD(sStart + pPos[P])];
        lList[S_MOD(sStart + pPos[P])] = lList[S_MOD(sStart + P)];
        lList[S_MOD(sStart + P)] = Temp;

        S = pPos[pPos[P]];
        pPos[pPos[P]] = pPos[P];
        pPos[P] = S;
          }
        P++;
         }
        }
        //......................................................................

        //Pre-sorting functions.................................................
        template <class Type> template <class Iterator2> bool CList <Type> ::
        PRE_SORT(Iterator2 iIterator, CList <Type> ::Transposer &tTrans,
        unsigned int bBegin, unsigned int eEnd, bool iIter, bool oOrig,
        bool iInv, bool sSelf, bool rRev, bool eEqual) const
        //Pre-sort reference data for transposing other data
        {
        //This function handles all pre-sorting operations for front-end
        //functions.  This takes into account sorting iterators, whether we are
        //sorting data from this list,  if the calling function intends to use
        //the results for an inverting operation, and whether the intended
        //operation will be used on the data in this list or not.
        int Size = eEnd - bBegin + 1;
        if (!Size) return true;
        bool PreCopy = !COPY_SAVER(Size);

        typedef typename std::iterator_traits <Iterator2> ::value_type Type2;

        typename LIST_CONTAINER <I_CELL <Iterator2> > ::TYPE I_Temp, I_TEMP;
        typename LIST_CONTAINER <CELL <Type2> > ::TYPE       Temp,   TEMP;

        if (iIter)
        //If we are sorting iterators we resize the iterator containers...
         {
        if (!CHECK_CAPACITY(I_Temp, Size)) return false;
        I_Temp.resize(Size);
        if (!CHECK_CAPACITY(I_TEMP, Size)) return false;
        I_TEMP.resize(Size);
         }

        else
        //...otherwise we resize the object containers.
         {
        if (!CHECK_CAPACITY(Temp, Size)) return false;
        Temp.resize(Size);
        if (!CHECK_CAPACITY(TEMP, Size)) return false;
        TEMP.resize(Size);
         }

        //Here we fill temporary containers with the data provided.  We also
        //sequentially number the containers so that we can find out where each
        //container moved after sorting.
        for (int I = 0; I < Size; I++)
         {
        if (iIter)
          {
        I_Temp[I] << (iIterator + (oOrig? S_MOD(I + bBegin) : (I + bBegin)));
        I_Temp[I] = I;
        if (PreCopy) I_TEMP[I] = I_Temp[I];
          }

        else
          {
        Temp[I] << *(iIterator + (oOrig? S_MOD(I + bBegin) : (I + bBegin)));
        Temp[I] = I;
        if (PreCopy) TEMP[I] = Temp[I];
          }
         }

        //We presort the lists of containers by the data value.
        if (iIter)
        C_MSORT_(&I_Temp[0], &I_Temp[Size], &I_TEMP[0], 0, Size - 1, rRev, eEqual);

        else
        C_MSORT_(&Temp[0], &Temp[Size], &TEMP[0], 0, Size - 1, rRev, eEqual);

        //We set the size of the transposer.
        if (!CHECK_CAPACITY(tTrans, Size)) return false;
        tTrans.resize(Size);

        if (!oOrig && !iInv) for (int I = 0; I < Size; I++)
        //If we are not in inverted mode and are not using the original list
        //data then we copy the results into the Transposer and also
        //sequentially number it.
         {
        if (iIter) tTrans[I] << I_Temp[I].POS;
        else       tTrans[I] << Temp[I].POS;
        tTrans[I] = I;
         }

        else if (!oOrig)
        //If we aren't using the original data, that means we are in inverted
        //mode, therefore we just copy the results into the Transposer.
        if (iIter) for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].POS;
        else       for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].POS;

        else if (iInv && !sSelf)
        //If we are in inverted mode and are not performing this to change the
        //order of the data in this list then we just copy the results into
        //the Transposer.
        if (iIter) for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].POS;
        else       for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].POS;

        else
        //If the other conditions were not met, that means that either we are
        //using this data to sort in normal mode, or we are sorting this list
        //in inverted mode.  In either case, we copy the results into the
        //Transposer.
         {
        for (int I = 0; I < Size; I++)
          {
        if (iIter) tTrans[I] << I_Temp[I].POS;
        else       tTrans[I] << Temp[I].POS;
        tTrans[I] = I;
          }

        if (iInv)
        //If we are in inverted mode, that means we are inverting this list,
        //therefore we PRE_ORDER and refill the Transposer with the results.
          {
        PRE_ORDER(&tTrans[0], Size);
        if (iIter) for (int I = 0; I < Size; I++) tTrans[I] << I_Temp[I].POS;
        else       for (int I = 0; I < Size; I++) tTrans[I] << Temp[I].POS;
          }
         }

        return true;
        }

        template <class Type> template <class Function2, class Iterator2>
        bool CList <Type> ::FPRE_SORT(Iterator2 iIterator,
        CList <Type> ::Transposer &tTrans, unsigned int bBegin,
        unsigned int eEnd, bool iIter, bool oOrig, bool iInv, bool sSelf,
        bool rRev, bool eEqual, Function2 fFunction) const
        //Pre-sort reference data for transposing other data using functor
        {
        //This is identical to PRE_SORT except where noted.
        int Size = eEnd - bBegin + 1;
        if (!Size) return true;
        bool PreCopy = !COPY_SAVER(Size);

        typedef typename std::iterator_traits <Iterator2> ::value_type Type2;

        typename LIST_CONTAINER <I_CELL <Iterator2> > ::TYPE I_Temp, I_TEMP;
        typename LIST_CONTAINER <CELL <Type2> > ::TYPE       Temp,   TEMP;

        if (iIter)
        //If we are sorting iterators we resize the iterator containers...
         {
        if (!CHECK_CAPACITY(I_Temp, Size)) return false;
        I_Temp.resize(Size);
        if (!CHECK_CAPACITY(I_TEMP, Size)) return false;
        I_TEMP.resize(Size);
         }

        else
        //...otherwise we resize the object containers.
         {
        if (!CHECK_CAPACITY(Temp, Size)) return false;
        Temp.resize(Size);
        if (!CHECK_CAPACITY(TEMP, Size)) return false;
        TEMP.resize(Size);
         }

        for (int I = 0; I < Size; I++)
         {
        if (iIter)
          {
        I_Temp[I] << (iIterator + (oOrig? S_MOD(I + bBegin) : (I + bBegin)));
        I_Temp[I] = I;
        if (PreCopy) I_TEMP[I] = I_Temp[I];
          }

        else
          {
        Temp[I] << *(iIterator + (oOrig? S_MOD(I + bBegin) : (I + bBegin)));
        Temp[I] = I;
        if (PreCopy) TEMP[I] = Temp[I];
          }
         }

        //We presort the containers with the functor.
        if (iIter)
        FC_MSORT_(&I_Temp[0], &I_Temp[Size], &I_TEMP[0], 0, Size - 1, fFunction,
                  rRev, eEqual);

        else
        FC_MSORT_(&Temp[0], &Temp[Size], &TEMP[0], 0, Size - 1, fFunction,
                  rRev, eEqual);

        if (!CHECK_CAPACITY(tTrans, Size)) return false;
        tTrans.resize(Size);

        if (!oOrig && !iInv) for (int I = 0; I < Size; I++)
         {
        if (iIter)  tTrans[I] << I_Temp[I].POS;
        else        tTrans[I] << Temp[I].POS;
        tTrans[I] = I;
         }

        else if (!oOrig)
        if (iIter)  for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].POS;
        else        for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].POS;

        else if (iInv && !sSelf)
        if (iIter)  for (int I = 0; I < Size; I++) tTrans[I] = I_Temp[I].POS;
        else        for (int I = 0; I < Size; I++) tTrans[I] = Temp[I].POS;

        else
         {
        for (int I = 0; I < Size; I++)
          {
        if (iIter)  tTrans[I] << I_Temp[I].POS;
        else        tTrans[I] << Temp[I].POS;
        tTrans[I] = I;
          }

        if (iInv)
          {
        PRE_ORDER(&tTrans[0], Size);
        if (iIter)  for (int I = 0; I < Size; I++) tTrans[I] << I_Temp[I].POS;
        else        for (int I = 0; I < Size; I++) tTrans[I] << Temp[I].POS;
          }
         }

        return true;
        }
        //......................................................................
        //----------------------------------------------------------------------

        //RemoveDuplicates assist functions-------------------------------------

        //The FIND_D functions might be the most complex functions in this
        //source file.  First we find the range, then we copy either elements
        //into D_CELL or iterators into ID_CELL.  Initially the comparison
        //functions for these objects base the comparison on the value of the
        //OBJ.  The D_CELL or ID_CELL are sorted first, therefore are put in
        //order by element value.  We then start with the first element of the
        //sorted list and compare the OBJ value with that of the next element.
        //If the elements pass the equality comparison, the DEL flag is set for
        //the second element.  The second element position is incremented until
        //an element different than the first element is found, then that
        //element becomes the first element, and the second becomes the element
        //following it.  This happens until the entire array of D_CELL or
        //ID_CELL has been analyzed.  During analysis, the SORT flag is set for
        //each element.  After analysis, the list is sorted.  Since the SORT
        //flag is set, they are sorted first by the DEL flag, and then by the
        //POS value.  The resulting list gives us all of the elements flagged
        //for deleting at the beginning, which are in the order of their
        //position in the actual list of elements.  The container provided is
        //filled with the positions of the elements to be removed, and the
        //number of elements to be removed is returned.

        template <class Type> unsigned int CList <Type> ::
        FIND_D(PosContainer &pPos, int sStart, int sStop) const
        //Finds duplicate elements
        {
        if (Index.Size() < 2) return 0;
        int S1, S2;
        int SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (S2 == S1) return 0;
        bool PreCopy = !COPY_SAVER(SIZE);

        typename LIST_CONTAINER <ID_CELL <ConstIterator> > ::TYPE I_Temp, I_TEMP;
        typename LIST_CONTAINER <D_CELL <BASE_TYPE> > ::TYPE      Temp,   TEMP;

        if (IteratorProcess())
         {
        if (!CHECK_CAPACITY(I_Temp, SIZE)) return 0;
        I_Temp.resize(SIZE);
        if (!CHECK_CAPACITY(I_TEMP, SIZE)) return 0;
        I_TEMP.resize(SIZE);
         }

        else
         {
        if (!CHECK_CAPACITY(Temp, SIZE)) return 0;
        Temp.resize(SIZE);
        if (!CHECK_CAPACITY(TEMP, SIZE)) return 0;
        TEMP.resize(SIZE);
         }

        for (int I = 0; I < SIZE; I++)
         {
        if (IteratorProcess())
          {
        I_Temp[I] << Element(S_MOD(S1 + I));
        I_Temp[I] = S_MOD(S1 + I);
        if (PreCopy) I_TEMP[I] = I_Temp[I];
          }

        else
          {
        Temp[I] << Reference(S_MOD(S1 + I));
        Temp[I] = S_MOD(S1 + I);
        if (PreCopy) TEMP[I] = Temp[I];
          }
         }

        if (IteratorProcess())
        C_MSORT_(&I_Temp[0], &I_Temp[SIZE], &I_TEMP[0], 0, SIZE - 1, RevProcess());

        else
        C_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1, RevProcess());

        int P1 = 0, P2 = 1;

        while (P2 < SIZE)
         {
        while
        ( IteratorProcess()? (I_Temp[P2] == I_Temp[P1]) : (Temp[P2] == Temp[P1]) )
          {
        if (IteratorProcess()) I_Temp[P2].DEL = true;
        else                   Temp[P2].DEL   = true;

        if (PreCopy)
        if (IteratorProcess()) I_TEMP[P2] = I_Temp[P2];
        else                   TEMP[P2]   = Temp[P2];

        if (++P2 >= SIZE) break;
          }
        P1 = P2++;
         }

        if (IteratorProcess())
        for (int I = 0; I < SIZE; I++) I_TEMP[I].SORT = I_Temp[I].SORT = true;

        else
        for (int I = 0; I < SIZE; I++) TEMP[I].SORT   = Temp[I].SORT   = true;

        if (IteratorProcess())
        C_MSORT_(&I_Temp[0], &I_Temp[SIZE], &I_TEMP[0], 0, SIZE - 1);

        else
        C_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1);

        int P = 0;

        while ((P < SIZE) && (IteratorProcess()? I_Temp[P].DEL : Temp[P].DEL))
        P++;

        if (P == 0) return 0;

        if (!CHECK_CAPACITY(pPos, P)) return 0;
        pPos.resize(P);

        for (int I = 0; I < P; I++)
        pPos[I] = (IteratorProcess()? I_Temp[I].POS : Temp[I].POS);
        return P;
        }

        template <class Type> template <class SortFunction2, class FindFunction2>
        int CList <Type> ::FFIND_D(PosContainer &pPos, int sStart, int sStop,
        SortFunction2 sSort, FindFunction2 fFind) const
        //Finds duplicate elements
        {
        if (Index.Size() < 2) return 0;
        int S1, S2;
        int SIZE = SET_RANGE(S1, S2, sStart, sStop);
        if (S2 == S1) return 0;
        bool PreCopy = !COPY_SAVER(SIZE);

        typename LIST_CONTAINER <ID_CELL <ConstIterator> > ::TYPE I_Temp, I_TEMP;
        typename LIST_CONTAINER <D_CELL <BASE_TYPE> > ::TYPE      Temp,   TEMP;

        if (IteratorProcess())
         {
        if (!CHECK_CAPACITY(I_Temp, SIZE)) return 0;
        I_Temp.resize(SIZE);
        if (!CHECK_CAPACITY(I_TEMP, SIZE)) return 0;
        I_TEMP.resize(SIZE);
         }

        else
         {
        if (!CHECK_CAPACITY(Temp, SIZE)) return 0;
        Temp.resize(SIZE);
        if (!CHECK_CAPACITY(TEMP, SIZE)) return 0;
        TEMP.resize(SIZE);
         }

        for (int I = 0; I < SIZE; I++)
         {
        if (IteratorProcess())
          {
        I_Temp[I] << Element(S_MOD(S1 + I));
        I_Temp[I] = S_MOD(S1 + I);
        if (PreCopy) I_TEMP[I] = I_Temp[I];
          }

        else
          {
        Temp[I] << Reference(S_MOD(S1 + I));
        Temp[I] = S_MOD(S1 + I);
        if (PreCopy) TEMP[I] = Temp[I];
          }
         }

        if (IteratorProcess())
        FC_MSORT_(&I_Temp[0], &I_Temp[SIZE], &I_TEMP[0], 0, SIZE - 1, sSort,
                  RevProcess());

        else
        FC_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1, sSort,
                  RevProcess());

        int P1 = 0, P2 = 1;

        while (P2 < SIZE)
         {
        while
        ( IteratorProcess()? EVALUATE_2(fFind, I_Temp[P2], I_Temp[P1]) :
                             EVALUATE_2(fFind, Temp[P2],   Temp[P1]  )   )
          {
        if (IteratorProcess()) I_Temp[P2].DEL = true;
        else                   Temp[P2].DEL   = true;

        if (PreCopy)
        if (IteratorProcess()) I_TEMP[P2] = I_Temp[P2];
        else                   TEMP[P2]   = Temp[P2];

        if (++P2 >= SIZE) break;
          }
        P1 = P2++;
         }

        if (IteratorProcess()) for (int I = 0; I < SIZE; I++)
        I_TEMP[I].SORT = I_Temp[I].SORT = true;

        else                   for (int I = 0; I < SIZE; I++)
        TEMP[I].SORT   = Temp[I].SORT   = true;

        if (IteratorProcess())
        C_MSORT_(&I_Temp[0], &I_Temp[SIZE], &I_TEMP[0], 0, SIZE - 1);

        else
        C_MSORT_(&Temp[0], &Temp[SIZE], &TEMP[0], 0, SIZE - 1);

        int P = 0;

        while ( (P < SIZE) && (IteratorProcess()? I_Temp[P].DEL : Temp[P].DEL) )
        P++;

        if (P == 0) return 0;

        if (!CHECK_CAPACITY(pPos, P)) return 0;
        pPos.resize(P);

        if (IteratorProcess()) for (int I = 0; I < P; I++) pPos[I] = I_Temp[I].POS;
        else                   for (int I = 0; I < P; I++) pPos[I] = Temp[I].POS;

        return P;
        }

        template <class Type> int *CList <Type> ::FAST_REM(int *pPos,
        unsigned int sSize)
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
        int SIZE = Index.Size(), NewSize = SIZE - sSize;

        while (Write < NewSize)
         {

        while (Read == pPos[Remove])
          {
        if (++Read >= SIZE) break;
        if (++Remove >= (signed) sSize) break;

        if (Remove != (signed) sSize - 1)
        while (pPos[Remove] == pPos[Remove - 1])
        if ((++NewSize >= SIZE) || (++Remove >= (signed) sSize - 1)) break;
          }

        if (Read >= SIZE) break;
        Reference(Write++) = Reference(Read++);
         }

        Resize(NewSize);
        return pPos;
        }

        template <class Type> int *CList <Type> ::FAST_KEEP(int *pPos,
        unsigned int sSize)
        //Keeps elements
        {
        //Here we start with the first element as the write position.  Then we
        //go through and move the elements to be kept to the beginning of the
        //list and set the list size.
        int Write = 0, Keep = 0;
        int SIZE = Index.Size(), NewSize = sSize;

        for (int I = 0; I < NewSize && Keep < (signed) sSize; I++)
         {
        if (Keep < (signed) sSize - 1)
        while (pPos[Keep] == pPos[Keep + 1])
          {
        if (++Keep >= (signed) sSize - 1) break;
        NewSize--;
          }

        Reference(Write++) = Reference(pPos[Keep++]);
         }

        Resize(NewSize);
        return pPos;
        }
        //----------------------------------------------------------------------

        template <class Type> inline size_t CList <Type> ::
        Allocate(size_t sSize)
        //Allocation function
        {
        //Here we either remove or insert elements as needed to change the size
        //of the list
        int Size = sSize;
        if (!CHECK_CAPACITY(LIST, Size)) Size = LIST.max_size();

        if (Size < (signed) LIST.size())
        while ((signed) LIST.size() > Size) LIST.pop_back();

        else
        while ((signed) LIST.size() < Size) LIST.insert(LIST.end(), BASE_TYPE());

        return Size;
        }

        //Access functions======================================================
        //Iterator access-------------------------------------------------------
        template <class Type> inline typename CList <Type> ::Iterator
        CList <Type> ::Element(unsigned int pPos)
        //Random access function
        {
        //This is seemingly backwards, but since the iterator type of the
        //container might not be a *, this is the better choice
        return &Reference(pPos);
        }

        template <class Type> inline typename CList <Type> ::ConstIterator
        CList <Type> ::Element(unsigned int pPos) const
        //Random access function
        { return &Reference(pPos); }
        //----------------------------------------------------------------------

        //Reference access------------------------------------------------------
        template <class Type> inline typename CList <Type> ::ASSIGN_TYPE
        CList <Type> ::Reference(unsigned int pPos)
        //Random access function
        { return *(LIST.begin() + pPos); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Reference(unsigned int pPos) const
        //Random access function
        { return *(LIST.begin() + pPos); }

        template <class Type> inline typename CList <Type> ::ASSIGN_TYPE
        CList <Type> ::Default()
        //Returns default element
        { return ELEMENT_ = BASE_TYPE(); }

        template <class Type> inline typename CList <Type> ::CONST_RETURN_TYPE
        CList <Type> ::Default() const
        //Returns default element
        { return ELEMENT_ = BASE_TYPE(); }
        //----------------------------------------------------------------------
        //======================================================================

        //Converters------------------------------------------------------------
        template <class Type> template <class Type2> inline const Type2
        &CList <Type> ::Convert(const Type2 &oObj)
        //Assists functor sorting by returning data as const
        { return oObj; }
        //----------------------------------------------------------------------

        template <class Type> inline int CList <Type> ::
        S_MOD(int pPos) const
        //Returns valid array pos from int
        {
        //This function is the private version of MOD, and stands for short MOD.
        //This version is slightly faster than MOD because here we don't use the
        //% operator.  The position argument must be between the negative of the
        //size of the list to one less than twice the size of the list (which is
        //the reason this is a private function.)  For this reason this is only
        //used internally after parsing range arguments with MOD.  The slight
        //decrease in time is noticeable when using IteratorProcess to sort very
        //large lists or other functions that require copying of interators or
        //elements of very large lists.
        if (pPos >= 0)
        if (pPos >= (signed) Index.Size()) return pPos - Index.Size();
        else                               return pPos;
        else                               return pPos + Index.Size();
        }
//==============================================================================
}

#endif
//==============================================================================
