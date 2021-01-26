#ifndef OFFSETS_H
#define OFFSETS_H

#include <unistd.h>

#define M_playerStates IAKLDPGLPFJ // MeetingHud
#define M_myPlayer LEIJCJIJMCD // DummyBehaviour
#define M_playerId DNFAGBBPHPI // PlayerInfo
#define M_targetSlotId KMJIEGNOBDB // KeyMinigame

#define PlayerInfo GameData_ ## LFILBENDJJI ## _o

struct OFFSETS_t {
#if defined(__ARM_ARCH_7A__)
    uintptr_t il2cpp_array_new                  = 0x021E608;
    uintptr_t String_Equals                     = 0x06C9928; // yes
    uintptr_t String_Concat                     = 0x06C1E74;
    uintptr_t Marshal_PtrToStringAnsi           = 0x03864BC;
    uintptr_t Marshal_PtrToStringUni            = 0x03864C0;

    uintptr_t MeetingHud_Close                  = 0x0ED30E8;
    uintptr_t GameObject_SetActive              = 0x073C34C;
    uintptr_t MessageReader_ReadBytesAndSize    = 0x09B6DB0;
    uintptr_t MessageReader_ReadByte            = 0x09B682C;
    uintptr_t MessageReader_ReadBoolean         = 0x09B6880;
    uintptr_t GameData_GetPlayerById            = 0x12D5224;
    uintptr_t InnerNetClient_StartRpc           = 0x0C92530;
    uintptr_t MessageWriter_WriteBytesAndSize   = 0x09B7F88;
    uintptr_t MessageWriter_WriteBoolean        = 0x09B7B3C;
    uintptr_t MessageWriter_WriteByte           = 0x09B7830;
    uintptr_t MessageWriter_EndMessage          = 0x09B7890;
    uintptr_t MeetingHud_CastVote               = 0x0ED322C;
    uintptr_t MeetingHud_ClearVote              = 0x0ECFEF8;
    uintptr_t MeetingHud_VotingComplete         = 0x0ED3510;
    uintptr_t PlayerControl_SetName             = 0x0B07388;
    uintptr_t PlayerControl_SetColor            = 0x0B076AC;
    uintptr_t PlayerControl_SetHat              = 0x0B07878;
    uintptr_t PlayerControl_SetSkin             = 0x0B065E0;
    uintptr_t PlayerControl_SetPet              = 0x0B029C4;
    uintptr_t PlayerVoteArea_GetState           = 0x0E55D8C;
    uintptr_t KeySlotBehaviour_SetHighlight     = 0x10B2BEC;

    uintptr_t Component_get_GameObject          = 0x07335AC;
    uintptr_t Component_get_Transform           = 0x073355C;
    uintptr_t Transform_get_LocalPosition       = 0x0727438;
    uintptr_t Transform_set_LocalPosition       = 0x0727510;
    uintptr_t AmongUsClient_get_AmHost          = 0x0C91F88;
    uintptr_t Input_GetTouch_Injected           = 0x0A367FC;
    uintptr_t Input_get_TouchCount              = 0x0A36D98;

    uintptr_t MeetingHud_Update                 = 0x0EDB3E8;
    uintptr_t MeetingHud_CheckForEndVoting      = 0x0ED21D4;
    uintptr_t MeetingHud_HandleRpc              = 0x0ED2F58;
    uintptr_t VersionShower_Start               = 0x13D4968;
    uintptr_t DummyBehaviour_Start              = 0x118490C;
    uintptr_t ShipStatus_Start                  = 0x0CEE6A0;
    uintptr_t GameData_GetAvailableId           = 0x12D9808;
    uintptr_t PlayerControl_CheckColor          = 0x0B0750C;
    uintptr_t PlayerControl_RpcSetColor         = 0x0B0A974;
    uintptr_t PlayerVoteArea_GetVotedFor        = 0x0E5725C;

    uintptr_t MeetingHud_PopulateResults_m              = 0x0ECF70C; // don't edit uwu
    uintptr_t PlayerTab_UpdateAvailableColors_m         = 0x0E4F2D8;
    uintptr_t SecurityLogger_ctor_m                     = 0x1086C3C;
    uintptr_t GameOptionsData_GetAdjustedNumImpostors_m = 0x0BDF990;
#elif defined(__aarch64__)
    uintptr_t il2cpp_array_new                  = 0x05BAC84;
    uintptr_t String_Equals                     = 0x09FD0FC; // yes
    uintptr_t String_Concat                     = 0x09FBF74;
    uintptr_t Marshal_PtrToStringAnsi           = 0x0740C80;
    uintptr_t Marshal_PtrToStringUni            = 0x0740C84;

