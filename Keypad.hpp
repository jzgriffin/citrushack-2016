#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include <bitset>
#include <cstdint>

class Keypad
{
public:
    static constexpr std::size_t keyCount = 16;

    using Bitset = std::bitset<keyCount>;

    virtual ~Keypad();

    virtual Bitset const &state() const noexcept { return _state; }

    virtual std::size_t wait() = 0;

private:
    std::bitset<keyCount> _state;
};

#endif // KEYPAD_HPP
