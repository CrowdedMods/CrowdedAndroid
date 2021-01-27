#include "generic.h"

struct Someone
{
    const char* name = "Dummy";
    const BYTE colorId = 7;
    const BYTE hatId = 0;
    const BYTE petId = 0;
    const BYTE skinId = 0;
};

constexpr Someone coolPeopleAndXtra[] = {
    Someone {
        .name = "Przebot",
        .colorId = 4,
        .hatId = 55
    },
    Someone {
        .name = "Galster",
        .colorId = 7,
        .hatId = 51
    },
    Someone {
        .name = "Sanek",
        .colorId = 11,
        .hatId = 44,
        .petId = 2
    },
    Someone {
        .name = "XtraSkid",
        .colorId = 6,
        .hatId = 15,
        .petId = 2,
        .skinId = 7
    }
};
constexpr uint8_t fingersAmount = sizeof(coolPeopleAndXtra)/sizeof(Someone);

void DummyBehaviour_Start_h(DummyBehaviour_o *pThis)
{
    DummyBehaviour_Start_o(pThis);
    static uint8_t i = 0;
    if(i == fingersAmount) i = 0;
    const Someone* sponsor = &coolPeopleAndXtra[i++];
    PlayerControl_SetName(pThis->fields.M_myPlayer, NSTR(sponsor->name));
    PlayerControl_SetColor(pThis->fields.M_myPlayer, sponsor->colorId);
    PlayerControl_SetHat(pThis->fields.M_myPlayer, sponsor->hatId, sponsor->colorId);
    PlayerControl_SetSkin(pThis->fields.M_myPlayer, sponsor->skinId);
    PlayerControl_SetPet(pThis->fields.M_myPlayer, sponsor->petId);
}

void VersionShower_Start_h(VersionShower_o *pThis)
{
    VersionShower_Start_o(pThis);
    pThis->fields.text->fields.Text = String_Concat(
        pThis->fields.text->fields.Text,
        NSTR("\n[3DAD2BFF]CrowdedMod by Galster & przebot\nForked from andy08")
    );
}

SBYTE PlayerVoteArea_GetVotedFor_h(uint32_t index)
{
#if defined(__aarch64__) // i'm sure everything is ok with x32, didn't test x64
    LOGF("index is: %d", index);
#endif
    return MeetingHudPatches::votes[index];
}

void KeyMinigame_Start_h(KeyMinigame_o* pThis)
{
    auto localPlayer = (*PlayerControl__Type)->static_fields->LocalPlayer;
    pThis->fields.M_targetSlotId = localPlayer == NULL ? 0 : localPlayer->fields.PlayerId % 10;
    KeySlotBehaviour_SetHighlight(pThis->fields.Slots->m_Items[pThis->fields.M_targetSlotId]);
}

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