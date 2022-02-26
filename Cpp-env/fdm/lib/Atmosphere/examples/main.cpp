// Include Files
#include "main.h"
#include "Atmosphere.h"
#include "Atmosphere_terminate.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_12x1_real_T(double result[12]);

static double argInit_real_T();

static void main_Atmosphere();

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
static void main_Atmosphere()
{
  double dv[12];
  double M;
  double T_atm;
  double g;
  double p_atm;
  double rho;
  // Initialize function 'Atmosphere' input arguments.
  // Initialize function input argument 'x'.
  // Call the entry-point 'Atmosphere'.
  argInit_12x1_real_T(dv);
  Atmosphere(dv, &T_atm, &p_atm, &rho, &M, &g);
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
  main_Atmosphere();
  // Terminate the application.
  // You do not need to do this more than one time.
  Atmosphere_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
