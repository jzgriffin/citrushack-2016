#include "VirtualMachine.hpp"

using namespace std;

void VirtualMachine::cycle()
{
    auto opcode = (static_cast<uint16_t>(memory[pc]) << 8) | memory[pc + 1];

    if ((opcode & 0xF000) == 0x6000) {
        instr6XNN(opcode);
    }
    else if ((opcode & 0xF00F) == 0x8000) {
        instr8XY0(opcode);
    }
    else if((opcode & 0xF000) == 0x7000) {
        instr7XNN(opcode);
    }
    else if((opcode & 0xF00F) == 0x8004) {
        instr8XY4(opcode);
    }
    else if((opcode & 0xF00F) == 0x8005) {
        instr8XY5(opcode);
    }
    else if((opcode & 0xF00F) == 0x8007) {
        instr8XY7(opcode);
    }
    else if((opcode & 0xF00F) == 0x8002) {
        instr8XY2(opcode);
    }
    else if ((opcode & 0xF00F) == 0x8001) {
        instr8XY1(opcode);
    }
    else if ((opcode & 0xF00F) == 0x8003) {
        instr8XY3(opcode);
    }
    else if((opcode & 0xF00F) == 0x8006) {
        instr8XY6(opcode);
    }
    else if((opcode & 0xF00F) == 0x800E) {
        instr8XYE(opcode);
    }
    else if((opcode & 0xF000) == 0xC000) {
        instrCXNN(opcode);
    }
    else if((opcode & 0xF000) == 0x1000) {
        instr1NNN(opcode);
    }
    else if((opcode & 0xF000) == 0xB000) {
        instrBNNN(opcode);
    }
    else if((opcode & 0xF000) == 0x2000) {
        instr2NNN(opcode);
    }
    else if(opcode == 0x00EE) {
        instr00EE(opcode);
    }
    else if((opcode & 0xF000) == 0x3000) {
        instr3XNN(opcode);
    }
    else if((opcode & 0xF00F) == 0x5000){
        instr5XY0(opcode);
    }
    else if((opcode & 0xF000) == 0x4000){
        instr4XNN(opcode);
    }
    else if((opcode & 0xF00F) == 0x9000){
        instr9XY0(opcode);
    }
    else if ((opcode & 0xF0FF) == 0xF015){
        instrFX15(opcode);
    }
    else if ((opcode & 0xF0FF) == 0xF007){
        instrFX07(opcode);
    }
    else if((opcode & 0xF0FF) == 0xF018){
        instrFX18(opcode);
    }
    else if((opcode & 0xF0FF) == 0xF00A){
        instrFX0A(opcode);
    }
    else if ((opcode & 0xF0FF) == 0xE09E){
        instrEX9E(opcode);
    }
    else if((opcode & 0xF0FF) == 0xE0A1){
        instrEXA1(opcode);
    }
    else if((opcode & 0xF000) == 0xA000){
        instrANNN(opcode);
    }
    else if((opcode & 0xF0FF) == 0xF01E){
        instrFX1E(opcode);
    }
    else if((opcode & 0xF000) == 0xD000){
        instrDXYN(opcode);
    }
    else if(opcode == 0x00E0){
        instr00E0(opcode);
    }
    else if((opcode & 0xF0FF) == 0xF029){
        instrFX29(opcode);
    }
    else if((opcode & 0xF00F) == 0xF033){
        instrFX33(opcode);
    }
    else if((opcode & 0xF0FF) == 0xF055){
        instrFX55(opcode);
    }
    else if((opcode & 0xF0FF) == 0xF065){
        instrFX65(opcode);
    }
    else if((opcode & 0xF000) == 0x0000) {
        instr0NNN(opcode);
    }
}

void VirtualMachine::run()
{
    while(_isRunning) {
        cycle();
    }
}

void VirtualMachine::halt()
{
    _isRunning = false;
}

void VirtualMachine::advance(uint16_t opcodes)
{
    pc += opcodes * 2;
}

