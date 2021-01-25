#ifndef MEETING_HUD_H
#define MEETING_HUD_H

#include "../log.h"
#include "../gamedata/func.h"
#include <cmath>
#include <algorithm>

namespace MeetingHudPatches
{
    extern BYTE *votes;

    void init();
    void Update_h(MeetingHud_o *pThis);
    void CheckForEndVoting_h(MeetingHud_o *pThis);
    void HandleRpc_h(MeetingHud_o *pThis, BYTE callId, Hazel_MessageReader_o *reader);
}

#endif