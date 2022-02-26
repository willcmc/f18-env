//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_Equations_of_Motion_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:55:52
//

#ifndef _CODER_EQUATIONS_OF_MOTION_API_H
#define _CODER_EQUATIONS_OF_MOTION_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void Equations_of_Motion(real_T x[12], real_T g, real_T ALPHA_BREAK[27],
                         real_T F18_Aerodata[1107], real_T Thrust[2],
                         real_T Geom[17], real_T F18_Geom_damaged[17],
                         real_T F18_Aerodata_damaged[1107], real_T rho,
                         real_T Cntl[10], real_T F[12], real_T FORCES[3],
                         real_T MOMENTS[3], real_T DCG[3]);

void Equations_of_Motion_api(const mxArray *const prhs[10], int32_T nlhs,
                             const mxArray *plhs[4]);

void Equations_of_Motion_atexit();

void Equations_of_Motion_initialize();

void Equations_of_Motion_terminate();

void Equations_of_Motion_xil_shutdown();

void Equations_of_Motion_xil_terminate();

void MEXGlobalSyncInFunction(const emlrtStack *sp);

void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck);

#endif
//
// File trailer for _coder_Equations_of_Motion_api.h
//
// [EOF]
//
