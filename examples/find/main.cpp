/*============================================================================*\
 *clist Example Program - Using find Functions                                *
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

#include <iostream>
#include <ta0kira/clist.hpp>


#include "applied.cpp"

int main()
{
        //This is just a basic overview of how to use each of the find functions

        //reset_list our randomness so we get different results each time
        srand(time(NULL));


        //Normal Finding========================================================
        std::cout << "**********Normal Finding**********\n";

        //Initialize the list
        data::clist <char> Letters(32);
        ( data::clist_sequence(Letters).random_order() %= 26 ) += 'A';
        //This creates a sequence from 0 - 31, randomizes the order, does a mod
        //26 to each element to make sure they are all within the range of
        //valid letters, then adds 'A' to all elements to turn all elements into
        //valid letters.

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Default find----------------------------------------------------------
        //find letter from beginning
        std::cout << "find 'C' from the beginning of the list: "
                  << Letters.find('C') << "\n";
        //----------------------------------------------------------------------

        //find in reverse-------------------------------------------------------
        //Set reverse mode
        Letters.o_reverse_find() = true;

        //find letter from end
        std::cout << "find 'C' from the end of the list: "
                  << Letters.find('C') << "\n";

        //Unset reverse mode
        Letters.o_reverse_find() = false;
        //----------------------------------------------------------------------

        //find from a Position--------------------------------------------------
        //find letter from 25
        std::cout << "find 'C' from 25 without crossing the end: "
                  << Letters.find('C', 25) << "\n";

        //find letter from 25 crossing end
        std::cout << "find 'C' from 25 crossing the end: "
                  << Letters.find('C', 25, 24) << "\n";
        //----------------------------------------------------------------------

        //find from a position in reverse---------------------------------------
        //Set reverse mode
        Letters.o_reverse_find() = true;

        //find letter from 5
        std::cout << "find 'C' from 5 in reverse without crossing the end: "
                  << Letters.find('C', data::first, 5) << "\n";

        //find letter from 5 crossing end
        std::cout << "find 'C' from 5 in reverse crossing the end: "
                  << Letters.find('C', 5, 4) << "\n";

        //Unset reverse mode
        Letters.o_reverse_find() = false;
        //----------------------------------------------------------------------

        //find all occurences of an element-------------------------------------
        //find all occurences
        data::clist <int> PositionList;
        int count;
        Letters.clist_find('C', PositionList);

        std::cout << "find all occurences of 'C':"
                  << data::f_bind_format_output(PositionList, &add_space <int>)
                  << "\n";
        //----------------------------------------------------------------------

        //find all occurrences of an element in reverse-------------------------
        //Set reverse mode
        Letters.o_reverse_find() = true;

        //find all occurences in reverse
        //(I know there will be 2 of them, otherwise I would check for 0 before
        //'new[]')
        int *Positions = new int[ count = Letters.count('C') ];
        Letters.find('C', Positions);

        std::cout << "find all occurences of 'C' in reverse: ";
        for (int I = 0; I < count; I++) std::cout << Positions[I] << " ";
        std::cout << "\n";

        delete[] Positions;
        Positions = NULL;

        //Unset reverse mode
        Letters.o_reverse_find() = false;
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Functor finding=======================================================
        std::cout << "**********Functor Finding**********\n";

        //Initialize a key list
        data::keylist <int, char> TabbedLetters(16);
        TabbedLetters.resize( TabbedLetters.max_size() );

        for (int I = 0; I < TabbedLetters.size(); I++)
        TabbedLetters.next_element().key()   = I % 5;
        TabbedLetters.random_order();

        for (int I = 0; I < TabbedLetters.size(); I++)
        TabbedLetters.next_element().value() = I % 13 + 'A';
        TabbedLetters.random_order();

        //Show our original letter list
        std::cout << "Our original tabbed list:\n[ "
                  << TabbedLetters << "]\n";

        //find by key-----------------------------------------------------------
        //find an element with a key of 3 from the beginning
        std::cout << "find an element with 3 as a key from the beginning: "
                  << TabbedLetters.f_find(3, &TabbedLetters.find_by_key) << "\n";
        //----------------------------------------------------------------------

        //find by value in reverse----------------------------------------------
        //Set reverse mode
        TabbedLetters.o_reverse_find() = true;

        //find an element with 'B' as a value from the end
        std::cout << "find an element with 'B' as a value from the end: "
                  << TabbedLetters.f_find('B', &TabbedLetters.find_by_value)
                  << "\n";

        //Unset reverse mode
        TabbedLetters.o_reverse_find() = false;
        //----------------------------------------------------------------------

        //find all occurences of a key------------------------------------------
        //find all from certain point
        count = TabbedLetters.f_count(3, &TabbedLetters.find_by_key, 4);
        if (count) Positions = new int[ count ];
        //This time we check to make sure we don't allocate 0
        TabbedLetters.f_find(3, Positions, &TabbedLetters.find_by_key, 4);

        std::cout << "find all elements with 3 as a key from position 4: ";
        for (int I = 0; I < count; I++) std::cout << Positions[I] << " ";
        std::cout << "\n";

        delete[] Positions;
        Positions = NULL;
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Shadow finding========================================================
        std::cout << "**********Shadow Finding**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Create a shadow sorted list-------------------------------------------
        //Create a shadow sorted list
        data::clist <int> Shadow;
        data::create_blank_shadow(Letters, Shadow);
        Letters.clist_ref_master_sort(Shadow);

        //Show our shadow sorted list
        std::cout << "Our shadow sorted letter list:\n[ ";
        for (int I = 0; I < Shadow.size(); I++)
        std::cout << Letters[ Shadow[I] ];
        std::cout << " ]\n";
        //----------------------------------------------------------------------

        //find using the shadow sorted list-------------------------------------
        //find letter from beginning
        std::cout << "find 'C' from the beginning of the shadow sorted list: "
                  << Shadow.f_find( 'C', data::bind_find_shadow(Letters, Shadow) )
                  << "\n";

        //Show our original letter list
        std::cout << "Our original letter list has not changed:\n[ "
                  << Letters << " ]\n";

        //Show our original tabbed list
        std::cout << "Our original tabbed list:\n[ "
                  << TabbedLetters << "]\n";
        //----------------------------------------------------------------------

        //Create a shadow list--------------------------------------------------
        //Create a shadow list
        data::create_blank_shadow(TabbedLetters, Shadow);
        TabbedLetters.clist_ref_master_sort(Shadow);

        //Show our shadow sorted list
        std::cout << "Our shadow sorted tabbed list:\n[ ";
        for (int I = 0; I < Shadow.size(); I++)
        std::cout << TabbedLetters[ Shadow[I] ];
        std::cout << "]\n";

        //find an element with a key of 3 from the beginning
        std::cout << "find an element with 3 as a key from the beginning: "
                  << Shadow.f_find( 3, data::f_bind_extern_shadow(TabbedLetters, Shadow,
                                                            &TabbedLetters.find_by_key) )
                  << "\n";

        //Show our original tabbed list
        std::cout << "Our original tabbed list has not changed:\n[ "
                  << TabbedLetters << "]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================
}
