#ifndef AI_GENOME_HPP
#define AI_GENOME_HPP

#include "ai/Configuration.hpp"
#include "ai/Innovator.hpp"
#include "ai/NeuronGene.hpp"
#include "ai/Random.hpp"
#include "ai/Real.hpp"
#include "ai/SynapseGene.hpp"
#include <functional>
#include <unordered_set>

namespace ai {

using namespace std;

class Genome
{
public:
    explicit Genome(Configuration const &config, size_t id,
                    size_t parent1Id, size_t parent2Id);

    size_t id() const noexcept { return _id; }

    void mutate(RandomEngine &engine);
    Genome crossover(Genome const &other, size_t childId,
                     RandomEngine &engine);
    void inherit(Genome const &parent1, Genome const &parent2,
                 RandomEngine &engine);

private:
    Configuration const &_config;

    size_t _id;
    size_t _parent1Id;
    size_t _parent2Id;
    size_t _speciesId;

    size_t _inputCount;
    size_t _outputCount;

    unordered_set<NeuronGene> _neuronGenes;
    unordered_set<SynapseGene> _synapseGenes;

    Real _fitness;
    Real _crossValidationFitness;

    void mutateAddNeuron(RandomEngine &engine);
    void mutateAddSynapse(RandomEngine &engine);
    void mutateDeleteNeuron(RandomEngine &engine);
    void mutateDeleteSynapse(RandomEngine &engine);

    void inheritNeuronGenes(Genome const &parent1, Genome const &parent2,
                            RandomEngine &engine);
    void inheritSynapseGenes(Genome const &parent1, Genome const &parent2,
                             RandomEngine &engine);
};

}

namespace std {

template<>
struct hash<ai::Genome>
{
    using argument_type = ai::Genome;
    using result_type = size_t;

    result_type operator()(argument_type const &v) const
    {
        return v.id();
    }
};

}

#endif // AI_GENOME_HPP
