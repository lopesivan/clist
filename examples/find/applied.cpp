/*============================================================================*\
 *clist Example Program - Using find Functions (helper file)                  *
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

//A simple function to convert a number to a letter
        bool
int_to_char(int vVal, char eEqual)
{ return vVal + 'A' == eEqual; }

//A simple function to convert a letter to a number
        bool
char_to_int(char vVal, int eEqual)
{ return (vVal - 'A') % 10 == eEqual; }

//An operator to let us display a keylist element
template <class Type1, class Type2>
        std::ostream
&operator << (std::ostream &sStream, const data::associated_element <Type1, Type2> &eElem)
{ return sStream << "<" << eElem.key() << ", " << eElem.value() << "> "; }

//A format function for output
template <class Type>
        void
add_space(std::ostream &sStream, const Type &eElem)
{ sStream << " " << eElem; }
