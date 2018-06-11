

#include "fpb.h"

static uint32_t FPB_BitEndian16(uint32_t data)
{
    return ((data & 0x0000FFFF) << 16) | ((data & 0xFFFF0000) >> 16);
}    

void FPB_Enable(bool enable)
{
    if(enable)
    {
        FPB->FP_CTRL = 0x03U;
    }
    else
    {
        FPB->FP_CTRL = 0x02U;
    }
}

void FPB_SetRemap(uint32_t remapAddr)
{
    FPB->FP_REMAP = remapAddr;
}
void FPB_SetComp(uint8_t idx, uint32_t compAddr)
{
    FPB->FP_COMP[idx] = compAddr | 0x01U;
}

void FPB_SetInstr(uint8_t idx, uint32_t oldInstrAddr, uint32_t newInstrAddr, uint32_t newInstr)
{
    uint32_t compInstr[2];

    newInstr = FPB_BitEndian16(newInstr);

    if(oldInstrAddr & 0x3U)
    {
        /* Half-word aligned */
        compInstr[0] = *(uint32_t *)(oldInstrAddr - 2);
        compInstr[1] = *(uint32_t *)(oldInstrAddr + 2);
        
        FPB_SetComp(idx, oldInstrAddr - 2);
        FPB_SetComp(idx + 1, oldInstrAddr + 2);
        
        *(uint32_t *)(newInstrAddr + ((idx + 0) << 2)) = ((newInstr & 0x0000FFFF) << 16) | (compInstr[0] & 0x0000FFFF);
        *(uint32_t *)(newInstrAddr + ((idx + 1) << 2)) = (compInstr[1] & 0xFFFF0000) | ((newInstr & 0xFFFF0000) >> 16);
        
    }
    else
    {
        /* Word aligned */
        FPB_SetComp(idx, oldInstrAddr);
        *(uint32_t *)(newInstrAddr + (idx << 2)) = newInstr;
    }
}
