//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_Atmosphere_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:34:30
//

#ifndef _CODER_ATMOSPHERE_API_H
#define _CODER_ATMOSPHERE_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void Atmosphere(real_T x[12], real_T *T_atm, real_T *p_atm, real_T *rho,
                real_T *M, real_T *g);

void Atmosphere_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[5]);

void Atmosphere_atexit();

void Atmosphere_initialize();

void Atmosphere_terminate();

void Atmosphere_xil_shutdown();

void Atmosphere_xil_terminate();

#endif
//
// File trailer for _coder_Atmosphere_api.h
//
// [EOF]
//
