//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Equations_of_Motion.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 26-Feb-2022 09:55:52
//

// Include Files
#include "Equations_of_Motion.h"
#include "Equations_of_Motion_data.h"
#include "Equations_of_Motion_initialize.h"
#include "interp1.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double x[12]
//                double g
//                const double ALPHA_BREAK[27]
//                const double F18_Aerodata[1107]
//                const double Thrust[2]
//                const double Geom[17]
//                const double F18_Geom_damaged[17]
//                const double F18_Aerodata_damaged[1107]
//                double rho
//                const double Cntl[10]
//                double F[12]
//                double FORCES[3]
//                double MOMENTS[3]
//                double DCG[3]
// Return Type  : void
//
void Equations_of_Motion(const double x[12], double g,
                         const double ALPHA_BREAK[27],
                         const double F18_Aerodata[1107],
                         const double Thrust[2], const double Geom[17],
                         const double F18_Geom_damaged[17],
                         const double F18_Aerodata_damaged[1107], double rho,
                         const double Cntl[10], double F[12], double FORCES[3],
                         double MOMENTS[3], double DCG[3])
{
  double AFY;
  double AFY_tmp;
  double Alfad;
  double CD0;
  double CD_d;
  double CD_del;
  double CD_der;
  double CD_q;
  double CL0;
  double CL_del;
  double CL_der;
  double CL_q;
  double CY_b;
  double CY_da;
  double CY_del;
  double CY_der;
  double CY_dr;
  double CY_p;
  double CY_r;
  double Cl_b;
  double Cl_d;
  double Cl_da;
  double Cl_del;
  double Cl_der;
  double Cl_dr;
  double Cl_p;
  double Cl_r;
  double Cm0;
  double Cm_d;
  double Cm_del;
  double Cm_der;
  double Cm_q;
  double Cn_b;
  double Cn_da;
  double Cn_del;
  double Cn_der;
  double Cn_dr;
  double Cn_p;
  double Cn_r;
  double Ixx;
  double Ixy;
  double Ixz;
  double Iyy;
  double Iyz;
  double Izz;
  double MX;
  double MY;
  double TY;
  double d_CD;
  double d_CD_da;
  double d_CD_p;
  double d_CL;
  double d_CL_da;
  double d_CL_p;
  double d_CL_q;
  double d_CY;
  double d_Cl;
  double d_Cl_da;
  double d_Cl_p;
  double d_Cl_q;
  double d_Cm;
  double d_Cm_da;
  double d_Cm_p;
  double d_Cm_q;
  double d_Cn;
  double d_Cn_da;
  double dxcg;
  double dycg;
  double dzcg;
  double m;
  double qbar_tmp;
  double udot_tmp;
  double w;
  if (!isInitialized_Equations_of_Motion) {
    Equations_of_Motion_initialize();
  }
  // =====================%
  //  Equations of Motion %
  // =====================%
  // deg to rad conversion
  // rad to deg conversion
  // =========================================================================%
  //          Aerodynamic Coeffecient Assignment to local variables           %
  // =========================================================================%
  //  Coefficient of Lift due to Angle of Attack
  //  Coefficient of Lift due to Pitch rate
  //  Coefficient of Lift due to Both Stabilator deflection
  //  Coefficient of Lift due to Left Stabilator deflection
  //  Coefficient of Lift due to Right Stabilator deflection
  //  Coefficient of Drag at Zero Lift
  //  Coefficient of Drag due to Pitch rate
  //  Coefficient of Drag due to Both Stabilator deflection
  //  Coefficient of Drag due to Left Stabilator deflection
  //  Coefficient of Drag due to Right Stabilator deflection
  //  Coefficient of Pitching Moment due to Angle of Attack
  //  Coefficient of Pitching Moment due to Both Stabilator deflection
  //  Coefficient of Pitching Moment due to Left Stabilator deflection
  //  Coefficient of Pitching Moment due to Right Stabilator deflection
  //  Coefficient of Pitching Moment due to Pitch rate
  //  Coefficient of Side Force due to Angle of Side Slip
  //  Coefficient of Side Force due to Roll rate
  //  Coefficient of Side Force due to Yaw rate
  //  Coefficient of Side Force due to Both Stabilator deflection
  //  Coefficient of Side Force due to Left Stabilator deflection
  //  Coefficient of Side Force due to Right Stabilator deflection
  //  Coefficient of Side Force due to Aileron deflection
  //  Coefficient of Side Force due to Rudder deflection
  //  Coefficient of Rolling Moment due to Angle of Side Slip
  //  Coefficient of Rolling Moment due to Roll rate
  //  Coefficient of Rolling Moment due to Yaw rate
  //  Coefficient of Rolling Moment due to Both Stabilator deflection
  //  Coefficient of Rolling Moment due to Left Stabilator deflection
  //  Coefficient of Rolling Moment due to Right Stabilator deflection
  //  Coefficient of Rolling Moment due to Aileron deflection
  //  Coefficient of Rolling Moment due to Rudder deflection
  //  Coefficient of Yawing  Moment due to Angle of Side Slip
  //  Coefficient of Yawing  Moment due to Roll rate
  //  Coefficient of Yawing  Moment due to Yaw rate
  //  Coefficient of Yawing  Moment due to Both Stabilator deflection
  //  Coefficient of Yawing  Moment due to Left Stabilator deflection
  //  Coefficient of Yawing  Moment due to Right Stabilator deflection
  //  Coefficient of Yawing  Moment due to Aileron deflection
  //  Coefficient of Yawing  Moment due to Rudder deflection
  //  Coefficient of Lift due to Rate of change of Angle of Attack (Not from
  //  same database) Coefficient of Pitching Moment due to Rate of change of
  //  Angle of Attack (Not from same database)
  m = Geom[0];
  //  Mass of Aircraft
  //  Wing Reference area
  //  Wing Span
  //  Mean Aerodynamic Chord
  Ixx = Geom[4];
  //  Mass Moment of Inertia about X axis
  Iyy = Geom[5];
  //  Mass Moment of Inertia about Y axis
  Izz = Geom[6];
  //  Mass Moment of Inertia about Z axis
  Ixz = Geom[7];
  //  Product Mass Moment of Inertia about XZ axis
  Ixy = Geom[8];
  //  Product Mass Moment of Inertia about XY axis
  Iyz = Geom[9];
  //  Product Mass Moment of Inertia about YZ axis
  //  CG location referenced from the leading edge of Mean Aerodynamic Chord as
  //  % MAC CG to the Reference point(Aerodynamic database) distance along X
  //  axis CG to the Reference point(Aerodynamic database) distance along Y axis
  //  CG to the Reference point(Aerodynamic database) distance along Z axis
  //  CG to the Engine distance along X axis
  //  CG to the Engine distance along Z axis
  //  CG to the Engine distance along Z axis
  // =========================================================================%
  //     Damaged Aerodynamic Coeffecient Assignment to local variables        %
  // =========================================================================%
  dxcg = F18_Geom_damaged[1];
  dycg = F18_Geom_damaged[2];
  dzcg = F18_Geom_damaged[3];
  // =========================================================================%
  //          State and Control Vectors Assignment to local variables         %
  // =========================================================================%
  //  Stabilator deflection Right
  //  Stabilator deflection Left
  //  Aileron deflection
  //  Rudder deflection
  //  Throttle Setting as % of Right Engine
  //  Throttle Setting as % of Left Engine
  //  Pitch Thrust Vectoring Nozzle deflection Right Engines
  //  Pitch Thrust Vectoring Nozzle deflection Left Engines
  //  Yaw Thrust Vectoring Nozzle deflection Right Engines
  //  Yaw Thrust Vectoring Nozzle deflection Left Engines
  //  Velocity
  //  Angle of Attack
  //  Angle of Side Slip
  //  Roll rate
  //  Pitch rate
  //  Yaw rate
  //  Roll angle
  //  Pitch angle
  //  Yaw angle
  //  X location from starting point
  //  Y location from starting point
  //  Altitude
  //  Right Engine Thrust
  //  Left Engine Thrust
  qbar_tmp = x[0] * x[0];
  //  Dynamic pressure
  // =========================================================================%
  //                Aerodynamic Coeffecient Interpolation                     %
  // =========================================================================%
  Alfad = x[1] * 57.295779513082323;
  //  The Aerodata is in Degrees
  CD0 =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[135], Alfad);
  CD_q =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[162], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[189], Alfad);
  CD_der =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[243], Alfad) *
      57.295779513082323;
  CD_del =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[216], Alfad) *
      57.295779513082323;
  CL0 = coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[0], Alfad);
  CL_q =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[27], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[54], Alfad);
  CL_der =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[108], Alfad) *
      57.295779513082323;
  CL_del =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[81], Alfad) *
      57.295779513082323;
  CY_b =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[405], Alfad) *
      57.295779513082323;
  CY_p =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[432], Alfad) *
      57.295779513082323;
  CY_r =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[459], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[486], Alfad);
  CY_der =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[540], Alfad) *
      57.295779513082323;
  CY_del =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[513], Alfad) *
      57.295779513082323;
  CY_da =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[567], Alfad) *
      57.295779513082323;
  CY_dr =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[594], Alfad) *
      57.295779513082323;
  Cl_b =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[621], Alfad) *
      57.295779513082323;
  Cl_p =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[648], Alfad) *
      57.295779513082323;
  Cl_r =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[675], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[702], Alfad);
  Cl_der =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[756], Alfad) *
      57.295779513082323;
  Cl_del =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[729], Alfad) *
      57.295779513082323;
  Cl_da =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[783], Alfad) *
      57.295779513082323;
  Cl_dr =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[810], Alfad) *
      57.295779513082323;
  Cn_b =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[837], Alfad) *
      57.295779513082323;
  Cn_p =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[864], Alfad) *
      57.295779513082323;
  Cn_r =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[891], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[918], Alfad);
  Cn_der =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[972], Alfad) *
      57.295779513082323;
  Cn_del =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[945], Alfad) *
      57.295779513082323;
  Cn_da =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[999], Alfad) *
      57.295779513082323;
  Cn_dr = coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[1026],
                         Alfad) *
          57.295779513082323;
  Cm0 =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[270], Alfad);
  Cm_q =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[378], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[297], Alfad);
  Cm_der =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[351], Alfad) *
      57.295779513082323;
  Cm_del =
      coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[324], Alfad) *
      57.295779513082323;
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[1053], Alfad);
  coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata[1080], Alfad);
  d_CL = coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[0],
                        Alfad);
  d_CD = coder::interp1(ALPHA_BREAK,
                        *(double(*)[27]) & F18_Aerodata_damaged[27], Alfad);
  d_Cm = coder::interp1(ALPHA_BREAK,
                        *(double(*)[27]) & F18_Aerodata_damaged[54], Alfad);
  d_CY = -coder::interp1(ALPHA_BREAK,
                         *(double(*)[27]) & F18_Aerodata_damaged[81], Alfad);
  d_Cl = -coder::interp1(ALPHA_BREAK,
                         *(double(*)[27]) & F18_Aerodata_damaged[108], Alfad);
  d_Cn = coder::interp1(ALPHA_BREAK,
                        *(double(*)[27]) & F18_Aerodata_damaged[135], Alfad);
  d_Cl_da =
      -coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[162],
                      Alfad) *
      57.295779513082323;
  d_Cn_da =
      -coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[189],
                      Alfad) *
      57.295779513082323;
  d_CL_da =
      -coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[216],
                      Alfad) *
      57.295779513082323;
  d_CD_da =
      -coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[243],
                      Alfad) *
      57.295779513082323;
  d_Cm_da =
      -coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[270],
                      Alfad) *
      57.295779513082323;
  d_Cl_q =
      -coder::interp1(ALPHA_BREAK, *(double(*)[27]) & F18_Aerodata_damaged[297],
                      Alfad) *
      57.295779513082323;
  d_Cm_q = coder::interp1(ALPHA_BREAK,
                          *(double(*)[27]) & F18_Aerodata_damaged[324], Alfad) *
           57.295779513082323;
  d_CL_q = coder::interp1(ALPHA_BREAK,
                          *(double(*)[27]) & F18_Aerodata_damaged[351], Alfad) *
           57.295779513082323;
  d_CL_p = coder::interp1(ALPHA_BREAK,
                          *(double(*)[27]) & F18_Aerodata_damaged[378], Alfad) *
           57.295779513082323;
  d_CD_p = coder::interp1(ALPHA_BREAK,
                          *(double(*)[27]) & F18_Aerodata_damaged[405], Alfad) *
           57.295779513082323;
  d_Cm_p = coder::interp1(ALPHA_BREAK,
                          *(double(*)[27]) & F18_Aerodata_damaged[432], Alfad) *
           57.295779513082323;
  d_Cl_p = coder::interp1(ALPHA_BREAK,
                          *(double(*)[27]) & F18_Aerodata_damaged[459], Alfad) *
           57.295779513082323;
  Alfad = coder::interp1(ALPHA_BREAK,
                         *(double(*)[27]) & F18_Aerodata_damaged[486], Alfad) *
          57.295779513082323;
  //  CD0    = interp1(ALPHA_BREAK,cd0,Alfad,'interp1');
  //  CD_q   = interp1(ALPHA_BREAK,cd_q,Alfad,'interp1')*r2d;
  //  CD_de  = interp1(ALPHA_BREAK,cd_de,Alfad,'interp1')*r2d;
  //  CD_der = interp1(ALPHA_BREAK,cd_der,Alfad,'interp1')*r2d;
  //  CD_del = interp1(ALPHA_BREAK,cd_del,Alfad,'interp1')*r2d;
  //
  //  CL0    = interp1(ALPHA_BREAK,clift,Alfad,'interp1');
  //  CL_q   = interp1(ALPHA_BREAK,clift_q,Alfad,'interp1')*r2d;
  //  CL_de  = interp1(ALPHA_BREAK,clift_de,Alfad,'interp1')*r2d;
  //  CL_der = interp1(ALPHA_BREAK,clift_der,Alfad,'interp1')*r2d;
  //  CL_del = interp1(ALPHA_BREAK,clift_del,Alfad,'interp1')*r2d;
  //
  //  CY_b   = interp1(ALPHA_BREAK,cy_b,Alfad,'interp1')*r2d;
  //  CY_p   = interp1(ALPHA_BREAK,cy_p,Alfad,'interp1')*r2d;
  //  CY_r   = interp1(ALPHA_BREAK,cy_r,Alfad,'interp1')*r2d;
  //  CY_de  = interp1(ALPHA_BREAK,cy_de,Alfad,'interp1')*r2d;
  //  CY_der = interp1(ALPHA_BREAK,cy_der,Alfad,'interp1')*r2d;
  //  CY_del = interp1(ALPHA_BREAK,cy_del,Alfad,'interp1')*r2d;
  //  CY_da  = interp1(ALPHA_BREAK,cy_da,Alfad,'interp1')*r2d;
  //  CY_dr  = interp1(ALPHA_BREAK,cy_dr,Alfad,'interp1')*r2d;
  //
  //  Cl_b   = interp1(ALPHA_BREAK,croll_b,Alfad,'interp1')*r2d;
  //  Cl_p   = interp1(ALPHA_BREAK,croll_p,Alfad,'interp1')*r2d;
  //  Cl_r   = interp1(ALPHA_BREAK,croll_r,Alfad,'interp1')*r2d;
  //  Cl_de  = interp1(ALPHA_BREAK,croll_de,Alfad,'interp1')*r2d;
  //  Cl_der = interp1(ALPHA_BREAK,croll_der,Alfad,'interp1')*r2d;
  //  Cl_del = interp1(ALPHA_BREAK,croll_del,Alfad,'interp1')*r2d;
  //  Cl_da  = interp1(ALPHA_BREAK,croll_da,Alfad,'interp1')*r2d;
  //  Cl_dr  = interp1(ALPHA_BREAK,croll_dr,Alfad,'interp1')*r2d;
  //
  //  Cn_b   = interp1(ALPHA_BREAK,cn_b,Alfad,'interp1')*r2d;
  //  Cn_p   = interp1(ALPHA_BREAK,cn_p,Alfad,'interp1')*r2d;
  //  Cn_r   = interp1(ALPHA_BREAK,cn_r,Alfad,'interp1')*r2d;
  //  Cn_de  = interp1(ALPHA_BREAK,cn_de,Alfad,'interp1')*r2d;
  //  Cn_der = interp1(ALPHA_BREAK,cn_der,Alfad,'interp1')*r2d;
  //  Cn_del = interp1(ALPHA_BREAK,cn_del,Alfad,'interp1')*r2d;
  //  Cn_da  = interp1(ALPHA_BREAK,cn_da,Alfad,'interp1')*r2d;
  //  Cn_dr  = interp1(ALPHA_BREAK,cn_dr,Alfad,'interp1')*r2d;
  //
  //  Cm0    = interp1(ALPHA_BREAK,cm,Alfad,'interp1');
  //  Cm_q   = interp1(ALPHA_BREAK,cm_q,Alfad,'interp1')*r2d;
  //  Cm_de  = interp1(ALPHA_BREAK,cm_de,Alfad,'interp1')*r2d;
  //  Cm_der = interp1(ALPHA_BREAK,cm_der,Alfad,'interp1')*r2d;
  //  Cm_del = interp1(ALPHA_BREAK,cm_del,Alfad,'interp1')*r2d;
  //
  //  CL_Ad = interp1(ALPHA_BREAK,CLAD,Alfad,'interp1')*r2d;
  //  Cm_Ad = interp1(ALPHA_BREAK,CMAD,Alfad,'interp1')*r2d;
  //
  //
  //  d_CL    =  interp1(ALPHA_BREAK,d_CLv,Alfad,'interp1');
  //  d_CD    =  interp1(ALPHA_BREAK,d_CDv,Alfad,'interp1');
  //  d_Cm    =  interp1(ALPHA_BREAK,d_Cmv,Alfad,'interp1');
  //  d_CY    = -interp1(ALPHA_BREAK,d_CYv,Alfad,'interp1');
  //  d_Cl    = -interp1(ALPHA_BREAK,d_Clv,Alfad,'interp1');
  //  d_Cn    =  interp1(ALPHA_BREAK,d_Cnv,Alfad,'interp1');
  //  d_Cl_da = -interp1(ALPHA_BREAK,d_Cl_dav,Alfad,'interp1')*r2d;
  //  d_Cn_da = -interp1(ALPHA_BREAK,d_Cn_dav,Alfad,'interp1')*r2d;
  //  d_CL_da = -interp1(ALPHA_BREAK,d_CL_dav,Alfad,'interp1')*r2d;
  //  d_CD_da = -interp1(ALPHA_BREAK,d_CD_dav,Alfad,'interp1')*r2d;
  //  d_Cm_da = -interp1(ALPHA_BREAK,d_Cm_dav,Alfad,'interp1')*r2d;
  //  d_Cl_q  = -interp1(ALPHA_BREAK,d_Cl_qv,Alfad,'interp1')*r2d;
  //  d_Cm_q  =  interp1(ALPHA_BREAK,d_Cm_qv,Alfad,'interp1')*r2d;
  //  d_CL_q  =  interp1(ALPHA_BREAK,d_CL_qv,Alfad,'interp1')*r2d;
  //  d_CL_p  =  interp1(ALPHA_BREAK,d_CL_pv,Alfad,'interp1')*r2d;
  //  d_CD_p  =  interp1(ALPHA_BREAK,d_CD_pv,Alfad,'interp1')*r2d;
  //  d_Cm_p  =  interp1(ALPHA_BREAK,d_Cm_pv,Alfad,'interp1')*r2d;
  //  d_Cl_p  =  interp1(ALPHA_BREAK,d_Cl_pv,Alfad,'interp1')*r2d;
  //  d_Cl_r  =  interp1(ALPHA_BREAK,d_Cl_rv,Alfad,'interp1')*r2d;
  // ================================================================================================================%
  //  Coeffecients
  // ================================================================================================================%
  //  + Adot*(CL_Ad*(cbar/(2*Vel)));
  //  + Adot*(Cm_Ad*(cbar/(2*Vel)));
  // ================================================================================================================%
  //  Unsteady monitering
  // ================================================================================================================%
  //  CLU = (CL0 + (CL_q*(cbar/(2*Vel))*q));% + Adot*(CL_Ad*(cbar/(2*Vel)));
  //  CDU = (CD0 + (CD_q*(cbar/(2*Vel))*q));
  //  CmU = (Cm0 + (Cm_q*(cbar/(2*Vel))*q));% + Adot*(Cm_Ad*(cbar/(2*Vel)));
  //  CYU = ((CY_b*Beta) + (CY_p*(b/(2*Vel))*p) + (CY_r*(b/(2*Vel))*r));
  //  ClU = ((Cl_b*Beta) + (Cl_p*(b/(2*Vel))*p) + (Cl_r*(b/(2*Vel))*r));
  //  CnU = ((Cn_b*Beta) + (Cn_p*(b/(2*Vel))*p) + (Cn_r*(b/(2*Vel))*r));
  //  MONITER = [CLU CDU CmU CYU ClU CnU Alfad];
  // ================================================================================================================%
  //  Damaged Aircraft Coeffecients and Inertias Variation
  // ================================================================================================================%
  if (damage == 0.0) {
    dxcg = 0.0;
    dycg = 0.0;
    dzcg = 0.0;
    CD_d = 0.0;
    d_CL_p = 0.0;
    Cm_d = 0.0;
    d_CY = 0.0;
    Cl_d = 0.0;
    d_Cn = 0.0;
  } else {
    m = Geom[0] - F18_Geom_damaged[0];
    Ixx = Geom[4] - F18_Geom_damaged[4];
    Iyy = Geom[5] - F18_Geom_damaged[5];
    Izz = Geom[6] - F18_Geom_damaged[6];
    Ixz = Geom[7] - F18_Geom_damaged[7];
    Ixy = Geom[8] - F18_Geom_damaged[8];
    Iyz = Geom[9] - F18_Geom_damaged[9];
    TY = Geom[2] / (2.0 * x[0]);
    CD_d = (d_CD + d_CD_da * Cntl[2]) + d_CD_p * TY * x[3];
    AFY = Geom[3] / (2.0 * x[0]);
    d_CL_p =
        ((d_CL + d_CL_da * Cntl[2]) + d_CL_q * AFY * x[4]) + d_CL_p * TY * x[3];
    Cm_d =
        ((d_Cm + d_Cm_da * Cntl[2]) + d_Cm_q * AFY * x[4]) + d_Cm_p * TY * x[3];
    Cl_d = (((d_Cl + d_Cl_da * Cntl[2]) + d_Cl_q * AFY * x[4]) +
            Alfad * TY * x[5]) +
           d_Cl_p * TY * x[3];
    d_Cn += d_Cn_da * Cntl[2];
  }
  //  for C.G at nwe location
  //  xref = xref + dxcg;
  //  yref = dycg;
  //  zref = zref + dzcg;
  //
  //  Xeng = Xeng + dxcg;
  //  Yeng = dycg;
  //  Zeng = Zeng + dzcg;
  // ================================================================================================================%
  //  Forces and Moments
  // ================================================================================================================%
  // =========================================================================%
  //            Engine Forces and Moments about Body axes                     %
  // =========================================================================%
  AFY = std::cos(Cntl[7]);
  d_CD_da = std::sin(Cntl[7]);
  d_CD_p = std::cos(Cntl[9]);
  d_CL_da = 1.0 / std::sqrt(AFY * AFY + d_CD_da * d_CD_da * (d_CD_p * d_CD_p));
  d_CL = std::cos(Cntl[6]);
  Alfad = std::sin(Cntl[6]);
  d_CD = std::cos(Cntl[8]);
  d_CL_q = 1.0 / std::sqrt(d_CL * d_CL + Alfad * Alfad * (d_CD * d_CD));
  d_Cn_da = Thrust[0] * (d_CL * d_CD) * d_CL_q;
  d_Cl_da = -Thrust[0] * (Alfad * d_CD) * d_CL_q;
  d_Cl_p = Thrust[1] * (AFY * d_CD_p) * d_CL_da;
  d_Cl = -Thrust[1] * (d_CD_da * d_CD_p) * d_CL_da;
  d_Cl_q = d_Cn_da + d_Cl_p;
  TY = Thrust[0] * (d_CL * std::sin(Cntl[8])) * d_CL_q +
       Thrust[1] * (AFY * std::sin(Cntl[9])) * d_CL_da;
  d_Cm_q = d_Cl_da + d_Cl;
  //  TRM = -TY*(Zeng + dzcg) + TZ_RE*(Yeng - dycg) - TZ_LE*(Yeng + dycg);
  //  TPM =  TX*(Zeng + dzcg) - TZ*(Xeng + dxcg);
  //  TYM =  TY*(Xeng + dxcg) - TX_RE*(Yeng - dycg) + TX_LE*(Yeng + dycg);
  // =========================================================================%
  //       Aerodynamic FORCES and MOMENTS About Stability Axes at C.G         %
  // =========================================================================%
  d_Cm_p = Geom[3] / (2.0 * x[0]);
  d_Cm_da = 0.5 * rho * qbar_tmp * Geom[1];
  // =========================================================================%
  //            Damaged Aircraft Forces and Moments Variation                 %
  // =========================================================================%
  // =========================================================================%
  //              AIRCRAFT and Engine Forces about Wind axes                  %
  // =========================================================================%
  //  AFLw = L - DL;
  //  AFYw = Y*cos(Beta) - D*sin(Beta) - DY;
  //  AFDw = D*cos(Beta) + Y*sin(Beta) - DD;
  //
  //  TXw = TX*(cos(Alpha)*cos(Beta)) + TY*(sin(Beta)) +
  //  TZ*(sin(Alpha)*cos(Beta)); TYw = TX*(cos(Alpha)*sin(Beta)) -
  //  TY*(cos(Beta)) + TZ*(sin(Alpha)*sin(Beta)); TZw = TX*(sin(Alpha)) -
  //  TZ*(cos(Alpha));
  // =========================================================================%
  //                AIRCRAFT Forces about Body axes                           %
  // =========================================================================%
  d_CD_da = std::cos(x[1]);
  d_CD_p = std::sin(x[1]);
  d_CL = std::cos(x[2]);
  d_CD = d_Cm_da * (((CD0 + CD_q * d_Cm_p * x[4]) + CD_der * Cntl[0]) +
                    CD_del * Cntl[1]) -
         d_Cm_da * CD_d;
  Alfad = d_Cm_da * (((CL0 + CL_q * d_Cm_p * x[4]) + CL_der * Cntl[0]) +
                     CL_del * Cntl[1]) -
          d_Cm_da * d_CL_p;
  d_CL_da = Alfad * d_CD_p - d_CD * (d_CD_da * d_CL);
  AFY_tmp = std::sin(x[2]);
  d_CL_q = Geom[2] / (2.0 * x[0]);
  AFY = (d_Cm_da *
             ((((((CY_b * x[2] + CY_p * d_CL_q * x[3]) + CY_r * d_CL_q * x[5]) +
                 CY_der * Cntl[0]) +
                CY_del * Cntl[1]) +
               CY_da * Cntl[2]) +
              CY_dr * Cntl[3]) -
         d_Cm_da * d_CY) -
        d_CD * AFY_tmp;
  d_CD_p = -Alfad * d_CD_da - d_CD * (d_CD_p * d_CL);
  // =========================================================================%
  //            AIRCRAFT Forces and Moments about Body axes                   %
  // =========================================================================%
  d_CL = d_CL_da + d_Cl_q;
  d_CL_p = AFY + TY;
  d_Cm = d_CD_p + d_Cm_q;
  d_CD = d_Cm_da * Geom[2];
  MX =
      (((d_CD *
             ((((((Cl_b * x[2] + Cl_p * d_CL_q * x[3]) + Cl_r * d_CL_q * x[5]) +
                 Cl_der * Cntl[0]) +
                Cl_del * Cntl[1]) +
               Cl_da * Cntl[2]) +
              Cl_dr * Cntl[3]) -
         d_CD * Cl_d) -
        Geom[13] * AFY) +
       Geom[12] * d_CD_p) +
      ((-TY * Geom[16] + d_Cl_da * Geom[15]) - d_Cl * Geom[15]);
  Alfad = d_Cm_da * Geom[3];
  MY = (((Alfad * (((Cm0 + Cm_q * d_Cm_p * x[4]) + Cm_der * Cntl[0]) +
                   Cm_del * Cntl[1]) -
          Alfad * Cm_d) -
         Geom[11] * d_CD_p) +
        Geom[13] * d_CL_da) +
       (d_Cl_q * Geom[16] - d_Cm_q * Geom[14]);
  Cl_da =
      (((d_CD *
             ((((((Cn_b * x[2] + Cn_p * d_CL_q * x[3]) + Cn_r * d_CL_q * x[5]) +
                 Cn_der * Cntl[0]) +
                Cn_del * Cntl[1]) +
               Cn_da * Cntl[2]) +
              Cn_dr * Cntl[3]) -
         d_CD * d_Cn) +
        Geom[11] * AFY) -
       Geom[12] * d_CL_da) +
      ((TY * Geom[14] - d_Cn_da * Geom[15]) + d_Cl_p * Geom[15]);
  FORCES[0] = d_CL;
  FORCES[1] = d_CL_p;
  FORCES[2] = d_Cm;
  MOMENTS[0] = MX;
  MOMENTS[1] = MY;
  MOMENTS[2] = Cl_da;
  DCG[0] = dxcg;
  DCG[1] = dycg;
  DCG[2] = dzcg;
  //      PMf = - xref*AFZ + zref*AFX
  //      PMa = qbar*S*cbar*(Cm0 + (Cm_q*(cbar/(2*Vel))*q))
  //      PMs = qbar*S*cbar*(Cm0 + (Cm_q*(cbar/(2*Vel))*q)) - xref*AFZ +
  //      zref*AFX PMc = qbar*S*cbar*((Cm_der*Del_er) + (Cm_del*Del_el))
  //
  //      Cl = ((Cl_b*Beta) + (Cl_p*(b/(2*Vel))*p) + (Cl_r*(b/(2*Vel))*r));
  //      Cm = (Cm0 + (Cm_q*(cbar/(2*Vel))*q));
  //      Cn = ((Cn_b*Beta) + (Cn_p*(b/(2*Vel))*p) + (Cn_r*(b/(2*Vel))*r));
  //
  //      ARMc = qbar*S*b*Cl    + zref*Y + yref*( L*cos(Alpha) + D*sin(Alpha))
  //      APMc = qbar*S*cbar*Cm - xref*(L*cos(Alpha) + D*sin(Alpha)) +
  //      zref*(D*cos(Alpha) - L*sin(Alpha)) AYMc = qbar*S*b*Cn    - xref*Y +
  //      yref*(D*cos(Alpha) - L*sin(Alpha))
  //
  //      ARMs = qbar*S*b*Cl    - zref*(FY - TY) + yref*(FZ - TZ);
  //      APMs = qbar*S*cbar*Cm - xref*(FZ - TZ) + zref*(FX - TX);
  //      AYMs = qbar*S*b*Cn    + xref*(FY - TY) - yref*(FX - TX);
  // ================================================================================================================%
  //  Equations of Motion
  // ================================================================================================================%
  // =========================================================================%
  //     Force Equations in Wind/Body Frame in Terms of Wind/Body Variables   %
  // =========================================================================%
  //  Wind frame Gravity components
  //  gXw = (sin(Theta)*cos(Alpha)*cos(Beta)) - (cos(Theta)*sin(Phi)*sin(Beta))
  //  - (sin(Alpha)*cos(Beta)*cos(Phi)*cos(Theta)); gYw =
  //  (1/Vel)*((cos(Alpha)*sin(Beta)*sin(Theta)) +
  //  (cos(Beta)*sin(Phi)*cos(Theta)) -
  //  (sin(Alpha)*sin(Beta)*cos(Phi)*cos(Theta))); gZw =
  //  (1/Vel)*(1/cos(Beta))*(sin(Alpha)*sin(Theta) +
  //  cos(Alpha)*cos(Phi)*cos(Theta));
  //
  //  Vdot = (1/m)*(TXw - AFDw) - g*gXw;
  //  Adot = q - ((p*cos(Alpha) + r*sin(Alpha))*tan(Beta)) -
  //  (1/m)*(1/Vel)*(1/cos(Beta))*(TZw + AFLw) + g*gZw; Bdot =  (p*sin(Alpha) -
  //  r*cos(Alpha)) - (1/m)*(1/Vel)*(TYw + AFYw) + g*gYw; Body axix Velocities
  Cn_der = std::cos(x[1]) * std::cos(x[2]);
  Cn_del = x[0] * Cn_der;
  Cn_da = x[0] * AFY_tmp;
  Cn_dr = std::sin(x[1]) * std::cos(x[2]);
  w = x[0] * Cn_dr;
  udot_tmp = std::sin(x[7]);
  d_CD = x[5] * Cn_da;
  d_CD_da = x[4] * w;
  Cl_dr = ((d_CD - d_CD_da) + d_CL / m) - g * udot_tmp;
  //  extra large
  Cn_p = std::cos(x[7]);
  Cn_r = std::sin(x[6]);
  d_CD_p = x[5] * Cn_del;
  AFY = x[3] * w;
  Cm0 = ((AFY - d_CD_p) + d_CL_p / m) + g * Cn_r * Cn_p;
  Cn_b = std::cos(x[6]);
  d_CL = x[4] * Cn_del;
  d_CL_da = x[3] * Cn_da;
  Cm_q = ((d_CL - d_CL_da) + d_Cm / m) + g * Cn_b * Cn_p;
  //  Vdot = ((u*udot) + (v*vdot) + (w*wdot))/Vel;
  //  Adot = ((u*wdot) - (w*udot))/(u^2 + w^2);
  //  Bdot = ((Vel*vdot) - (v*Vdot))/((Vel^2)*sqrt((1-v^2)/(Vel^2)));
  // =========================================================================%
  //               Moment Equations in Body Frame (Symmetric)                 %
  // =========================================================================%
  //  pdot_rate = ((Iyy-Ixx-Izz)*Ixz/(Ixz^2-Ixx*Izz))*p*q +
  //  ((Ixz^2+Izz^2-Izz*Iyy)/(Ixz^2-Ixx*Izz))*q*r; qdot_rate =
  //  ((Izz-Ixx)/Iyy)*r*p - (Ixz/Iyy)*((p^2) - (r^2)); rdot_rate =
  //  ((Ixx*Iyy-Ixx^2-Ixz^2)/(Ixz^2-Ixx*Izz))*p*q +
  //  (((Ixx-Iyy+Izz)*Ixz)/(Ixz^2-Ixx*Izz))*q*r;
  //
  //  pdot = pdot_rate + (Izz/(Ixx*Izz-Ixz^2))* RM + (Ixz/(Ixx*Izz-Ixz^2))* YM;
  //  qdot = qdot_rate + (1/Iyy)* PM;
  //  rdot = rdot_rate + (Ixz/(Ixx*Izz-Ixz^2))* RM + (Ixx/(Ixx*Izz-Ixz^2))* YM;
  // =========================================================================%
  //                Moment Equations in Body Frame (Asymmetric)               %
  // =========================================================================%
  d_Cl_q = Iyz * Iyz;
  Cm_d = Ixz * Ixz;
  Cl_p = Ixy * Ixy;
  Alfad = Ixx * Iyy;
  CY_b = Izz * Cl_p;
  Cl_r = Iyy * Cm_d;
  Cl_der = Ixx * d_Cl_q;
  Cl_del =
      1.0 / ((((Alfad * Izz - Cl_der) - CY_b) - Cl_r) - 2.0 * Ixz * Iyz * Ixy);
  d_Cl_p = Iyy * Izz - d_Cl_q;
  d_Cn = d_Cl_p * Cl_del;
  CY_p = Alfad - Cl_p;
  CY_r = CY_p * Cl_del;
  CD_del = Ixx * Izz - Cm_d;
  CL0 = CD_del * Cl_del;
  CL_q = Izz * Ixy;
  CL_der = Ixz * Iyz;
  CL_del = (CL_q + CL_der) * Cl_del;
  CY_der = Iyz * Ixy;
  CY_del = Iyy * Ixz;
  CY_da = (CY_del + CY_der) * Cl_del;
  CY_dr = Ixz * Ixy;
  d_CY = Ixx * Iyz;
  Cl_b = (d_CY + CY_dr) * Cl_del;
  // =========================================================================%
  //                            Kinematic Equations                           %
  // =========================================================================%
  // =========================================================================%
  //                            Position Equations                            %
  // =========================================================================%
  Cm_der = std::cos(x[8]);
  Cm_del = std::sin(x[8]);
  // ================================================================================================================%
  //  Equations of Motion - adding effect of damage
  // ================================================================================================================%
  CD_der = m * (((Cl_dr - d_CD) + d_CD_da) + g * std::sin(x[7]));
  d_Cn_da = m * (((Cm0 + d_CD_p) - AFY) - g * Cn_p * Cn_r);
  d_CL_q = m * (((Cm_q - d_CL) + d_CL_da) - g * std::cos(x[7]) * Cn_b);
  d_CL_p = Ixx - Iyy;
  d_Cl = x[5] * x[5];
  Cl_d = x[3] * x[3];
  CD_d = x[4] * x[4];
  AFY = Iyy - Izz;
  CD0 = x[4] * x[5];
  d_CD_da = d_CL_p + Izz;
  d_CD_p = d_CL_p - Izz;
  d_Cl_da = x[3] * x[4];
  d_CL = Izz - Ixx;
  CD_q = x[3] * x[5];
  d_Cm = (CD_d - d_Cl) * Iyz;
  d_Cm_da = (d_Cl - Cl_d) * Ixz;
  d_Cm_q = (Cl_d - CD_d) * Ixy;
  d_CL_da = CL_del * d_CL_q;
  d_Cm_p = d_CL - Iyy;
  TY = CY_da * d_Cn_da;
  d_Cl_q =
      ((((((((((MX * d_Cn + MY * CL_del) + Cl_da * CY_da) +
              CD0 * (((d_Cl_p * AFY + CY_b) - Cl_r) * Cl_del)) +
             CD_q * (((CL_q * d_Cm_p + CL_der * ((Iyy + Izz) - Ixx)) +
                      2.0 * d_Cl_q * Ixy) *
                     Cl_del)) +
            d_Cl_da *
                (((CY_der * d_CD_p + CY_del * d_CD_da) - 2.0 * d_Cl_q * Ixz) *
                 Cl_del)) +
           d_Cm * d_Cn) +
          d_Cm_da * CL_del) +
         d_Cm_q * CY_da) +
        (TY - d_CL_da) * dxcg) +
       (d_Cn * d_CL_q - CY_da * CD_der) * dycg) +
      (CL_del * CD_der - d_Cn * d_Cn_da) * dzcg;
  d_CD = (Ixx + Iyy) - Izz;
  AFY -= Ixx;
  Alfad = Cl_b * CD_der;
  d_CL =
      ((((((((((MX * CL_del + MY * CL0) + Cl_da * Cl_b) +
              CD0 * (((CL_der * AFY + CL_q * d_CD) - 2.0 * Ixy * Cm_d) *
                     Cl_del)) +
             d_Cl_da * (((CY_dr * d_CD_da + d_CY * d_CD_p) - 2.0 * Iyz * Cm_d) *
                        Cl_del)) +
            CD_q * (((CD_del * d_CL + Cl_der) - CY_b) * Cl_del)) +
           d_Cm * CL_del) +
          d_Cm_da * CL0) +
         d_Cm_q * Cl_b) +
        (Cl_b * d_Cn_da - CL0 * d_CL_q) * dxcg) +
       (d_CL_da - Alfad) * dycg) +
      (CL0 * CD_der - CL_del * d_Cn_da) * dzcg;
  //  In6 --> In3 in dzcg - modified
  d_CD_da = ((((((((((MX * CY_da + MY * Cl_b) + Cl_da * CY_r) +
                    CD0 * (((CY_der * d_CD + CY_del * AFY) + 2.0 * Cl_p * Ixz) *
                           Cl_del)) +
                   d_Cl_da * (((CY_p * d_CL_p + Cl_r) - Cl_der) * Cl_del)) +
                  CD_q * (((d_CY * ((Iyy - Ixx) + Izz) + CY_dr * d_Cm_p) -
                           2.0 * Iyz * Cl_p) *
                          Cl_del)) +
                 d_Cm * CY_da) +
                d_Cm_da * Cl_b) +
               d_Cm_q * CY_r) +
              (CY_r * d_Cn_da - Cl_b * d_CL_q) * dxcg) +
             (CY_da * d_CL_q - CY_r * CD_der) * dycg) +
            (Alfad - TY) * dzcg;
  //  In2 --> In6 in dzcg - modified
  AFY = ((Cl_dr + (CD_d + d_Cl) * dxcg) - (d_Cl_da - d_CD_da) * dycg) -
        (CD_q + d_CL) * dzcg;
  d_CD = ((Cm0 + (Cl_d + d_Cl) * dycg) - (d_Cl_da + d_CD_da) * dxcg) -
         (CD0 - d_Cl_q) * dzcg;
  Alfad = ((Cm_q + (Cl_d + CD_d) * dzcg) - (CD_q - d_CL) * dxcg) -
          (CD0 + d_Cl_q) * dycg;
  //  display(udot)
  //  display(vdot)
  //  display(wdot)
  d_CD_p = ((Cn_del * AFY + Cn_da * d_CD) + w * Alfad) / x[0];
  // ================================================================================================================%
  //  Function decleration
  // ================================================================================================================%
  F[0] = d_CD_p;
  F[1] = (Cn_del * Alfad - w * AFY) / (Cn_del * Cn_del + w * w);
  F[2] = (x[0] * d_CD - Cn_da * d_CD_p) /
         (qbar_tmp * std::sqrt(1.0 - Cn_da * Cn_da / qbar_tmp));
  F[3] = d_Cl_q;
  F[4] = d_CL;
  F[5] = d_CD_da;
  F[6] = x[3] + (x[4] * Cn_r + x[5] * Cn_b) * std::tan(x[7]);
  F[7] = x[4] * Cn_b - x[5] * Cn_r;
  F[8] = (x[4] * std::sin(x[6]) + x[5] * std::cos(x[6])) * (1.0 / Cn_p);
  F[9] = x[0] * ((Cn_der * Cm_der * Cn_p +
                  AFY_tmp * (-Cm_del * Cn_b + Cn_r * udot_tmp * Cm_der)) +
                 Cn_dr * (Cn_r * Cm_del + Cn_b * udot_tmp * Cm_der));
  F[10] =
      x[0] *
      ((Cn_der * Cm_del * Cn_p +
        AFY_tmp * (Cm_der * Cn_b + std::sin(x[6]) * std::sin(x[7]) * Cm_del)) +
       Cn_dr * (-Cn_r * Cm_der + std::cos(x[6]) * std::sin(x[7]) * Cm_del));
  F[11] = x[0] *
          ((Cn_der * udot_tmp - AFY_tmp * Cn_p * Cn_r) - Cn_dr * Cn_p * Cn_b);
}

//
// File trailer for Equations_of_Motion.cpp
//
// [EOF]
//
