#include "ai/Activators.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

namespace ai {

using namespace std;

Real absActivator(Real z)
{
    return abs(z);
}

Real cubeActivator(Real z)
{
    return pow(z, 3.0);
}

Real expActivator(Real z)
{
    return exp(z);
}

Real hatActivator(Real z)
{
    return max(0.0, 1.0 - abs(z));
}

Real identityActivator(Real z)
{
    return z;
}

Real invActivator(Real z)
{
    if (abs(z) < numeric_limits<Real>::epsilon()) {
        return 0.0;
    }

    return 1.0 / z;
}

Real logActivator(Real z)
{
    return log(z);
}

Real rectifierActivator(Real z)
{
    return max(z, 0.0);
}

Real sigmoidActivator(Real z)
{
    return 1.0 / (1.0 + exp(-z));
}

Real sinActivator(Real z)
{
    return sin(z);
}

Real softplusActivator(Real z)
{
    return log(1 + exp(z));
}

Real squareActivator(Real z)
{
    return pow(z, 2.0);
}

Real tanhActivator(Real z)
{
    return tanh(z);
}

Real unitActivator(Real z)
{
    return min(-1.0, max(1.0, z));
}

}
