/*
 * File: z_molly_npc.c
 * Overlay: ovl_Molly_npc
 * Description: Molly NPC - Undead Girl
 */

#include "z_molly_npc.h"
#include "assets/objects/object_molly_npc/object_molly_npc.h"

// Makes it Z target-able: (ACTOR_FLAG_0)
#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_3 | ACTOR_FLAG_4 | ACTOR_FLAG_5)

void MollyNpc_Init(Actor* thisx, PlayState* play);
void MollyNpc_Destroy(Actor* thisx, PlayState* play);
void MollyNpc_Update(Actor* thisx, PlayState* play);
void MollyNpc_Draw(Actor* thisx, PlayState* play);

u16 MollyNpc_GetNextTextId(PlayState* play, Actor* thisx);
s16 MollyNpc_UpdateTalkState(PlayState* play, Actor* thisx);

ActorInit Molly_npc_InitVars = {
    /**/ ACTOR_MOLLY_NPC,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MOLLY_NPC,
    /**/ sizeof(MollyNpc),
    /**/ (ActorFunc)MollyNpc_Init,
    /**/ (ActorFunc)MollyNpc_Destroy,
    /**/ (ActorFunc)MollyNpc_Update,
    /**/ (ActorFunc)MollyNpc_Draw,
};

typedef enum {
    NPCTEST_MESSAGE_WHAT = 0x71B9,
    NPCTEST_MESSAGE_COMING_BACK = 0x71C0,
    NPCTEST_MESSAGE_EXPLAINS = 0x71C1,
    NPCTEST_MESSAGE_UNSURE = 0x71C2,
    NPCTEST_MESSAGE_CURIOUS = 0x71C3,
} MollyNpcMessageId;

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

s32 MollyNpc_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx, Gfx** gfx) {
    MollyNpc* this = (MollyNpc*)thisx;

    switch (limbIndex) {
        case GMOLLYNPCSKEL_HEAD_LIMB: // Head
            rot->y += this->headYRotation;
            break;
        case GMOLLYNPCSKEL_MIDDLE_BACK_LIMB: // Torso
            rot->y += this->upperBodyYRotation;
            break;
    }

    return false;
}

void MollyNpc_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    static Vec3f sMultVec = { 800.0f, 500.0f, 0.0f };
    MollyNpc* this = (MollyNpc*)thisx;

    if (limbIndex == GMOLLYNPCSKEL_MIDDLE_BACK_LIMB) { // Torso
        Matrix_MultVec3f(&sMultVec, &this->actor.focus.pos);
    }
}

void MollyNpc_Init(Actor* thisx, PlayState* play) {
    MollyNpc* this = (MollyNpc*)thisx;

    ActorShape_Init(&thisx->shape, 0.0f, NULL, 0.0f);
    Actor_SetFocus(thisx, 80.0f);

    SkelAnime_InitFlex(play, &this->skelAnime, &gMollyNpcSkel, &gMollyNpcIdleAnim, this->jointTable, this->morphTable, GMOLLYNPCSKEL_NUM_LIMBS);

    Animation_Change(&this->skelAnime, &gMollyNpcIdleAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gMollyNpcIdleAnim), ANIMMODE_LOOP, 0.0f);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);

    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);
}

void MollyNpc_Destroy(Actor* thisx, PlayState* play) {
    MollyNpc* this = (MollyNpc*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void MollyNpc_Update(Actor* thisx, PlayState* play) {
    MollyNpc* this = (MollyNpc*)thisx;

    SkelAnime_Update(&this->skelAnime);
    Npc_UpdateTalking(
        play,
        &this->actor,
        &this->interactInfo.talkState,
        50.0f,
        MollyNpc_GetNextTextId,
        MollyNpc_UpdateTalkState
    );
    
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider);
}

void MollyNpc_Draw(Actor* thisx, PlayState* play) {
    MollyNpc* this = (MollyNpc*)thisx;
    static Vec3f D_80AE494C = { 300.0f, 0.0f, 0.0f };
    static Vec3f sShadowScale = { 0.25f, 0.25f, 0.25f };
    Vec3f thisPos = thisx->world.pos;
    GfxPrint printer;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->alpha);
    gSPSegment(POLY_OPA_DISP++, 8, &D_80116280[2]);
    POLY_OPA_DISP =
        SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                            MollyNpc_OverrideLimbDraw, MollyNpc_PostLimbDraw, this, POLY_OPA_DISP);

    // CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    // OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    // gfx = POLY_OPA_DISP + 1;
    // gSPDisplayList(OVERLAY_DISP++, gfx);

    // GfxPrint_Init(&printer);
    // GfxPrint_Open(&printer, gfx);

    // GfxPrint_SetColor(&printer, 255, 0, 255, 255);
    // GfxPrint_SetPos(&printer, 10, 10);
    // GfxPrint_Printf(&printer, "Molly_npc Loaded");

    // gfx = GfxPrint_Close(&printer);
    // GfxPrint_Destroy(&printer);

    // gSPEndDisplayList(gfx++);
    // gSPBranchList(POLY_OPA_DISP, gfx);
    // POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

}

u16 MollyNpc_GetNextTextId(PlayState* play, Actor* thisx) {
    if (GET_INFTABLE(INFTABLE_E0)) {
        return NPCTEST_MESSAGE_CURIOUS;
    } else {
        return NPCTEST_MESSAGE_WHAT;
    }
}

s16 MollyNpc_UpdateTalkState(PlayState* play, Actor* thisx) {
    s16 talkState = NPC_TALK_STATE_TALKING;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            if (Message_ShouldAdvance(play)) {
                // Set the next text ID based on the player's choice
                thisx->textId = play->msgCtx.choiceIndex == 0 ? NPCTEST_MESSAGE_EXPLAINS : NPCTEST_MESSAGE_UNSURE;
                // Continue the dialogue with the new text ID
                Message_ContinueTextbox(play, thisx->textId);
            }
            break;
        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                // Handle the next part of the dialogue based on the current text ID
                switch (thisx->textId) {
                    case NPCTEST_MESSAGE_WHAT:
                        // Advance message 1 to message 2
                        thisx->textId = NPCTEST_MESSAGE_COMING_BACK;
                        Message_ContinueTextbox(play, thisx->textId);
                        break;
                    case NPCTEST_MESSAGE_UNSURE:
                    case NPCTEST_MESSAGE_EXPLAINS:
                        // Mark the appropriate inftable entry and end the dialogue
                        SET_INFTABLE(INFTABLE_E0);
                        talkState = NPC_TALK_STATE_IDLE;
                        break;
                    case NPCTEST_MESSAGE_CURIOUS:
                        // Just end the dialogue
                        talkState = NPC_TALK_STATE_IDLE;
                        break;
                }
            }
            break;
    }
    return talkState;
}
