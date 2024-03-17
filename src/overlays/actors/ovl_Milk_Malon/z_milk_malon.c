/*
 * File: z_milk_malon.c
 * Overlay: ovl_Milk_Malon
 * Description: Milk Malon - Enemy
 */

#include "z_milk_malon.h"
#include "assets/objects/object_milk_malon/object_milk_malon.h"
#include "assets/objects/object_dekunuts/object_dekunuts.h"
#include "src/overlays/effects/ovl_Effect_Ss_Mm_Milk/z_eff_ss_mm_milk.h"
#include "overlays/actors/ovl_En_Fhg_Fire/z_en_fhg_fire.h"
// #include "overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.h"

// Makes it Z target-able: (ACTOR_FLAG_0)
#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4)

void MilkMalon_Init(Actor* thisx, PlayState* play);
void MilkMalon_Destroy(Actor* thisx, PlayState* play);
void MilkMalon_Update(Actor* thisx, PlayState* play);
void MilkMalon_Draw(Actor* thisx, PlayState* play);

void MilkMalon_Idle(MilkMalon* this, PlayState* play);
void MilkMalon_Notice(MilkMalon* this, PlayState* play);
void MilkMalon_StartRunFromNotice(MilkMalon* this, PlayState* play);
void MilkMalon_Run(MilkMalon* this, PlayState* play);
void MilkMalon_EndRun(MilkMalon* this, PlayState* play);
void MilkMalon_Attack(MilkMalon* this, PlayState* play);
void MilkMalon_Damaged(MilkMalon* this, PlayState* play);
void MilkMalon_Stunned(MilkMalon* this, PlayState* play);
void MilkMalon_Die(MilkMalon* this, PlayState* play);
void MilkMalon_StopAndBlock(MilkMalon* this, PlayState* play);
void MilkMalon_JumpBack(MilkMalon* this, PlayState* play);
void MilkMalon_Shoot(MilkMalon* this, PlayState* play);
void MilkMalon_FloatInAir(MilkMalon* this, PlayState* play);
void MilkMalon_ChargeLightBall(MilkMalon* this, PlayState* play);
void MilkMalon_Throw(MilkMalon* this, PlayState* play);
void MilkMalon_Return(MilkMalon* this, PlayState* play);
void MilkMalon_Vulnerable(MilkMalon* this, PlayState* play);

typedef enum {
    MILKMALON_DMGEFF_NONE,
    MILKMALON_DMGEFF_STUN,
    MILKMALON_DMGEFF_DEFAULT,
} MilkMalonDamageEffect;

typedef enum {
    /* 0 */ STUNNED_FALL,
    /* 1 */ STUNNED_GROUND
} MilkMalonStunnedAction;

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, MILKMALON_DMGEFF_STUN),
    /* Deku stick    */ DMG_ENTRY(3, MILKMALON_DMGEFF_DEFAULT),
    /* Slingshot     */ DMG_ENTRY(2, MILKMALON_DMGEFF_DEFAULT),
    /* Explosive     */ DMG_ENTRY(4, MILKMALON_DMGEFF_DEFAULT),
    /* Boomerang     */ DMG_ENTRY(0, MILKMALON_DMGEFF_STUN),
    /* Normal arrow  */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Hammer swing  */ DMG_ENTRY(3, MILKMALON_DMGEFF_DEFAULT),
    /* Hookshot      */ DMG_ENTRY(0, MILKMALON_DMGEFF_STUN),
    /* Kokiri sword  */ DMG_ENTRY(2, MILKMALON_DMGEFF_DEFAULT),
    /* Master sword  */ DMG_ENTRY(3, MILKMALON_DMGEFF_DEFAULT),
    /* Giant's Knife */ DMG_ENTRY(4, MILKMALON_DMGEFF_DEFAULT),
    /* Fire arrow    */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Ice arrow     */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Light arrow   */ DMG_ENTRY(10, MILKMALON_DMGEFF_DEFAULT),
    /* Unk arrow 1   */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Unk arrow 2   */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Unk arrow 3   */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Fire magic    */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Ice magic     */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Light magic   */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Shield        */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Mirror Ray    */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Kokiri spin   */ DMG_ENTRY(2, MILKMALON_DMGEFF_DEFAULT),
    /* Giant spin    */ DMG_ENTRY(4, MILKMALON_DMGEFF_DEFAULT),
    /* Master spin   */ DMG_ENTRY(3, MILKMALON_DMGEFF_DEFAULT),
    /* Kokiri jump   */ DMG_ENTRY(3, MILKMALON_DMGEFF_DEFAULT),
    /* Giant jump    */ DMG_ENTRY(5, MILKMALON_DMGEFF_DEFAULT),
    /* Master jump   */ DMG_ENTRY(4, MILKMALON_DMGEFF_DEFAULT),
    /* Unknown 1     */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Unblockable   */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
    /* Hammer jump   */ DMG_ENTRY(4, MILKMALON_DMGEFF_DEFAULT),
    /* Unknown 2     */ DMG_ENTRY(0, MILKMALON_DMGEFF_NONE),
};

