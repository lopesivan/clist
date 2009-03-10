/*============================================================================*\
 *clist Example Program - Using Sorting and Related Functios                  *
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
#include <string>
#include <ta0kira/clist.hpp>


#include "applied.cpp"

int main()
{
        //This is just a basic overview of how to use each of the sorting and
        //related functions

        //Reset our randomness so we get different results each time
        srand(time(NULL));

        //Initialize a new list
        data::clist <char> Letters(32), NewLetters;
        while ( Letters.add_element(rand() % 26 + 'A') );

        NewLetters = Letters;

        //Initialize an associated list
        data::clist <int_char> Associated(16), NewAssociated;
        Associated.resize( Associated.max_size() );

        for (int I = 0; I < Associated.size(); I++)
        {
        Associated[I].Character = rand() % 10 + 'A';
        Associated[I].Integer   = rand() % 8;
        }

        NewAssociated = Associated;


        //Basic Sorting=========================================================
        std::cout << "**********Basic Sorting**********\n";

        //Show our original letter list
        std::cout << "Our original letter list (redone after each sort):\n[ "
                  << Letters << " ]\n";

        //Default sort----------------------------------------------------------
        //Normal sort
        Letters.sort();

        //Show sorted list
        std::cout << "Normal sort:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Sort in reverse-------------------------------------------------------
        //Set reverse flag
        Letters.o_reverse_process() =  true;

        //Reverse sort
        Letters.sort();

        //Show reverse sorted list
        std::cout << "Reverse sort:\n[ "
                  << Letters << " ]\n";

        //Verify that they are sorted
        std::cout << "Data " << ( Letters.verify_order()? "IS" : "IS NOT" )
                  << " in reverse order\n";

        //Unset reverse flag
        Letters.o_reverse_process() =  false;

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Sort with a Normal Range----------------------------------------------
        //Sort a normal range
        Letters.sort(10, 27);

        //Show normal range sorted list
        std::cout << "Normal range sort (10 - 26):\n"
                  << "            |               |\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Sort with a Circular Range--------------------------------------------
        //Sort a circular range
        Letters.sort(26, 11);

        //Show circular range sorted list
        std::cout << "Circular range sort (26 - 10):\n"
                  << "            |               |\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Reversing Equal Elements==============================================
        std::cout << "\n**********Reversing Equal Elements**********\n";

        //Show our original associated list
        std::cout << "Our original associated list (redone after each sort):"
                  << "\n[ " << Associated << "]\n";

        //Default sort----------------------------------------------------------
        //Normal sort
        Associated.sort();

        //Show the results of normal sort
        std::cout << "Normal sort:\n[ "
                  << Associated << "]\n";

        //Reset list
        Associated = NewAssociated;
        //----------------------------------------------------------------------

        //Reverse Equal Elements------------------------------------------------
        //Set reversed equals option
        Associated.o_reverse_equals() = true;

        //Reversed equals sort
        Associated.sort();

        //Show the results of reversed equals sort
        std::cout << "Reversed equals sort:\n[ "
                  << Associated << "]\n";

        //Reset list
        Associated = NewAssociated;

        //Unset reversed equals option
        Associated.o_reverse_equals() = false;
        //----------------------------------------------------------------------

        //Reverse sort Order----------------------------------------------------
        //Set reverse flag
        Associated.o_reverse_process() = true;

        //Reverse sort
        Associated.sort();

        //Show the results of reverse sort
        std::cout << "Reverse sort:\n[ "
                  << Associated << "]\n";

        //Reset list
        Associated = NewAssociated;
        //----------------------------------------------------------------------

        //Reverse Equals and sort Order-----------------------------------------
        //Set reversed equals option
        Associated.o_reverse_equals() = true;

        //Reversed equals reverse sort
        Associated.sort();

        //Show the results of reversed equals reverse sort
        std::cout << "Reversed equals reverse sort:\n[ "
                  << Associated << "]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Functor Sorting=======================================================
        std::cout << "\n**********Functor Sorting**********\n";

        //Initialize a key list
        data::keylist <int, char> TaggedLetters(16), NewTaggedLetters;
        TaggedLetters.resize( TaggedLetters.max_size() );

        for (int I = 0; I < TaggedLetters.size(); I++)
        TaggedLetters[I].key()   = I % 10;
        TaggedLetters.random_order();

        for (int I = 0; I < TaggedLetters.size(); I++)
        TaggedLetters[I].value() = I % 26 + 'A';
        TaggedLetters.random_order();

        NewTaggedLetters = TaggedLetters;

        //Show our original key list
        std::cout << "Our original key list (redone after each sort):\n[ "
                  << TaggedLetters << "]\n";

        //Sort Using key Functor------------------------------------------------
        //Sort by key
        TaggedLetters.f_sort(&TaggedLetters.sort_by_key);

        //Show the results of the key sort
        std::cout << "Sorted by key:\n[ "
                  << TaggedLetters << "]\n";

        //Verify that they are sorted by key
        std::cout << "Data " << ( TaggedLetters.f_verify_order(
                        &TaggedLetters.sort_by_key)? "IS" : "IS NOT" )
                  << " in order by key\n";

        //Reset the list
        TaggedLetters = NewTaggedLetters;
        //----------------------------------------------------------------------

        //Sort in reverse Using value Functor-----------------------------------
        //Set the reverse flag
        TaggedLetters.o_reverse_process() = true;

        //Reverse sort by value
        TaggedLetters.f_sort(&TaggedLetters.sort_by_value);

        //Show the results of the value reverse sort
        std::cout << "Sorted in reverse by value:\n[ "
                  << TaggedLetters << "]\n";

        //Unset the reverse flag
        TaggedLetters.o_reverse_process() = false;
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Sorting by reference==================================================
        std::cout << "\n**********Sorting by Reference**********\n";

        //Initialize the list
        Letters.reset_list(10);
        data::clist_sequence( Letters ) += 'A';
        NewLetters = Letters;

        //Initialize reference
        int IntReference[] = { 5, 9, 7, 2, 4, 0, 1, 3, 8, 6 };

        //Show our original letter list
        std::cout << "Our original letter list (redone after each sort):\n[ "
                  << Letters << " ]\n";

        //Show our reference data
        std::cout << "Reference data:\n[ ";

        for (int I = 0; I < 10; I++) std::cout << IntReference[I];
        std::cout << " ]\n";

        //Sort a clist Using a reference----------------------------------------
        //Sort by reference
        //(make sure the reference is at least as large as the list!)
        Letters.ref_sort(IntReference);

        //Show the results of the reference sort
        std::cout << "Reference sort:\n[ "
                  << Letters << " ]\n";

        //Sort the reference list using the list it just sorted
        Letters.ref_master_sort(IntReference);

        std::cout << "Reference master sort (switch roles):\n[ ";

        for (int I = 0; I < 10; I++) std::cout << IntReference[I];
        std::cout << " ]\n";

        //Revert the reference by inverting
        Letters.o_inverted_sort_mode() = true;
        Letters.f_ref_master_sort(IntReference, &sort_char);
        Letters.o_inverted_sort_mode() = false;

        std::cout << "Reference master sort undone using a functor:\n[ ";

        for (int I = 0; I < 10; I++) std::cout << IntReference[I];
        std::cout << " ]\n";

        //Reset the list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Sort a Section of a clist by reference--------------------------------
        //Sort a section by reference
        Letters.f_ref_sort(IntReference + 3, &sort_int, 3, 8);

        //Show the results of the reference sort
        std::cout << "Functor reference sort (3 - 7, reference offset = +3):\n"
                  << "     |   |\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Inverting a sort by reference=========================================
        std::cout << "\n**********Inverting a sort by Reference**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Show our reference data
        std::cout << "Reference data:\n[ ";

        for (int I = 0; I < 10; I++) std::cout << IntReference[I];
        std::cout << " ]\n";

        //Sort by reference
        Letters.ref_sort(IntReference);

        //Show the results of the reference sort
        std::cout << "Reference sort:\n[ "
                  << Letters << " ]\n";

        //Invert the reference sort---------------------------------------------
        //Set inverted mode
        Letters.o_inverted_sort_mode() = true;

        //Invert the reference sort
        Letters.ref_sort(IntReference);

        //Show the results of the undone reference sort
        std::cout << "Undone reference sort:\n[ "
                  << Letters << " ]\n";

        //Unset inverted mode
        Letters.o_inverted_sort_mode() = false;
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Choosing element Order================================================
        std::cout << "\n**********Choosing Element Order**********\n";

        //New data
        const char OrderData[] = " aeinrrvyBK";

        //The order we chose to put the letters in
        const int NameOrder[] = { 10, 2, 7, 3, 4, 0, 9, 1, 5, 6, 8 };

        //Copy the data to our list
        Letters.copy_from(OrderData, 11);

        //Show our original data
        std::cout << "Our original data:\n[ "
                  << OrderData << " ]\n";

        //Show our reference data
        std::cout << "Reference data:\n[ ";

        for (int I = 0; I < 11; I++) std::cout << NameOrder[I] << " ";
        std::cout << "]\n";

        //Choosing Element Order------------------------------------------------
        //Set inverted mode
        Letters.o_inverted_sort_mode() = true;

        //Perform the ordering
        Letters.ref_sort(NameOrder);

        //Show the results of the ordering
        std::cout << "Ordering of elements:\n[ "
                  << Letters << " ]\n";

        //Unset inverted mode
        Letters.o_inverted_sort_mode() = false;
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Sorting a reference===================================================
        std::cout << "\n**********Sorting a Reference**********\n";

        //New reference data
        const char *RunnerNames[] = { "Robert", "Jane", "John", "Beth",
                                      "Martha"                          };
        data::clist <std::string> Runners;

        //Fill in runner list
        for (int I = 0; I < 5; I++) Runners.add_element( RunnerNames[I] );

        //New list data
        const int Places[] = { 3, 2, 5, 1, 4 };

        //insert_element places into a list
        data::clist <int> PlaceList;
        PlaceList.copy_from(Places, 5);

        //Show the runners and places
        std::cout << "Our runners and their places:\n";

        for (int I = 0; I < 5; I++)
        std::cout << PlaceList[I] << ") " << Runners[I] << "\n";

        //Sort a reference------------------------------------------------------
        //Sort the runners by place
        PlaceList.clist_ref_master_sort(Runners);

        //Show the runners in order
        std::cout << "\nOur runners in order of finish:\n";

        std::cout << data::f_bind_format_output(Runners,
                       &add_line <std::string>);
        //----------------------------------------------------------------------

        //Undoing sort a reference----------------------------------------------
        //Set inverted sort mode
        PlaceList.o_inverted_sort_mode() = true;

        //Undo the sort
        PlaceList.f_clist_ref_master_sort(Runners, &sort_int);

        //Show the runners in original order
        std::cout << "\nUndone reference sort with a functor:\n";

        std::cout << data::f_bind_format_output(Runners,
                       &add_line <std::string>);

        //Unset inverted sort mode
        PlaceList.o_inverted_sort_mode() = false;
        //----------------------------------------------------------------------

        //Sort a section of the reference---------------------------------------
        //Only sort a section of the runners
        //(sort runners 1 through 3; don't forget the offset of 1 for the
        //reference!)
        PlaceList.clist_ref_master_sort(Runners, 1, 4, 1);

        //Show the runners in order
        std::cout << "\nOnly the middle names put in relative order:\n";

        std::cout << data::f_bind_format_output(Runners,
                       &add_line <std::string>);
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Shadow sorting========================================================
        std::cout << "\n**********Shadow Sorting**********\n";

        //Initialize a list
        ( data::clist_sequence( Letters.reset_list(32) ).random_order() %= 26 ) += 'A';

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Create a Shadow Sorted list-------------------------------------------
        //Create a shadow sorted list
        data::clist <int> LetterShadow;
        data::create_blank_shadow(Letters, LetterShadow);
        Letters.clist_ref_master_sort(LetterShadow);

        //Show our original letter list using the shadow
        std::cout << "Our original letter list using the shadow:\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Show our original letter list using the shadow
        std::cout << "An alternate method of output:\n[";

        std::cout << data::f_bind_convert_format_output( LetterShadow,
                       data::bind_convert_shadow(Letters, LetterShadow),
                       &add_space <char> );
        std::cout << " ]\n";

        //Show our original letter list using the shadow
        std::cout << "An alternate method showing 5-15:\n[ ";

        std::cout << data::f_bind_convert_output( LetterShadow,
                       data::bind_convert_shadow(Letters, LetterShadow),
                       5, 16 );
        std::cout << " ]\n";

        //Show our original letter list
        std::cout << "5-15 of the original list:\n[ "
                  << data::bind_range_output(Letters, 5, 16)
                  << " ]\n";

        //Show our original letter list
        std::cout << "Our original list was not changed:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        //Shift the shadow sorted list------------------------------------------
        //Shift our shadow
        std::cout << "Our shadow shifted << 5:\n[ ";
        LetterShadow << 5;

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Show our original letter list
        std::cout << "Our original list was not changed:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        //Remove Elements from the Shadow Sorted list---------------------------
        //Remove elements
        LetterShadow.remove_range(5, 11);

        //Show our shadow with elements removed
        std::cout << "Shadow with elements 5 - 10 removed:\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Show our original letter list
        std::cout << "Our original list was not changed:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Binding a shadow======================================================
        std::cout << "\n**********Binding a Shadow**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Create a shadow sorted list
        data::create_blank_shadow(Letters, LetterShadow);
        Letters.clist_ref_master_sort(LetterShadow);

        //Show our original letter list using the shadow
        std::cout << "Our original letter list using the shadow:\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Bind the shadow to the original data and sort a section---------------
        //Sort a section of the shadow by binding
        LetterShadow.o_reverse_process() = true;
        LetterShadow.f_sort( data::bind_sort_shadow(Letters, LetterShadow), 5, 21 );

        //Show our original letter list using the shadow
        std::cout << "Our shadow has been sorted in reverse from 5 - 20:\n"
                  << "       |              |\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Show our original letter list
        std::cout << "Our original list was not changed:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Shadow lists==========================================================
        std::cout << "\n**********Shadow Lists**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Create a shadow list--------------------------------------------------
        //Set inverted mode
        Letters.o_inverted_sort_mode() = true;

        //Create a shadow list
        data::create_blank_shadow(Letters, LetterShadow);
        Letters.clist_ref_master_sort(LetterShadow);

        //Unset inverted mode
        Letters.o_inverted_sort_mode() = false;

        //Show our sorted list
        std::cout << "Our sorted letter list:\n[ "
                  << Letters.sort() << " ]\n";

        //Show our original letter list using the shadow
        std::cout << "Our sorted letter list using the shadow:\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";
        //----------------------------------------------------------------------

        //Remove Elements from the Shadow list----------------------------------
        //Remove elements
        LetterShadow.remove_range(5, 11);

        //Show our shadow with elements removed
        std::cout << "Shadow with elements 5 - 10 removed:\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Show our original letter list
        std::cout << "Our sorted list was not changed:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        //Binding a shadow------------------------------------------------------
        //Remove all elements with value 'A'
        LetterShadow.f_remove_pattern( 'A', data::bind_find_shadow(Letters,
                                                             LetterShadow) );

        //Show our shadow with elements removed
        std::cout << "Shadow with 'A' removed (by binding with original list):\n[ ";

        for (int I = 0; I < LetterShadow.size(); I++)
        std::cout << Letters[ LetterShadow[I] ];
        std::cout << " ]\n";

        //Show our original letter list
        std::cout << "Our sorted list was not changed:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Shadow list as a reference============================================
        std::cout << "\n**********Shadow List as a Reference**********\n";

        //Copy the data to our list
        Letters.copy_from(OrderData, 11);

        //Show our original data
        std::cout << "Our original raw data:\n[ "
                  << Letters << " ]\n";

        //Create a Shadow list for Use as a reference---------------------------
        //Create a shadow of the order data
        data::clist <int> Shadow;
        data::clist_sequence( Shadow.reset_list(11) );
        Shadow.o_inverted_sort_mode() = true;
        Shadow.ref_sort(NameOrder);
        Shadow.o_inverted_sort_mode() = false;

        //Show our original letter list using the shadow
        std::cout << "Our original letter list using the shadow:\n[ ";

        for (int I = 0; I < Shadow.size(); I++)
        std::cout << Letters[ Shadow[I] ];
        std::cout << " ]\n";
        //----------------------------------------------------------------------

        //Shift the Shadow------------------------------------------------------
        //Shift the shadow
        Shadow >> 5;

        //Show the original letter list using shifted shadow
        std::cout << "Shifting the shadow +5:\n[ ";

        for (int I = 0; I < Shadow.size(); I++)
        std::cout << Letters[ Shadow[I] ];
        std::cout << " ]\n";
        //----------------------------------------------------------------------

        //Use the shadow list to Choose element order---------------------------
        //Use our shadow list to choose the order of our data
        Letters.o_inverted_sort_mode() = true;
        Letters.clist_ref_sort(Shadow);
        Letters.o_inverted_sort_mode() = false;

        //Show the reference sort using the shadow
        std::cout << "Choosing the order of letters using the shadow:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Inverting a list======================================================
        std::cout << "\n**********Inverting a List**********\n";

        Letters.reset_list(10);
        data::clist_sequence( Letters ) += 'A';
        NewLetters = Letters;

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters << " ]\n";

        //Put the external data in a list for convenience
        data::clist <int> ReferenceList;
        ReferenceList.copy_from(IntReference, 10).random_order();

        //Show our sorting reference
        std::cout << "Our sorting reference:\n[ "
                  << ReferenceList << " ]\n";

        //Sort a clist Using a reference----------------------------------------
        //Sort by reference
        Letters.f_clist_ref_sort(ReferenceList, &sort_int);

        //Show the results of the reference sort
        std::cout << "Reference sort with a functor:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        //Invert the reference--------------------------------------------------
        //Set inverted mode
        ReferenceList.o_inverted_sort_mode() = true;

        //Invert the list
        ReferenceList.sort();

        //Unset inverted mode
        ReferenceList.o_inverted_sort_mode() = false;

        //Show the results of the inversion
        std::cout << "Our inverted reference:\n[ "
                  << ReferenceList << " ]\n";
        //----------------------------------------------------------------------

        //Sort the Same clist Using the Inverted reference----------------------
        //Sort by reference
        Letters.clist_ref_sort(ReferenceList);

        //Show the results of the reference sort
        std::cout << "Reference sort using inverted reference:\n[ "
                  << Letters << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Removing duplicates===================================================
        std::cout << "\n**********Removing Duplicates**********\n";

        //Initialize our list
        Letters.reset_list(32);
        while ( Letters.add_element(rand() % 26 + 'A') );
        NewLetters = Letters;

        //Show our original letter list
        std::cout << "Our original letter list (redone after each removal):\n[ "
                  << Letters << " ]\n";

        //Remove duplicate elements---------------------------------------------
        //Remove all duplicates
        Letters.remove_duplicates();

        //Show the list without duplicates
        std::cout << "With duplicates removed:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove duplicate elements in reverse----------------------------------
        //Set reverse flag
        Letters.o_reverse_process() = true;

        data::clist <int> Removed;

        //Remove all duplicates
        Letters.remove_duplicates(Removed);

        //Show the list without duplicates
        std::cout << "With duplicates removed (in reverse):\n[ "
                  << Letters << " ]\n";

        //Show the removed positions
        std::cout << "Positions of removed elements:\n["
                  << data::f_bind_format_output(Removed, &add_space <int>)
                  << " ]\n";

        //Unset reverse flag
        Letters.o_reverse_process() = false;

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove duplicated elements--------------------------------------------
        //Remove all duplicated
        Letters.remove_all_duplicated();

        //Show the list without any duplicated
        std::cout << "With all duplicated removed:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove non-duplicated elements----------------------------------------
        //Remove all duplicated
        Letters.keep_only_duplicated();

        //Show the list without any duplicated
        std::cout << "With only duplicated:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove first-occurence elements---------------------------------------
        //Remove all first occurences
        Letters.keep_only_duplicates();

        //Show the list without first occurences
        std::cout << "With only subsequent duplicates:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove unique elements------------------------------------------------
        //Remove all unique elements
        Letters.keep_all_duplicated();

        //Show the list without unique elements
        std::cout << "With only non-unique elements:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove duplicates in a normal range-----------------------------------
        //Remove all duplicates in a normal range
        Letters.remove_duplicates(5, 26);

        //Show the list without duplicates in a normal range
        std::cout << "With duplicates removed from positions 5 - 25:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Remove duplicate elements in a circular range-------------------------
        //Remove all duplicates in a circular range
        Letters.remove_duplicates(25, 6);

        //Show the list without duplicates in a circular range
        std::cout << "With duplicates removed from positions 25 - 5:\n[ "
                  << Letters << " ]\n";

        //Reset list
        Letters = NewLetters;
        //----------------------------------------------------------------------

        //Store duplicate positions during removal------------------------------
        //Remove all duplicates and store positions
        Letters.remove_duplicates(Removed);

        //Show the list without duplicates in a circular range
        std::cout << "With duplicates removed:\n[ "
                  << Letters << " ]\n";

        //Show the list without duplicates in a circular range
        std::cout << "Elements that were removed:\n[ ";

        //Show the removed positions
        std::cout << "Positions of removed elements:\n["
                  << data::f_bind_format_output(Removed, &add_space <int>)
                  << " ]\n";
        //----------------------------------------------------------------------

        //Remove duplicate elements with functors-------------------------------
        //Mix up an old list
        TaggedLetters.random_order();

        //Show our original key list
        std::cout << "Our original key list:\n[ "
                  << TaggedLetters << " ]\n";

        //Create a shadow sorted list
        data::clist <int> TaggedShadow;
        data::create_blank_shadow(TaggedLetters, TaggedShadow);
        TaggedLetters.clist_ref_master_sort(TaggedShadow);

        //Show our original key list using the shadow
        std::cout << "Our key list using a sorted shadow:\n[ ";

        for (int I = 0; I < TaggedShadow.size(); I++)
        std::cout << TaggedLetters[ TaggedShadow[I] ];
        std::cout << " ]\n";

        TaggedShadow.f_remove_duplicates( f_bind_intern_shadow( TaggedLetters, TaggedShadow,
                                                           &TaggedLetters.sort_by_key),
                                          f_bind_intern_shadow( TaggedLetters, TaggedShadow,
                                                           &TaggedLetters.find_dup_key) );

        //Show our key list after removing duplicate keys
        std::cout << "Shadow with duplicate keys removed:\n[ ";

        for (int I = 0; I < TaggedShadow.size(); I++)
        std::cout << TaggedLetters[ TaggedShadow[I] ];
        std::cout << " ]\n";

        //Show our original key list
        std::cout << "Our original key list was not changed:\n[ "
                  << TaggedLetters << " ]\n";

        TaggedLetters.f_remove_duplicates(Removed, &TaggedLetters.sort_by_key,
          &TaggedLetters.find_dup_key);

        //Show our original key list with duplicates removed
        std::cout << "Our original key list with duplicate keys removed:\n[ "
                  << TaggedLetters << " ]\n";

        //Show the removed positions
        std::cout << "Positions of removed elements:\n["
                  << data::f_bind_format_output(Removed, &add_space <int>)
                  << " ]\n";
        //----------------------------------------------------------------------

        std::cin.get();
        //======================================================================


        //Shifting/reversing====================================================
        std::cout << "\n**********Shifting/Reversing**********\n";

        //Show our original letter list
        std::cout << "Our original letter list:\n[ "
                  << Letters.sort() << " ]\n";

        //Show a reverse shift
        std::cout << "Shifted << 4:\n[ "
                  << (Letters << 4) << " ]\n";

        //Show a forward shift
        std::cout << "Shifted >> 4:\n[ "
                  << (Letters >> 4) << " ]\n";

        //Show the list reversed
        std::cout << "Reversed:\n[ "
                  << Letters.reverse_order() << " ]\n";

        //Show a normal section reversed
        std::cout << "Positions 5 - 10 reversed:\n"
                  << "       |    |\n[ "
                  << Letters.reverse_order(5, 11) << " ]\n";

        //Show a circular section reversed
        std::cout << "Positions 14 - 2 reversed:\n"
                  << "    |           |\n[ "
                  << Letters.reverse_order(14, 3) << " ]\n";

        //Show a normal section shifted
        std::cout << "Positions 4 - 11 shifted +3:\n"
                  << "      |      |\n[ "
                  << Letters.shift_elements(3, 4, 12) << " ]\n";

        //Show a circular section shifted
        std::cout << "Positions 13 - 2 shifted -1:\n"
                  << "    |          |\n[ "
                  << Letters.shift_elements(-1, 13, 3) << " ]\n";

        std::cin.get();
        //======================================================================


        //Inverted shift========================================================
        std::cout << "\n**********Inverted shift_elements**********\n";

        //Initialize a pair of numerical lists
        data::clist <int> Numbers1, Numbers2;
        Numbers2 = data::clist_sequence( Numbers1.reset_list(10) ).random_order();

        //Show our original letter list
        std::cout << "Our original number lists:\n[ "
                  << Numbers1 << " ]\n[ "
                  << Numbers2 << " ]\n";

        //Set inverted mode
        Numbers1.o_inverted_sort_mode() = true;

        //Shift list one then invert
        std::cout << "List one shifted << 4 then inverted:\n[ ";
        Numbers1 << 4;
        std::cout << Numbers1 << " ]\n[ ";
        Numbers1.sort();
        std::cout << Numbers1 << " ]\n";

        //Set inverted mode
        Numbers2.o_inverted_sort_mode() = true;

        //Invert list two then invert
        std::cout << "List two inverted then inverse-shifted -4:\n[ ";
        Numbers2.sort();
        std::cout << Numbers2 << " ]\n[ ";
        data::clist_inverted_shift(Numbers2, -4);
        std::cout << Numbers2 << " ]\n";

        //Reinvert list two and use that to inverse sort one
        std::cout << "One inverse-sorted by two after it's been reinverted:\n[ "
                  << Numbers1.clist_ref_sort( Numbers2.sort() ) << " ]\n";

        std::cin.get();
        //======================================================================
}
