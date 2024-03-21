/*
 * File: z_en_dekustickrefill.c
 * Overlay: ovl_En_Dekustickrefill
 * Description: Custom Actor - Deku stick refill
 */

#include "z_en_dekustickrefill.h"
#include "assets/objects/object_dekubaba/object_dekubaba.h"

#define FLAGS (0)

void En_Dekustickrefill_Init(Actor* thisx, PlayState* play);
void En_Dekustickrefill_Destroy(Actor* thisx, PlayState* play);
void En_Dekustickrefill_Update(Actor* thisx, PlayState* play);
void En_Dekustickrefill_Draw(Actor* thisx, PlayState* play);
void En_Dekustickrefill_DeadStickDrop(En_Dekustickrefill* this, PlayState* play);

void En_Dekustickrefill_DoNothing(En_Dekustickrefill* this, PlayState* play);

ActorInit En_Dekustickrefill_InitVars = {
    ACTOR_EN_DEKUSTICKREFILL,
    ACTORCAT_MISC,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(En_Dekustickrefill),
    (ActorFunc)En_Dekustickrefill_Init,
    (ActorFunc)En_Dekustickrefill_Destroy,
    (ActorFunc)En_Dekustickrefill_Update,
    (ActorFunc)En_Dekustickrefill_Draw,
};

void En_Dekustickrefill_Init(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 22.0f);
    this->stickAvailable = true;
    this->timer = -1;
    this->stickScale = 0;
    this->baseHeightAdjustment = 0.0f;
    En_Dekustickrefill_SetupDeadStickDrop(this, play);
}

void En_Dekustickrefill_Destroy(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;
}

void En_Dekustickrefill_DeadStickDrop(En_Dekustickrefill* this, PlayState* play) {
    // Decrement the timer if it's greater than 0.
    if (this->timer > 0) {
        this->timer--;
    }

    // If the timer has run out, reset the collection state and make the item available again.
    if (this->timer == 0 && !this->stickAvailable) {
        this->stickAvailable = true;
        this->collected = false; // Reset the collected state to allow for re-collection.
    }

    // Offer the stick to Link if it's available and has not yet been collected.
    if (this->stickAvailable && !this->collected) {
        if (!Actor_HasParent(&this->actor, play)) {
            Actor_OfferGetItem(&this->actor, play, GI_DEKU_STICKS_1, 30.0f, 50.0f);
        } else {
            // Mark as collected to prevent multiple collections.
            this->collected = true;
            this->stickAvailable = false;
            this->timer = 40; // Start the timer for the stick to reappear.
            this->actor.parent = NULL; // Ensure the parent is cleared after collection.
            this->stickScale = 0.0f;
            this->baseHeightAdjustment = 0.0f;
        }
    }
}

void En_Dekustickrefill_SetupDeadStickDrop(En_Dekustickrefill* this, PlayState* play) {
    this->actor.shape.yOffset = 1000.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.shape.shadowScale = 3.0f;
    this->actionFunc = En_Dekustickrefill_DeadStickDrop;
}

void En_Dekustickrefill_Update(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;

    // If the stick is available and not fully grown, increase its scale
    if (this->stickAvailable && this->stickScale < 0.03f) {
        this->stickScale += 0.003f; // Adjust this value as needed for smooth growth
        if (this->stickScale > 0.03f) {
            this->stickScale = 0.03f; // Clamp the scale to the maximum value
        }
    }

    if (this->stickAvailable) {
        if (this->baseHeightAdjustment < 30.0f) {
            this->baseHeightAdjustment += 3.0f;
            if (this->baseHeightAdjustment > 30.0f) {
                this->baseHeightAdjustment = 30.0f;
            }
        }
    }

    this->actionFunc(this, play);
}

void En_Dekustickrefill_Draw(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    // Set the scale for the leaves
    Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, MTXMODE_NEW);
    Matrix_RotateY(BINANG_TO_RAD(this->actor.home.rot.y), MTXMODE_APPLY);
    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY); 
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gDekuBabaBaseLeavesDL);

    // Only draw the stick if it is currently available
    if (this->stickAvailable) {

        // Reset the matrix before drawing the stick
        Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y + this->baseHeightAdjustment, this->actor.home.pos.z, MTXMODE_NEW);
        Matrix_RotateY(BINANG_TO_RAD(this->actor.home.rot.y), MTXMODE_APPLY);

        // Apply scaling - since the base is already adjusted to ground level, the stick grows upwards from there.
        Matrix_Scale(this->stickScale, this->stickScale, this->stickScale, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gDekuBabaStickDropDL);
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void En_Dekustickrefill_DoNothing(En_Dekustickrefill* this, PlayState* play) {

}