ActorInit Milk_Malon_InitVars = {
    /**/ ACTOR_MILK_MALON,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_MILK_MALON,
    /**/ sizeof(MilkMalon),
    /**/ (ActorFunc)MilkMalon_Init,
    /**/ (ActorFunc)MilkMalon_Destroy,
    /**/ (ActorFunc)MilkMalon_Update,
    /**/ (ActorFunc)MilkMalon_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 70, -50, { 0, 0, 0 } },
};

static ColliderQuadInit sSwordColliderInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK0,
        { 0xFFCFFFFF, 0x00, 0x10 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static ColliderCylinderInit sShieldColliderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFC1FFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 20, 70, -50, { 0, 0, 0 } },
};

#define SLASH_BLURE_START_COLOR_RGBA 255, 255, 255, 255 // White, fully opaque
#define SLASH_BLURE_END_COLOR_RGBA 255, 255, 255, 0    // White, fully transparent
#define SLASH_BLURE_MIDDLE_COLOR_RGBA 255, 255, 255, 64 // White, semi-transparent

void MilkMalon_Init(Actor* thisx, PlayState* play) {
    MilkMalon* this = (MilkMalon*)thisx;
    EffectBlureInit1 slashBlure;

    // Actor properties initialization
    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.colChkInfo.health = 15;
    this->actor.gravity = -1.0f;
    this->floatMagnitude = 100.0f; // Initial float magnitude
    this->energyBallActive = false;

    // Actor shape and focus initialization
    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 15.0f);
    Actor_SetFocus(thisx, 80.0f);

    // Background collision check initialization
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);

    // Collider initialization
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);

    Collider_InitQuad(play, &this->swordCollider);
    Collider_SetQuad(play, &this->swordCollider, &this->actor, &sSwordColliderInit);

    Collider_InitCylinder(play, &this->shieldCollider);
    Collider_SetCylinder(play, &this->shieldCollider, &this->actor, &sShieldColliderInit);

    // SkelAnime initialization
    SkelAnime_InitFlex(play, &this->skelAnime, &gMilkMalonSkel, &gMilkMalonDanceAnim, this->jointTable, this->morphTable, GMILKMALONSKEL_NUM_LIMBS);
    this->actor.colChkInfo.damageTable = &sDamageTable;

    // EffectBlure initialization
    const u8 startColorRGBA[] = {SLASH_BLURE_START_COLOR_RGBA};
    const u8 middleColorRGBA[] = {SLASH_BLURE_MIDDLE_COLOR_RGBA};
    const u8 endColorRGBA[] = {SLASH_BLURE_END_COLOR_RGBA};
    memcpy(slashBlure.p1StartColor, startColorRGBA, sizeof(startColorRGBA));
    memcpy(slashBlure.p2StartColor, middleColorRGBA, sizeof(middleColorRGBA));
    memcpy(slashBlure.p1EndColor, endColorRGBA, sizeof(endColorRGBA));
    memcpy(slashBlure.p2EndColor, endColorRGBA, sizeof(endColorRGBA));

    slashBlure.elemDuration = 4;
    slashBlure.unkFlag = 0;
    slashBlure.calcMode = 2;

    Effect_Add(play, &this->effectIndex, EFFECT_BLURE1, 0, 0, &slashBlure);

    // Set the initial action function
    MilkMalon_SetupFloatInAir(this, play);
}

void MilkMalon_Destroy(Actor* thisx, PlayState* play) {
    MilkMalon* this = (MilkMalon*)thisx;

    Effect_Delete(play, this->effectIndex);
    Collider_DestroyCylinder(play, &this->collider);
    Collider_DestroyQuad(play, &this->swordCollider);
    Collider_DestroyCylinder(play, &this->shieldCollider);
}

// HELPERS

void MilkMalon_RotateTowardPoint(MilkMalon* this, Vec3f* point, s16 step) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_WorldYawTowardPoint(&this->actor, point), 3, step, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// Helper function to maintain floating behavior
void MilkMalon_MaintainFloat(MilkMalon* this, PlayState* play) {
    f32 sinValue, cosValue;
    f32 centerX = this->actor.home.pos.x; 
    f32 centerZ = this->actor.home.pos.z;
    f32 radius = 50.0f;
    f32 floatTimerScaled = this->skelAnime.curFrame * 1500;
    
    sinValue = Math_SinS(floatTimerScaled);
    cosValue = Math_CosS(floatTimerScaled);

    f32 targetX = centerX + sinValue * radius;
    f32 targetZ = centerZ + cosValue * radius;

    Math_ApproachF(&this->actor.world.pos.x, targetX, 0.05f, this->floatMagnitude);
    Math_ApproachF(&this->actor.world.pos.y, 125.0f + (sinValue * 16.67f), 0.115f, this->floatMagnitude * 0.25f);
    Math_ApproachF(&this->actor.world.pos.z, targetZ, 0.05f, this->floatMagnitude);
    Math_ApproachF(&this->floatMagnitude, 50.0f, 1.0f, 0.5f);

    // Update velocity based on position change
    this->actor.velocity.x = this->actor.world.pos.x - this->actor.prevPos.x;
    this->actor.velocity.y = this->actor.world.pos.y - this->actor.prevPos.y;
    this->actor.velocity.z = this->actor.world.pos.z - this->actor.prevPos.z;

    // Smoothly update rotation to face the player
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0xBB8);
    // Play floating sound effect
    Sfx_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EN_FANTOM_FLOAT - SFX_FLAG);
}

