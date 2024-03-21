/*
 * File: z_en_aevumtulip.c
 * Overlay: ovl_En_Aevumtulip
 * Description: Custom Actor
 */

#include "z_en_aevumtulip.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (0)

void En_Aevumtulip_Init(Actor* thisx, PlayState* play);
void En_Aevumtulip_Destroy(Actor* thisx, PlayState* play);
void En_Aevumtulip_Update(Actor* thisx, PlayState* play);
void En_Aevumtulip_Draw(Actor* thisx, PlayState* play);

void En_Aevumtulip_DrawCollectible(En_Aevumtulip* this, PlayState* play);
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

    this->itemDropped = 0;
    this->collected = 0;

    this->actionFunc = En_Aevumtulip_DoNothing;
}

void En_Aevumtulip_Destroy(Actor* thisx, PlayState* play) {
    En_Aevumtulip* this = (En_Aevumtulip*)thisx;
}

void En_Aevumtulip_Update(Actor* thisx, PlayState* play) {
    En_Aevumtulip* this = (En_Aevumtulip*)thisx;
    Player* player = GET_PLAYER(play);

    Lights_PointGlowSetInfo(&this->lightInfoGlow, this->actor.world.pos.x, this->actor.world.pos.y + 25.0f,
                            this->actor.world.pos.z, 135, 206, 250, 100);
    Lights_PointNoGlowSetInfo(&this->lightInfoNoGlow, this->actor.world.pos.x, this->actor.world.pos.y + 25.0f,
                              this->actor.world.pos.z, 135, 206, 250, 100);

    if (this->actor.xzDistToPlayer < 50.0f && !this->collected) {
        if (!Actor_HasParent(&this->actor, play)) {
            Actor_OfferGetItem(&this->actor, play, GI_AEVUMTULIP, 30.0f, 50.0f);
        } else {
            if (!this->collected) {
                this->collected = 1;

                // Only initialize the despawn timer if the item has been collected before
                if (GET_INFTABLE(INFTABLE_10F)) {
                    this->despawnTimer = 25;
                    Audio_PlaySfxGeneral(NA_SE_SY_GET_ITEM, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                }
            }
        }
    }

    // Only apply the "jumping above the head" effect if the INFTABLE flag is set (item has been collected before)
    if (this->collected && GET_INFTABLE(INFTABLE_10F)) {
        this->actor.draw = En_Aevumtulip_DrawCollectible;
        Actor_SetScale(&this->actor, 0.040 - 1e-10);

        if (this->despawnTimer > 0) {
            this->actor.world.pos = player->actor.world.pos;
            this->actor.world.pos.y += 40.0f + Math_SinS(this->despawnTimer * 15000) * (this->despawnTimer * 0.3f);
            if (LINK_IS_ADULT) this->actor.world.pos.y += 20.0f;
            this->despawnTimer--;
        } else {
            Actor_Kill(&this->actor);
            if (this->lightNodeGlow != NULL) {
                LightContext_RemoveLight(play, &play->lightCtx, this->lightNodeGlow);
                this->lightNodeGlow = NULL;
            }
            if (this->lightNodeNoGlow != NULL) {
                LightContext_RemoveLight(play, &play->lightCtx, this->lightNodeNoGlow);
                this->lightNodeNoGlow = NULL;
            }
        }
    }

    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }
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

void En_Aevumtulip_DrawCollectible(En_Aevumtulip* this, PlayState* play) {
    s32 texIndex = this->actor.params - 3;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);

    POLY_OPA_DISP = Gfx_SetupDL_66(POLY_OPA_DISP);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(gDropAevumTulipTex));

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
            G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, gItemDropDL);  

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void En_Aevumtulip_DoNothing(En_Aevumtulip* this, PlayState* play) {

}

