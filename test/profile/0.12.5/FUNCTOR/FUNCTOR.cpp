/*============================================================================*\
 *Functor Classes. Used to add functor functionality to other classes.        *
 *Copyright (C) 2003 Kevin P. Barry (ta0kira)                                 *
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
//(C) 2003 Kevin P. Barry

//==============================================================================
#ifndef FUNCTOR_CPP
#define FUNCTOR_CPP FUNCTOR_HPP
#include "FUNCTOR.hpp"

namespace FUNCTOR_CPP
{

//Function EVALUATE_0-----------------------------------------------------------
//Evaluates 0 argument function object
template <class Function> inline typename FUNCTION_0 <Function> ::RETURN
EVALUATE_0(Function fFunction)
{
        return E_ASSIST_0 <Function,
               IS_POINTER <FUNCTION_0 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_0(fFunction);
} //END-------------------------------------------------------------------------

//Function EVALUATE_1-----------------------------------------------------------
//Evaluates 1 argument function object
template <class Function> inline typename FUNCTION_1 <Function> ::RETURN
EVALUATE_1(Function fFunction, typename FUNCTION_1 <Function> ::ARG1 aArg1)
{
        return E_ASSIST_1 <Function,
               IS_POINTER <FUNCTION_1 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_1(fFunction, aArg1);
} //END-------------------------------------------------------------------------

//Function EVALUATE_2-----------------------------------------------------------
//Evaluates 2 argument function object
template <class Function> inline typename FUNCTION_2 <Function> ::RETURN
EVALUATE_2(Function fFunction, typename FUNCTION_2 <Function> ::ARG1 aArg1,
typename FUNCTION_2 <Function> ::ARG2 aArg2)
{
        return E_ASSIST_2 <Function,
               IS_POINTER <FUNCTION_2 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_2(fFunction, aArg1, aArg2);
} //END-------------------------------------------------------------------------

//Function EVALUATE_3-----------------------------------------------------------
//Evaluates 3 argument function object
template <class Function> inline typename FUNCTION_3 <Function> ::RETURN
EVALUATE_3(Function fFunction, typename FUNCTION_3 <Function> ::ARG1 aArg1,
typename FUNCTION_3 <Function> ::ARG2 aArg2,
typename FUNCTION_3 <Function> ::ARG3 aArg3)
{
        return E_ASSIST_3 <Function,
               IS_POINTER <FUNCTION_3 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_3(fFunction, aArg1, aArg2, aArg3);
} //END-------------------------------------------------------------------------

//Function EVALUATE_4-----------------------------------------------------------
//Evaluates 4 argument function object
template <class Function> inline typename FUNCTION_4 <Function> ::RETURN
EVALUATE_4(Function fFunction, typename FUNCTION_4 <Function> ::ARG1 aArg1,
typename FUNCTION_4 <Function> ::ARG2 aArg2,
typename FUNCTION_4 <Function> ::ARG3 aArg3,
typename FUNCTION_4 <Function> ::ARG4 aArg4)
{
        return E_ASSIST_4 <Function,
               IS_POINTER <FUNCTION_4 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_4(fFunction, aArg1, aArg2, aArg3, aArg4);
} //END-------------------------------------------------------------------------
//==============================================================================

//Evaluation function pointers==================================================
//Function EVALUATOR_0----------------------------------------------------------
//Returns function pointer to functor evaluator for 0 argument function
template <class Function> inline typename FUNCTION_0 <Function> ::
EVALUATE *EVALUATOR_0()
{
        return &E_ASSIST_0 <Function,
               IS_POINTER <FUNCTION_0 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_0;
} //END-------------------------------------------------------------------------

//Function EVALUATOR_1----------------------------------------------------------
//Returns function pointer to functor evaluator for 1 argument function
template <class Function> inline typename FUNCTION_1 <Function> ::
EVALUATE *EVALUATOR_1()
{
        return &E_ASSIST_1 <Function,
               IS_POINTER <FUNCTION_1 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_1;
} //END-------------------------------------------------------------------------

//Function EVALUATOR_2----------------------------------------------------------
//Returns function pointer to functor evaluator for 2 argument function
template <class Function> inline typename FUNCTION_2 <Function> ::
EVALUATE *EVALUATOR_2()
{
        return &E_ASSIST_2 <Function,
               IS_POINTER <FUNCTION_2 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_2;
} //END-------------------------------------------------------------------------

//Function EVALUATOR_3----------------------------------------------------------
//Returns function pointer to functor evaluator for 3 argument function
template <class Function> inline typename FUNCTION_3 <Function> ::
EVALUATE *EVALUATOR_3()
{
        return &E_ASSIST_3 <Function,
               IS_POINTER <FUNCTION_3 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_3;
} //END-------------------------------------------------------------------------

//Function EVALUATOR_4----------------------------------------------------------
//Returns function pointer to functor evaluator for 4 argument function
template <class Function> inline typename FUNCTION_4 <Function> ::
EVALUATE *EVALUATOR_4()
{
        return &E_ASSIST_4 <Function,
               IS_POINTER <FUNCTION_4 <Function> ::FUNCTOR_TYPE> ::TYPE> ::
               EVALUATE_4;
} //END-------------------------------------------------------------------------
//==============================================================================

//E_ASSIST_0 function bodies====================================================
        template <class Function> inline typename FUNCTION_0 <Function> ::RETURN
        E_ASSIST_0 <Function, false> ::EVALUATE_0(Function fFunction)
        { return fFunction(); }

        template <class Function> inline typename FUNCTION_0 <Function> ::RETURN
        E_ASSIST_0 <Function, true> ::EVALUATE_0(Function fFunction)
        { return (*fFunction)(); }
//==============================================================================

//E_ASSIST_1 function bodies====================================================
        template <class Function> inline typename FUNCTION_1 <Function> ::RETURN
        E_ASSIST_1 <Function, false> ::EVALUATE_1(Function fFunction,
        typename FUNCTION_1 <Function> ::ARG1 aArg1)
        { return fFunction(aArg1); }

        template <class Function> inline typename FUNCTION_1 <Function> ::RETURN
        E_ASSIST_1 <Function, true> ::EVALUATE_1(Function fFunction,
        typename FUNCTION_1 <Function> ::ARG1 aArg1)
        { return (*fFunction)(aArg1); }
//==============================================================================

//E_ASSIST_2 function bodies====================================================
        template <class Function> inline typename FUNCTION_2 <Function> ::RETURN
        E_ASSIST_2 <Function, false> ::EVALUATE_2(Function fFunction,
        typename FUNCTION_2 <Function> ::ARG1 aArg1,
        typename FUNCTION_2 <Function> ::ARG2 aArg2)
        { return fFunction(aArg1, aArg2); }

        template <class Function> inline typename FUNCTION_2 <Function> ::RETURN
        E_ASSIST_2 <Function, true> ::EVALUATE_2(Function fFunction,
        typename FUNCTION_2 <Function> ::ARG1 aArg1,
        typename FUNCTION_2 <Function> ::ARG2 aArg2)
        { return (*fFunction)(aArg1, aArg2); }
//==============================================================================

//E_ASSIST_3 function bodies====================================================
        template <class Function> inline typename FUNCTION_3 <Function> ::RETURN
        E_ASSIST_3 <Function, false> ::EVALUATE_3(Function fFunction,
        typename FUNCTION_3 <Function> ::ARG1 aArg1,
        typename FUNCTION_3 <Function> ::ARG2 aArg2,
        typename FUNCTION_3 <Function> ::ARG3 aArg3)
        { return fFunction(aArg1, aArg2, aArg3); }

        template <class Function> inline typename FUNCTION_3 <Function> ::RETURN
        E_ASSIST_3 <Function, true> ::EVALUATE_3(Function fFunction,
        typename FUNCTION_3 <Function> ::ARG1 aArg1,
        typename FUNCTION_3 <Function> ::ARG2 aArg2,
        typename FUNCTION_3 <Function> ::ARG3 aArg3)
        { return (*fFunction)(aArg1, aArg2, aArg3); }
//==============================================================================

//E_ASSIST_4 function bodies====================================================
        template <class Function> inline typename FUNCTION_4 <Function> ::RETURN
        E_ASSIST_4 <Function, false> ::EVALUATE_4(Function fFunction,
        typename FUNCTION_4 <Function> ::ARG1 aArg1,
        typename FUNCTION_4 <Function> ::ARG2 aArg2,
        typename FUNCTION_4 <Function> ::ARG3 aArg3,
        typename FUNCTION_4 <Function> ::ARG4 aArg4)
        { return fFunction(aArg1, aArg2, aArg3, aArg4); }

        template <class Function> inline typename FUNCTION_4 <Function> ::RETURN
        E_ASSIST_4 <Function, true> ::EVALUATE_4(Function fFunction,
        typename FUNCTION_4 <Function> ::ARG1 aArg1,
        typename FUNCTION_4 <Function> ::ARG2 aArg2,
        typename FUNCTION_4 <Function> ::ARG3 aArg3,
        typename FUNCTION_4 <Function> ::ARG4 aArg4)
        { return (*fFunction)(aArg1, aArg2, aArg3, aArg4); }
//==============================================================================
}

#endif
//==============================================================================