// PHASE 1 SETUP FUNCTIONS

void MilkMalon_SetupIdle(MilkMalon* this, PlayState* play) {
    this->actor.speed = 0.0f;
    this->actor.velocity.y = 0.0f;
    Animation_MorphToLoop(&this->skelAnime, &gMilkMalonDanceAnim, -2.0f);
    this->actionFunc = MilkMalon_Idle;
}

void MilkMalon_SetupNotice(MilkMalon* this, PlayState* play) {
    Animation_PlayOnce(&this->skelAnime, &gMilkMalonNoticeAnim);
    this->actionFunc = MilkMalon_Notice;
}

void MilkMalon_SetupStartRunFromNotice(MilkMalon* this, PlayState* play) {
    Animation_PlayOnce(&this->skelAnime, &gMilkMalonWalkAnim);
    this->actionFunc = MilkMalon_StartRunFromNotice;
}

void MilkMalon_SetupRun(MilkMalon* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gMilkMalonWalkAnim, -1.0f);
    this->actionFunc = MilkMalon_Run;
}

void MilkMalon_SetupEndRun(MilkMalon* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonWalkAnim, -1.0f);
    this->actor.speed = 0.0f;
    this->actionFunc = MilkMalon_EndRun;
}

void MilkMalon_SetupAttack(MilkMalon* this, PlayState* play) {
    this->swordCollider.base.atFlags &= ~AT_BOUNCED;
    this->actor.speed = 8.0f;
    this->actor.velocity.y = 2.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonAttackAnim, 0.0f);
    Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_YOUNG_DAMAGE);
    this->actionFunc = MilkMalon_Attack;
    this->swordCollider.info.toucher.damage = 32;
}

void MilkMalon_SetupDamaged(MilkMalon* this, PlayState* play) {
    this->actor.speed = -4.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonDamagedAnim, 0.0f);
    this->actionFunc = MilkMalon_Damaged;
}

void MilkMalon_SetupStunned(MilkMalon* this, PlayState* play) {
    this->actor.speed = 0.0f;
    Animation_Change(&this->skelAnime, &gMilkMalonDamagedAnim, 0.0f, 3.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
    this->actionFunc = MilkMalon_Stunned;
}

void MilkMalon_SetupDie(MilkMalon* this, PlayState* play) {
    this->actor.speed = 0.0f;
    this->actor.flags &= ~ACTOR_FLAG_0;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonDieAnim, 0.0f);
    this->actionFunc = MilkMalon_Die;
}

void MilkMalon_SetupStopAndBlock(MilkMalon* this) {
    Animation_Change(&this->skelAnime, &gMilkMalonBlockAnim, 2.0f, 0.0f,
                     Animation_GetLastFrame(&gMilkMalonBlockAnim), 2, 0.0f);
    this->actor.speed = 0.0f;
    this->timer = (Rand_ZeroOne() * 10.0f) + 11.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = MilkMalon_StopAndBlock;
}

void MilkMalon_SetupJumpBack(MilkMalon* this) {
    Animation_PlayOnce(&this->skelAnime, &gMilkMalonJumpAnim);
    Actor_PlaySfx(&this->actor, NA_SE_EN_STAL_JUMP);
    this->timer = 14;
    this->actionFunc = MilkMalon_JumpBack;
}

void MilkMalon_SetupShoot(MilkMalon* this) {
    this->actor.speed = 0.0f;
    Animation_PlayOnce(&this->skelAnime, &gMilkMalonShootAnim);
    this->actionFunc = MilkMalon_Shoot;
}

// PHASE 2 SETUP FUNCTIONS

void MilkMalon_SetupFloatInAir(MilkMalon* this, PlayState* play) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &gMilkMalonFloatAnim, 0.75f);
    this->actionFunc = MilkMalon_FloatInAir;
}

void MilkMalon_SetupChargeLightBall(MilkMalon* this, PlayState* play) {
    this->lightBallMag = Animation_GetLastFrame(&gMilkMalonChargeLightBallAnim);
    Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonChargeLightBallAnim, -3.0f);
    this->actionFunc = MilkMalon_ChargeLightBall;
    this->lightBallTimer = 25;
}

void MilkMalon_SetupThrow(MilkMalon* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonThrowAnim, -5.0f);
    this->actionFunc = MilkMalon_Throw;
}

