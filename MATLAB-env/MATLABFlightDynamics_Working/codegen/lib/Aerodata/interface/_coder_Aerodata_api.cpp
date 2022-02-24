//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_Aerodata_api.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 24-Feb-2022 03:23:51
//

// Include Files
#include "_coder_Aerodata_api.h"
#include "_coder_Aerodata_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131610U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "Aerodata",                                           // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static const mxArray *b_emlrt_marshallOut(const real_T u[27]);

static const mxArray *c_emlrt_marshallOut(const real_T u[1107]);

static const mxArray *emlrt_marshallOut(const real_T u[17]);

// Function Definitions
//
// Arguments    : const real_T u[27]
// Return Type  : const mxArray *
//
static const mxArray *b_emlrt_marshallOut(const real_T u[27])
{
  static const int32_T i{0};
  static const int32_T i1{27};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const real_T u[1107]
// Return Type  : const mxArray *
//
static const mxArray *c_emlrt_marshallOut(const real_T u[1107])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{27, 41};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const real_T u[17]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u[17])
{
  static const int32_T i{0};
  static const int32_T i1{17};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : int32_T nlhs
//                const mxArray *plhs[3]
// Return Type  : void
//
void Aerodata_api(int32_T nlhs, const mxArray *plhs[3])
{
  real_T(*F18_Aerodata)[1107];
  real_T(*ALPHA_BREAK)[27];
  real_T(*Geom)[17];
  Geom = (real_T(*)[17])mxMalloc(sizeof(real_T[17]));
  ALPHA_BREAK = (real_T(*)[27])mxMalloc(sizeof(real_T[27]));
  F18_Aerodata = (real_T(*)[1107])mxMalloc(sizeof(real_T[1107]));
  // Invoke the target function
  Aerodata(*Geom, *ALPHA_BREAK, *F18_Aerodata);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*Geom);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*ALPHA_BREAK);
  }
  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(*F18_Aerodata);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void Aerodata_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Aerodata_xil_terminate();
  Aerodata_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void Aerodata_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void Aerodata_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_Aerodata_api.cpp
//
// [EOF]
//
