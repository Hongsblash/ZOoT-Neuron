/*
 * File: z_en_dekustickrefill.c
 * Overlay: ovl_En_Dekustickrefill
 * Description: Custom Actor - Deku stick refill
 * Requires OBJECT_DEKUBABA to be loaded in your room's object properties.
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

void En_Dekustickrefill_SetupDeadStickDrop(En_Dekustickrefill* this, PlayState* play) {
    this->actionFunc = En_Dekustickrefill_DeadStickDrop;
}

void En_Dekustickrefill_Init(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 22.0f);

    // Initialise variables
    this->stickAvailable = true; // Available for pick-up upon spawning.
    this->timer = -1; // Initialise timer as invalid value.
    this->stickScale = 0.03f; // Initial scale set as the max used, as we don't want them to start growing upon loading the area.
    this->baseHeightAdjustment = 30.0f; // Initial actor height, same explanation as scale.

    // Set up stick behaviour making it available for pick-up.
    En_Dekustickrefill_SetupDeadStickDrop(this, play);
}

// No colliders are being set/nothing to destroy.
void En_Dekustickrefill_Destroy(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;
}

void En_Dekustickrefill_DeadStickDrop(En_Dekustickrefill* this, PlayState* play) {
    // Decrement the timer if it's greater than 0, for respawning.
    if (this->timer > 0) {
        this->timer--;
    }

    // If the timer has run out, reset the collection state and make the item available again.
    if (this->timer == 0 && !this->stickAvailable) {
        this->stickAvailable = true;
        this->collected = false; // Reset the collected state to allow for re-collection.
    }

    // Offer the stick to Link if it's available and has not yet been collected (he is able to get the item by walking over it).
    if (this->stickAvailable && !this->collected) {
        // Continue to offer item until actor has a parent (once link picks up the item).
        if (!Actor_HasParent(&this->actor, play)) {
            Actor_OfferGetItem(&this->actor, play, GI_DEKU_STICKS_1, 30.0f, 50.0f);
        } else {
            this->collected = true; // Mark as collected to prevent multiple collections.
            this->stickAvailable = false; // Mark as unavailable so the item cannot be offered. 
            this->timer = 200; // Start the timer for the stick to reappear.
            this->actor.parent = NULL; // Ensure the parent is cleared after collection, as the parent will stay set otherwise.
            this->stickScale = 0.0f; // Reset scale to reset the 'growing' effect on respawn.
            this->baseHeightAdjustment = 0.0f; // Reset baseHeightAdjustment to reset the 'growing' effect on respawn.
        }
    }
}

void En_Dekustickrefill_Update(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;

    // If the stick is available and not fully grown, increase its scale.
    // This is to give the illusion of 'growing' upon respawn/becoming available again.
    if (this->stickAvailable && this->stickScale < 0.03f) {
        this->stickScale += 0.003f; // Increase the scale until maximum desired size.
        if (this->stickScale > 0.03f) {
            this->stickScale = 0.03f; // Clamp the scale to the maximum value.
        }
    }

    // If the stick is available and not fully grown increase its height too.
    // This is to stop the stick from appearing as if it's getting larger from the centre, in mid-air.
    if (this->stickAvailable) {
        if (this->baseHeightAdjustment < 30.0f) { // Max height.
            this->baseHeightAdjustment += 3.0f; // Increase until max height.
            if (this->baseHeightAdjustment > 30.0f) {
                this->baseHeightAdjustment = 30.0f; // Clamp the scale to maximum desired height.
            }
        }
    }

    // Run current action function again.
    this->actionFunc(this, play);
}

void En_Dekustickrefill_Draw(Actor* thisx, PlayState* play) {
    En_Dekustickrefill* this = (En_Dekustickrefill*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    // Set the matrix, rotation, scale and display list for the leaves.
    Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z, MTXMODE_NEW);
    Matrix_RotateY(BINANG_TO_RAD(this->actor.home.rot.y), MTXMODE_APPLY);
    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY); 
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gDekuBabaBaseLeavesDL);

    // Only draw the stick if it is currently available
    if (this->stickAvailable) {

        // Reset the matrix before drawing the stick, adjust baseHeightAdjustment to keep the base of the stick on the ground.
        Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y + this->baseHeightAdjustment, this->actor.home.pos.z, MTXMODE_NEW);
        Matrix_RotateY(BINANG_TO_RAD(this->actor.home.rot.y), MTXMODE_APPLY);

        // Apply scaling - since the base is adjusted to ground level, the stick grows upwards from there.
        Matrix_Scale(this->stickScale, this->stickScale, this->stickScale, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gDekuBabaStickDropDL);
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void En_Dekustickrefill_DoNothing(En_Dekustickrefill* this, PlayState* play) {

}
