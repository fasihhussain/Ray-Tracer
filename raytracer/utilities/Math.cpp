
#include "Math.hpp"

double sampleNormal() {
    double u = ((float) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((float) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
}