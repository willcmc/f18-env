#ifndef _SOLVER_H
#define _SOLVER_H
void rk4(double* x, double* dx, float Ts, int t, double x_new[3][12], double* cntl, double* F18_Aerodata, double* ALPHA_BREAK, double* Geom);
void rk4_fehlberg(double* x, double* dx, float Ts, int t, double x_new[3][12], double* cntl,double* F18_Aerodata,double* ALPHA_BREAK, double* Geom);
#endif