#ifndef ENGINE_H
#define ENGINE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void Engine(double Time, double Ts, const double x[12],
                   const double cntl[10], double Mach, double g,
                   double Thrust[2]);

extern void Engine_init();

#endif
