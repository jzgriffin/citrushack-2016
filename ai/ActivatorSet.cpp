#include "ai/ActivatorSet.hpp"
#include "ai/Activators.hpp"
#include <random>
#include <iterator>

namespace ai {

using namespace std;

ActivatorSet ActivatorSet::defaultSet()
{
    ActivatorSet result;
    result.activators.emplace_back(absActivator);
    result.activators.emplace_back(cubeActivator);
    result.activators.emplace_back(expActivator);
    result.activators.emplace_back(hatActivator);
    result.activators.emplace_back(identityActivator);
    result.activators.emplace_back(invActivator);
    result.activators.emplace_back(logActivator);
    result.activators.emplace_back(rectifierActivator);
    result.activators.emplace_back(sigmoidActivator);
    result.activators.emplace_back(sinActivator);
    result.activators.emplace_back(softplusActivator);
    result.activators.emplace_back(squareActivator);
    result.activators.emplace_back(tanhActivator);
    result.activators.emplace_back(unitActivator);
    return result;
}

Activator const &ActivatorSet::choose(RandomEngine &engine) const noexcept
{
    uniform_int_distribution<decltype(activators)::size_type> dist{
        0, activators.size()
    };

    return activators[dist(engine)];
}

}
