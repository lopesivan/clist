/*============================================================================*\
 *Miscellaneous Basic Functions.                                              *
 *Copyright (C) 2007 Kevin P. Barry (ta0kira)                                 *
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
  This file is the header for various functions and classes:

  GTME: this function sets a variable equal to a given argument if the given
  argument is greater than the variable value.

  LTME: this function sets a variable equal to a given argument if the given
  argument is less than the variable value.

  HI: this function returns the higher of the 2 values.  If the values pass
  the equality test then the first value is returned.

  LO: this function returns the lower of the 2 values.  If the values pass
  the equality test then the second value is returned.

  RANGE: this sets 2 variables to the lower and higher of 2 values
  respectively.
 *____________________________________________________________________________*/

//BasicComponents_______________________________________________________________
//(C) 2003-2004,2007 Kevin P. Barry

//==============================================================================
#ifndef MISC_HPP
#define MISC_HPP BC

namespace MISC_HPP
{

//Misc functions================================================================
//Function GTME-----------------------------------------------------------------
//If greater than, make equal to
template <class Type1, class Type2> inline
        void
GTME(Type1 &eEqual, Type2 vVal)
//Variable, comparison value
{ if (vVal > eEqual) eEqual = vVal; } //END-------------------------------------

//Function LTME-----------------------------------------------------------------
//If less than, make equal to
template <class Type1, class Type2> inline
        void
LTME(Type1 &eEqual, Type2 vVal)
//Variable, comparison value
{ if (vVal < eEqual) eEqual = vVal; } //END-------------------------------------

//Function HI-------------------------------------------------------------------
//Returns higher of the 2 values
template <class Type> inline
        Type
HI(Type oOne, Type tTwo)
//value 1, value 2
{ return (oOne >= tTwo)? oOne : tTwo; } //END-----------------------------------

//Function LO-------------------------------------------------------------------
//Returns lower value
template <class Type> inline
        Type
LO(Type oOne, Type tTwo)
//value 1, value 2
{ return (oOne < tTwo)? oOne : tTwo; } //END------------------------------------

//Function RANGE----------------------------------------------------------------
//Sets hi and lo values
template <class Type> inline
        void
RANGE(Type &lLo, Type &hHi, Type oOne, Type tTwo)
//Lo variable, hi variable, value 1, value 2
{
        lLo = LO(oOne, tTwo);
        hHi = HI(oOne, tTwo);
        //If equal then lLo = oOne, hHi = tTwo
} //END-------------------------------------------------------------------------
//==============================================================================
}

#endif
//==============================================================================
