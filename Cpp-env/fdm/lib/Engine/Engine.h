//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Engine.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:35:34
//

#ifndef ENGINE_H
#define ENGINE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void Engine(double Time, double Ts, const double x[12],
                   const double cntl[10], double Mach, double g,
                   double Thrust[2]);

void Engine_init();

#endif
//
// File trailer for Engine.h
//
// [EOF]
//
