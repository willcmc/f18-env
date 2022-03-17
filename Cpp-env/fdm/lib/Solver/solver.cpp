#include "solver.h"
#include "../Equations_of_Motion/Equations_of_Motion.h"
#include "../Atmosphere/Atmosphere.h"
#include "../Engine/Engine.h"
#include <iostream>
#include <math.h>

void rk4(double* x, double* dx, float Ts, int t, double x_new[3][12], double* cntl,double* F18_Aerodata,double* ALPHA_BREAK, double* Geom)
{
  double dx_new[3][12];
  float K1,K2,K3,K4;
   
   
  double DCG[3];
  double FORCES[3];
  double MOMENTS[3];
   
  double T_atm;
  double p_atm; 
  double rho;
  double M;
  double g;
  double Thrust[2];

  for (int i = 0; i <12; i++)
  {
    K1 = Ts*dx[i];
    x_new[0][i] += K1/2;
    x[i] += K1/6;
  }
  
  Atmosphere(x_new[0], &T_atm, &p_atm, &rho, &M, &g);
  Engine(t, Ts/2, x_new[0], cntl, M, g, Thrust); 
  Equations_of_Motion(x_new[0], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, g, cntl, dx_new[0], FORCES, MOMENTS, DCG);
  
  
  for (int i = 0; i <12; i++){
    K2 = Ts*dx_new[0][i];
    x_new[1][i] += K2/2; 
    x[i] += K2/3;
  }
  

  Atmosphere(x_new[1], &T_atm, &p_atm, &rho, &M, &g);
  Engine(t, Ts/2, x_new[1], cntl, M, g, Thrust); 
  Equations_of_Motion(x_new[1], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, g, cntl, dx_new[1], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    K3 = Ts*dx_new[1][i];
    x_new[2][i] += K3; 
    x[i] += K3/3;
  }

  Atmosphere(x_new[2], &T_atm, &p_atm, &rho, &M, &g);
  Engine(t, Ts/2, x_new[2], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[2], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, g, cntl, dx_new[2], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    K4 = Ts*dx_new[2][i];
    x[i] += K4/6;
    if (std::isnan(x[i])){
      std::cerr << "States out of bound after " << t << " timesteps (" << t*Ts << " seconds). Terminating." << "\n";
      exit(-1);
    }
    
  }
}