/*
 * File: z_en_spectral_fist.c
 * Overlay: ovl_En_Spectral_Fist
 * Description: Custom Actor
 */

#include "z_en_spectral_fist.h"
#include "assets/objects/object_en_spectral_fist/object_en_spectral_fist.h"

#define FLAGS (0)

void En_Spectral_Fist_Init(Actor* thisx, PlayState* play);
void En_Spectral_Fist_Destroy(Actor* thisx, PlayState* play);
void En_Spectral_Fist_Update(Actor* thisx, PlayState* play);
void En_Spectral_Fist_Draw(Actor* thisx, PlayState* play);

void En_Spectral_Fist_DoNothing(En_Spectral_Fist* this, PlayState* play);
void En_Spectral_Fist_Still(En_Spectral_Fist* this, PlayState* play);
void En_Spectral_DownPunch(En_Spectral_Fist* this, PlayState* play);

ActorInit En_Spectral_Fist_InitVars = {
    ACTOR_EN_SPECTRAL_FIST,
    ACTORCAT_EXPLOSIVE,
    FLAGS,
    OBJECT_EN_SPECTRAL_FIST,
    sizeof(En_Spectral_Fist),
    (ActorFunc)En_Spectral_Fist_Init,
    (ActorFunc)En_Spectral_Fist_Destroy,
    (ActorFunc)En_Spectral_Fist_Update,
    (ActorFunc)En_Spectral_Fist_Draw,
};

// Needa turn this into a quad, I think, so TOUCH_NEAREST can be used.

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000100, 0x00, 0x01 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { 55, 70, 0, { 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 0, 12, 60, MASS_IMMOVABLE };

void En_Spectral_Fist_Init(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;

    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 50.0f);

    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | 
                    UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);

    SkelAnime_Init(play, &this->skelAnime, &gSpectralFistSkel, &gSpectralFistStillAnim, 
                    this->jointTable, this->morphTable, GSPECTRALFISTSKEL_NUM_LIMBS);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);
    CollisionCheck_SetInfo(&thisx->colChkInfo, NULL, &sColChkInfoInit);

    En_Spectral_Fist_SetupStill(this, play);
}

void En_Spectral_Fist_Destroy(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void En_Spectral_Fist_SetupStill(En_Spectral_Fist* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gSpectralFistStillAnim, -1.0f);
    this->actionFunc = En_Spectral_Fist_Still;
}

void En_Spectral_Fist_SetupDownPunch(En_Spectral_Fist* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gSpectralFistStillAnim, -1.0f);
    this->actionFunc = En_Spectral_DownPunch;
    this->attackPhase = FIST_CHARGING; // Start with charging
    this->attackTimer = 8; // Example: 20 frames to charge
}

void En_Spectral_Fist_Still(En_Spectral_Fist* this, PlayState* play) {
    // If not already in the idle animation, switch to it.
    if (this->skelAnime.animation != &gSpectralFistStillAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gSpectralFistStillAnim, 0.0f);
    }
}

void En_Spectral_DownPunch(En_Spectral_Fist* this, PlayState* play) {
    // Switch to idle animation if not already in it.
    if (this->skelAnime.animation != &gSpectralFistStillAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gSpectralFistStillAnim, -5.0f);
    }

    // Movement and phase logic specific to the down punch action.
    switch (this->attackPhase) {
        case FIST_CHARGING:
            // Move the actor up to prepare for the down punch.
            this->actor.world.pos.y += 4.0f; // Move up at a constant rate.
            if (--this->attackTimer <= 0) {
                this->attackPhase = FIST_ATTACKING; // Transition to attacking phase.
                this->attackTimer = 10; // Set the timer for the attack duration if needed.
            }
            break;
        case FIST_ATTACKING:
            // Execute the down punch.
            this->actor.world.pos.y -= 50.0f; // Move down rapidly to simulate the punch.
            // Setting damage flags and damage value should now be moved to the update function or handled prior to this logic.
            break;
        // No need to handle FIST_COOLDOWN here as it's managed in the update function.
    }
}



