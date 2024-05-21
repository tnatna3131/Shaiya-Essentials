#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    typedef Array<char, 52> NpcName;

    enum struct NpcType : UINT32
    {
        None,
        Merchant,
        GateKeeper,
        Blacksmith,
        VetManager,
        GamblingHouse,
        Warehouse,
        Normal,
        Guard,
        Animal,
        Apprentice,
        GuildMaster,
        Dead,
        SkillReset
    };

    #pragma pack(push, 1)
    // 0049AB60 ctor
    struct CNpc
    {
        PAD(4);
        NpcName name;           //0x04
        D3DVECTOR pos;          //0x38
        D3DVECTOR dir;          //0x44
        D3DVECTOR up;           //0x50
        ULONG id;               //0x5C
        UINT8 type;             //0x60
        PAD(1);
        UINT16 typeId;          //0x62
        PAD(200);
        // 0x12C
    };
    #pragma pack(pop)
}
