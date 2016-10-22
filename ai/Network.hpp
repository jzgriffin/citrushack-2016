#ifndef AI_NETWORK_HPP
#define AI_NETWORK_HPP

#include "ai/Neuron.hpp"
#include <vector>

namespace ai {

using namespace std;

class Network
{
public:
    Network(vector<Neuron> neurons,
            vector<size_t> inputs, vector<size_t> outputs);

    vector<Neuron> const &neurons() const noexcept { return _neurons; }
    vector<size_t> const &inputs() const noexcept { return _inputs; }
    vector<size_t> const &outputs() const noexcept { return _outputs; }
    vector<Real> const &values() const noexcept { return _values; }

    vector<Real> activate(vector<Real> const &inputs);

    void reset();

private:
    vector<Neuron> _neurons;
    vector<size_t> _inputs;
    vector<size_t> _outputs;
    vector<Real> _values;
};

}

#endif // AI_NETWORK_HPP
