#ifndef GENERIC_H
#define GENERIC_H

// #include "../gamedata/func.h"
#include "meeting_hud.h"

void DummyBehaviour_Start_h(DummyBehaviour_o *pThis);
void VersionShower_Start_h(VersionShower_o *pThis);
void KeyMinigame_Start_h(KeyMinigame_o* pThis);
void PingTracker_Update_h(PingTracker_o* pThis);
SBYTE PlayerVoteArea_GetVotedFor_h(uint32_t index);

namespace GameDataPatches
{
    SBYTE GetAvailableId_h(GameData_o* pThis);
    void init();
}

#endif // GENERIC_H