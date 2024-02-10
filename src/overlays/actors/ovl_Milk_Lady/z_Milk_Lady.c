/*
 * File: z_Milk_Lady.c
 * Overlay: ovl_Milk_Lady
 * Description: Milk Lady
 */

#include "z_Milk_Lady.h"
#include "assets/objects/object_milk_lady/object_milk_lady.h"

// Makes it Z target-able (ACTOR_FLAG_0)
#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_3 | ACTOR_FLAG_4 | ACTOR_FLAG_5)

void MilkLady_Init(Actor* thisx, PlayState* play);
void MilkLady_Destroy(Actor* thisx, PlayState* play);
void MilkLady_Update(Actor* thisx, PlayState* play);
void MilkLady_Draw(Actor* thisx, PlayState* play);

u16 MilkLady_GetNextTextId(PlayState* play, Actor* thisx);
s16 MilkLady_UpdateTalkState(PlayState* play, Actor* thisx);

ActorInit Milk_Lady_InitVars = {
    /**/ ACTOR_MILK_LADY,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MILK_LADY,
    /**/ sizeof(MilkLady),
    /**/ (ActorFunc)MilkLady_Init,
    /**/ (ActorFunc)MilkLady_Destroy,
    /**/ (ActorFunc)MilkLady_Update,
    /**/ (ActorFunc)MilkLady_Draw,
};

typedef enum {
    MILKLADY_MESSAGE_STORY_1 = 0x71B3,
    MILKLADY_MESSAGE_STORY_2 = 0x71B4,
    MILKLADY_MESSAGE_STORY_3 = 0x71B5,
    MILKLADY_MESSAGE_JERK = 0x71B6,
    MILKLADY_MESSAGE_END = 0x71B7,
    MILKLADY_MESSAGE_GO_AWAY = 0x71B8
} MilkLadyMessageId;

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

s32 MilkLady_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx, Gfx** gfx) {
    MilkLady* this = (MilkLady*)thisx;

    if (limbIndex == GMILKLADYSKEL_HEAD_LIMB) {
        rot->y += this->headYRotation;
    } else if (limbIndex == GMILKLADYSKEL_MIDDLE_BACK_LIMB) {
        rot->y += this->upperBodyYRotation;
    }

    return false;
}

void MilkLady_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    MilkLady* this = (MilkLady*)thisx;

    if (limbIndex == GMILKLADYSKEL_HAND_L_LIMB) {
        Vec3f src = { 0.0f, 10.0f, 0.0f };
        Vec3f dest;

        Matrix_MultVec3f(&src, &dest);
        this->actor.focus.pos.x = dest.x;
        this->actor.focus.pos.y = dest.y;
        this->actor.focus.pos.z = dest.z;
    }
}

void MilkLady_Init(Actor* thisx, PlayState* play) {
    MilkLady* this = (MilkLady*)thisx;

    Actor_SetScale(&this->actor, 0.08f);
    ActorShape_Init(&thisx->shape, 0.0f, NULL, 0.0f);
    Actor_SetFocus(thisx, 72.0f);

    SkelAnime_InitFlex(play, &this->skelAnime, &gMilkLadySkel, &gMilkLadySkelIdleAnim, this->jointTable, this->morphTable, GMILKLADYSKEL_NUM_LIMBS);

    Animation_Change(&this->skelAnime, &gMilkLadySkelIdleAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gMilkLadySkelIdleAnim), ANIMMODE_LOOP, 0.0f);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);

    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);
}

void MilkLady_Destroy(Actor* thisx, PlayState* play) {
    MilkLady* this = (MilkLady*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void MilkLady_Update(Actor* thisx, PlayState* play) {
    MilkLady* this = (MilkLady*)thisx;

    SkelAnime_Update(&this->skelAnime);
    Npc_UpdateTalking(
        play,
        &this->actor,
        &this->interactInfo.talkState,
        50.0f,
        MilkLady_GetNextTextId,
        MilkLady_UpdateTalkState
    );
    
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider);
}

void MilkLady_Draw(Actor* thisx, PlayState* play) {
    MilkLady* this = (MilkLady*)thisx;
    static Vec3f D_80AE494C = { 300.0f, 0.0f, 0.0f };
    static Vec3f sShadowScale = { 0.25f, 0.25f, 0.25f };
    Vec3f thisPos = thisx->world.pos;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->alpha);
    gSPSegment(POLY_OPA_DISP++, 8, &D_80116280[2]);
    POLY_OPA_DISP =
        SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                            MilkLady_OverrideLimbDraw, MilkLady_PostLimbDraw, this, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

}

u16 MilkLady_GetNextTextId(PlayState* play, Actor* thisx) {
    if (GET_INFTABLE(INFTABLE_F4)) {
        return MILKLADY_MESSAGE_GO_AWAY;
    } else {
        return MILKLADY_MESSAGE_STORY_1;
    }
}

s16 MilkLady_UpdateTalkState(PlayState* play, Actor* thisx) {
    s16 talkState = NPC_TALK_STATE_TALKING;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            if (Message_ShouldAdvance(play)) {
                // Set the next text ID based on the player's choice
                thisx->textId = play->msgCtx.choiceIndex == 0 ? MILKLADY_MESSAGE_END : MILKLADY_MESSAGE_JERK;
                // Continue the dialogue with the new text ID
                Message_ContinueTextbox(play, thisx->textId);
            }
            break;
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                // Handle the next part of the dialogue based on the current text ID
                switch (thisx->textId) {
                    case MILKLADY_MESSAGE_STORY_1:
                        // Advance message 1 to message 2
                        thisx->textId = MILKLADY_MESSAGE_STORY_2;
                        Message_ContinueTextbox(play, thisx->textId);
                        break;
                    case MILKLADY_MESSAGE_STORY_2:
                        // Advance message 2 to message 3
                        thisx->textId = MILKLADY_MESSAGE_STORY_3;
                        Message_ContinueTextbox(play, thisx->textId);
                        break;
                    case MILKLADY_MESSAGE_JERK:
                    case MILKLADY_MESSAGE_END:
                        // Mark the appropriate inftable entry and end the dialogue
                        SET_INFTABLE(INFTABLE_F4);
                        talkState = NPC_TALK_STATE_IDLE;
                        break;
                    case MILKLADY_MESSAGE_GO_AWAY:
                        // Just end the dialogue
                        talkState = NPC_TALK_STATE_IDLE;
                        break;
                }
            }
            break;
    }
    return talkState;
}
