#ifndef AI_ACTIVATORS_HPP
#define AI_ACTIVATORS_HPP

#include "ai/Activator.hpp"

namespace ai {

Real absActivator(Real z);
Real cubeActivator(Real z);
Real expActivator(Real z);
Real hatActivator(Real z);
Real identityActivator(Real z);
Real invActivator(Real z);
Real logActivator(Real z);
Real rectifierActivator(Real z);
Real sigmoidActivator(Real z);
Real sinActivator(Real z);
Real softplusActivator(Real z);
Real squareActivator(Real z);
Real tanhActivator(Real z);
Real unitActivator(Real z);

}

#endif // AI_ACTIVATORS_HPP
