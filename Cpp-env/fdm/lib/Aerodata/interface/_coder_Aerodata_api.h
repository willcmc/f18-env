//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_Aerodata_api.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 24-Feb-2022 03:23:51
//

#ifndef _CODER_AERODATA_API_H
#define _CODER_AERODATA_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void Aerodata(real_T Geom[17], real_T ALPHA_BREAK[27],
              real_T F18_Aerodata[1107]);

void Aerodata_api(int32_T nlhs, const mxArray *plhs[3]);

void Aerodata_atexit();

void Aerodata_initialize();

void Aerodata_terminate();

void Aerodata_xil_shutdown();

void Aerodata_xil_terminate();

#endif
//
// File trailer for _coder_Aerodata_api.h
//
// [EOF]
//
