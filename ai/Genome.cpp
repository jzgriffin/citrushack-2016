#include "ai/Genome.hpp"
#include <stdexcept>

namespace ai {

using namespace std;

Genome::Genome(Configuration const &config, size_t id,
               size_t parent1Id, size_t parent2Id)
    : _config{config}
    , _id{id}
    , _parent1Id{parent1Id}
    , _parent2Id{parent2Id}
{
}

void Genome::mutate(RandomEngine &engine)
{
    UniformDistribution probDist;

    if (probDist(engine) < _config.probAddNeuron) {
        mutateAddNeuron(engine);
    }

    if (probDist(engine) < _config.probAddSynapse) {
        mutateAddSynapse(engine);
    }

    if (probDist(engine) < _config.probDeleteNeuron) {
        mutateDeleteNeuron(engine);
    }

    if (probDist(engine) < _config.probDeleteSynapse) {
        mutateDeleteSynapse(engine);
    }

    unordered_set<NeuronGene> mutatedNeuronGenes;
    for (auto gene : _neuronGenes) {
        gene.mutate(_config, engine);
        mutatedNeuronGenes.emplace(gene);
    }

    _neuronGenes = move(mutatedNeuronGenes);

    unordered_set<SynapseGene> mutatedSynapseGenes;
    for (auto gene : _synapseGenes) {
        gene.mutate(_config, engine);
        mutatedSynapseGenes.emplace(gene);
    }

    _synapseGenes = move(mutatedSynapseGenes);
}

Genome Genome::crossover(Genome const &other, size_t childId,
                         RandomEngine &engine)
{
    hash<Genome> hashGenome;
    if (hashGenome(*this) != hashGenome(other)) {
        throw runtime_error{"Attempted crossover between different genomes"};
    }

    Genome const *parent1;
    Genome const *parent2;
    if (_fitness > other._fitness) {
        parent1 = this;
        parent2 = &other;
    }
    else {
        parent1 = &other;
        parent2 = this;
    }

    Genome child{_config, childId, parent1->_id, parent2->_id};
    child.inherit(*parent1, *parent2, engine);
    child._speciesId = parent1->_id;
    return child;
}

void Genome::inherit(Genome const &parent1, Genome const &parent2,
                     RandomEngine &engine)
{
    if (parent1._fitness >= parent2._fitness) {
        throw runtime_error{"Primary parent is less fit than secondary"};
    }

    inheritSynapseGenes(parent1, parent2, engine);
    inheritNeuronGenes(parent1, parent2, engine);
}

void Genome::mutateAddNeuron(RandomEngine &engine)
{
    // TODO
}

void Genome::mutateAddSynapse(RandomEngine &engine)
{
    // TODO
}

void Genome::mutateDeleteNeuron(RandomEngine &engine)
{
    // TODO
}

void Genome::mutateDeleteSynapse(RandomEngine &engine)
{
    // TODO
}

void Genome::inheritNeuronGenes(Genome const &parent1, Genome const &parent2,
                                RandomEngine &engine)
{
    for (auto &&gene1 : parent1._neuronGenes) {
        NeuronGene gene;

        auto gene2 = parent2._neuronGenes.find(gene1);
        if (gene2 == end(parent2._neuronGenes)) {
            gene = gene1;
        }
        else {
            gene = gene1.crossover(*gene2, engine);
        }

        _neuronGenes.emplace(gene);
    }
}

void Genome::inheritSynapseGenes(Genome const &parent1, Genome const &parent2,
                                 RandomEngine &engine)
{
    hash<SynapseGene> hashGene;
    auto areGenesEqual =
            [&](SynapseGene const &gene1, SynapseGene const &gene2) {
        return hashGene(gene1) == hashGene(gene2);
    };

    for (auto &&gene1 : parent1._synapseGenes) {
        SynapseGene gene;

        auto gene2 = parent2._synapseGenes.find(gene1);
        if (gene2 == end(parent2._synapseGenes)) {
            gene = gene1;
        }
        else if (areGenesEqual(gene1, *gene2)) {
                gene = gene1.crossover(*gene2, engine);
        }
        else {
            gene = gene1;
        }

        _synapseGenes.erase(gene);
        _synapseGenes.emplace(gene);
    }
}

}
