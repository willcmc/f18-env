#include "Gauss_Noise_Model.h"
#include "math.h"

double gauss_noise(double std_dev, double mean_val, double amplitude)
{
 double x;
 double U1 = (double(rand())/RAND_MAX);
 double U2 = (double(rand())/RAND_MAX);

 if(U1 == 0)
    x = 0;
 else
     x = mean_val + std_dev * std::sqrt(-2*std::log(U1/amplitude))*std::cos(2*M_PI*U2);    
 return x;
}

void add_gauss_noise(double* x, double* x_noise, double std_dev, double mean_val, double amplitude,double div_factor)
{
    for (int i=0 ;i<12;i++)
    x_noise[i] = x[i] - gauss_noise(std_dev,mean_val,amplitude)/div_factor;
}
