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
