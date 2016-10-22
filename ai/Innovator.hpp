#ifndef AI_INNOVATOR_HPP
#define AI_INNOVATOR_HPP

#include <cstddef>

namespace ai {

using namespace std;

class Innovator
{
public:
    explicit Innovator(size_t first = 1);

    size_t next();

private:
    size_t _next;
};

}

#endif // AI_INNOVATOR_HPP
