#ifndef HOOK_H
#define HOOK_H

#include <dobby.h>

#include "patches/meeting_hud.h"
#include "patches/generic.h"

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
    BYTE* buf = new BYTE[4]; // useless! Yay!
    DobbyHook(
        (void*)Memory::getAbsoluteAddress(OFFSETS.PlayerControl_CheckColor),
        (void*)Memory::getAbsoluteAddress(OFFSETS.PlayerControl_RpcSetColor),
        (void**)&buf
    ); // redirect CheckColor to RpcSetColor
}
#undef DO_HOOK
#undef DO_PATCH

#endif