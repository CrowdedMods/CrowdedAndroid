#include "generic.h"

namespace GameDataPatches
{
    bool checkId(GameData_o* inst, SBYTE id)
    {
        for(auto i = 0; i < inst->fields.AllPlayers->fields._size; i++)
        {
            if(inst->fields.AllPlayers->fields._items->m_Items[i]->fields.M_playerId == id)
                return false;
        }
        return true;
    }

    SBYTE GetAvailableId_h(GameData_o* pThis)
    {
        for(auto i = 0; i < 127; i++)
        {
            if(checkId(pThis, i)) return i;
        }
        return -1;
    }

    void init()
    {
        // inline asm patch to allow choosing already used colors
        constexpr BYTE opcodes[] = {
#if defined(__ARM_ARCH_7A__)
            0xF0, 0x8B, 0xBD, 0xE8      // POP {R4-R9,R11,PC} (return)
#elif defined(__aarch64__)
            0xC0, 0x03, 0x5F, 0xD6      // RET
#endif
        };
        Memory::writeOffset(OFFSETS.PlayerTab_UpdateAvailableColors_m, (char*)opcodes, sizeof(opcodes));
        // inline asm patch to fix mira logs
        constexpr BYTE otheropcodes[] = {
#if defined(__ARM_ARCH_7A__)
            0x7F            // replace hardcoded 10 with 127
#elif defined(__aarch64__)
            0xE1, 0x0F  
#endif
        };
        Memory::writeOffset(OFFSETS.SecurityLogger_ctor_m, (char*)otheropcodes, sizeof(otheropcodes));
        // inline asm patch to force return impostor amoung instead of adjusted one
        constexpr BYTE impostoramountopcodes[] = {
#if defined(__ARM_ARCH_7A__)
            0x38, 0x00, 0x94, 0xE5,         // LDR R0, [R4, #0x38]      @ original opcode, but store in R0 (return)
            0x70, 0x4C, 0xBD, 0xE8,         // POP {R4-R6,R10,R11,LR}   @ postlude
            0x1E, 0xFF, 0x2F, 0xE1          // BX LR                    @ return
#elif defined(__aarch64__)
            0x00, 0x41, 0x40, 0xB9,         // LDR W0, [X8,#0x40]       @ original opcode, but store in W0 (return)
            0xC0, 0x03, 0x5F, 0xD6          // RET
#endif
        };
        Memory::writeOffset(OFFSETS.GameOptionsData_GetAdjustedNumImpostors_m, (char*)impostoramountopcodes, sizeof(impostoramountopcodes));
    }
}