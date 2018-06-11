

#include <stdint.h>

/**
 * @brief Get the B instruction
 * 
 * @param oldInstrAddr The old instruction address
 * @param newInstrAddr The new instruction address
 * @return uint32_t BL instruction
 * 
 * @Note
 *  Encoding T4
 *  Offset = newInstrAddr - oldInstrAddr. shall within 16M = 2^24 = 0x1000000
 */
uint32_t B_GetInstr(uint32_t oldInstrAddr, uint32_t newInstrAddr);