void MilkMalon_SetupReturn(MilkMalon* this, PlayState* play) {
    static AnimationHeader* returnAnim[] = { &gMilkMalonReflectAnim1, &gMilkMalonReflectAnim2 };
    s16 rand = Rand_ZeroOne() * 1.99f;

    this->returnEndFrame = Animation_GetLastFrame(returnAnim[rand]);
    Animation_MorphToPlayOnce(&this->skelAnime, returnAnim[rand], 0.0f);
    this->returnFlag = true;
    this->actionFunc = MilkMalon_Return;
}

void MilkMalon_SetupVulnerable(MilkMalon* this, PlayState* play) {
    if (this->actionFunc != MilkMalon_Vulnerable) {
        this->vulnerableEndFrame = Animation_GetLastFrame(&gMilkMalonDamagedAnim);
        Animation_MorphToLoop(&this->skelAnime, &gMilkMalonDamagedAnim, 0.0f);
        if (this->vulnerableTimer == 0) {
            this->vulnerableTimer = 150;
        }
    } else {
        this->vulnerableEndFrame = Animation_GetLastFrame(&gMilkMalonDamagedAnim);
        Animation_MorphToLoop(&this->skelAnime, &gMilkMalonDamagedAnim, 0.0f);
    }

    this->actionFunc = MilkMalon_Vulnerable;
    this->damageState = STUNNED_FALL;
}

// PHASE 1 MAIN

#define MILKMALON_HOME_RADIUS 450.0f
#define MILKMALON_NOTICE_RADIUS 200.0f
#define MILKMALON_SHOOT_RADIUS 200.0f
#define MILKMALON_ATTACK_RADIUS 100.0f

void MilkMalon_Shoot(MilkMalon* this, PlayState* play) {
    Vec3f spawnPos;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);
    if (SkelAnime_Update(&this->skelAnime)) {
        if ((this->actor.xzDistToPlayer <= MILKMALON_SHOOT_RADIUS) && (this->actor.xzDistToPlayer > MILKMALON_ATTACK_RADIUS)) {
            if (Actor_IsFacingPlayer(&this->actor, 0x1555)) {
                MilkMalon_SetupShoot(this);
            } else {
                MilkMalon_SetupRun(this, play);
                this->timer = (Rand_ZeroOne() * 5.0f) + 5.0f;
            }
        } else {
            if ((this->actor.xzDistToPlayer <= MILKMALON_SHOOT_RADIUS) && 
            Actor_IsFacingPlayer(&this->actor, 0xE38) && (this->actor.xzDistToPlayer > MILKMALON_ATTACK_RADIUS)) {
                MilkMalon_SetupShoot(this);
            } else {
                MilkMalon_SetupRun(this, play);
                this->timer = (Rand_ZeroOne() * 5.0f) + 5.0f;
            }
        }
    } else if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
        spawnPos.x = this->actor.world.pos.x + (Math_SinS(this->actor.shape.rot.y) * 20.0f);
        spawnPos.y = this->actor.world.pos.y + 52.0f;
        spawnPos.z = this->actor.world.pos.z + (Math_CosS(this->actor.shape.rot.y) * 23.0f);
        if (Actor_Spawn(&play->actorCtx, play, ACTOR_EN_NUTSBALL, spawnPos.x, spawnPos.y, spawnPos.z,
                        this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z, 0) != NULL) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_THROW);
        }
    }
}

void MilkMalon_JumpBack(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->swordState = 0;
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 0xBB8, 1);

    this->timer--;

    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        this->actor.speed = -7.0f;
    }
    if (Animation_OnFrame(&this->skelAnime, 24.0f)) {
        this->actor.speed = 0.0f;
    }

    if (SkelAnime_Update(&this->skelAnime)) {

        // if (this->actor.xzDistToPlayer <= MILKMALON_SHOOT_RADIUS) {
        //     if (Actor_IsFacingPlayer(&this->actor, 0x1555)) {
        //         MilkMalon_SetupShoot(this);
        //     } else {
        //         MilkMalon_SetupRun(this, play);
        //         this->timer = (Rand_ZeroOne() * 5.0f) + 5.0f;
        //     }
        // } else {
            if (Actor_IsFacingPlayer(&this->actor, 0xE38)) {
                MilkMalon_SetupShoot(this);
            } else {
                MilkMalon_SetupRun(this, play);
                this->timer = (Rand_ZeroOne() * 5.0f) + 5.0f;
            }
        // }
        
    } else if (this->skelAnime.curFrame == (this->skelAnime.endFrame - 7.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_DODO_M_GND);
    }
}

void MilkMalon_StopAndBlock(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->swordState = 0;
    
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 1.0f, 0.5f, 0.0f);
    SkelAnime_Update(&this->skelAnime);

    if ((ABS((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y)) > 0x3E80) && 
        ((play->gameplayFrames % 2) != 0)) {
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        MilkMalon_SetupJumpBack(this);
    }

    if (this->timer == 0) {
        MilkMalon_SetupRun(this, play);
    } else {
        this->timer--;
    }
}

