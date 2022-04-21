#ifndef _GAUSS_NOISE_MODEL_H
#define _GAUSS_NOISE_MODEL_H
double gauss_noise(double std_dev, double mean_val, double amplitude);
void add_gauss_noise(double* x, double* x_noise, double std_dev = 1.0, double mean_val = 0.0, double amplitude = 1.0,double div_factor = 4.0);
#endif