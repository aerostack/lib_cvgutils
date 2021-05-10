#include "cvg_random.h"

double cvg_normal_distribution(double mu, double sigma) {
    static bool initialized_rand = false;
    if (!initialized_rand) {
        srand( time(0) );
        initialized_rand = true;
    }
    double r1 = (std::rand() + 1.0)/(RAND_MAX + 1.0); // gives equal distribution in (0, 1]
    double r2 = (std::rand() + 1.0)/(RAND_MAX + 1.0);
    return mu + sigma * std::sqrt(-2*std::log(r1))*std::cos(2*M_PI*r2);
} // returns a single normally distributed number

double cvg_uniform_random( double min, double max) {
    static bool initialized_rand = false;
    if (!initialized_rand) {
        srand( time(0) );
        initialized_rand = true;
    }
    return ( min + (max-min)*( (double)(rand())/(double)(RAND_MAX) ) );
}
