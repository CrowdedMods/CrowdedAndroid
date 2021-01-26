#ifndef HOOK_H
#define HOOK_H

#include <dobby.h>

#include "patches/meeting_hud.h"
#include "patches/generic.h"

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

#define DO_HOOK(__func) DobbyHook((void*)__func ## _o, (void*)&__func ## _h, (void**)&__func ## _o)
#define DO_PATCH(__patch, __func) DobbyHook((void*)__patch ## _ ## __func ## _o, (void*)&__patch ## Patches::__func ## _h, (void**)&__patch ## _ ## __func ## _o)
void init_hooks()
{
    DO_HOOK(VersionShower_Start);
    DO_HOOK(DummyBehaviour_Start);
    DO_HOOK(PlayerVoteArea_GetVotedFor);
    DO_HOOK(KeyMinigame_Start);
    //DO_HOOK(ShipStatus_Start);
    
    DO_PATCH(MeetingHud, Update);
    DO_PATCH(MeetingHud, HandleRpc);
    DO_PATCH(MeetingHud, CheckForEndVoting);

    DO_PATCH(GameData, GetAvailableId);
    void** buf = (void**)new BYTE[4]; // useless! Yay!
    DobbyHook(
        (void*)Memory::getAbsoluteAddress(OFFSETS.PlayerControl_CheckColor),
        (void*)Memory::getAbsoluteAddress(OFFSETS.PlayerControl_RpcSetColor),
        buf
    ); // redirect CheckColor to RpcSetColor
}
#undef DO_HOOK
#undef DO_PATCH

#endif