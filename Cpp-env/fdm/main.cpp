// Include Files

#include "main.h"

int main()
{
  float Ts = 0.5;

  AerodataF18 Aero;

  // Aerodynamic data vars
  double F18_Aerodata[1107];
  double ALPHA_BREAK[27];
  double Geom[17];

  // Atmospheric data vars
  double T_atm;
  double p_atm; 
  double rho;
  double M; 
  double g;

  // Engine data vars
  double Thrust[2] = {0, 0};

  // Initial states
  double x[12] = {200, 2*M_PI/180, 0, 0, 0, 0, 0, 1.2*M_PI/180, 0, 0.1, 0.1, 1000};

  // Initial control
  float delta_e = 0.0;
  double cntl[10] = {delta_e, delta_e, 0, 0, 1, 1, 0, 0, 0, 0};

  // Get aerodynamic data
  Aero.Aerodata(Geom, ALPHA_BREAK, F18_Aerodata);


  // Construct Visualizer object
  Visualizer viz("127.0.0.1", 5000, "generic");  

  for (int t = 0; t < 10; t++){
    Atmosphere(x, &T_atm, &p_atm, &rho, &M, &g);
    Engine(t, Ts, x, cntl, M, g, Thrust);
    std::cout << *Thrust << "\n";
    cntl[3] = -1;
    x[11] = 100;
    viz.send_fg(x, cntl);
  }

  return 0;
}