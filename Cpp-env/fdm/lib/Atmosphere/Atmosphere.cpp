//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Atmosphere.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:34:30
//

// Include Files
#include "Atmosphere.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }
  return y;
}

//
// Arguments    : const double x[12]
//                double *T_atm
//                double *p_atm
//                double *rho
//                double *M
//                double *g
// Return Type  : void
//
void Atmosphere(const double x[12], double *T_atm, double *p_atm, double *rho,
                double *M, double *g)
{
  double a;
  // ==================%
  //  Atmosphere model %
  // ==================%
  //  Altitude (0 to 16 Km)
  //  Velocity (0 to 250 m/s)
  //  Radius of Earth
  if (x[11] <= 11000.0) {
    *T_atm = 288.15 - 0.0065 * x[11];
    //  Temperature
    *p_atm = 101325.0 * rt_powd_snf(*T_atm / 288.15, 5.2586437952291618);
    //  Pressure
  } else {
    *T_atm = 216.65;
    //  Temperature
    *p_atm = 22632.0 * std::exp(-9.81 * (x[11] - 11000.0) / 62178.55);
    //  Pressure
  }
  *rho = *p_atm / (287.0 * *T_atm);
  //  Density
  //  Gas constant
  //  Speed of Sound
  *M = x[0] / std::sqrt(401.94 * *T_atm);
  //  Mach number
  a = 6378.135 / (x[11] / 1000.0 + 6378.135);
  *g = 9.80665 * (a * a);
  //  Accleration due to gravity
}

//
// File trailer for Atmosphere.cpp
//
// [EOF]
//
