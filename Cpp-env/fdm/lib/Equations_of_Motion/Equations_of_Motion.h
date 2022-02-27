//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Equations_of_Motion.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:55:52
//

#ifndef EQUATIONS_OF_MOTION_H
#define EQUATIONS_OF_MOTION_H

// Include Files
#include "../rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void
Equations_of_Motion(const double x[12], double g, const double ALPHA_BREAK[27],
                    const double F18_Aerodata[1107], const double Thrust[2],
                    const double Geom[17], const double F18_Geom_damaged[17],
                    const double F18_Aerodata_damaged[1107], double rho,
                    const double Cntl[10], double F[12], double FORCES[3],
                    double MOMENTS[3], double DCG[3]);

#endif
//
// File trailer for Equations_of_Motion.h
//
// [EOF]
//