void En_Spectral_Fist_Update(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;
    Player* player = GET_PLAYER(play);

    static Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    SkelAnime_Update(&this->skelAnime);

    // Handle collision with an enemy or object, including the boulder.
    if (this->collider.base.atFlags & AT_HIT && this->attackPhase == FIST_ATTACKING) {
        this->collider.base.atFlags &= ~AT_HIT; // Clear the collision flag for future collisions.
        this->attackPhase = FIST_COOLDOWN; // Switch to cooldown phase.
        this->attackTimer = 5; // Set cooldown timer.
        player->spectralDownPunch = 0; // Reset player's punch state.

        // Immediately adjust the position to prevent indefinite floating.
        // Consider resetting to a specific position or using a different logic based on your game design.
        this->actor.world.pos.y = player->actor.world.pos.y + 120.0f; // Example reset position
    }

    // Automatically transition from cooldown back to ready to punch, and reset position.
    if (this->attackPhase == FIST_COOLDOWN && --this->attackTimer <= 0) {
        En_Spectral_Fist_SetupStill(this, play);
        // Reset the spectral fist's position here if not done above.
    }

    // Check for collision with the ground.
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        this->newYPosition = this->actor.floorHeight; // Adjust the Y position to the ground level.
        this->attackPhase = FIST_COOLDOWN; // Move to cooldown phase.
        this->attackTimer = 5; // Set cooldown timer.
        player->spectralDownPunch = 0; // Reset player's punch state.

        Vec3f fistPunchPos = {this->actor.world.pos.x, this->newYPosition, this->actor.world.pos.z};
        EffectSsBlast_SpawnWhiteShockwave(play, &fistPunchPos, &zeroVec, &zeroVec); // Visual effect for hitting the ground.
        Sfx_PlaySfxCentered(NA_SE_IT_HAMMER_HIT); // Sound effect for hitting the ground.

        this->actor.world.pos.y = player->actor.world.pos.y + 120.0f; // Example reset position
        En_Spectral_Fist_SetupStill(this, play);
    }

    if (player->spectralDownPunch && this->actionFunc != En_Spectral_DownPunch) {
        En_Spectral_Fist_SetupDownPunch(this, play);
        // Do not reset player->spectralDownPunch here to allow the action to complete.
    }

    // Call the current action function.
    this->actionFunc(this, play);

    // Conditionally update position only if not attacking.
    if (this->actionFunc != En_Spectral_DownPunch) {
        Vec3f relativePos; // Relative position of the Spectral Fist in front of the player
        f32 angleRadians;

        // Initialize relative position in front of the player.
        relativePos.x = 0.0f;
        relativePos.y = 120.0f;
        relativePos.z = 50.0f;

        // Convert player's yaw rotation to radians for trigonometric calculations.
        angleRadians = (player->actor.shape.rot.y / (f32)0x8000) * M_PI;

        // Calculate new position based on player's rotation.
        this->actor.world.pos.x = player->actor.world.pos.x + relativePos.z * sinf(angleRadians);
        this->actor.world.pos.y = player->actor.world.pos.y + relativePos.y;
        this->actor.world.pos.z = player->actor.world.pos.z + relativePos.z * cosf(angleRadians);

        // Ensure the actor faces the same direction as the player.
        this->actor.shape.rot.y = player->actor.shape.rot.y;
    }

    this->collider.dim.pos.x = (f32)this->actor.world.pos.x;
    this->collider.dim.pos.y = (f32)this->actor.world.pos.y;
    this->collider.dim.pos.z = (f32)this->actor.world.pos.z;

    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, 
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | 
                                UPDBGCHECKINFO_FLAG_4);
    if (this->attackPhase == FIST_ATTACKING) {
        // Set the punch to act like a hammer swing.
        this->collider.info.toucher.dmgFlags |= DMG_HAMMER_SWING;
        this->collider.info.toucher.damage = 2; // Ensure this is the desired damage level.
        
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base); // Reactivate the attack collider for the next attack.
    }
}

s32 En_Spectral_Fist_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;
    return 0; 
}

void En_Spectral_Fist_Draw(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;
    GfxPrint printer;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    // gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->alpha);
    gSPSegment(POLY_OPA_DISP++, 8, &D_80116280[2]);
    POLY_OPA_DISP =
        SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                            En_Spectral_Fist_OverrideLimbDraw, NULL, this, POLY_OPA_DISP);


    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void En_Spectral_Fist_DoNothing(En_Spectral_Fist* this, PlayState* play) {

}
