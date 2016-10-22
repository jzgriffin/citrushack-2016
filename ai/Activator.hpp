#ifndef AI_ACTIVATOR_HPP
#define AI_ACTIVATOR_HPP

#include "ai/Real.hpp"
#include <functional>

namespace ai {

using namespace std;

using Activator = function<Real(Real)>;

}

#endif // AI_ACTIVATOR_HPP
