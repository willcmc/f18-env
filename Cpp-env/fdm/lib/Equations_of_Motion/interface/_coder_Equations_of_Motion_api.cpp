//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_Equations_of_Motion_api.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:55:52
//

// Include Files
#include "_coder_Equations_of_Motion_api.h"
#include "_coder_Equations_of_Motion_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

static real_T damage;

static uint32_T damage_guard;

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131610U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "Equations_of_Motion",                                // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void Equations_of_Motion_once();

static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                                   const char_T *identifier))[12];

static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[12];

static const mxArray *b_emlrt_marshallOut(const real_T u[3]);

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp,
                                   const mxArray *ALPHA_BREAK,
                                   const char_T *identifier))[27];

static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[27];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp,
                                   const mxArray *F18_Aerodata,
                                   const char_T *identifier))[1107];

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[1107];

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[2];

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Thrust,
                                   const char_T *identifier))[2];

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_damage,
                               const char_T *identifier);

static const mxArray *emlrt_marshallOut(const real_T u);

static const mxArray *emlrt_marshallOut(const real_T u[12]);

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Geom,
                                   const char_T *identifier))[17];

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[17];

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10];

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Cntl,
                                   const char_T *identifier))[10];

static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[12];

static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[27];

static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[1107];

static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[2];

static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[17];

static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10];

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
static void Equations_of_Motion_once()
{
  damage_guard = 0U;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[12]
//
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[12]
{
  real_T(*y)[12];
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *x
//                const char_T *identifier
// Return Type  : real_T (*)[12]
//
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *x,
                                   const char_T *identifier))[12]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[12];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(x), &thisId);
  emlrtDestroyArray(&x);
  return y;
}

//
// Arguments    : const real_T u[3]
// Return Type  : const mxArray *
//
static const mxArray *b_emlrt_marshallOut(const real_T u[3])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 3};
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
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[27]
//
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[27]
{
  real_T(*y)[27];
  y = j_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *ALPHA_BREAK
//                const char_T *identifier
// Return Type  : real_T (*)[27]
//
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp,
                                   const mxArray *ALPHA_BREAK,
                                   const char_T *identifier))[27]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[27];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = c_emlrt_marshallIn(sp, emlrtAlias(ALPHA_BREAK), &thisId);
  emlrtDestroyArray(&ALPHA_BREAK);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[1107]
//
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[1107]
{
  real_T(*y)[1107];
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *F18_Aerodata
//                const char_T *identifier
// Return Type  : real_T (*)[1107]
//
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp,
                                   const mxArray *F18_Aerodata,
                                   const char_T *identifier))[1107]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[1107];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(F18_Aerodata), &thisId);
  emlrtDestroyArray(&F18_Aerodata);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[2]
//
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[2]
{
  real_T(*y)[2];
  y = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *Thrust
//                const char_T *identifier
// Return Type  : real_T (*)[2]
//
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Thrust,
                                   const char_T *identifier))[2]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[2];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = e_emlrt_marshallIn(sp, emlrtAlias(Thrust), &thisId);
  emlrtDestroyArray(&Thrust);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *b_damage
//                const char_T *identifier
// Return Type  : real_T
//
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_damage,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_damage), &thisId);
  emlrtDestroyArray(&b_damage);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T
//
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const real_T u
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const real_T u[12]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u[12])
{
  static const int32_T i{0};
  static const int32_T i1{12};
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
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[17]
//
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[17]
{
  real_T(*y)[17];
  y = m_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *Geom
//                const char_T *identifier
// Return Type  : real_T (*)[17]
//
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Geom,
                                   const char_T *identifier))[17]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[17];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(Geom), &thisId);
  emlrtDestroyArray(&Geom);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[10]
//
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10]
{
  real_T(*y)[10];
  y = n_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *Cntl
//                const char_T *identifier
// Return Type  : real_T (*)[10]
//
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Cntl,
                                   const char_T *identifier))[10]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[10];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = g_emlrt_marshallIn(sp, emlrtAlias(Cntl), &thisId);
  emlrtDestroyArray(&Cntl);
  return y;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T
