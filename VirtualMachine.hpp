#ifndef VIRTUAL_MACHINE_HPP
#define VIRTUAL_MACHINE_HPP

#include "Keypad.hpp"
#include <cstdint>
#include <stack>
#include <functional>
#include <istream>

class VirtualMachine
{
public:
    static constexpr std::size_t displayWidth = 64;
    static constexpr std::size_t displayHeight = 32;

    std::function<void(std::size_t, std::size_t, std::uint8_t)> drawCallback; // params: x, y, color
    std::function<void()> clearCallback;

    explicit VirtualMachine(Keypad &keypad, std::istream &input);    // Constructor

    void cycle();       // Cycles through one instruction
    void run();         // Cycles through instructions while _isRunning is true
    void halt();        // Stops cycling through instructions when _isRunning is false
    void tick();        // Decreases st and dt

private:
    union       // Objects take up the same memory space, so they can be accessed either by the array or by the name
    {
        std::uint8_t v[16]; // Array to simulate registers, every element is one register
        struct
        {
            std::uint8_t v0, v1, v2, v3, v4, v5, v6, v7, v8, v9;
            std::uint8_t va, vb, vc, vd, ve, vf;
        };
    };

    bool _isRunning{true};
    Keypad &_keypad;    // Reference to keypad
    std::uint16_t I;     // Register I
    std::uint8_t st;     // Sound timer
    std::uint8_t dt;     // Delay timer
    std::uint16_t pc = 0x200;    // Program counter
    std::uint8_t memory[0x1000];     // Memory array of size 4096 bytes
    std::stack<std::int16_t> callStack;
    std::uint8_t display[displayHeight * displayWidth];     // Display array with 2048 pixels

    void instr6XNN(std::uint16_t opcode);   // Store number NN in register VX
    void instr8XY0(std::uint16_t opcode);   // Store the value of register VY in register VX
    void instr7XNN(std::uint16_t opcode);   // Add the value NN to register VX
    void instr8XY4(std::uint16_t opcode);   // Add the value of register VY to register VX, set VF to 01 if carry, and 00 if no carry
    void instr8XY5(std::uint16_t opcode);   // Subtract the value of register VY from register VX, set VF to 00 if borrow, 01 if no borrow
    void instr8XY7(std::uint16_t opcode);   // Set register VX to the value of VY minus VX, set VF to 00 if borrow, 01 if no borrow
    void instr8XY2(std::uint16_t opcode);   // Set VX to VX AND VY
    void instr8XY1(std::uint16_t opcode);   // Set VX to VX OR VY
    void instr8XY3(std::uint16_t opcode);   // Set VX to VX XOR VY
    void instr8XY6(std::uint16_t opcode);   // Store value of register VY shifted right one bit in register VX, VF set to least significant bit prior to shift
    void instr8XYE(std::uint16_t opcode);   // Store value of register VY shifted left one bit in register VX, VF set to most significant bit prior to shift
    void instrCXNN(std::uint16_t opcode);   // Set VX to a random number with a mask of NN
    void instr1NNN(std::uint16_t opcode);   // Jump to address NNN
    void instrBNNN(std::uint16_t opcode);   // Jump to address NNN + V0
    void instr2NNN(std::uint16_t opcode);   // Execute subroutine starting at address NNN
    void instr00EE(std::uint16_t opcode);   // Return from a subroutine
    void instr0NNN(std::uint16_t opcode);   // Execute machine language subroutine at address NNN
    void instr3XNN(std::uint16_t opcode);   // Skip the following instruction if the value of register VX equals NN
    void instr5XY0(std::uint16_t opcode);   // Skip the following instruction if the value of register VX is equal to the value of register VY
    void instr4XNN(std::uint16_t opcode);   // Skip the following instruction if the value of register VX is not equal to NN
    void instr9XY0(std::uint16_t opcode);   // Skip the following instruction if the value of register VX is not equal to the value of register VY
    void instrFX15(std::uint16_t opcode);   // Set the delay timer to the value of register VX
    void instrFX07(std::uint16_t opcode);   // Store the current value of the delay timer in register VX
    void instrFX18(std::uint16_t opcode);   // Set the sound timer to the value of register VX
    void instrFX0A(std::uint16_t opcode);   // Wait for a keypress and store the result in register VX
    void instrEX9E(std::uint16_t opcode);   // Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed
    void instrEXA1(std::uint16_t opcode);   // Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed
    void instrANNN(std::uint16_t opcode);   // Store memory address NNN in register I
    void instrFX1E(std::uint16_t opcode);   // Add the value stored in register VX to register I
    void instrDXYN(std::uint16_t opcode);   // Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I.
                        // Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
    void instr00E0(std::uint16_t opcode);   // Clear the screen
    void instrFX29(std::uint16_t opcode);   // Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
    void instrFX33(std::uint16_t opcode);   // Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I+1, and I+2
    void instrFX55(std::uint16_t opcode);   // Store the values of registers V0 to VX inclusive in memory starting at address I.
                        // I is set to I + X + 1 after operation
    void instrFX65(std::uint16_t opcode);   // Fill registers V0 to VX inclusive with the values stored in memory starting at address I.
                        // I is set to I + X + 1 after operation

    void advance(std::uint16_t opcodes = 1);      // Steps through opcodes
};

#endif // VIRTUAL_MACHINE_HPP
