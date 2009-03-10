/*============================================================================*\
 *clist Example Program - Using General Functions (helper file)               *
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
        char
int_to_char(int vVal)
{ return vVal % 26 + 'A'; }

//A simple function to convert a letter to a number
        int
char_to_int(char vVal)
{ return vVal % 10; }


//A simple function to find an int by comparing it as a char
        bool
find_int_to_char(int vVal1, char vVal2)
{ return int_to_char(vVal1) == vVal2; }

//A simple function to find a char by comparing it as an int
        bool
find_char_to_int(char vVal1, int vVal2)
{ return char_to_int(vVal1) == vVal2; }
