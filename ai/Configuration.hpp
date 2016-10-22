#ifndef AI_CONFIGURATION_HPP
#define AI_CONFIGURATION_HPP

#include "ai/ActivatorSet.hpp"
#include "ai/Real.hpp"

namespace ai {

struct Configuration
{
    // Genome mutation
    Real probAddNeuron;
    Real probDeleteNeuron;
    Real probAddSynapse;
    Real probDeleteSynapse;

    // Neuron mutation
    ActivatorSet activatorSet;
    Real probMutateBias;
    Real probMutateResponse;
    Real probMutateActivator;
    Real probReplaceBias;
    Real biasStdDev;
    Real biasMutationPower;
    Real minBias;
    Real maxBias;
    Real probReplaceResponse;
    Real responseStdDev;
    Real responseMutationPower;
    Real minResponse;
    Real maxResponse;

    // Synapse mutation
    Real probMutateWeight;
    Real probReplaceWeight;
    Real probToggleSynapse;
    Real weightStdDev;
    Real weightMutationPower;
    Real minWeight;
    Real maxWeight;
};

}

#endif // AI_CONFIGURATION_HPP
