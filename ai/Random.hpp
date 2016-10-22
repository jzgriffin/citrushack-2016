#ifndef AI_RANDOM_HPP
#define AI_RANDOM_HPP

#include "ai/Real.hpp"
#include <random>

namespace ai {

using namespace std;

using RandomEngine = default_random_engine;
using UniformDistribution = uniform_real_distribution<Real>;
using NormalDistribution = normal_distribution<Real>;

}

#endif // AI_RANDOM_HPP
