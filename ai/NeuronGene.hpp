#ifndef AI_NEURONGENE_HPP
#define AI_NEURONGENE_HPP

#include "ai/Activator.hpp"
#include "ai/ActivatorSet.hpp"
#include "ai/Configuration.hpp"
#include "ai/Random.hpp"
#include "ai/Real.hpp"
#include <functional>

namespace ai {

using namespace std;

struct NeuronGene
{
    size_t id;
    Real bias;
    Real response;
    Activator activator;

    void mutate(Configuration const &config, RandomEngine &engine);
    NeuronGene crossover(NeuronGene const &other, RandomEngine &engine) const;
};

bool operator==(NeuronGene const &lhs, NeuronGene const &rhs);
bool operator!=(NeuronGene const &lhs, NeuronGene const &rhs);

}

namespace std {

template<>
struct hash<ai::NeuronGene>
{
    using argument_type = ai::NeuronGene;
    using result_type = size_t;

    result_type operator()(argument_type const &v) const
    {
        return v.id;
    }
};

}

#endif // AI_NEURONGENE_HPP
