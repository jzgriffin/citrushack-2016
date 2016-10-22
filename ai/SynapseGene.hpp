#ifndef AI_SYNAPSEGENE_HPP
#define AI_SYNAPSEGENE_HPP

#include "ai/Configuration.hpp"
#include "ai/Random.hpp"
#include "ai/Real.hpp"
#include <functional>
#include <utility>

namespace ai {

using namespace std;

struct SynapseGene
{
    bool isEnabled;
    Real weight;
    size_t inputId;
    size_t outputId;

    void mutate(Configuration const &config, RandomEngine &engine);
    pair<SynapseGene, SynapseGene> split(size_t neuronId);
    SynapseGene crossover(SynapseGene const &other,
                          RandomEngine &engine) const;
};

bool operator==(SynapseGene const &lhs, SynapseGene const &rhs);
bool operator!=(SynapseGene const &lhs, SynapseGene const &rhs);

}

namespace std {

template<>
struct hash<ai::SynapseGene>
{
    using argument_type = ai::SynapseGene;
    using result_type = size_t;

    result_type operator()(argument_type const &v) const
    {
        return v.inputId ^ (v.outputId << 1);
    }
};

}

#endif // AI_SYNAPSEGENE_HPP