void MilkMalon_Idle(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->swordState = 0;

    SkelAnime_Update(&this->skelAnime);

    if (this->actor.xzDistToPlayer < MILKMALON_NOTICE_RADIUS) {
        MilkMalon_SetupNotice(this, play);
    }
}

void MilkMalon_Notice(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 animDone = SkelAnime_Update(&this->skelAnime);

    this->swordState = 0;

    MilkMalon_RotateTowardPoint(this, &player->actor.world.pos, DEG_TO_BINANG(15.0f));

    if (Actor_IsFacingPlayer(&this->actor, DEG_TO_BINANG(20.0f))) {
        if (animDone) {
            if ((this->actor.xzDistToPlayer < MILKMALON_SHOOT_RADIUS) && Actor_IsFacingPlayer(&this->actor, 0xE38)) {
                // MilkMalon_SetupShoot(this);
            } else if (this->actor.xzDistToPlayer < MILKMALON_ATTACK_RADIUS) {
                MilkMalon_SetupAttack(this, play);
            } else {
                MilkMalon_SetupStartRunFromNotice(this, play);
            }
        }
    }
}

void MilkMalon_StartRunFromNotice(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->swordState = 0;

    Math_SmoothStepToF(&this->actor.speed, 4.0f, 0.1f, 1.0f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        MilkMalon_SetupRun(this, play);
    }
}

void MilkMalon_Run(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 playerOutsideHomeRadius = Actor_WorldDistXYZToPoint(&player->actor, &this->actor.home.pos) > MILKMALON_HOME_RADIUS;
    u8 MilkMalonOutsideHomeRadius = Actor_WorldDistXYZToPoint(&this->actor, &this->actor.home.pos) > MILKMALON_HOME_RADIUS;
    u8 MilkMalonAtHome = Actor_WorldDistXYZToPoint(&this->actor, &this->actor.home.pos) <= 100.0f;
    u8 playerOutsideNoticeRadius = this->actor.xzDistToPlayer > MILKMALON_NOTICE_RADIUS;
    u8 readyToAttack = Actor_IsFacingAndNearPlayer(&this->actor, MILKMALON_ATTACK_RADIUS, DEG_TO_BINANG(35.0f)) ||
                       Actor_IsFacingAndNearPlayer(&this->actor, MILKMALON_ATTACK_RADIUS * 0.5f, DEG_TO_BINANG(75.0f));

    this->swordState = 0;

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToF(&this->actor.speed, 4.0f, 0.1f, 1.0f, 0.0f);

    MilkMalon_RotateTowardPoint(this, &this->targetPos, DEG_TO_BINANG(10.0f));

    if (MilkMalonAtHome && playerOutsideNoticeRadius) {
        MilkMalon_SetupEndRun(this, play);
        return;
    }

    if (MilkMalonOutsideHomeRadius || playerOutsideHomeRadius) {
        this->targetPos = this->actor.home.pos;
        return;
    }

    this->targetPos = player->actor.world.pos;

    // if (this->actor.xzDistToPlayer <= 100.0f) {
    //     if (Actor_IsFacingPlayer(&this->actor, 0x1555)) {
    //         MilkMalon_SetupShoot(this);
    //     } else {
    //         MilkMalon_SetupRun(this, play);
    //         this->timer = (Rand_ZeroOne() * 5.0f) + 5.0f;
    //     }
    // } else {
    //     if ((this->actor.xzDistToPlayer <= 220.0f) && Actor_IsFacingPlayer(&this->actor, 0xE38)) {
    //         MilkMalon_SetupShoot(this);
    //     } else {
    //         MilkMalon_SetupRun(this, play);
    //         this->timer = (Rand_ZeroOne() * 5.0f) + 5.0f;
    //     }
    // }

    if (player->meleeWeaponState != 0) {
        MilkMalon_SetupStopAndBlock(this);
    }

    if (readyToAttack) {
        MilkMalon_SetupAttack(this, play);
    }
}

void MilkMalon_EndRun(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->swordState = 0;

    if (SkelAnime_Update(&this->skelAnime)) {
        MilkMalon_SetupIdle(this, play);
    }
}

void MilkMalon_Attack(MilkMalon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        this->actor.speed = 0.0f;
    }
    if (Animation_OnFrame(&this->skelAnime, 16.0f)) {
        this->actor.speed = 10.0f;
    }

    this->swordState = 1;
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 0.1f, 1.0f, 0.0f);

    if (player->meleeWeaponState != 0) {
        MilkMalon_SetupStopAndBlock(this);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        MilkMalon_SetupRun(this, play);
    }
}

// PHASE 2 MAIN

void MilkMalon_FloatInAir(MilkMalon* this, PlayState* play) {
    u8 animDone = SkelAnime_Update(&this->skelAnime);

    // Maintain floating
    MilkMalon_MaintainFloat(this, play);

    if (this->returnSuccess) {
        this->returnSuccess = false;
        MilkMalon_SetupReturn(this, play);
    }

    // Check if player is facing and no energy ball is active before deciding next action
    if (Actor_IsFacingPlayer(&this->actor, DEG_TO_BINANG(20.0f)) && animDone) {
        if (this->actor.xzDistToPlayer < MILKMALON_SHOOT_RADIUS  && !this->energyBallActive) {
            MilkMalon_SetupChargeLightBall(this, play);
        } else {
            MilkMalon_SetupFloatInAir(this, play);
        }
    }
}

