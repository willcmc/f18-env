//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Engine.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:35:34
//

// Include Files
#include "Engine.h"
#include "Engine_data.h"
#include "Engine_initialize.h"
#include "rt_nonfinite.h"

// Variable Definitions
static double Eng_FBK[2];

// Function Definitions
void Engine(double Time, double Ts, const double x[12], const double cntl[10],
            double Mach, double g, double Thrust[2])
{
  static const double dv[10]{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
  static const short a[70]{
      16000, 12160, 8580,  5410,  4105,  3158,  1837,  16000, 12225, 8664,
      5465,  4143,  3225,  1863,  16250, 12560, 8775,  5614,  4278,  3263,
      1907,  17180, 13310, 9332,  6004,  4573,  3547,  2102,  18230, 14140,
      9873,  6461,  4927,  3811,  2338,  19230, 15030, 10580, 7088,  5378,
      4128,  2529,  20330, 15760, 11420, 7740,  5890,  4546,  2744,  21940,
      17030, 12430, 8474,  6674,  5107,  3040,  23290, 18370, 13510, 9288,
      7512,  5715,  3395,  23810, 19890, 14710, 10220, 8211,  6445,  3762};
  static const short iv[7]{0, 3048, 6096, 9144, 10668, 12192, 15240};
  double THRUST[70];
  double RE_Thrust;
  double qx1;
  double qx2;
  double rx;
  double ry;
  int low_ip1;
  if (!isInitialized_Engine) {
    Engine_initialize();
  }
  // ==============%
  //  Engine model %
  // ==============%
  //  if(time_traj == 1)
  //      x(12) = Altitude;
  //  end
  //  Altitude
  //  GE F404 Engine simple Real Time model max AB Static thrust breakpoints
  for (low_ip1 = 0; low_ip1 < 70; low_ip1++) {
    THRUST[low_ip1] = static_cast<double>(a[low_ip1]) * g / 2.2046;
  }
  //  GE F404 Engine simple Real Time model max AB Static thrust
  if ((Mach >= 0.0) && (Mach <= 0.9) && (x[11] >= 0.0) && (x[11] <= 15240.0)) {
    int b_low_i;
    int high_i;
    int low_i;
    int mid_i;
    low_i = 1;
    low_ip1 = 2;
    high_i = 10;
    while (high_i > low_ip1) {
      mid_i = (low_i + high_i) >> 1;
      if (Mach >= dv[mid_i - 1]) {
        low_i = mid_i;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }
    b_low_i = 1;
    low_ip1 = 2;
    high_i = 7;
    while (high_i > low_ip1) {
      mid_i = (b_low_i + high_i) >> 1;
      if (x[11] >= iv[mid_i - 1]) {
        b_low_i = mid_i;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }
    RE_Thrust = dv[low_i - 1];
    if (Mach == RE_Thrust) {
      low_ip1 = b_low_i + 7 * (low_i - 1);
      qx1 = THRUST[low_ip1 - 1];
      qx2 = THRUST[low_ip1];
    } else if (Mach == dv[low_i]) {
      low_ip1 = b_low_i + 7 * low_i;
      qx1 = THRUST[low_ip1 - 1];
      qx2 = THRUST[low_ip1];
    } else {
      rx = (Mach - RE_Thrust) / (dv[low_i] - RE_Thrust);
      low_ip1 = (b_low_i + 7 * (low_i - 1)) - 1;
      RE_Thrust = THRUST[low_ip1];
      ry = THRUST[(b_low_i + 7 * low_i) - 1];
      if (RE_Thrust == ry) {
        qx1 = THRUST[low_ip1];
      } else {
        qx1 = (1.0 - rx) * RE_Thrust + rx * ry;
      }
      low_ip1 = b_low_i + 7 * (low_i - 1);
      RE_Thrust = THRUST[b_low_i + 7 * low_i];
      if (THRUST[low_ip1] == RE_Thrust) {
        qx2 = THRUST[low_ip1];
      } else {
        qx2 = (1.0 - rx) * THRUST[low_ip1] + rx * RE_Thrust;
      }
    }
    low_ip1 = iv[b_low_i - 1];
    if ((x[11] == low_ip1) || (qx1 == qx2)) {
      qx2 = qx1;
    } else if (!(x[11] == iv[b_low_i])) {
      ry = (x[11] - static_cast<double>(low_ip1)) /
           static_cast<double>(iv[b_low_i] - low_ip1);
      qx2 = (1.0 - ry) * qx1 + ry * qx2;
    }
  } else {
    qx2 = rtNaN;
  }
  //  max AB Thrust at 100% Throttle for Flight Mach and Altitude
  if (Ts <= 0.1) {
    double DLE_Thrtl;
    double LE_Rlim;
    double LE_Thrtl_DYN;
    double RE_Rlim;
    double RE_Thrtl_DYN;
    //  Engine dynamics involved for use in Simulation, Ts is time step ususlly
    //  <= 0.1 for simulation
    ry = (cntl[4] + 0.31) * 100.0;
    //  Right Engine Throttle converted to PLA scale (31 - 131, >87 --> AB on)
    rx = (cntl[5] + 0.31) * 100.0;
    //  Left Engine Throttle converted to PLA scale
    //  Retreiving Feedback signal
    if (Time <= Ts) {
      //  Initialize Dynamic Throttle Variable and Difference in throttle
      //  Variable
      qx1 = 0.0;
      DLE_Thrtl = 0.0;
      RE_Thrtl_DYN = ry;
      LE_Thrtl_DYN = rx;
    } else {
      //  Compute the Difference in throttle from previous value
      qx1 = ry - Eng_FBK[0];
      DLE_Thrtl = rx - Eng_FBK[1];
      RE_Thrtl_DYN = Eng_FBK[0];
      LE_Thrtl_DYN = Eng_FBK[1];
    }
    if (ry <= 87.0) {
      //  Select Right Engine time constant and Rate limiter based on Throttle
      //  settings
      ry = 0.625;
      RE_Rlim = 19.03;
    } else {
      ry = 0.55;
      RE_Rlim = 26.81;
    }
    if (rx <= 87.0) {
      //  Select Left Engine time constant and Rate limiter based on Throttle
      //  settings
      RE_Thrust = 0.625;
      LE_Rlim = 19.03;
    } else {
      RE_Thrust = 0.55;
      LE_Rlim = 26.81;
    }
    rx = qx1 / ry;
    //  Compute Rate of change of Throttle
    ry = DLE_Thrtl / RE_Thrust;
    if (rx >= RE_Rlim) {
      //  Limit the Rate of change of throttle in Right Engine
      rx = RE_Rlim;
    }
    if (ry >= LE_Rlim) {
      //  Limit the Rate of change of throttle in Left Engine
      ry = LE_Rlim;
    }
    RE_Thrtl_DYN += rx * Ts;
    //  compute the Dynamic Throttle from rate using Euker's Integration
    LE_Thrtl_DYN += ry * Ts;
    //  Assign variables to be used as feedback to compute change in Throttle
    Eng_FBK[0] = RE_Thrtl_DYN;
    Eng_FBK[1] = LE_Thrtl_DYN;
    RE_Thrust = qx2 * (RE_Thrtl_DYN - 31.0) / 100.0;
    //  Right Engine Thrust with Throttle converted back to % scale
    ry = qx2 * (LE_Thrtl_DYN - 31.0) / 100.0;
    //  Left  Engine Thrust with Throttle converted back to % scale
  } else {
    //  No dynamics involved for use in trim
    //  Right Engine Throttle
    //  left Engine Throttle
    Eng_FBK[0] = 0.0;
    Eng_FBK[1] = 0.0;
    RE_Thrust = qx2 * cntl[4];
    //  Right Engine Thrust in % scale
    ry = qx2 * cntl[5];
    //  Left Engine Thrust  in % scale
  }
  Thrust[0] = RE_Thrust;
  Thrust[1] = ry;
}

//
// Arguments    : void
// Return Type  : void
//

void Engine_init()
{
  Eng_FBK[0] = 0.0;
  Eng_FBK[1] = 0.0;
}