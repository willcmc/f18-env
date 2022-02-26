//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: interp1.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:55:52
//

// Include Files
#include "interp1.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <math.h>

// Function Definitions
//
// Arguments    : const double varargin_1[27]
//                const double varargin_2[27]
//                double varargin_3
// Return Type  : double
//
namespace coder {
double interp1(const double varargin_1[27], const double varargin_2[27],
               double varargin_3)
{
  double pp_coefs[104];
  double md[27];
  double s[27];
  double x[27];
  double y[27];
  double dvdf[26];
  double dx[26];
  double Vq;
  int low_i;
  int low_ip1;
  std::copy(&varargin_2[0], &varargin_2[27], &y[0]);
  std::copy(&varargin_1[0], &varargin_1[27], &x[0]);
  low_i = 0;
  int exitg1;
  do {
    exitg1 = 0;
    if (low_i < 27) {
      if (std::isnan(varargin_1[low_i])) {
        exitg1 = 1;
      } else {
        low_i++;
      }
    } else {
      double d2max;
      double h;
      double xtmp;
      if (varargin_1[1] < varargin_1[0]) {
        for (low_i = 0; low_i < 13; low_i++) {
          xtmp = x[low_i];
          x[low_i] = x[26 - low_i];
          x[26 - low_i] = xtmp;
          xtmp = y[low_i];
          y[low_i] = y[26 - low_i];
          y[26 - low_i] = xtmp;
        }
      }
      h = 0.0;
      if ((!std::isinf(x[0])) && (!std::isinf(x[26]))) {
        d2max = 0.0;
        for (low_i = 0; low_i < 25; low_i++) {
          xtmp = x[low_i + 1];
          xtmp = std::abs((x[low_i + 2] - xtmp) - (xtmp - x[low_i]));
          if (xtmp > d2max) {
            d2max = xtmp;
          }
        }
        xtmp = std::fmax(std::abs(x[0]), std::abs(x[26]));
        if ((!std::isinf(xtmp)) && (!std::isnan(xtmp))) {
          if (xtmp <= 2.2250738585072014E-308) {
            xtmp = 4.94065645841247E-324;
          } else {
            frexp(xtmp, &low_ip1);
            xtmp = std::ldexp(1.0, low_ip1 - 53);
          }
        } else {
          xtmp = rtNaN;
        }
        if (d2max <= 2.0 * xtmp) {
          h = (x[26] - x[0]) / 26.0;
        }
      }
      if (h > 0.0) {
        Vq = rtNaN;
        if ((!std::isnan(varargin_3)) && (varargin_3 >= x[0]) &&
            (varargin_3 <= x[26])) {
          double c0;
          double c1;
          double c2;
          double dzzdx;
          if (varargin_3 < x[1]) {
            low_i = 1;
            dzzdx = (varargin_3 - x[0]) / h;
          } else if (varargin_3 >= x[25]) {
            low_i = 26;
            dzzdx = (varargin_3 - x[25]) / h;
          } else {
            xtmp = std::floor((varargin_3 - x[0]) / h);
            low_i = static_cast<int>(xtmp + 1.0);
            dzzdx = (varargin_3 - x[static_cast<int>(xtmp + 1.0) - 1]) / h;
          }
          xtmp = dzzdx / 2.0;
          d2max = dzzdx * xtmp;
          h = 3.0 * dzzdx - 4.0;
          c0 = -dzzdx * (dzzdx * (xtmp - 1.0) + 0.5);
          c1 = d2max * (h - 1.0) + 1.0;
          c2 = -xtmp * (dzzdx * h - 1.0);
          xtmp = d2max * (dzzdx - 1.0);
          if (low_i < 2) {
            h = y[low_i - 1];
            dzzdx = y[low_i + 1];
            Vq = ((c0 * ((3.0 * h - 3.0 * y[low_i]) + dzzdx) + c1 * h) +
                  c2 * y[low_i]) +
                 xtmp * dzzdx;
          } else if (low_i < 26) {
            Vq = ((c0 * y[low_i - 2] + c1 * y[low_i - 1]) + c2 * y[low_i]) +
                 xtmp * y[low_i + 1];
          } else {
            h = y[low_i - 2];
            Vq = ((c0 * h + c1 * y[low_i - 1]) + c2 * y[low_i]) +
                 xtmp * ((3.0 * y[low_i] - 3.0 * y[low_i - 1]) + h);
          }
        }
      } else {
        double c2;
        for (low_i = 0; low_i < 26; low_i++) {
          c2 = x[low_i + 1] - x[low_i];
          dx[low_i] = c2;
          dvdf[low_i] = (y[low_i + 1] - y[low_i]) / c2;
        }
        d2max = x[2] - x[0];
        h = x[26] - x[24];
        s[0] = ((dx[0] + 2.0 * d2max) * dx[1] * dvdf[0] +
                dx[0] * dx[0] * dvdf[1]) /
               d2max;
        s[26] = ((dx[25] + 2.0 * h) * dx[24] * dvdf[25] +
                 dx[25] * dx[25] * dvdf[24]) /
                h;
        md[0] = dx[1];
        md[26] = dx[24];
        for (low_i = 0; low_i < 25; low_i++) {
          xtmp = dx[low_i + 1];
          c2 = dx[low_i];
          s[low_i + 1] = 3.0 * (xtmp * dvdf[low_i] + c2 * dvdf[low_i + 1]);
          md[low_i + 1] = 2.0 * (xtmp + c2);
        }
        xtmp = dx[1] / md[0];
        md[1] -= xtmp * d2max;
        s[1] -= xtmp * s[0];
        for (low_i = 0; low_i < 24; low_i++) {
          xtmp = dx[low_i + 2] / md[low_i + 1];
          md[low_i + 2] -= xtmp * dx[low_i];
          s[low_i + 2] -= xtmp * s[low_i + 1];
        }
        xtmp = h / md[25];
        md[26] -= xtmp * dx[24];
        s[26] -= xtmp * s[25];
        s[26] /= md[26];
        for (low_i = 24; low_i >= 0; low_i--) {
          s[low_i + 1] =
              (s[low_i + 1] - dx[low_i] * s[low_i + 2]) / md[low_i + 1];
        }
        s[0] = (s[0] - d2max * s[1]) / md[0];
        for (low_i = 0; low_i < 26; low_i++) {
          double dzzdx;
          c2 = dvdf[low_i];
          d2max = s[low_i];
          h = dx[low_i];
          dzzdx = (c2 - d2max) / h;
          xtmp = (s[low_i + 1] - c2) / h;
          pp_coefs[low_i] = (xtmp - dzzdx) / h;
          pp_coefs[low_i + 26] = 2.0 * dzzdx - xtmp;
          pp_coefs[low_i + 52] = d2max;
          pp_coefs[low_i + 78] = y[low_i];
        }
        if (std::isnan(varargin_3)) {
          Vq = varargin_3;
        } else {
          int high_i;
          low_i = 0;
          low_ip1 = 2;
          high_i = 27;
          while (high_i > low_ip1) {
            int mid_i;
            mid_i = ((low_i + high_i) + 1) >> 1;
            if (varargin_3 >= x[mid_i - 1]) {
              low_i = mid_i - 1;
              low_ip1 = mid_i + 1;
            } else {
              high_i = mid_i;
            }
          }
          xtmp = varargin_3 - x[low_i];
          Vq = xtmp * (xtmp * (xtmp * pp_coefs[low_i] + pp_coefs[low_i + 26]) +
                       pp_coefs[low_i + 52]) +
               pp_coefs[low_i + 78];
        }
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  return Vq;
}

} // namespace coder

//
// File trailer for interp1.cpp
//
// [EOF]
//