void VirtualMachine::instr6XNN(uint16_t opcode)      // Store number NN in register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;
    uint8_t nn = (opcode & 0x00FF);

    v[vx] = nn;
    advance();
}

void VirtualMachine::instr8XY0(uint16_t opcode)      // Store the value of register VY in register VX
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    v[vx] = v[vy];
    advance();
}

void VirtualMachine::instr7XNN(uint16_t opcode)      // Add the value NN to register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;
    uint8_t nn = (opcode & 0x00FF);

    v[vx] += nn;
    advance();
}

void VirtualMachine::instr8XY4(uint16_t opcode)      // Add the value of register VY to register VX
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    uint16_t sum = static_cast<uint16_t>(v[vx]) + v[vy];
    vf = sum > UINT8_MAX ? 1 : 0;

    v[vx] = static_cast<uint8_t>(sum);
    advance();
}

void VirtualMachine::instr8XY5(uint16_t opcode)      // Subtract the value of register VY from register VX
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    vf = v[vy] > v[vx] ? 1 : 0;
    v[vx] -= v[vy];
    advance();
}

void VirtualMachine::instr8XY7(uint16_t opcode)      // Set register VX to the value of VY minus VX
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    vf = v[vx] > v[vy] ? 1 : 0;
    v[vx] = v[vy] - v[vx];
    advance();
}

void VirtualMachine::instr8XY2(uint16_t opcode)      // Set VX to VX AND VY
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;
    v[vx] = v[vx] & v[vy];
    advance();
}

void VirtualMachine::instr8XY1(uint16_t opcode)      // Set VX to VX OR VY
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;
    v[vx] = v[vx] | v[vy];
    advance();
}

void VirtualMachine::instr8XY3(uint16_t opcode)      // Set VX to VX XOR VY
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;
    v[vx] = v[vx] ^ v[vy];
    advance();
}

void VirtualMachine::instr8XY6(uint16_t opcode)      // Store value of register VY shifted right one bit in register VX
{                                                   // Set register VF to the least significant bit prior to shift
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    vf = v[vy] & 0x01;
    v[vx] = v[vy] >> 1;
    advance();
}

void VirtualMachine::instr8XYE(uint16_t opcode)      // Store value of register VY shifted left one bit in register VX
{                                                   // Set register VF to the most significant bit prior to shift
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    vf = v[vy] & 0x80;
    v[vx] = v[vy] << 1;
    advance();
}

void VirtualMachine::instrCXNN(uint16_t opcode)      // Set VX to a random number with a mask of NN
{
    uint8_t vx = (opcode & 0x0F00) >> 8;
    uint8_t nn = (opcode & 0x00FF);

    v[vx] = rand() & nn;
    advance();
}

void VirtualMachine::instr1NNN(uint16_t opcode)      // Jump to address NNN
{
    uint16_t nnn = (opcode & 0x0FFF);

    pc = nnn;
}

void VirtualMachine::instrBNNN(uint16_t opcode)      // Jump to address NNN + V0
{
    uint16_t nnn = (opcode & 0x0FFF);

    pc = nnn + v[0];
}

void VirtualMachine::instr2NNN(uint16_t opcode)      // Execute subroutine starting at address NNN
{
    uint16_t nnn = (opcode & 0x0FFF);

    advance();      // Advance to return address
    callStack.push(pc);
    pc = nnn;
}

void VirtualMachine::instr00EE(uint16_t opcode)      // Return from a subroutine
{
    (void) opcode;
    pc = callStack.top();
    callStack.pop();
}

void VirtualMachine::instr0NNN(uint16_t opcode)      // Execute machine language subroutine at address NNN
{
    (void) opcode;
    advance();
}

void VirtualMachine::instr3XNN(uint16_t opcode)   // Skip the following instruction if the value of register VX equals NN
{
    uint8_t vx = (opcode & 0x0F00) >> 8;
    uint8_t nn = (opcode & 0x00FF);

    if(v[vx] == nn)
        advance(2);
    else
        advance();
}

