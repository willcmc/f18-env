// Include Files
#include "Atmosphere.h"
#include <cmath>

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
    *p_atm = 101325.0 * pow((*T_atm/288.15), (9.81/(287*0.0065)));
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
