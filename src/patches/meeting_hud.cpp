#include "meeting_hud.h"

enum TouchPhase // too lazy to import it dynamically
{
    Began = 0,
    Moved = 1,
    Stationary = 2,
    Ended = 3,
    Canceled = 4
};

// i hate c#
namespace IEnumerableUtils
{
    bool orderByIsDead(PlayerVoteArea_o *a, PlayerVoteArea_o *b)
    {
        return a->fields.isDead < b->fields.isDead;
    }
    bool allDeadOrVoted(PlayerVoteArea_array *arr)
    {
        for(size_t i = 0; i < arr->max_length; i++)
        {
            auto item = arr->m_Items[i];
            if(!item->fields.isDead && !item->fields.didVote) return false;
        }
        return true;
    }
    System_Byte_array *selectVotedFor(PlayerVoteArea_array *players)
    {
        auto result = CREATE_ARRAY(System_Byte, players->max_length);
        for(size_t i = 0; i < players->max_length; i++)
        {
            result->m_Items[i] = players->m_Items[i]->fields.votedFor;
            LOGF("[%d] voted for %d", i, result->m_Items[i]);
        }
        return result;
    }
    System_Byte_array *selectVoteState(PlayerVoteArea_array *players)
    {
        auto result = CREATE_ARRAY(System_Byte, players->max_length);
        for(size_t i = 0; i < players->max_length; i++)
        {
            BYTE state = PlayerVoteArea_GetState(players->m_Items[i]);
            LOGF("[%d] writing state %X to %p", i, state, result->m_Items + i);
            result->m_Items[i] = state;
        }
        return result;
    }
}

namespace MeetingHudPatches
{
    System_String_o* lastTimerText;
    uint32_t currentPage = 0;
    UnityEngine_Vector2_o touchStartPos;
    BYTE *votes = new BYTE[127];

    uint32_t get_maxPages()
    {
        return static_cast<uint32_t>(ceil((double)(*PlayerControl__Type)->static_fields->AllPlayerControls->fields._items->max_length / 10));
    }
    BYTE* calculateVotes(PlayerVoteArea_array *arr)
    {
        size_t len = arr->max_length;
        BYTE* result = new BYTE[len+1];
        std::fill(result, result+len+1, (BYTE)0);
        for(size_t i = 0; i < len; i++)
        {
            auto item = arr->m_Items[i]->fields;
            if(item.didVote && !item.isDead && item.votedFor > -2 && item.votedFor < len)
            {
                result[item.votedFor+1]++;
                LOGF("added a vote to %d", item.votedFor);
            }
        }
        return result;
    }
    SBYTE indexOfMax(BYTE* arr, size_t len)
    {
        SBYTE result = -1;
        int max = -1;
        for(int i = 0; i < len; i++)
        {
            auto it = arr[i];
            if(it > max)
            {
                max = it;
                result = i;
            } else if(it == max)
            {
                result = -1;
            }
        }
        return result;
    }
    inline void writeVotes(System_Byte_array* arr)
    {
        memcpy(votes, arr->m_Items, arr->max_length);
    }
    void init()
    {
        /*auto addr = (BYTE *) &votes;
        LOGF("address is %p, second byte: %X", votes, addr[1]);
        const BYTE opcodes[] = {
            0x04, 0x00, 0x1F, 0xE5,             // { LDR R0,             @ Load array address in
            addr[0], addr[1], addr[2], addr[3], //   =votes }            @ register R0
            0xDA, 0x00, 0x90, 0xE1,             // LDRSB R0, [R0, R10]   @ Load signed byte by offset which is stored in R10
        };
        Memory::writeOffset(OFFSETS.MeetingHud_PopulateResults_m, (char *) opcodes, sizeof(opcodes));*/

        /// inline asm patch to make app choose votes in our var instead of extracting it from the state
        const BYTE opcodes[] = {
#if defined(__ARM_ARCH_7A__)
            0x0A, 0x00, 0xA0, 0xE1              // MOV R0, R10           @ load iteration index instead of state
#elif defined(__aarch64__)
            0xE0, 0x03, 0x1C, 0xAA              // MOV X0, X28
#endif
        };
        Memory::writeOffset(OFFSETS.MeetingHud_PopulateResults_m, (char*)opcodes, sizeof(opcodes));
    }

