/*
 * File: z_npc_test.c
 * Overlay: ovl_Npc_Test
 * Description: Test NPC
 */

#include "z_npc_test.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

// Makes it Z target-able (ACTOR_FLAG_0)
#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_3 | ACTOR_FLAG_4 | ACTOR_FLAG_5)

void NpcTest_Init(Actor* thisx, PlayState* play);
void NpcTest_Destroy(Actor* thisx, PlayState* play);
void NpcTest_Update(Actor* thisx, PlayState* play);
void NpcTest_Draw(Actor* thisx, PlayState* play);

u16 NpcTest_GetNextTextId(PlayState* play, Actor* thisx);
s16 NpcTest_UpdateTalkState(PlayState* play, Actor* thisx);

ActorInit Npc_Test_InitVars = {
    /**/ ACTOR_NPC_TEST,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_GAMEPLAY_KEEP,
    /**/ sizeof(NpcTest),
    /**/ (ActorFunc)NpcTest_Init,
    /**/ (ActorFunc)NpcTest_Destroy,
    /**/ (ActorFunc)NpcTest_Update,
    /**/ (ActorFunc)NpcTest_Draw,
};

typedef enum {
    NPCTEST_MESSAGE_1 = 0x71B3,
    NPCTEST_MESSAGE_2 = 0x71B4,
    NPCTEST_MESSAGE_3 = 0x71B5,
    NPCTEST_MESSAGE_4 = 0x71B6,
    NPCTEST_MESSAGE_5 = 0x71B7
} NpcTestMessageId;

void NpcTest_Init(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;

}

void NpcTest_Destroy(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;

}

void NpcTest_Update(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;
    
    Npc_UpdateTalking(
        play,
        &this->actor,
        &this->interactInfo.talkState,
        50.0f,
        NpcTest_GetNextTextId,
        NpcTest_UpdateTalkState
    );
}

void NpcTest_Draw(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;

    Gfx_DrawDListOpa(play, gBombchuDL);
}

u16 NpcTest_GetNextTextId(PlayState* play, Actor* thisx) {
    return NPCTEST_MESSAGE_1;
}

s16 NpcTest_UpdateTalkState(PlayState* play, Actor* thisx) {
    return NPC_TALK_STATE_IDLE;
}