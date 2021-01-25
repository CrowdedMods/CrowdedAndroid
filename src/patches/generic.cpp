#include "generic.h"

namespace GameDataPatches
{
    bool checkId(GameData_o* inst, SBYTE id)
    {
        for(auto i = 0; i < inst->fields.AllPlayers->fields._size; i++)
        {
            if(inst->fields.AllPlayers->fields._items->m_Items[i]->fields.DNFAGBBPHPI == id)
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
        constexpr BYTE opcodes[] = {
#if defined(__ARM_ARCH_7A__)
            0xF0, 0x8B, 0xBD, 0xE8      // POP {R4-R9,R11,PC} (return)
#elif defined(__aarch64__)
            0xC0, 0x03, 0x5F, 0xD6      // RET
#endif
        };
        Memory::writeOffset(OFFSETS.PlayerTab_UpdateAvailableColors_m, (char*)opcodes, sizeof(opcodes));
        constexpr BYTE otheropcodes[] = {
#if defined(__ARM_ARCH_7A__)
            0x7F
#elif defined(__aarch64__)
            0xE1, 0x0F
#endif
        };
        Memory::writeOffset(OFFSETS.SecurityLogger_ctor_m, (char*)otheropcodes, sizeof(otheropcodes)); // replace 10 with 127
    }
}