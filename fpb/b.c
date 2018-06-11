

#include "b.h"

typedef union
{
    struct
    {
        uint32_t imm11:11;
        uint32_t j2:1;
        uint32_t _resv0:1;
        uint32_t j1:1;
        uint32_t _resv1:2;
        uint32_t imm10:10;
        uint32_t s:1;
        uint32_t _resv2:5;
    }b;
    uint32_t w;
} B_Type;

#define B_POS_IMM11    1U
#define B_POS_IMM10    12U
#define B_POS_I2       22U
#define B_POS_I1       23U
#define B_POS_S        24U

uint32_t B_GetInstr(uint32_t oldInstrAddr, uint32_t newInstrAddr)
{
    B_Type b;
    uint32_t imm32;

    imm32 = newInstrAddr - oldInstrAddr - 4;

    b.b._resv0 = 0x1;
    b.b._resv1 = 0x2;
    b.b._resv2 = 0x1E;

    b.b.imm11 = (imm32 >> B_POS_IMM11) & 0x7FF;
    b.b.imm10 = (imm32 >> B_POS_IMM10) & 0x3FF;

    b.b.s  = (imm32 >> B_POS_S) & 0x01;
    b.b.j2 = (~((imm32 >> B_POS_I2) & 0x01) ^ b.b.s) & 0x01;
    b.b.j1 = (~((imm32 >> B_POS_I1) & 0x01) ^ b.b.s) & 0x01;
    
    return b.w;
}
