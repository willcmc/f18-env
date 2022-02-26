// Include Files
#include "main.h"
#include "./lib/Atmosphere/Atmosphere.h"
#include <math.h>

int main()
{
  AerodataF18 Aero;

  double F18_Aerodata[1107];
  double ALPHA_BREAK[27];
  double Geom[17];

  double T_atm;
  double p_atm; 
  double rho;
  double M; 
  double g;

  double x[12] = {200, 2*M_PI/180, 0, 0, 0, 0, 0, 1.2*M_PI/180, 0, 0.1, 0.1, 1000};

  Aero.Aerodata(Geom, ALPHA_BREAK, F18_Aerodata);
  Atmosphere(x, &T_atm, &p_atm, &rho, &M, &g);

  std::cout << T_atm;

  Visualizer viz("127.0.0.1", 5000, "generic");
  return 0;
}