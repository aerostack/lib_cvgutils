#ifndef CVG_RANDOM_H
#define CVG_RANDOM_H

#include <cstdlib>   // for rand
#include <cmath>     // for atan, sqrt, log, cos
#include <math.h>    // M_PI
#include <ctime>     // time(0)

double cvg_normal_distribution(double mu = 0.0, double sigma = 1.0);

double cvg_uniform_random( double min = 0.0, double max = 1.0);

#endif // CVG_RANDOM_H
