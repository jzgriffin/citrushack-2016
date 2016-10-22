#ifndef AI_ACTIVATORSET_HPP
#define AI_ACTIVATORSET_HPP

#include "ai/Activator.hpp"
#include "ai/Random.hpp"
#include <vector>

namespace ai {

struct ActivatorSet
{
    static ActivatorSet defaultSet();

    vector<Activator> activators;

    Activator const &choose(RandomEngine &engine) const noexcept;
};

}

#endif // AI_ACTIVATORSET_HPP