//
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[12]
//
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[12]
{
  static const int32_T dims{12};
  real_T(*ret)[12];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[12])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[27]
//
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[27]
{
  static const int32_T dims{27};
  real_T(*ret)[27];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[27])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[1107]
//
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[1107]
{
  static const int32_T dims[2]{27, 41};
  real_T(*ret)[1107];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[1107])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[2]
//
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[2]
{
  static const int32_T dims{2};
  real_T(*ret)[2];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[2])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[17]
//
static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[17]
{
  static const int32_T dims{17};
  real_T(*ret)[17];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[17])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[10]
//
static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10]
{
  static const int32_T dims[2]{1, 10};
  real_T(*ret)[10];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 2U, (void *)&dims[0]);
  ret = (real_T(*)[10])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const mxArray * const prhs[10]
//                int32_T nlhs
//                const mxArray *plhs[4]
// Return Type  : void
//
void Equations_of_Motion_api(const mxArray *const prhs[10], int32_T nlhs,
                             const mxArray *plhs[4])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*F18_Aerodata)[1107];
  real_T(*F18_Aerodata_damaged)[1107];
  real_T(*ALPHA_BREAK)[27];
  real_T(*F18_Geom_damaged)[17];
  real_T(*Geom)[17];
  real_T(*F)[12];
  real_T(*x)[12];
  real_T(*Cntl)[10];
  real_T(*DCG)[3];
  real_T(*FORCES)[3];
  real_T(*MOMENTS)[3];
  real_T(*Thrust)[2];
  real_T g;
  real_T rho;
  st.tls = emlrtRootTLSGlobal;
  F = (real_T(*)[12])mxMalloc(sizeof(real_T[12]));
  FORCES = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  MOMENTS = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  DCG = (real_T(*)[3])mxMalloc(sizeof(real_T[3]));
  // Marshall function inputs
  x = b_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "x");
  g = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "g");
  ALPHA_BREAK = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "ALPHA_BREAK");
  F18_Aerodata = d_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "F18_Aerodata");
  Thrust = e_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "Thrust");
  Geom = f_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "Geom");
  F18_Geom_damaged =
      f_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "F18_Geom_damaged");
  F18_Aerodata_damaged =
      d_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "F18_Aerodata_damaged");
  rho = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "rho");
  Cntl = g_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "Cntl");
  // Marshall in global variables
  MEXGlobalSyncInFunction(&st);
  // Invoke the target function
  Equations_of_Motion(*x, g, *ALPHA_BREAK, *F18_Aerodata, *Thrust, *Geom,
                      *F18_Geom_damaged, *F18_Aerodata_damaged, rho, *Cntl, *F,
                      *FORCES, *MOMENTS, *DCG);
  // Marshall out global variables
  MEXGlobalSyncOutFunction(true);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*F);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*FORCES);
  }
  if (nlhs > 2) {
    plhs[2] = b_emlrt_marshallOut(*MOMENTS);
  }
  if (nlhs > 3) {
    plhs[3] = b_emlrt_marshallOut(*DCG);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void Equations_of_Motion_atexit()
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
  Equations_of_Motion_xil_terminate();
  Equations_of_Motion_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void Equations_of_Motion_initialize()
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
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    Equations_of_Motion_once();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void Equations_of_Motion_terminate()
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
// Arguments    : const emlrtStack *sp
// Return Type  : void
//
void MEXGlobalSyncInFunction(const emlrtStack *sp)
{
  const mxArray *tmp;
  // Marshall in global variables
  tmp = emlrtGetGlobalVariable((const char_T *)"damage");
  if (tmp != nullptr) {
    damage = emlrt_marshallIn(sp, tmp, "damage");
    damage_guard = 1U;
  }
}

//
// Arguments    : boolean_T skipDirtyCheck
// Return Type  : void
//
void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck)
{
  // Marshall out global variables
  if (skipDirtyCheck || (damage_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"damage", emlrt_marshallOut(damage));
  }
}

//
// File trailer for _coder_Equations_of_Motion_api.cpp
//
// [EOF]
//
