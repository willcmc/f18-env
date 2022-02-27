// Include Files
#include "main.h"
#include "Engine.h"
#include "Engine_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_12x1_real_T(double result[12]);

static void argInit_1x10_real_T(double result[10]);

static double argInit_real_T();

static void main_Engine();

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
static void main_Engine()
{
  double dv[12];
  double dv1[10];
  double Thrust[2];
  double Time_tmp;
  // Initialize function 'Engine' input arguments.
  Time_tmp = argInit_real_T();
  // Initialize function input argument 'x'.
  // Initialize function input argument 'cntl'.
  // Call the entry-point 'Engine'.
  argInit_12x1_real_T(dv);
  argInit_1x10_real_T(dv1);
  Engine(Time_tmp, Time_tmp, dv, dv1, Time_tmp, Time_tmp, Thrust);
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
  main_Engine();
  // Terminate the application.
  // You do not need to do this more than one time.
  Engine_terminate();
  return 0;
}