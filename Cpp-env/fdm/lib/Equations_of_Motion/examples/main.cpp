//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:55:52
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
#include "Equations_of_Motion.h"
#include "Equations_of_Motion_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_12x1_real_T(double result[12]);

static void argInit_17x1_real_T(double result[17]);

static void argInit_1x10_real_T(double result[10]);

static void argInit_27x1_real_T(double result[27]);

static void argInit_27x41_real_T(double result[1107]);

static void argInit_2x1_real_T(double result[2]);

static double argInit_real_T();

static void main_Equations_of_Motion();

// Function Definitions
//
// Arguments    : double result[12]
// Return Type  : void
//
static void argInit_12x1_real_T(double result[12])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 12; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[17]
// Return Type  : void
//
static void argInit_17x1_real_T(double result[17])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 17; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[10]
// Return Type  : void
//
static void argInit_1x10_real_T(double result[10])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 10; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

//
// Arguments    : double result[27]
// Return Type  : void
//
static void argInit_27x1_real_T(double result[27])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 27; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : double result[1107]
// Return Type  : void
//
static void argInit_27x41_real_T(double result[1107])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 27; idx0++) {
    for (int idx1{0}; idx1 < 41; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 27 * idx1] = argInit_real_T();
    }
  }
}

//
// Arguments    : double result[2]
// Return Type  : void
//
static void argInit_2x1_real_T(double result[2])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 2; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real_T();
  }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_Equations_of_Motion()
{
  double F18_Aerodata_tmp[1107];
  double dv1[27];
  double Geom_tmp[17];
  double F[12];
  double dv[12];
  double dv3[10];
  double DCG[3];
  double FORCES[3];
  double MOMENTS[3];
  double dv2[2];
  double g_tmp;
  // Initialize function 'Equations_of_Motion' input arguments.
  // Initialize function input argument 'x'.
  g_tmp = argInit_real_T();
  // Initialize function input argument 'ALPHA_BREAK'.
  // Initialize function input argument 'F18_Aerodata'.
  argInit_27x41_real_T(F18_Aerodata_tmp);
  // Initialize function input argument 'Thrust'.
  // Initialize function input argument 'Geom'.
  argInit_17x1_real_T(Geom_tmp);
  // Initialize function input argument 'F18_Geom_damaged'.
  // Initialize function input argument 'F18_Aerodata_damaged'.
  // Initialize function input argument 'Cntl'.
  // Call the entry-point 'Equations_of_Motion'.
  argInit_12x1_real_T(dv);
  argInit_27x1_real_T(dv1);
  argInit_2x1_real_T(dv2);
  argInit_1x10_real_T(dv3);
  Equations_of_Motion(dv, g_tmp, dv1, F18_Aerodata_tmp, dv2, Geom_tmp, Geom_tmp,
                      F18_Aerodata_tmp, g_tmp, dv3, F, FORCES, MOMENTS, DCG);
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_Equations_of_Motion();
  // Terminate the application.
  // You do not need to do this more than one time.
  Equations_of_Motion_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
