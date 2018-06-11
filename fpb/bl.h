

#include "b.h"

/**
 * @brief Get the BL instruction
 * 
 * @param oldInstrAddr The old instruction address
 * @param newInstrAddr The new instruction address
 * @return uint32_t BL instruction
 * 
 * @Note
 *  Encoding T1
 *  Offset = newInstrAddr - oldInstrAddr. shall within 16M = 2^24 = 0x1000000
 */
uint32_t BL_GetInstr(uint32_t oldInstrAddr, uint32_t newInstrAddr);
