#ifndef AI_NEURON_HPP
#define AI_NEURON_HPP

#include "ai/Activator.hpp"
#include "ai/Real.hpp"
#include "ai/Synapse.hpp"
#include <vector>

namespace ai {

using namespace std;

struct Neuron
{
    size_t index;
    Activator activator;
    Real bias;
    Real response;
    vector<Synapse> synapses;
};

}

#endif // AI_NEURON_HPP
