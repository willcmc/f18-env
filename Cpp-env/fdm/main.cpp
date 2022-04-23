// Include Files

#include "main.h"

const float RT_FACTOR = 1;

// Controls
  //0  Stabilator deflection Right
  //1  Stabilator deflection Left
  //2  Aileron deflection
  //3  Rudder deflection
  //4  Throttle Setting as % of Right Engine
  //5  Throttle Setting as % of Left Engine
  //6  Pitch Thrust Vectoring Nozzle deflection Right Engines
  //7  Pitch Thrust Vectoring Nozzle deflection Left Engines
  //8  Yaw Thrust Vectoring Nozzle deflection Right Engines
  //9  Yaw Thrust Vectoring Nozzle deflection Left Engines



// States
  //0  Velocity
  //1  Angle of Attack
  //2  Angle of Side Slip
  //3  Roll rate
  //4  Pitch rate
  //5  Yaw rate
  //6  Roll angle
  //7  Pitch angle
  //8  Yaw angle
  //9  X location from starting point
  //10 Y location from starting point
  //11 Altitude

void next_state(double* x, double* dx, float Ts, int t,double* cntl, double* F18_Aerodata,double* ALPHA_BREAK, double* Geom)
{
  // Print states
  double x_new[5][12];
  for (int i = 0; i <12; i++) {
      // std::cout << x[i] << "\n";
      x_new[0][i] = x[i];
      x_new[1][i] = x[i];
      x_new[2][i] = x[i];  
      x_new[3][i] = x[i];  
      x_new[4][i] = x[i];    
  }
    // std::cout << "\n";

  rk4_fehlberg(x,dx,Ts,t,x_new,cntl,F18_Aerodata,ALPHA_BREAK,Geom);
}

int main(int argc, char *argv[]){
  /*
  Run using -ci to test build.
  */

  bool isTest = false;

  // CMD LINE PARSER
  for(int i = 1; i < argc; i++){
    std::string arg (argv[i]);
    std::string check ("-ci");
    if (arg.compare(check) == 0){
      isTest = true;
    }
  }

  float Ts = 0.01;

  FILE* fp;
  fp = fopen("states.txt", "w");

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
  double x[12] = {100, 0.3, 0, 0, 0, 0, 0, 0.3, 0, 0, 0, 10000};

  // Initial control
  float delta_e = -0.1;
  double cntl[10] = {delta_e, delta_e, 0, 0, 7, 7, 0, 0, 0, 0};

  // Get aerodynamic data
  Aero.Aerodata(Geom, ALPHA_BREAK, F18_Aerodata);

  // EOM returns
  double dx[12];
  double DCG[3];
  double FORCES[3];
  double MOMENTS[3];

  // Construct Visualizer object
  Visualizer viz("127.0.0.1", 5000, "generic", isTest);
  xbox jst;

  for (int t = 0; t < 100000000; t++){
    if(isTest) break;
    
    std::cout << "t=" << t*Ts << "\r";
    Atmosphere(x, &T_atm, &p_atm, &rho, &M, &g);

    // Joystick
    jst.update(cntl);

    //Thrust is returned via pointers
    Engine(t, Ts, x, cntl, M, g, Thrust);  

    // std::cout << Thrust[0] << " " << Thrust[1] << "\n";

    //Forces, Moments and DCG is returned via pointers
    Equations_of_Motion(x, g, ALPHA_BREAK, F18_Aerodata, Thrust, Geom, Geom,F18_Aerodata, rho, cntl, dx, FORCES, MOMENTS, DCG); 

    next_state(x, dx, Ts, t,cntl,F18_Aerodata, ALPHA_BREAK, Geom);
    viz.send_fg(x, cntl);
    fprintf(fp, "%f ", Ts*t);
    
    for(int i=0; i<12; i++){
      fprintf(fp, "%f ", x[i]);
    }
    fprintf(fp, "\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(Ts*1000/RT_FACTOR)));
  }
  
  fclose(fp);
  return 0;
}