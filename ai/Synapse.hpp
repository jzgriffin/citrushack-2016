#ifndef AI_SYNAPSE_HPP
#define AI_SYNAPSE_HPP

#include "ai/Real.hpp"
#include <cstddef>

namespace ai {

using namespace std;

struct Synapse
{
    size_t index;
    Real weight;
};

}

#endif // AI_SYNAPSE_HPP