    void Update_h(MeetingHud_o *pThis)
    {
        MeetingHud_Update_o(pThis);
        // swipe detect
        if (Input_get_TouchCount() > 0)
        {
            UnityEngine_Touch_o touch = UnityEngine_Touch_o{};
            Input_GetTouch_Injected(0, &touch);
            switch (touch.fields.m_Phase)
            {
            case TouchPhase::Began:
                touchStartPos = touch.fields.m_Position;
                break;
            case TouchPhase::Ended:
                float x = touch.fields.m_Position.fields.x - touchStartPos.fields.x;
                float y = touch.fields.m_Position.fields.y - touchStartPos.fields.y;
                if (abs(x) >= abs(y) || abs(y) < 50.f) // drop if right/left swipe or
                    break;                             // vertical isn't big enough
                currentPage = std::clamp(
                    currentPage + (y > 0 ? 1 : -1),
                    0U,
                    get_maxPages()-1
                );
                break;
            }
        }
        if (!String_Equals(pThis->fields.TimerText->fields.Text, lastTimerText))
        {
            char buf[64];
            sprintf(buf, " - Page %d/%d", currentPage + 1, get_maxPages());
            pThis->fields.TimerText->fields.Text = lastTimerText = String_Concat(
                pThis->fields.TimerText->fields.Text,
                NSTR(buf)
            );
        }
        PlayerVoteArea_array *playerButtons = pThis->fields.M_playerStates;
        std::sort(playerButtons->m_Items, playerButtons->m_Items + playerButtons->max_length, IEnumerableUtils::orderByIsDead);
        for (uint32_t i = 0; i < playerButtons->max_length; i++)
        {
            PlayerVoteArea_o *item = playerButtons->m_Items[i];
            if (i >= currentPage * 10 && i < (currentPage + 1) * 10)
            {
                GameObject_SetActive(Component_get_GameObject((void *)item), true);
                uint32_t relativeIndex = i % 10;

                UnityEngine_Vector3_o vec = pThis->fields.VoteOrigin;
                // this is easier than calling add opertator function etc
                vec.fields.x += pThis->fields.VoteButtonOffsets.fields.x * (relativeIndex % 2);
                vec.fields.y += pThis->fields.VoteButtonOffsets.fields.y * (relativeIndex / 2);
                vec.fields.z += -1.f;
                Transform_set_LocalPosition(Component_get_Transform((void *)item), vec);
            }
            else
            {
                GameObject_SetActive(Component_get_GameObject((void *)item), false);
            }
        }
    }
    void CheckForEndVoting_h(MeetingHud_o *pThis)
    {
        auto& playerStates = pThis->fields.M_playerStates;
        if(!IEnumerableUtils::allDeadOrVoted(playerStates)) return;
        auto cvotes = calculateVotes(playerStates);
        SBYTE maxId = indexOfMax(cvotes, playerStates->max_length+1) - 1;
        bool tie = maxId == -2;
        LOGF("max id is %d, tie: %d", maxId+1, tie);
        PlayerInfo *exiled = maxId < 0 ? NULL : GameData_GetPlayerById((*GameData__Type)->static_fields->Instance, maxId);
        auto states = IEnumerableUtils::selectVoteState(playerStates);
        auto votes = IEnumerableUtils::selectVotedFor(playerStates);
        writeVotes(votes);
        if (AmongUsClient_get_AmHost((*AmongUsClient__Type)->static_fields->Instance))
        {
            Hazel_MessageWriter_o *writer = InnerNetClient_StartRpc((*AmongUsClient__Type)->static_fields->Instance, pThis->fields.NetId, 23, 1);
            MessageWriter_WriteBytesAndSize(writer, states);
            MessageWriter_WriteBytesAndSize(writer, votes);
            MessageWriter_WriteByte(writer, tie ? 255 : exiled->fields.M_playerId);
            MessageWriter_WriteBoolean(writer, tie);
            MessageWriter_EndMessage(writer);
        }
        MeetingHud_VotingComplete(pThis, states, exiled, tie);
    }
    void HandleRpc_h(MeetingHud_o *pThis, BYTE callId, Hazel_MessageReader_o* reader)
    {
        if(callId == 23)
        {
            System_Byte_array *states = MessageReader_ReadBytesAndSize(reader);
            auto votes = MessageReader_ReadBytesAndSize(reader);
            writeVotes(votes);
            PlayerInfo *player = GameData_GetPlayerById(
                (*GameData__Type)->static_fields->Instance,
                MessageReader_ReadByte(reader)
            );
            bool tie = MessageReader_ReadBoolean(reader);
            MeetingHud_VotingComplete(pThis, states, player, tie);
        } else {
            MeetingHud_HandleRpc_o(pThis, callId, reader);
        }
    }
} // namespace MeetingHudPatches