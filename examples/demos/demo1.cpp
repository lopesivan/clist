/*============================================================================*\
 *CList list library demo program 1.                                          *
 *Copyright (C) 2007 Kevin P. Barry                                           *
 *                                                                            *
 *This program is free software; you can redistribute it and/or modify it     *
 *under the terms of the GNU General Public License as published by the Free  *
 *Software Foundation; either version 2 of the License, or (at your option)   *
 *any later version.                                                          *
 *                                                                            *
 *This program is distributed in the hope that it will be useful, but WITHOUT *
 *ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
 *FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for    *
 *more details.                                                               *
 *                                                                            *
 *You should have received a copy of the GNU General Public License along with*
 *this program; if not, write to the                                          *
 *                                                                            *
 *    Free Software Foundation, Inc.,                                         *
 *    59 Temple Place, Suite 330,                                             *
 *    Boston, MA 02111-1307 USA                                               *
 *                                                                            *
 *Please contact ta0kira@users.sourceforge.net for feedback, questions, or    *
 *comments.                                                                   *
\*============================================================================*/

/* This program demonstrates the versatility of the CList library.  It makes
   use of a lot of the available functionality that separates it from other
   list libraries.

   This program gives the user a list of objects to choose the order of.  The
   user selects the objects one at a time by partial or full name.  Once all
   objects are selected, the program places them in their chosen order.

   The program starts by creating a string list of object names, a shadow
   list of positions corresponding to the string list, and an empty shadow
   list.  As the user enters object names, the corresponding element from the
   shadow list which mirrors the string list is removed and placed in the
   second shadow list.  After all input is complete, the first shadow list is
   empty and the second contains a list of element positions denoting the
   object order the user chose.  The program then sorts the object list based
   on the order of the second shadow list.

   The original order of the object list isn't changed until all input is
   complete.  If the user leaves an input line blank then the selection lists
   are reset.                                                                 */

#include <string>   //'std::string'
#include <string.h> //'strcmp', 'strncmp', 'strlen'
#include <iostream> //'std::cout', 'std::cin'

#include <ta0kira/clist.hpp>


//list of objects to choose from
static const char *objects[] = {         "ball",
                                        "apple",
                                     "elephant",
                                       "purple",
                                 "packing tape",
                                 "fire hydrant",
                                    "last item",
                                       __FILE__,
                                   "technology"  };


//output-formatting function
template <class Type>
static void add_space_newline(std::ostream &oOutput, Type &dData)
{ oOutput << " " << dData << std::endl; }


//comparison function allowing user to type only the first part
static bool partial_string_compare(const std::string &lLeft, const char *rRight)
{ return strncmp(lLeft.c_str(), rRight, strlen(rRight)) == 0; }


//main function
int main(int argc, char *argv[])
{
	data::clist <const std::string> object_list;
	data::list_shadow               select_list, position_list;
	//object_list:   holds the names of the objects
	//select_list:   holds the positions of objects yet to be chosen
	//position_list: holds the positions of chosen objects


	//fill the object list with the object names
	const char **input_object = objects;
	while (*input_object && object_list.add_element(*input_object++));

	//create a "blank shadow", or sequence of positions for the object list
	data::create_blank_shadow(object_list, select_list);

	//user input buffer
	char user_input[32];


	//object-selection loop (user input)
	while (select_list.size() && !std::cin.eof())
	{
	//mix up the remaining items just for fun
	select_list.random_order();

	std::cin.clear();
	user_input[0] = '\0';

	std::cout << "PLEASE SELECT THE NEXT ITEM TO PLACE IN THE LIST\n"
	          << "(type the name of the item or just the beginning)\n"
	          << "(press [Enter] to start over, type \"DONE\" to finish)\n\n";


	std::cout << data::f_bind_convert_format_output( select_list,
                       data::bind_convert_shadow(object_list, select_list),
                       &add_space_newline <const std::string> );
	//'bind_convert_shadow' converts the elements of 'select_list' to
	//elements of 'object_list'. 'f_bind_convert_format_output' binds the
	//conversion functor ('bind_convert_shadow') and the format functor
	//('add_space_newline') to 'select_list' for output.


	//get user input
	std::cout << "\n> ";
	std::cin.getline(user_input, 32);


	if (!std::cin) break;
	//cancel if there's an input error

	else if (strlen(user_input) == 0)
	//reset everything if input is left blank
	 {
	std::cout << "STARTING OVER!\n\n";
	select_list.reset_list(); //(not actually necessary)
	position_list.reset_list();
	data::create_blank_shadow(object_list, select_list);
	continue;
	 }


	if (strcmp(user_input, "DONE") == 0)
	 {
	std::cout << "AUTOMATICALLY SELECTING THE REST!\n\n";
	break;
	 }


	//find the position of the object entered
	int position = select_list.f_find( user_input,
	                 data::f_bind_extern_shadow( object_list, select_list,
	                   &partial_string_compare ) );
	//'f_bind_extern_shadow' binds the 'partial_string_compare' functor to
	//both the shadow list ('select_list') and the original list
	//('object_list') for use as a functor in 'f_find'.  This allows the
	//user to enter a partial object name and also allows the program to
	//find the corresponding element in the shadow 'select_list'.


	if (position == data::not_found)
	//continue if the item isn't found
	 {
	std::cout << "ITEM NOT FOUND IN THE LIST!\n\n";
	continue;
	 }


	//add the position of the chosen item to the new list
	position_list.add_element( select_list[position] );

	//display the chosen item and remove the position from the old list
	std::cout << "ITEM CHOSEN: "
	          << object_list[ select_list.p_get_element(position) ]
	          << std::endl << std::endl << std::endl;
	}


	if (std::cin.eof())
	//input loop canceled by user
	 {
	std::cout << "\nCANCELLED!\n";
	return 1;
	 }


	//add the remaining elements if necessary
	if (!select_list.size()) std::cout << "ALL ITEMS CHOSEN!\n\n";
	else position_list.add_element(select_list);


	//chose element order by using inverted mode
	object_list.o_inverted_sort_mode() = true;
	object_list.clist_ref_sort(position_list);
	//REMEMBER: in order for a reference sort to reflect the actual
	//numerical values of the shadow list, the shadow list MUST contain an
	//element for every position in the list to be sorted.  That's why we
	//have to add the remaining elements if the user left any.


	//show the list of objects in the chosen order
	if (select_list.size() < object_list.size())
	{
	std::cout << "THE OBJECTS YOU CHOSE IN THE ORDER YOU CHOSE THEM:\n\n";

	std::cout << data::f_bind_format_output( object_list,
                       &add_space_newline <const std::string>,
	               data::first, data::last - select_list.size() + 1 );
	//'f_bind_format_output' binds 'add_space_newline' to 'object_list'
	//for formatted output
	}


	//show the remaining list objects
	if (select_list.size())
	{
	std::cout << "\nTHE OBJECTS LEFT AFTER YOU WERE DONE:\n\n";

	std::cout << data::f_bind_format_output( object_list,
                       &add_space_newline <const std::string>,
	               data::last - select_list.size() + 1 );
	//'f_bind_format_output' binds 'add_space_newline' to 'object_list'
	//for formatted output
	}

	std::cout << "\nDEMO COMPLETE!\n";

	return 0;
}
