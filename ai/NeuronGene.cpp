#include "ai/NeuronGene.hpp"
#include <stdexcept>

namespace ai {

void NeuronGene::mutate(Configuration const &config, RandomEngine &engine)
{
    UniformDistribution probDist;

    if (probDist(engine) < config.probMutateBias) {
        if (probDist(engine) < config.probReplaceBias) {
            NormalDistribution biasDist{0, config.biasStdDev};
            bias = biasDist(engine);
        }
        else {
            NormalDistribution biasDist{0, 1};
            bias += biasDist(engine) * config.biasMutationPower;
            bias = max(config.minBias, min(config.maxBias, bias));
        }
    }

    if (probDist(engine) < config.probMutateResponse) {
        if (probDist(engine) < config.probReplaceResponse) {
            NormalDistribution responseDist{0, config.responseStdDev};
            response = responseDist(engine);
        }
        else {
            NormalDistribution responseDist{0, 1};
            response += responseDist(engine) * config.responseMutationPower;
            response = max(config.minResponse,
                           min(config.maxResponse, response));
        }
    }

    if (probDist(engine) < config.probMutateActivator) {
        activator = config.activatorSet.choose(engine);
    }
}

NeuronGene NeuronGene::crossover(NeuronGene const &other,
                                 RandomEngine &engine) const
{
    if (*this != other) {
        throw runtime_error{"Attempted crossover between different genes"};
    }

    UniformDistribution probDist;
    return {
        id,
        probDist(engine) < 0.5 ? bias : other.bias,
        probDist(engine) < 0.5 ? response : other.response,
        probDist(engine) < 0.5 ? activator : other.activator,
    };
}

bool operator==(NeuronGene const &lhs, NeuronGene const &rhs)
{
    hash<NeuronGene> hashGene;
    return hashGene(lhs) == hashGene(rhs);
}

bool operator!=(NeuronGene const &lhs, NeuronGene const &rhs)
{
    return !(lhs == rhs);
}

}