void MilkMalon_ChargeLightBall(MilkMalon* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    MilkMalon_MaintainFloat(this, play);

    if (this->skelAnime.curFrame < 17.0f) {
        this->envLightMode = 1;
    }

    if (this->skelAnime.curFrame == 10.0f) {
        this->lightBallTimer = 10;
        Actor_PlaySfx(&this->actor, NA_SE_EN_GANON_SPARK);
    }

    if (this->skelAnime.curFrame == 18.0f) {
        MilkMalon_SetupThrow(this, play);
    }
}

void MilkMalon_Throw(MilkMalon* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 25.0f)) {
        MilkMalon_SetupFloatInAir(this, play);
    }

    MilkMalon_MaintainFloat(this, play);

    if (Animation_OnFrame(&this->skelAnime, 14.0f)) {
        this->spawnedActor = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_FHG_FIRE, this->ballPos.x, this->ballPos.y,
                           this->ballPos.z, 0, 0, 0, FHGFIRE_ENERGY_BALL);
        Actor_PlaySfx(&this->actor, NA_SE_EN_FANTOM_MASIC2);
        Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_YOUNG_DAMAGE);
        this->energyBallActive = true;
    }
}

void MilkMalon_Return(MilkMalon* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    MilkMalon_MaintainFloat(this, play);

    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_FANTOM_VOICE);
    }

    if (Animation_OnFrame(&this->skelAnime, this->returnEndFrame)) {
        MilkMalon_SetupFloatInAir(this, play);
    }

    if (this->returnSuccess) {
        this->returnSuccess = false;
        MilkMalon_SetupReturn(this, play);
    }
}

void MilkMalon_Vulnerable(MilkMalon* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->actor.gravity = -0.2f;
    if (this->actor.world.pos.y <= 5.0f) {
        if (this->damageState == STUNNED_FALL) {
            Animation_MorphToLoop(&this->skelAnime, &gMilkMalonDamagedAnim, -3.0f);
            this->damageState = STUNNED_GROUND;
        }
        this->actor.gravity = -1.0f;
        if (Animation_OnFrame(&this->skelAnime, this->vulnerableEndFrame)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_FANTOM_DAMAGE2);
        }
        this->actor.flags |= ACTOR_FLAG_10;
    }
    if (this->vulnerableTimer == 0) {
        MilkMalon_SetupFloatInAir(this, play);
        this->actor.gravity = -1.0f;
    }
    Actor_MoveXZGravity(&this->actor);
}

// ALL PHASES MAIN

void MilkMalon_Damaged(MilkMalon* this, PlayState* play) {
    this->swordState = 0;
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 3.0f, 0.5f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->vulnerableTimer != 0) {
            MilkMalon_SetupVulnerable(this, play);
        } else {
            MilkMalon_SetupRun(this, play);
        }
    }
}

void MilkMalon_Stunned(MilkMalon* this, PlayState* play) {
    this->swordState = 0;
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            MilkMalon_SetupDie(this, play);
        } else {
            MilkMalon_SetupJumpBack(this);
        }
    }
}

void MilkMalon_Die(MilkMalon* this, PlayState* play) {
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    Vec3f effectVel = { 0.0f, 4.0f, 0.0f };
    Vec3f effectPos = this->actor.world.pos;

    this->swordState = 0;

    if (SkelAnime_Update(&this->skelAnime)) {
        Actor_SetScale(&this->actor, this->actor.scale.x * 0.8f);

        if (this->actor.scale.x <= 0.001f) {
            effectPos.y += 10.0f;
            EffectSsDeadDb_Spawn(play, &effectPos, &effectVel, &zeroVec, 90, 0, 255, 255, 255, 255, 0, 0, 255, 1, 9,
                                 true);
            Item_DropCollectible(play, &this->actor.world.pos, ITEM00_NUTS);
            Actor_Kill(&this->actor);
        }
    }
}

