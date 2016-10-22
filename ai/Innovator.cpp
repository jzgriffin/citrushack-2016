#include "ai/Innovator.hpp"

namespace ai {

using namespace std;

Innovator::Innovator(std::size_t first)
    : _next{first}
{
}

std::size_t Innovator::next()
{
    return _next++;
}

}
