#ifndef FUNC_H
#define FUNC_H

#include "offsets.h"
#include "il2cpp.h"
#include "../structs/memory.h"

#define BYTE uint8_t
#define SBYTE int8_t
#define DO_ETYPE(__type) extern __type ## _c **__type ## __Type

DO_ETYPE(PlayerControl);
DO_ETYPE(GameData);
DO_ETYPE(AmongUsClient);
DO_ETYPE(System_Byte);

#define CREATE_ARRAY(__type, __size) ((__type ## _array *(*)(void*, il2cpp_array_size_t)) Memory::getAbsoluteAddress(OFFSETS.il2cpp_array_new))((void*)*__type ## __Type, __size)
#define NSTR(str) Marshal_PtrToStringAnsi(str)

typedef bool                       String_Equals_f                      (System_String_o*, System_String_o*);
typedef System_String_o           *String_Concat_f                      (System_String_o*, System_String_o*);
typedef System_String_o           *Marshal_PtrToStringAnsi_f            (const char *);
typedef System_String_o           *Marshal_PtrToStringUni_f             (const char *);
typedef void                       GameObject_SetActive_f               (UnityEngine_GameObject_o*, bool);
typedef System_Byte_array         *MessageReader_ReadBytesAndSize_f     (Hazel_MessageReader_o*);
typedef BYTE                       MessageReader_ReadByte_f             (Hazel_MessageReader_o*);
typedef bool                       MessageReader_ReadBoolean_f          (Hazel_MessageReader_o*);
typedef PlayerInfo                *GameData_GetPlayerById_f             (GameData_o*, BYTE);
typedef Hazel_MessageWriter_o     *InnerNetClient_StartRpc_f            (void*, uint32_t, BYTE, int);
typedef void                       MessageWriter_WriteBytesAndSize_f    (Hazel_MessageWriter_o*, System_Byte_array*);
typedef void                       MessageWriter_WriteBoolean_f         (Hazel_MessageWriter_o*, bool);
typedef void                       MessageWriter_WriteByte_f            (Hazel_MessageWriter_o*, BYTE);
typedef void                       MessageWriter_EndMessage_f           (Hazel_MessageWriter_o*);
typedef void                       MeetingHud_VotingComplete_f          (MeetingHud_o*, System_Byte_array*, PlayerInfo*, bool);
typedef void                       PlayerControl_SetName_f              (PlayerControl_o*, System_String_o*);
typedef void                       PlayerControl_SetColor_f             (PlayerControl_o*, BYTE);
typedef void                       PlayerControl_SetHat_f               (PlayerControl_o*, BYTE, SBYTE);
typedef void                       PlayerControl_SetSkin_f              (PlayerControl_o*, BYTE);
typedef void                       PlayerControl_SetPet_f               (PlayerControl_o*, BYTE);
typedef BYTE                       PlayerVoteArea_GetState_f            (PlayerVoteArea_o*);
typedef void                       ShipStatus_Start_f                   (ShipStatus_o*);
typedef void                       KeySlotBehaviour_SetHighlight_f      (KeySlotBehaviour_o*);

typedef UnityEngine_GameObject_o  *Component_get_GameObject_f           (void*);
typedef UnityEngine_Transform_o   *Component_get_Transform_f            (void*);
typedef UnityEngine_Vector3_o     *Transform_get_LocalPosition_f        (UnityEngine_Transform_o*);
typedef void                      *Transform_set_LocalPosition_f        (UnityEngine_Transform_o*, UnityEngine_Vector3_o);
typedef bool                       AmongUsClient_get_AmHost_f           (AmongUsClient_o*);
typedef void                      *Input_GetTouch_Injected_f            (int, UnityEngine_Touch_o*);
typedef int                        Input_get_TouchCount_f               ();

typedef void                       VersionShower_Start_f                (VersionShower_o*);
typedef void                       MeetingHud_Update_f                  (MeetingHud_o*);
typedef void                       MeetingHud_CheckForEndVoting_f       (MeetingHud_o*);
typedef void                       MeetingHud_HandleRpc_f               (MeetingHud_o*, BYTE, Hazel_MessageReader_o*);
typedef void                       DummyBehaviour_Start_f               (DummyBehaviour_o*);
typedef SBYTE                      GameData_GetAvailableId_f            (GameData_o*);
typedef SBYTE                      PlayerVoteArea_GetVotedFor_f         (uint32_t);
typedef void                       KeyMinigame_Start_f                  (KeyMinigame_o*);

extern String_Equals_f                   *String_Equals;
extern String_Concat_f                   *String_Concat;
extern Marshal_PtrToStringAnsi_f         *Marshal_PtrToStringAnsi;
extern Marshal_PtrToStringUni_f          *Marshal_PtrToStringUni;
extern GameObject_SetActive_f            *GameObject_SetActive;
extern MessageReader_ReadBytesAndSize_f  *MessageReader_ReadBytesAndSize;
extern MessageReader_ReadByte_f          *MessageReader_ReadByte;
extern MessageReader_ReadBoolean_f       *MessageReader_ReadBoolean;
extern GameData_GetPlayerById_f          *GameData_GetPlayerById;
extern InnerNetClient_StartRpc_f         *InnerNetClient_StartRpc;
extern MessageWriter_WriteBytesAndSize_f *MessageWriter_WriteBytesAndSize;
extern MessageWriter_WriteBoolean_f      *MessageWriter_WriteBoolean;
extern MessageWriter_WriteByte_f         *MessageWriter_WriteByte;
extern MessageWriter_EndMessage_f        *MessageWriter_EndMessage;
extern MeetingHud_VotingComplete_f       *MeetingHud_VotingComplete;
extern PlayerControl_SetName_f           *PlayerControl_SetName;
extern PlayerControl_SetColor_f          *PlayerControl_SetColor;
extern PlayerControl_SetHat_f            *PlayerControl_SetHat;
extern PlayerControl_SetSkin_f           *PlayerControl_SetSkin;
extern PlayerControl_SetPet_f            *PlayerControl_SetPet;
extern PlayerVoteArea_GetState_f         *PlayerVoteArea_GetState;
extern KeySlotBehaviour_SetHighlight_f   *KeySlotBehaviour_SetHighlight;

extern Component_get_GameObject_f        *Component_get_GameObject;
extern Component_get_Transform_f         *Component_get_Transform;
extern Transform_get_LocalPosition_f     *Transform_get_LocalPosition;
extern Transform_set_LocalPosition_f     *Transform_set_LocalPosition;
extern AmongUsClient_get_AmHost_f        *AmongUsClient_get_AmHost;
extern Input_GetTouch_Injected_f         *Input_GetTouch_Injected;
extern Input_get_TouchCount_f            *Input_get_TouchCount;

extern MeetingHud_Update_f               *MeetingHud_Update_o;
extern MeetingHud_CheckForEndVoting_f    *MeetingHud_CheckForEndVoting_o;
extern MeetingHud_HandleRpc_f            *MeetingHud_HandleRpc_o;
extern VersionShower_Start_f             *VersionShower_Start_o;
extern DummyBehaviour_Start_f            *DummyBehaviour_Start_o;
extern ShipStatus_Start_f                *ShipStatus_Start_o;
extern GameData_GetAvailableId_f         *GameData_GetAvailableId_o;
extern PlayerVoteArea_GetVotedFor_f      *PlayerVoteArea_GetVotedFor_o;
extern KeyMinigame_Start_f               *KeyMinigame_Start_o;

void init_functions();

#undef DO_ETYPEDEF

#endif