void MilkMalon_CheckDamage(MilkMalon* this, PlayState* play) {
    if (this->shieldCollider.base.acFlags & AC_BOUNCED) {
        this->shieldCollider.base.acFlags &= ~AC_BOUNCED;
        this->collider.base.acFlags &= ~AC_HIT;

    } else if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.info, true);
        
        if ((this->actionFunc != MilkMalon_Die) && (this->actionFunc != MilkMalon_Damaged)) {
            switch (this->actor.colChkInfo.damageEffect) {
                case MILKMALON_DMGEFF_STUN:
                    if (this->actor.colChkInfo.health > 1) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
                        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_BLUE, 255, COLORFILTER_BUFFLAG_OPA,
                                             80);
                        this->actionFunc = MilkMalon_SetupStunned;
                        break;
                    }
                    break;
                case MILKMALON_DMGEFF_DEFAULT:
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 200, COLORFILTER_BUFFLAG_OPA, 20);
                    Actor_ApplyDamage(&this->actor);
                    if (this->actor.colChkInfo.health == 0) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_YOUNG_DAMAGE2);
                        Enemy_StartFinishingBlow(play, &this->actor);
                        this->actionFunc = MilkMalon_SetupDie;
                    } else {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_CUTBODY);
                        this->actionFunc = MilkMalon_SetupDamaged;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void MilkMalon_Update(Actor* thisx, PlayState* play) {
    MilkMalon* this = (MilkMalon*)thisx;
    CsCmdActorCue* cue;

    osSyncPrintf("Cutscene test");

    // if (play->csCtx.state != CS_STATE_IDLE) {
    //     cue = play->csCtx.actorCues[0];

    //     if (cue->id == 1) {
    //         f32 frameCount = Animation_GetLastFrame(&gMilkMalonDanceAnim);
    //         Animation_Change(&this->skelAnime, &gMilkMalonDanceAnim, 1.0f, 0.0f, frameCount, ANIMMODE_LOOP, 0.0f);
    //     }
    // }

    osSyncPrintf("Actor Position: x: %.2f, y: %.2f, z: %.2f\n", this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z);
    osSyncPrintf("Collider Position: x: %.2f, y: %.2f, z: %.2f\n", this->collider.dim.pos.x, this->collider.dim.pos.y, this->collider.dim.pos.z);

    MilkMalon_CheckDamage(this, play);
    this->actionFunc(this, play);

    this->collider.dim.pos.x = (f32)this->actor.world.pos.x;
    this->collider.dim.pos.y = (f32)this->actor.world.pos.y;
    this->collider.dim.pos.z = (f32)this->actor.world.pos.z;

    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, 
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | 
                                UPDBGCHECKINFO_FLAG_4);

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    if (this->actionFunc != MilkMalon_Damaged && this->actionFunc != MilkMalon_Die) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->actionFunc == MilkMalon_Attack) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->actionFunc == MilkMalon_StopAndBlock) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->shieldCollider.base);
    }

    if (this->swordState >= 1) {
        if (!(this->swordCollider.base.atFlags & AT_BOUNCED)) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->swordCollider.base);
        } else {
            this->swordCollider.base.atFlags &= ~AT_BOUNCED;
        }
    }

    if (this->vulnerableTimer != 0) {
        this->vulnerableTimer--;
    }

    if (this->returnCount > 0) { // This variable needs to be updated, it isn't a return count and is only being used for the effect's length
        EffectSsMmMilk_SpawnSplash(play, &this->actor, &this->actor.world.pos, 45, MMMILK_SPLASH_MM);
        if (this->returnCount == 19) {
            this->actionFunc = MilkMalon_SetupVulnerable;
        }
        this->returnCount--;
    }

    if (this->lightBallTimer != 0) {
        this->lightBallTimer--;

        static Color_RGBA8 primColor = { 200, 200, 200, 255 };
        static Color_RGBA8 envColor = { 255, 255, 255, 200 };
        Vec3f vel = { 0.0f, 0.0f, 0.0f };
        Vec3f accel = { 0.0f, -0.08f, 0.0f }; // Acceleration adjusted for gravity effect
        Vec3f relativePos; // Relative position of the ball in actor's hand
        f32 angleRadians;
        s32 i;

        // Relative position of the milk ball in the actor's hand before rotation
        relativePos.x = -15.0f;
        relativePos.y = 75.0f;
        relativePos.z = -5.0f;

        // Convert actor's yaw rotation from degrees to radians for trigonometric calculations
        angleRadians = (this->actor.shape.rot.y / (f32)0x8000) * M_PI;

        // Calculate new position of the milk ball based on actor's rotation
        this->ballPos.x = this->actor.world.pos.x + relativePos.x * cosf(angleRadians) + relativePos.z * sinf(angleRadians);
        this->ballPos.y = this->actor.world.pos.y + relativePos.y;
        this->ballPos.z = this->actor.world.pos.z - relativePos.x * sinf(angleRadians) + relativePos.z * cosf(angleRadians);

        // EffectSsLightning_Spawn(play, &ballPos, &primColor, &envColor, 60, 0, 6, 0); 
        EffectSsMmMilk_SpawnSplash(play, &this, &this->ballPos, 20, MMMILK_SPLASH_NO_ACTOR);
        for (i = 0; i < 2; i++) {
            EffectSsMmMilk_SpawnMilkBall(play, &this->ballPos, &vel, &accel, (s16)(Rand_ZeroOne() * 80.0f) + 200, MMMILK_MILKBALL_WHITE1);
        }
    }
}

