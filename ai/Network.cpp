#include "ai/Network.hpp"
#include <utility>

namespace ai {

using namespace std;

Network::Network(vector<Neuron> neurons,
                 vector<size_t> inputs, vector<size_t> outputs)
    : _neurons{move(neurons)}
    , _inputs{move(inputs)}
    , _outputs{move(outputs)}
    , _values(_neurons.size(), 0)
{
}

vector<Real> Network::activate(vector<Real> const &inputs)
{
    if (inputs.size() != _inputs.size()) {
        throw runtime_error{"input vector sizes differ"};
    }

    for (decltype(inputs.size()) i = 0; i < inputs.size(); ++i) {
        _values[_inputs[i]] = inputs[i];
    }

    for (auto &&neuron : _neurons) {
        Real sum = 0;
        for (auto &&synapse : neuron.synapses) {
            sum += _values[synapse.index] * synapse.weight;
        }

        auto signal = neuron.bias + neuron.response * sum;
        _values[neuron.index] = neuron.activator(signal);
    }

    vector<Real> outputs;
    for (auto &&output : _outputs) {
        outputs.push_back(_values[output]);
    }

    return outputs;
}

void Network::reset()
{
    _values.clear();
    _values.resize(_neurons.size(), 0);
}

}