    uintptr_t MeetingHud_Close                  = 0x10A2910;
    uintptr_t GameObject_SetActive              = 0x0A637DC;
    uintptr_t MessageReader_ReadBytesAndSize    = 0x09B6DB0;
    uintptr_t MessageReader_ReadByte            = 0x0C87CD4;
    uintptr_t MessageReader_ReadBoolean         = 0x0C87D24;
    uintptr_t GameData_GetPlayerById            = 0x13D772C;
    uintptr_t InnerNetClient_StartRpc           = 0x0ED3CBC;
    uintptr_t MessageWriter_WriteBytesAndSize   = 0x0C8904C;
    uintptr_t MessageWriter_WriteBoolean        = 0x0C88CA0;
    uintptr_t MessageWriter_WriteByte           = 0x0C88A30;
    uintptr_t MessageWriter_EndMessage          = 0x0C88A88;
    uintptr_t MeetingHud_CastVote               = 0x10A29FC;
    uintptr_t MeetingHud_ClearVote              = 0x10A03FC;
    uintptr_t MeetingHud_VotingComplete         = 0x10A2C40; // AHIEMIOAKPL
    uintptr_t PlayerControl_SetName             = 0x0D92EB4;
    uintptr_t PlayerControl_SetColor            = 0x0D93128;
    uintptr_t PlayerControl_SetHat              = 0x0D932B4;
    uintptr_t PlayerControl_SetSkin             = 0x0D9239C;
    uintptr_t PlayerControl_SetPet              = 0x0D8F6AC;
    uintptr_t PlayerVoteArea_GetState           = 0x10405F4;
    uintptr_t KeySlotBehaviour_SetHighlight     = 0x1222300; // NNEIBKOLNME

    uintptr_t Component_get_GameObject          = 0x0A5C4BC;
    uintptr_t Component_get_Transform           = 0x0A5C47C;
    uintptr_t Transform_get_LocalPosition       = 0x0A51438;
    uintptr_t Transform_set_LocalPosition       = 0x0A514E8;
    uintptr_t AmongUsClient_get_AmHost          = 0x0ED3880;
    uintptr_t Input_GetTouch_Injected           = 0x0CF1280;
    uintptr_t Input_get_TouchCount              = 0x0CF16CC;

    uintptr_t MeetingHud_Update                 = 0x10A8D54;
    uintptr_t MeetingHud_CheckForEndVoting      = 0x10A1D94; // EMCPEAIADBM
    uintptr_t MeetingHud_HandleRpc              = 0x10A27BC;
    uintptr_t VersionShower_Start               = 0x14A203C;
    uintptr_t DummyBehaviour_Start              = 0x118490C;
    uintptr_t ShipStatus_Start                  = 0x12CC85C;
    uintptr_t GameData_GetAvailableId           = 0x13DB108;
    uintptr_t PlayerControl_CheckColor          = 0x0D92FCC;
    uintptr_t PlayerControl_RpcSetColor         = 0x0D95760;
    uintptr_t PlayerVoteArea_GetVotedFor        = 0x1041674;

    uintptr_t MeetingHud_PopulateResults_m              = 0x109FC7C + 0x208; // JGEFNHBFEMA
    uintptr_t PlayerTab_UpdateAvailableColors_m         = 0x103B0C4 + 0x0E4;
    uintptr_t SecurityLogger_ctor_m                     = 0x11FEA54 + 0x044;
    uintptr_t GameOptionsData_GetAdjustedNumImpostors_m = 0x0E468F8 + 0x068; // MNDMMKIDNAL
#endif
};
extern const OFFSETS_t OFFSETS;

struct TYPE_OFFSETS_t
{
#if defined(__ARM_ARCH_7A__)
    uintptr_t System_Byte           = 0x1B25218;
    uintptr_t PlayerControl         = 0x1B2CA80;
    uintptr_t GameData              = 0x1B28C50;
    uintptr_t AmongUsClient         = 0x1B230D4;
#elif defined(__aarch64__)
    uintptr_t System_Byte           = 0x20ACCF8;
    uintptr_t PlayerControl         = 0x20C12A0;
    uintptr_t GameData              = 0x20C9540;
    uintptr_t AmongUsClient         = 0x20D1E10;
#endif
};
extern const TYPE_OFFSETS_t TYPE_OFFSETS;

#endif