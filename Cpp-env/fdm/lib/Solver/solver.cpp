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
  //Engine(t+(Ts/2), Ts, x_new[0], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[0], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[0], FORCES, MOMENTS, DCG);
  
  
  for (int i = 0; i <12; i++){
    K2 = Ts*dx_new[0][i];
    x_new[1][i] += K2/2; 
    x[i] += K2/3;
  }
  

  Atmosphere(x_new[1], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+(Ts/2), Ts, x_new[1], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[1], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[1], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    K3 = Ts*dx_new[1][i];
    x_new[2][i] += K3; 
    x[i] += K3/3;
  }

  Atmosphere(x_new[2], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+(Ts), Ts, x_new[2], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[2], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[2], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    
    K4 = Ts*dx_new[2][i];
    x[i] += K4/6;
    
    if (std::isnan(x[i])){
      std::cerr << "States out of bound after " << t << " timesteps (" << t*Ts << " seconds). Terminating." << "\n";
      exit(-1);
    }
  }
  
}


void rk4_fehlberg(double* x, double* dx, float Ts, int t, double x_new[3][12], double* cntl,double* F18_Aerodata,double* ALPHA_BREAK, double* Geom)
{
  double dx_new[5][12];
  double K1[12],K2[12],K3[12],K4[12],K5[12],K6;
   
   
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
    K1[i] = Ts*dx[i];
    x_new[0][i] += (2*K1[i])/9;
    x[i] += (47*K1[i])/450;
  }
  
  Atmosphere(x_new[0], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+((2*Ts)/9), Ts, x_new[0], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[0], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[0], FORCES, MOMENTS, DCG);
  
  
  for (int i = 0; i <12; i++){
    K2[i] = Ts*dx_new[0][i];
    x_new[1][i] += ( K1[i]/12 + K2[i]/4 ); 
  }
  

  Atmosphere(x_new[1], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+(Ts/3), Ts, x_new[1], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[1], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[1], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    K3[i] = Ts*dx_new[1][i];
    x_new[2][i] += ( (69*K1[i])/128 + (K2[i]*(-243))/128 + (K3[i]*135)/64 ); 
    x[i] += (12*K3[i])/25;
  }

  Atmosphere(x_new[2], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+((3*Ts)/4), Ts, x_new[1], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[2], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[2], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    
    K4[i] = Ts*dx_new[2][i];
    x_new[3][i] += ( (-17*K1[i])/12 + (K2[i]*(27))/4 + (K3[i]*-27)/5 + (K4[i]*16)/15 );
    x[i] += (K4[i]*32)/225;
  }
 

  Atmosphere(x_new[3], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+(Ts), Ts, x_new[1], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[3], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[3], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    
    K5[i] = Ts*dx_new[3][i];
    x_new[4][i] += ( (65*K1[i])/432 + (K2[i]*(-5))/16 + (K3[i]*13)/16 + (K4[i]*4)/27 + (K5[i]*4)/144 );
    x[i] += (K5[i])/30;
  }

  Atmosphere(x_new[4], &T_atm, &p_atm, &rho, &M, &g);
  //Engine(t+((5*Ts)/6), Ts, x_new[1], cntl, M, g, Thrust);
  Equations_of_Motion(x_new[4], g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom, F18_Aerodata, rho, cntl, dx_new[4], FORCES, MOMENTS, DCG);

  for (int i = 0; i <12; i++){
    
    K6 = Ts*dx_new[4][i];
    x[i] += (K6*6)/25;

    if (std::isnan(x[i])){
      std::cerr << "States out of bound after " << t << " timesteps (" << t*Ts << " seconds). Terminating." << "\n";
      exit(-1);
    }

  }
}