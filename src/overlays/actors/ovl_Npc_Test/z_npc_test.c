/*
 * File: z_npc_test.c
 * Overlay: ovl_Npc_Test
 * Description: Test NPC
 */

#include "z_npc_test.h"
#include "assets/objects/object_rd/object_rd.h"

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
    /**/ OBJECT_RD,
    /**/ sizeof(NpcTest),
    /**/ (ActorFunc)NpcTest_Init,
    /**/ (ActorFunc)NpcTest_Destroy,
    /**/ (ActorFunc)NpcTest_Update,
    /**/ (ActorFunc)NpcTest_Draw,
};

typedef enum {
    NPCTEST_MESSAGE_STORY_1 = 0x71B3,
    NPCTEST_MESSAGE_STORY_2 = 0x71B4,
    NPCTEST_MESSAGE_STORY_3 = 0x71B5,
    NPCTEST_MESSAGE_JERK = 0x71B6,
    NPCTEST_MESSAGE_END = 0x71B7,
    NPCTEST_MESSAGE_GO_AWAY = 0x71B8
} NpcTestMessageId;

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

s32 NpcTest_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx, Gfx** gfx) {
    NpcTest* this = (NpcTest*)thisx;

    if (limbIndex == REDEAD_GIBDO_LIMB_HEAD_ROOT) {
        rot->y += this->headYRotation;
    } else if (limbIndex == REDEAD_GIBDO_LIMB_UPPER_BODY_ROOT) {
        rot->y += this->upperBodyYRotation;
    }

    return false;
}

void NpcTest_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    Vec3f D_80AE4940 = { 300.0f, 0.0f, 0.0f };
    NpcTest* this = (NpcTest*)thisx;
    s32 idx = -1;
    Vec3f destPos;

    switch (limbIndex) {
        case REDEAD_GIBDO_LIMB_HEAD:
            idx = 0;
            break;

        case REDEAD_GIBDO_LIMB_ROOT:
            idx = 1;
            break;

        case REDEAD_GIBDO_LIMB_RIGHT_HAND:
            idx = 2;
            break;

        case REDEAD_GIBDO_LIMB_LEFT_HAND:
            idx = 3;
            break;

        case REDEAD_GIBDO_LIMB_TORSO:
            idx = 4;
            break;

        case REDEAD_GIBDO_LIMB_PELVIS:
            idx = 5;
            break;

        case REDEAD_GIBDO_LIMB_RIGHT_SHIN:
            idx = 6;
            break;

        case REDEAD_GIBDO_LIMB_LEFT_SHIN:
            idx = 7;
            break;

        case REDEAD_GIBDO_LIMB_RIGHT_FOOT:
            idx = 8;
            break;

        case REDEAD_GIBDO_LIMB_LEFT_FOOT:
            idx = 9;
            break;
    }
}

void NpcTest_Init(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;

    ActorShape_Init(&thisx->shape, 0.0f, NULL, 0.0f);
    Actor_SetFocus(thisx, 72.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gGibdoSkel, &gGibdoSkelGgibdoredeadpeaceoutanimAnim, this->jointTable, this->morphTable, REDEAD_GIBDO_LIMB_MAX);
    Animation_Change(&this->skelAnime, &gGibdoSkelGgibdoredeadpeaceoutanimAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGibdoSkelGgibdoredeadpeaceoutanimAnim), ANIMMODE_LOOP, 0.0f);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);

    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);
}

void NpcTest_Destroy(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void NpcTest_Update(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;

    SkelAnime_Update(&this->skelAnime);
    Npc_UpdateTalking(
        play,
        &this->actor,
        &this->interactInfo.talkState,
        50.0f,
        NpcTest_GetNextTextId,
        NpcTest_UpdateTalkState
    );
    
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider);
}

void NpcTest_Draw(Actor* thisx, PlayState* play) {
    NpcTest* this = (NpcTest*)thisx;
    static Vec3f D_80AE494C = { 300.0f, 0.0f, 0.0f };
    static Vec3f sShadowScale = { 0.25f, 0.25f, 0.25f };
    Vec3f thisPos = thisx->world.pos;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->alpha);
    gSPSegment(POLY_OPA_DISP++, 8, &D_80116280[2]);
    POLY_OPA_DISP =
        SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                            NpcTest_OverrideLimbDraw, NpcTest_PostLimbDraw, this, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

}

u16 NpcTest_GetNextTextId(PlayState* play, Actor* thisx) {
    if (GET_INFTABLE(INFTABLE_F4)) {
        return NPCTEST_MESSAGE_GO_AWAY;
    } else {
        return NPCTEST_MESSAGE_STORY_1;
    }
}

s16 NpcTest_UpdateTalkState(PlayState* play, Actor* thisx) {
    s16 talkState = NPC_TALK_STATE_TALKING;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            if (Message_ShouldAdvance(play)) {
                // Set the next text ID based on the player's choice
                thisx->textId = play->msgCtx.choiceIndex == 0 ? NPCTEST_MESSAGE_END : NPCTEST_MESSAGE_JERK;
                // Continue the dialogue with the new text ID
                Message_ContinueTextbox(play, thisx->textId);
            }
            break;
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                // Handle the next part of the dialogue based on the current text ID
                switch (thisx->textId) {
                    case NPCTEST_MESSAGE_STORY_1:
                        // Advance message 1 to message 2
                        thisx->textId = NPCTEST_MESSAGE_STORY_2;
                        Message_ContinueTextbox(play, thisx->textId);
                        break;
                    case NPCTEST_MESSAGE_STORY_2:
                        // Advance message 2 to message 3
                        thisx->textId = NPCTEST_MESSAGE_STORY_3;
                        Message_ContinueTextbox(play, thisx->textId);
                        break;
                    case NPCTEST_MESSAGE_JERK:
                    case NPCTEST_MESSAGE_END:
                        // Mark the appropriate infotable entry and end the dialogue
                        SET_INFTABLE(INFTABLE_F4);
                        talkState = NPC_TALK_STATE_IDLE;
                        break;
                    case NPCTEST_MESSAGE_GO_AWAY:
                        // Just end the dialogue
                        talkState = NPC_TALK_STATE_IDLE;
                        break;
                }
            }
            break;
    }
    return talkState;
}