s32 MilkMalon_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    MilkMalon* this = (MilkMalon*)thisx;

    switch (limbIndex) {
        case GMILKMALONSKEL_HAMMER_LIMB:
            // Hide the hammer in specific conditions
            if (this->skelAnime.animation == &gMilkMalonFloatAnim || 
                this->skelAnime.animation == &gMilkMalonChargeLightBallAnim || 
                this->skelAnime.animation == &gMilkMalonThrowAnim ||
                this->actionFunc == MilkMalon_Shoot ||
                this->actionFunc == MilkMalon_Return) {
                *dList = NULL; // Hides the hammer during the float animation or when shooting
            }
            break;
        case GMILKMALONSKEL_CANNON_LIMB:
            // Hide the cannon in specific conditions
            if (this->skelAnime.animation == &gMilkMalonFloatAnim || 
                this->actionFunc != MilkMalon_Shoot) {
                *dList = NULL; // Hides the cannon during the float animation or when not shooting
            }
            break;
    }
    return 0; 
}

void MilkMalon_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    MilkMalon* this = (MilkMalon*)thisx;

    // Predefined offsets and colors for the sword and shield
    static Vec3f swordTipOffset = { -300.0f, 4000.0f, 500.0f };
    static Vec3f swordHiltOffset = { 400.0f, 0.0f, 0.0f };
    static Vec3f quadOffsets[] = {
        { -3000.0f, 2000.0f, 1300.0f }, // swordQuadOffset0
        { 1600.0f, 4000.0f, 0.0f },    // swordQuadOffset1
        { 1000.0f, -1000.0f, 0.0f },   // swordQuadOffset2
        { -3000.0f, 2000.0f, -1300.0f } // swordQuadOffset3
    };
    static Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    Vec3f shieldFace, swordTip, swordHilt;

    if (limbIndex == GMILKMALONSKEL_HAMMER_LIMB) {
        s32 i;
        for (i = 0; i < 4; i++) {
            Matrix_MultVec3f(&quadOffsets[i], &this->swordCollider.dim.quad[i]);
        }
        Collider_SetQuadVertices(&this->swordCollider, &this->swordCollider.dim.quad[0],
                                 &this->swordCollider.dim.quad[1], &this->swordCollider.dim.quad[2],
                                 &this->swordCollider.dim.quad[3]);

        Matrix_MultVec3f(&swordTipOffset, &swordTip);
        Matrix_MultVec3f(&swordHiltOffset, &swordHilt);
        Matrix_MultVec3f(&zeroVec, &shieldFace);

        this->shieldCollider.dim.pos.x = (s16)shieldFace.x;
        this->shieldCollider.dim.pos.y = (s16)shieldFace.y;
        this->shieldCollider.dim.pos.z = (s16)shieldFace.z;

        if (this->swordState >= 1) {
            EffectSsMmMilk_SpawnSplash(play, &this->actor, &swordTip, 40, 0);
            EffectBlure_AddVertex(Effect_GetByIndex(this->effectIndex), &swordTip, &swordHilt);

            if (Animation_OnFrame(&this->skelAnime, 18.0f)) {
                EffectSsBlast_SpawnWhiteShockwave(play, &swordTip, &zeroVec, &zeroVec);
            }
        } else if (this->swordState == 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->effectIndex));
            this->swordState = -1;
        }
    }

    if (limbIndex == GMILKMALONSKEL_HEAD_LIMB) {
        Vec3f headFocusOffset = { 0.0f, 10.0f, 0.0f };
        Vec3f headFocusPos;

        Matrix_MultVec3f(&headFocusOffset, &headFocusPos);
        this->actor.focus.pos.x = (s16)headFocusPos.x;
        this->actor.focus.pos.y = (s16)headFocusPos.y;
        this->actor.focus.pos.z = (s16)headFocusPos.z;
    }

    if (limbIndex <= 25) {
        Matrix_MultVec3f(&zeroVec, &this->bodyPartsPos[limbIndex - 1]);
    }
}


void MilkMalon_Draw(Actor* thisx, PlayState* play) {
    MilkMalon* this = (MilkMalon*)thisx;
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
                            MilkMalon_OverrideLimbDraw, MilkMalon_PostLimbDraw, this, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    gfx = POLY_OPA_DISP + 1;
    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    GfxPrint_SetColor(&printer, 150, 0, 0, 255);
    GfxPrint_SetPos(&printer, 1, 7);
    GfxPrint_Printf(&printer, "health: %u", this->actor.colChkInfo.health);

    GfxPrint_SetColor(&printer, 255, 0, 255, 255);
    GfxPrint_SetPos(&printer, 1, 8);
    GfxPrint_Printf(&printer, "end: %.2f", this->skelAnime.endFrame);

    // Set the color to teal for the next line
    GfxPrint_SetColor(&printer, 0, 128, 128, 255);
    GfxPrint_SetPos(&printer, 1, 9);
    GfxPrint_Printf(&printer, "cur: %.2f", this->skelAnime.curFrame);

    GfxPrint_SetColor(&printer, 128, 56, 0, 255);
    GfxPrint_SetPos(&printer, 1, 10);
    GfxPrint_Printf(&printer, "vulnTimer: %u", this->vulnerableTimer);

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    gSPBranchList(POLY_OPA_DISP, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}
