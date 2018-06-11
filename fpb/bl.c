
#include "bl.h"

uint32_t BL_GetInstr(uint32_t oldInstrAddr, uint32_t newInstrAddr)
{
    uint32_t B = B_GetInstr(oldInstrAddr, newInstrAddr);
    return (B | (0x01U << 14));
}
