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

//BasicComponents_______________________________________________________________
//(C) 2003-2005 Kevin P. Barry

//==============================================================================
#ifndef INDEX_CPP
#define INDEX_CPP INDEX_HPP
#include "INDEX.hpp"
#include "../MISC/MISC.cpp"

namespace INDEX_CPP
{

//IndexManager function bodies==================================================
        //Information===========================================================
        inline unsigned int IndexManager::Size() const
        //Returns size
        { return SIZE; }

        inline unsigned int IndexManager::Max() const
        //Returns max size
        { return MAX; }
        //======================================================================

        //Limit information=====================================================
        inline bool IndexManager::AtMin() const
        //Returns true if size is 0
        { return !SIZE; }

        inline bool IndexManager::AtMax() const
        //Returns true if size is equal to max
        { return MAX && SIZE == MAX; }

        inline bool IndexManager::AtBegin() const
        //Returns true if index is at beginning
        { return SIZE? !INDEX : false; }

        inline bool IndexManager::AtEnd() const
        //Returns true if index is at end
        { return INDEX >= SIZE - 1; }
        //======================================================================

        //Index functions=======================================================
        inline IndexManager &IndexManager::SetBegin()
        //Sets index to beginning
        {
        INDEX = 0;
        return *this;
        }

        inline IndexManager &IndexManager::SetEnd()
        //Sets index to end
        {
        INDEX = S_MOD(-1);
        return *this;
        }
        //======================================================================

        //Index operators=======================================================
        inline IndexManager &IndexManager::operator = (int iIndex)
        //Sets index
        {
        INDEX = MOD(iIndex);
        return *this;
        }

        inline IndexManager &IndexManager::operator = (const IndexManager &iIndex)
        //Sets index
        {
        //The above operator will work fine in this case, however we define this
        //operator so that the default operator does not overwrite our size/max
        INDEX = MOD(iIndex.INDEX);
        return *this;
        }

        inline int IndexManager::operator ++ (int)
        //Increments index (postfix)
        {
        if (SIZE == 0) return 0;
        INDEX = S_MOD(INDEX + 1);
        return S_MOD(INDEX - 1);
        }

        inline int IndexManager::operator ++ ()
        //Increments index (prefix)
        {
        if (SIZE == 0) return 0;
        return (INDEX = S_MOD(INDEX + 1));
        }

        inline int IndexManager::operator -- (int)
        //Decrements index (postfix)
        {
        if (SIZE == 0) return 0;
        INDEX = S_MOD(INDEX - 1);
        return S_MOD(INDEX + 1);
        }

        inline int IndexManager::operator -- ()
        //Decrements index (prefix)
        {
        if (SIZE == 0) return 0;
        return (INDEX = S_MOD(INDEX - 1));
        }
        //======================================================================

        //Arithmetic operators (based on index)=================================
        inline IndexManager &IndexManager::operator += (int vVal)
        //Add, correct, and equal
        {
        INDEX = MOD(INDEX + vVal);
        return *this;
        }

        inline IndexManager &IndexManager::operator -= (int vVal)
        //Subtract, correct, and equal
        {
        INDEX = MOD(INDEX - vVal);
        return *this;
        }

        inline IndexManager &IndexManager::operator *= (int vVal)
        //Multiply, correct, and equal
        {
        INDEX = MOD(INDEX * vVal);
        return *this;
        }

        inline IndexManager &IndexManager::operator /= (int vVal)
        //Divide, correct, and equal
        {
        INDEX = (vVal == 0)? 0 : MOD(INDEX / vVal);
        return *this;
        }

        inline IndexManager &IndexManager::operator %= (int vVal)
        //Modulus, correct, and equal
        {
        INDEX = (vVal == 0)? 0 : MOD(INDEX % vVal);
        return *this;
        }
        //======================================================================

        //Other operators=======================================================
        inline int IndexManager::operator [] (int vVal) const
        //Returns valid index position
        { return MOD(vVal); }

        inline IndexManager::operator int() const
        //Conversion operator
        { return INDEX; }
        //======================================================================

        IndexManager::IndexManager(unsigned int mMax)
        //Constructor
        {
        MAX = mMax;
        SIZE = 0;
        INDEX = 0;
        }

        //Private functions-----------------------------------------------------
        inline unsigned int IndexManager::SET_SIZE(unsigned int sSize)
        //Sets size, adjusts index
        {
        //If the requested size is less than the max then we set the new size to
        //the max.  If the max is 0, we set the new size to that requested.  If
        //the index falls out of the range of the size we set it to the new
        //endpoint.  In case we set the size to 0, we set the index to 0 also.
        LTME(INDEX, (SIZE = MAX? LO(MAX , (int) sSize) : (int) sSize) - 1);
        GTME(INDEX, 0);
        return SIZE;
        }

        inline IndexManager &IndexManager::SET_MAX(unsigned int mMax)
        //Sets max size
        {
        //If the max is less than the current size, we reduce the current size
        //to the max.  We adjust the index as above.
        MAX = mMax;
        LTME(SIZE, (MAX? MAX : SIZE));
        LTME(INDEX, SIZE - 1);
        GTME(INDEX, 0);
        return *this;
        }

        inline int IndexManager::MOD(int iIndex) const
        //Returns valid array position (for mod of externally provided values)
        {
        if (SIZE <= 1) return 0;
        if (iIndex < 0) return (iIndex % SIZE) + SIZE;
        return iIndex % SIZE;
        }

        inline int IndexManager::S_MOD(int iIndex) const
        //Returns valid array position (shortened for internal use)
        {
        //If the value is greater than 0 and greater than the size, we just
        //subtract the size.  It is greater than zero otherwise then we just
        //return the value.  If it is less than zero we just add the size.
        if (iIndex >= 0)
        if (iIndex >= SIZE) return iIndex - SIZE;
        else return iIndex;
        else return iIndex + SIZE;
        }
        //----------------------------------------------------------------------
//==============================================================================
}

#endif
//==============================================================================