void VirtualMachine::instr5XY0(uint16_t opcode)   // Skip the following instruction if the value of register VX is equal to the value of register VY
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    if(v[vx] == v[vy])
        advance(2);
    else
        advance();
}

void VirtualMachine::instr4XNN(uint16_t opcode)   // Skip the following instruction if the value of register VX is not equal to NN
{
    uint8_t vx = (opcode & 0x0F00) >> 8;
    uint8_t nn = (opcode & 0x00FF);

    if(v[vx] != nn)
        advance(2);
    else
        advance();
}

void VirtualMachine::instr9XY0(uint16_t opcode)   // Skip the following instruction if the value of register VX is not equal to the value of register VY
{
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    if(v[vx] != v[vy])
        advance(2);
    else
        advance();
}

void VirtualMachine::instrFX15(uint16_t opcode)   // Set the delay timer to the value of register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    dt = v[vx];
    advance();
}

void VirtualMachine::instrFX07(uint16_t opcode)   // Store the current value of the delay timer in register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    v[vx] = dt;
    advance();
}

void VirtualMachine::instrFX18(uint16_t opcode)   // Set the sound timer to the value of register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    st = v[vx];
    advance();
}

void VirtualMachine::instrFX0A(uint16_t opcode)   // Wait for a keypress and store the result in register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    //v[vx] = cin.get();
    advance();
}

void VirtualMachine::instrEX9E(uint16_t opcode)   // Skip the following instruction if the key corresponding to the hex value currently stored in register VX is pressed
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    //if(cin.get() == v[vx])
        //advance(2);
    //else
        //advance();
}

void VirtualMachine::instrEXA1(uint16_t opcode)   // Skip the following instruction if the key corresponding to the hex value currently stored in register VX is not pressed
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    //if(cin.get() != v[vx])
        //advance(2);
    //else
        //advance();
}

void VirtualMachine::instrANNN(uint16_t opcode)   // Store memory address NNN in register I
{
    uint16_t nnn = (opcode & 0x0FFF);

    I = nnn;
    advance();
}

void VirtualMachine::instrFX1E(uint16_t opcode)   // Add the value stored in register VX to register I
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    I += v[vx];
    advance();
}

void VirtualMachine::instrDXYN(uint16_t opcode)   // Draw a sprite at position VX, VY with N bytes of sprite data starting at the address stored in I.
{                               // Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t vx = (opcode & 0x0F00) >> 8;

    //TODO
    advance();
}

void VirtualMachine::instr00E0(uint16_t opcode)   // Clear the screen
{
    (void) opcode;
    //TODO: clear screen
    advance();
}

void VirtualMachine::instrFX29(uint16_t opcode)   // Set I to the memory address of the sprite data corresponding to the hexadecimal digit stored in register VX
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    //TODO
    advance();
}

void VirtualMachine::instrFX33(uint16_t opcode)   // Store the binary-coded decimal equivalent of the value stored in register VX at addresses I, I+1, and I+2
{
    uint8_t vx = (opcode & 0x0F00) >> 8;

    memory[I] = v[vx] / 100;
    memory[I + 1] = (v[vx] % 100) / 10;
    memory[I + 2] = (v[vx] % 100) % 10;
    advance();
}

void VirtualMachine::instrFX55(uint16_t opcode)   // Store the values of registers V0 to VX inclusive in memory starting at address I.
{                                   // I is set to I + X + 1 after operation
    uint8_t vx = (opcode & 0x0F00) >> 8;

    for(int i = 0; i <= vx; i++)
    {
        memory[I] = v[i];
        I++;
    }

    advance();
}

void VirtualMachine::instrFX65(uint16_t opcode)     // Fill registers V0 to VX inclusive with the values stored in memory starting at address I
{                                                   // I is set to I + X + 1 after operation
    uint8_t vx = (opcode & 0x0F00) >> 8;

    for(int i = 0; i <= vx; i++)
    {
        v[i] = memory[I];
        I++;
    }

    advance();
}
