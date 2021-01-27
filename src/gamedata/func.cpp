#include "func.h"

// define function pointer for calling it
#define FUNC_PTR(__func)  __func       = (__func ## _f *) Memory::getAbsoluteAddress(OFFSETS.__func)
// define original function buffer (for hooks)
#define FUNC_HPTR(__func) __func ## _o = (__func ## _f *) Memory::getAbsoluteAddress(OFFSETS.__func)
// complete defining static pointers
#define DO_TYPE(__type) __type ## _c **__type ## __Type = (__type ## _c**) Memory::getAbsoluteAddress(TYPE_OFFSETS.__type)

DO_TYPE(PlayerControl);
DO_TYPE(GameData);
DO_TYPE(AmongUsClient);
DO_TYPE(System_Byte);

// complete defining functions pointers
String_Equals_f                   *String_Equals;
String_Concat_f                   *String_Concat;
Marshal_PtrToStringAnsi_f         *Marshal_PtrToStringAnsi;
Marshal_PtrToStringUni_f          *Marshal_PtrToStringUni;
GameObject_SetActive_f            *GameObject_SetActive;
MessageReader_ReadBytesAndSize_f  *MessageReader_ReadBytesAndSize;
MessageReader_ReadByte_f          *MessageReader_ReadByte;
MessageReader_ReadBoolean_f       *MessageReader_ReadBoolean;
GameData_GetPlayerById_f          *GameData_GetPlayerById;
InnerNetClient_StartRpc_f         *InnerNetClient_StartRpc;
MessageWriter_WriteBytesAndSize_f *MessageWriter_WriteBytesAndSize;
MessageWriter_WriteBoolean_f      *MessageWriter_WriteBoolean;
MessageWriter_WriteByte_f         *MessageWriter_WriteByte;
MessageWriter_EndMessage_f        *MessageWriter_EndMessage;
MeetingHud_VotingComplete_f       *MeetingHud_VotingComplete;
PlayerControl_SetName_f           *PlayerControl_SetName;
PlayerControl_SetColor_f          *PlayerControl_SetColor;
PlayerControl_SetHat_f            *PlayerControl_SetHat;
PlayerControl_SetSkin_f           *PlayerControl_SetSkin;
PlayerControl_SetPet_f            *PlayerControl_SetPet;
PlayerVoteArea_GetState_f         *PlayerVoteArea_GetState;
KeySlotBehaviour_SetHighlight_f   *KeySlotBehaviour_SetHighlight;

Component_get_GameObject_f        *Component_get_GameObject;
Component_get_Transform_f         *Component_get_Transform;
Transform_get_LocalPosition_f     *Transform_get_LocalPosition;
Transform_set_LocalPosition_f     *Transform_set_LocalPosition;
AmongUsClient_get_AmHost_f        *AmongUsClient_get_AmHost;
Input_GetTouch_Injected_f         *Input_GetTouch_Injected;
Input_get_TouchCount_f            *Input_get_TouchCount;

MeetingHud_Update_f               *MeetingHud_Update_o;
MeetingHud_CheckForEndVoting_f    *MeetingHud_CheckForEndVoting_o;
MeetingHud_HandleRpc_f            *MeetingHud_HandleRpc_o;
VersionShower_Start_f             *VersionShower_Start_o;
DummyBehaviour_Start_f            *DummyBehaviour_Start_o;
ShipStatus_Start_f                *ShipStatus_Start_o;
GameData_GetAvailableId_f         *GameData_GetAvailableId_o;
PlayerVoteArea_GetVotedFor_f      *PlayerVoteArea_GetVotedFor_o;
KeyMinigame_Start_f               *KeyMinigame_Start_o;
PingTracker_Update_f              *PingTracker_Update_o;

void init_functions()
{
    FUNC_PTR(String_Equals);
    FUNC_PTR(String_Concat);
    FUNC_PTR(Marshal_PtrToStringAnsi);
    FUNC_PTR(Marshal_PtrToStringUni);
    FUNC_PTR(GameObject_SetActive);
    FUNC_PTR(MessageReader_ReadBytesAndSize);
    FUNC_PTR(MessageReader_ReadByte);
    FUNC_PTR(MessageReader_ReadBoolean);
    FUNC_PTR(GameData_GetPlayerById);
    FUNC_PTR(InnerNetClient_StartRpc);
    FUNC_PTR(MessageWriter_WriteBytesAndSize);
    FUNC_PTR(MessageWriter_WriteBoolean);
    FUNC_PTR(MessageWriter_WriteByte);
    FUNC_PTR(MessageWriter_EndMessage);
    FUNC_PTR(MeetingHud_VotingComplete);
    FUNC_PTR(PlayerControl_SetName);
    FUNC_PTR(PlayerControl_SetColor);
    FUNC_PTR(PlayerControl_SetHat);
    FUNC_PTR(PlayerControl_SetSkin);
    FUNC_PTR(PlayerControl_SetPet);
    FUNC_PTR(PlayerVoteArea_GetState);
    FUNC_PTR(KeySlotBehaviour_SetHighlight);

    FUNC_PTR(Component_get_GameObject);
    FUNC_PTR(Component_get_Transform);
    FUNC_PTR(Transform_get_LocalPosition);
    FUNC_PTR(Transform_set_LocalPosition);
    FUNC_PTR(AmongUsClient_get_AmHost);
    FUNC_PTR(Input_GetTouch_Injected);
    FUNC_PTR(Input_get_TouchCount);

    FUNC_HPTR(MeetingHud_Update);
    FUNC_HPTR(MeetingHud_CheckForEndVoting);
    FUNC_HPTR(MeetingHud_HandleRpc);
    FUNC_HPTR(VersionShower_Start);
    FUNC_HPTR(DummyBehaviour_Start);
    FUNC_HPTR(ShipStatus_Start);
    FUNC_HPTR(GameData_GetAvailableId);
    FUNC_HPTR(PlayerVoteArea_GetVotedFor);
    FUNC_HPTR(KeyMinigame_Start);
    FUNC_HPTR(PingTracker_Update);
}

#undef FUNC_PTR
#undef FUNC_HPTR
#undef DO_TYPEDEF