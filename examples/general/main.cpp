/*============================================================================*\
 *clist Example Program - Using General Functions                             *
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
#include <cstdlib>
#include <ta0kira/clist.hpp>
#include "applied.cpp"

//Uncomment the line below to see the differences between const and regular
//list element types.  You WILL get compiler errors for assignment of read-only
//locations.
//#define CONST const
#ifndef CONST
#define CONST
#endif

int main()
{
        //This is just a basic overview of how to use each of the significant
        //general functions

        //Reset our randomness so we get different results each time
        srand(time(NULL));


        //Creating/filling a list===============================================
        std::cout << "**********Creating/Filling a shadowed_list**********\n";

        //Create our list (with no argument we have an unlimited-size list)
        data::clist <CONST char> Letters, NewLetters;

        //Raw data
        const char RawCharData[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        //Add the raw data
        Letters.copy_from(RawCharData, 26);

        //Show that we've added the raw data
        std::cout << "We have added all of the raw data:\n[ "
                  << Letters << " ]\n";

        //Copy letters 5 - 15 to a new list
        NewLetters.copy_from(Letters, 5, 15);

        //Show that we've copied the data
        std::cout << "We have added elements 5 - 15 to the new list:\n[ "
                  << NewLetters << " ]\n";

        //Different type of raw data
        const int RawIntData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        //We can also add data that is of a different type
        Letters.f_copy_from(RawIntData, 10, &int_to_char);

        //Show that we've added the different type data
        std::cout << "We have added data of a different type:\n[ "
                  << Letters << " ]\n";

        //Different clist; now we have a max size of 10
        data::clist <int> Integers(10), NewIntegers;

        //We can quickly fill the list with data::clist_sequence then mix them up
        data::clist_sequence( Integers ).random_order();

        //Here we will add elements 2 - 7 to our new letter list
        NewLetters.f_copy_from(Integers, &int_to_char, 2, 7);

        //Show that we've copied the different type data
        std::cout << "We have added elements 2 - 7 of the different type:\n[ "
                  << NewLetters << " ]\n";

        std::cin.get();
        //======================================================================


        //Adding elements=======================================================
        std::cout << "\n**********Adding Elements**********\n";

        //Here we make sure our letter list has unlimited capacity
        Letters.set_max_size();

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Add a single letter
        Letters.add_element('v');

        //Show the added letter
        std::cout << "We have added a letter to the end:\n[ "
                  << Letters << " ]\n";

        //Add a few letters starting at position 5 of the raw data
        Letters.add_element(RawCharData + 5, 3);

        //Show the added letters
        std::cout << "We have added 3 letters to the end:\n[ "
                  << Letters << " ]\n";

        //An alternate use of add
        Letters.add_element() = 'r';

        //Show the added letter
        std::cout << "We have used the alternate method to add one letter:\n[ "
                  << Letters << " ]\n";

        //Show our original number list
        std::cout << "Our original number list:\n[ "
                  << Integers << " ]\n";

        //Try to add a number
        if ( Integers.add_element(5) ) std::cout << "We have added a number:\n[ ";
        else                   std::cout << "Our list was full:\n[ ";
        std::cout << Integers << " ]\n";

        //Add letters with iterators and show how many were added
        std::cout << "We have added "
                  << Letters.add_element(RawCharData, RawCharData + 5)
                  << " letters to our list using iterators:\n[ "
                  << Letters << " ]\n";

        //Add data of a different type
        Letters.f_add_element(RawIntData, 4, &int_to_char);

        //Show the added data of a different type
        std::cout << "We have added 4 elements of a different type:\n[ "
                  << Letters << " ]\n";

        //Add a different type data from another list
        Letters.f_add_element(Integers, &int_to_char);

        //Show the added data of a different type
        std::cout << "We have added all elements of a different type from "
                  << "another list:\n[ " << Letters << " ]\n";

        std::cin.get();
        //======================================================================


        //Inserting elements====================================================
        std::cout << "\n**********Inserting Elements**********\n";

        //Simplify our list a little; sequence up to 10, mix up, make it
        //letters, then make the capacity unlimited
        ( data::clist_sequence( Letters.reset_list(10) ).random_order() += 'A' ).set_max_size();

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Insert a single letter
        Letters.insert_element(3, 'd');

        //Show the inserted letter
        std::cout << "We have inserted a letter at position 3:\n[ "
                  << Letters << " ]\n";

        //An alternate use of insert
        Letters.insert_element(4) = 'z';

        //Show the added letter
        std::cout << "We have used the alternate method to insert one letter "
                  << "at 4:\n[ " << Letters << " ]\n";

        //Insert multiple letters
        Letters.insert_element(5, RawCharData + 15, 5);

        //Show the inserted letters
        std::cout << "We have inserted 5 letters at position 5:\n[ "
                  << Letters << " ]\n";

        //Insert letters with iterators and show how many were inserted
        std::cout << "We have inserted "
                  << Letters.insert_element(9, RawCharData + 3, RawCharData + 7)
                  << " letters to our list using iterators at position 9:\n[ "
                  << Letters << " ]\n";

        //Inserting data of a different type
        Letters.f_insert_element(12, RawIntData, 3, &int_to_char);

        //Show the inserted data of a different type
        std::cout << "We have inserted 3 elements of a different type at "
                  << "position 12:\n[ " << Letters << " ]\n";

        //Insert a different type data from another list
        Letters.f_insert_element(15, Integers, &int_to_char);

        //Show the inserted data of a different type
        std::cout << "We have inserted elements of a different type at "
                  << "position 15:\n[ " << Letters << " ]\n";

        std::cin.get();
        //======================================================================


        //Element removal=======================================================
        std::cout << "\n**********Element Removal**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Removing a single element
        Letters.remove_single(11);

        //Show that we removed a letter
        std::cout << "We have removed element 11:\n[ "
                  << Letters << " ]\n";

        //Remove a range of elements
        Letters.remove_range(4, 9);

        //Show that we removed the range
        std::cout << "We have removed elements 4 - 9:\n[ "
                  << Letters << " ]\n";

        //Removal list
        const int Removal[] = { 2, 4, 5, 9 };

        //Remove certain elements
        Letters.remove_list(Removal, 4);

        //Show that we removed the letters
        std::cout << "We have removed elements 2, 4, 5, and 9:\n[ "
                  << Letters << " ]\n";

        //Put the data to remove in a list
        data::clist <int> RemovalList;
        RemovalList.copy_from(Removal, 4);

        //Remove elements using a list
        Letters.remove_list(RemovalList);

        //Show that we removed the letters
        std::cout << "We have removed elements 2, 4, 5, and 9 using a list:\n[ "
                  << Letters << " ]\n";

        //Remove a certain value
        Letters.remove_pattern('A');

        //Show that we removed the letters
        std::cout << "We have removed all 'A' from the list:\n[ "
                  << Letters << " ]\n";

        //Remove a certain value using a functor
        Letters.f_remove_pattern(1, &find_char_to_int);

        //Show that we removed the letters
        std::cout << "We have removed elements with a functor:\n[ "
                  << Letters << " ]\n";

        std::cin.get();
        //======================================================================


        //Element keeping=======================================================
        std::cout << "\n**********Element Keeping**********\n";

        //Create a new list of random letters
        NewLetters.reset_list(30);
        while ( NewLetters.add_element(rand() % 26 + 'A') );
        Letters = NewLetters;

        //Show our original letter list
        std::cout << "Our original letter list (remade after each keep "
                  << "operation):\n[ " << Letters << " ]\n";

        //Keep only one element
        Letters.keep_single(5);

        //Show that we kept the letter
        std::cout << "We have only kept letter 5:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;

        //Keep a range of elements
        Letters.keep_range(6, 20);

        //Show that we kept the range of letters
        std::cout << "We have kept letters 6 - 20:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;

        //Keep list
        const int keep_list[] = { 4, 5, 6, 2, 3, 9, 0, 2 };

        //Keep selected letters
        Letters.keep_list(keep_list, 8);

        //Show that we kept the selected letters
        std::cout << "We have kept letters 4, 5, 6, 2, 3, 9, 0, and 2:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;

        //Put or selections into a list
        data::clist <int> KeepList;
        KeepList.copy_from(keep_list, 8);

        //Keep selected letters from a list
        Letters.keep_list(KeepList);

        //Show that we kept the selected letters
        std::cout << "We have kept letters 4, 5, 6, 2, 3, 9, 0, and 2 using a "
                  << "list:\n[ " << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;

        //Keep a certain value
        Letters.keep_pattern('C');

        //Show that we kept the element value
        std::cout << "We have kept only 'C':\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;

        //Keep a certain value using a functor (should keep 'F', 'P', and 'Z')
        Letters.f_keep_pattern(5, &find_char_to_int);

        //Show that we kept the element value
        std::cout << "We have kept a certain value using a functor:\n[ "
                  << Letters << " ]\n";

        std::cin.get();
        //======================================================================


        //Element Access========================================================
        std::cout << "\n**********Element Access**********\n";

        //Reset list
        Letters = NewLetters;

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Show certain selected elements
        std::cout << "Show first element, 4, 104 (" << Letters.index[104]
                  << "), last, and 10 (hold at 10):\n[ "
                  << Letters.first_element() << Letters.get_element(4) << Letters[104]
                  << Letters.last_element()  << Letters.h_get_element(10) << " ]\n";

        //Show the current element
        std::cout << "Show the current element:\n[ "
                  << Letters.current_element() << " ]\n";

        //Show the next 10 elements
        std::cout << "Show the next 10 elements:\n[ ";
        for (int I = 0; I < 10; I++) std::cout << Letters.next_element();
        std::cout << " ]\n";

        //Show the current element
        std::cout << "Show the current element:\n[ "
                  << Letters.current_element() << " ]\n";

        //Show the next 10 elements
        std::cout << "Show the previous 10 elements:\n[ ";
        for (int I = 0; I < 10; I++) std::cout << Letters.previous_element();
        std::cout << " ]\n";

        //Pull the first element
        std::cout << "Pull and show the first element:\n[ "
                  << Letters.p_first_element() << " ][ "
                  << Letters << " ]\n";

        //Pull the first element
        std::cout << "Pull and show the last element:\n[ "
                  << Letters.p_last_element() << " ][ "
                  << Letters << " ]\n";

        //Pull an element
        std::cout << "Pull and show element 5 (hold at 5):\n[ "
                  << Letters.hp_get_element(5) << " ][ "
                  << Letters << " ]\n";

        //Pull several elements
        std::cout << "Pull 5 elements from the current position:\n[ ";
        for (int I = 0; I < 5; I++) std::cout << Letters.p_current_element();
        std::cout << " ][ " << Letters << " ]\n";

        std::cin.get();
        //======================================================================


        //Modifying elements====================================================
        std::cout << "\n**********Modifying Elements**********\n";

        //Reset list
        Letters = NewLetters;

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Change elements
        Letters.first_element() = 'h';
        Letters.last_element()  = 'p';
        Letters[5]      = 'q';
        Letters.get_element(8)  = 't';
        Letters.replace_element(3, 'f');

        //Show our original letter list
        std::cout << "Change first element, last element, 5, 8, and 3:\n[ "
                  << Letters << " ]\n";

        std::cin.get();
        //======================================================================


        //Misc operators/functions==============================================
        std::cout << "\n**********Misc Operators/Functions**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Set all elements to 'f'
        Letters = 'f';

        //Show the new values
        std::cout << "All elements are now 'f':\n[ "
                  << Letters << " ]\n";

        //Add a value
        Letters += 2;

        //Show the new values
        std::cout << "All elements have been increased by 2:\n[ "
                  << Letters << " ]\n";

        //Subtract a value
        Letters -= 5;

        //Show the new values
        std::cout << "All elements have been decreased by 5:\n[ "
                  << Letters << " ]\n";

        //Show our original number list
        std::cout << "Our original number list:\n[ "
                  << Integers << " ]\n";

        //Make sure none are > 6
        Integers %= 6;

        //Show the new values
        std::cout << "We have done '%= 6':\n[ "
                  << Integers << " ]\n";

        //Divide all by 2
        Integers /= 2;

        //Show the new values
        std::cout << "We have done '/= 2':\n[ "
                  << Integers << " ]\n";

        //Multiply all by 3
        Integers *= 3;

        //Show the new values
        std::cout << "We have done '*= 3':\n[ "
                  << Integers << " ]\n";

        //Backup data
        NewIntegers = Integers;

        //Delta
        Integers.o_reverse_process() = false;
        data::clist_delta( Integers );

        //Show the new values
        std::cout << "Via clist_delta, we have subtracted the previous from each "
                  << "element:\n[ ";
        Integers.index.set_to_begin();
        for (int I = 0; I < Integers.size(); I++)
        std::cout << Integers.next_element() << " ";
        std::cout << "]\n";

        //Reset data
        Integers = NewIntegers;

        //reverse_order delta
        Integers.o_reverse_process() = true;
        data::clist_delta( Integers );

        //Show the new values
        std::cout << "Via clist_delta, we have subtracted the next from each "
                  << "element:\n[ ";
        Integers.index.set_to_begin();
        for (int I = 0; I < Integers.size(); I++)
        std::cout << Integers.next_element() << " ";
        std::cout << "]\n";

        //Show the total of all elements
        std::cout << "The total of all elements (data reset):\n[ ";
        Integers = NewIntegers;
        std::cout << data::clist_sigma( Integers ) << " ]\n";

        std::cin.get();
        //======================================================================
}
