//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_Engine_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:35:34
//

#ifndef _CODER_ENGINE_API_H
#define _CODER_ENGINE_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void Engine(real_T Time, real_T Ts, real_T x[12], real_T cntl[10], real_T Mach,
            real_T g, real_T Thrust[2]);

void Engine_api(const mxArray *const prhs[6], const mxArray **plhs);

void Engine_atexit();

void Engine_initialize();

void Engine_terminate();

void Engine_xil_shutdown();

void Engine_xil_terminate();

#endif
//
// File trailer for _coder_Engine_api.h
//
// [EOF]
//
