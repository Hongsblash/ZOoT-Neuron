/*
 * File: z_en_aevumtulip.c
 * Overlay: ovl_En_Aevumtulip
 * Description: Custom Actor
 */

#include "z_en_aevumtulip.h"

#define FLAGS (0)

void En_Aevumtulip_Init(Actor* thisx, PlayState* play);
void En_Aevumtulip_Destroy(Actor* thisx, PlayState* play);
void En_Aevumtulip_Update(Actor* thisx, PlayState* play);
void En_Aevumtulip_Draw(Actor* thisx, PlayState* play);

void En_Aevumtulip_DoNothing(En_Aevumtulip* this, PlayState* play);

ActorInit En_Aevumtulip_InitVars = {
    ACTOR_EN_AEVUMTULIP,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_EN_AEVUMTULIP,
    sizeof(En_Aevumtulip),
    (ActorFunc)En_Aevumtulip_Init,
    (ActorFunc)En_Aevumtulip_Destroy,
    (ActorFunc)En_Aevumtulip_Update,
    (ActorFunc)En_Aevumtulip_Draw,
};

void En_Aevumtulip_Init(Actor* thisx, PlayState* play) {
    En_Aevumtulip* this = (En_Aevumtulip*)thisx;

    ActorShape_Init(&thisx->shape, 700.0f, ActorShadow_DrawCircle, 16.0f);

    Lights_PointGlowSetInfo(&this->lightInfoGlow, thisx->world.pos.x, thisx->world.pos.y + 25.0f, thisx->world.pos.z, 255, 255,
                            255, 0);
    this->lightNodeGlow = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfoGlow);

    Lights_PointNoGlowSetInfo(&this->lightInfoNoGlow, thisx->world.pos.x, thisx->world.pos.y + 25.0f, thisx->world.pos.z, 255,
                              255, 255, 0);
    this->lightNodeNoGlow = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfoNoGlow);

    this->actionFunc = En_Aevumtulip_DoNothing;
}

void En_Aevumtulip_Destroy(Actor* thisx, PlayState* play) {
    En_Aevumtulip* this = (En_Aevumtulip*)thisx;
}

void En_Aevumtulip_Update(Actor* thisx, PlayState* play) {
    En_Aevumtulip* this = (En_Aevumtulip*)thisx;

    Lights_PointGlowSetInfo(&this->lightInfoGlow, this->actor.world.pos.x, this->actor.world.pos.y + 25.0f,
                            this->actor.world.pos.z,  135, 206, 250, 100); // Custom values

    // Actor_OfferGetItemNearby(&this->actor, play, GI_NAYRUS_LOVE);
    Actor_OfferGetItem(&this->actor, play, GI_NAYRUS_LOVE, 30.0f, 50.0f);

    if (Actor_HasParent(&this->actor, play)) {
        Actor_Kill(&this->actor);

        // Remove the glow light node
        if (this->lightNodeGlow != NULL) {
            LightContext_RemoveLight(play, &play->lightCtx, this->lightNodeGlow);
            this->lightNodeGlow = NULL;
        }

        // Remove the no-glow light node, if you also want to remove it
        if (this->lightNodeNoGlow != NULL) {
            LightContext_RemoveLight(play, &play->lightCtx, this->lightNodeNoGlow);
            this->lightNodeNoGlow = NULL;
        }
        return;
    }

    this->actionFunc(this, play);
}

void En_Aevumtulip_Draw(Actor* thisx, PlayState* play) {
    En_Aevumtulip* this = (En_Aevumtulip*)thisx;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    func_8002EBCC(thisx, play, 0);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gAevumTulipDL);
    Matrix_RotateZYX(0x4000, 0, 0, MTXMODE_APPLY);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void En_Aevumtulip_DoNothing(En_Aevumtulip* this, PlayState* play) {

}
