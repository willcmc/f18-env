//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 24-Feb-2022 03:23:51
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "AerodataF18.h"

// Function Declarations
static void main_Aerodata(AerodataF18 *instancePtr);

// Function Definitions
//
// Arguments    : AerodataF18 *instancePtr
// Return Type  : void
//
static void main_Aerodata(AerodataF18 *instancePtr)
{
  double F18_Aerodata[1107];
  double ALPHA_BREAK[27];
  double Geom[17];
  // Call the entry-point 'Aerodata'.
  instancePtr->Aerodata(Geom, ALPHA_BREAK, F18_Aerodata);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  AerodataF18 *classInstance;
  classInstance = new AerodataF18;
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_Aerodata(classInstance);
  delete classInstance;
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
