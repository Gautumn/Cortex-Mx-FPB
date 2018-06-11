
#include <stdint.h>
#include <stdbool.h>
#include "QN908XB.h"

/* Flash patch and breakpoint register */
typedef struct
{
    __IO uint32_t FP_CTRL;      /**<  */
    __IO uint32_t FP_REMAP;     /**< Bit[31:29] are hardwired to 3'b001
                                     The remaped value is arranged as a continuous eight words, which must be 8-word boundary */
    __IO uint32_t FP_COMP[8];   /**< Comparators #0 to #5 are instruction address comparators
                                     Comparators #6 to #7 are literal comparators */
    __I  uint32_t PID[8];
    __I  uint32_t CID[4];
} FPB_Type;

#define FPB_BASE (0xE0002000U)
#define FPB ((FPB_Type *)FPB_BASE)


/**
 * @brief Enable FPB
 * 
 * @param enable  true to enable FPB, false to disable FPB
 */
void FPB_Enable(bool enable);

/**
 * @brief Set FPB remap register
 * 
 * @param remapAddr Address value in SRAM
 * 
 * @note 
 *  REMAP register bit[31:29] is hardwired to 3'b001, remap to SRAM region
 *  Please reference <<ARMv7-M Architecture Reference Manual>> for more.
 */
void FPB_SetRemap(uint32_t remapAddr);

/**
 * @brief Configure the FPB the jump from instruction in compAddr to the new instruction
 * 
 * @param idx FPB comparator register index
 * @param oldInstrAddr The old instruction address
 * @param newInstrAddr The new instruction address
 * @param newInstr The new instructure
 */
void FPB_SetInstr(uint8_t idx, uint32_t oldInstrAddr, uint32_t newInstrAddr, uint32_t newInstr);
