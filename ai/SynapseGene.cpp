#include "ai/SynapseGene.hpp"
#include <stdexcept>

namespace ai {

using namespace std;

void SynapseGene::mutate(Configuration const &config, RandomEngine &engine)
{
    UniformDistribution probDist;

    if (probDist(engine) < config.probMutateWeight) {
        if (probDist(engine) < config.probReplaceWeight) {
            NormalDistribution weightDist{0, config.weightStdDev};
            weight = weightDist(engine);
        }
        else {
            NormalDistribution weightDist{0, 1};
            weight += weightDist(engine) * config.weightMutationPower;
            weight = max(config.minWeight, min(config.maxWeight, weight));
        }
    }

    if (probDist(engine) < config.probToggleSynapse) {
        isEnabled = !isEnabled;
    }
}

pair<SynapseGene, SynapseGene> SynapseGene::split(size_t neuronId)
{
    isEnabled = false;

    return {
        {true, 1, inputId, neuronId},
        {true, weight, neuronId, outputId}
    };
}

SynapseGene SynapseGene::crossover(SynapseGene const &other,
                                   RandomEngine &engine) const
{
    if (*this != other) {
        throw runtime_error{"Attempted crossover between different genes"};
    }

    UniformDistribution probDist;
    return {
        probDist(engine) < 0.5 ? isEnabled : other.isEnabled,
        probDist(engine) < 0.5 ? weight : other.weight,
        inputId,
        outputId,
    };
}

bool operator==(SynapseGene const &lhs, SynapseGene const &rhs)
{
    hash<SynapseGene> hashGene;
    return hashGene(lhs) == hashGene(rhs);
}

bool operator!=(SynapseGene const &lhs, SynapseGene const &rhs)
{
    return !(lhs == rhs);
}

}
