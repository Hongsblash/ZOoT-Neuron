/*
 * File: z_milk_malon.c
 * Overlay: ovl_Milk_Malon
 * Description: Milk Malon - Enemy
 */

// Need to finish setting up the blocking functionality
// Need to get the attack function to face link before lunging

#include "z_milk_malon.h"
#include "assets/objects/object_milk_malon/object_milk_malon.h"
#include "assets/objects/object_dekunuts/object_dekunuts.h"

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


typedef enum {
    MILKMALON_DMGEFF_NONE,
    MILKMALON_DMGEFF_STUN,
    MILKMALON_DMGEFF_DEFAULT,
} MilkMalonDamageEffect;

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
    /**/ ACTORCAT_NPC,
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
        COLTYPE_HIT5,
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
    { 20, 70, 0, { 0, 0, 0 } },
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

void MilkMalon_Init(Actor* thisx, PlayState* play) {
    EffectBlureInit1 slashBlure;
    MilkMalon* this = (MilkMalon*)thisx;

    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.colChkInfo.health = 15;
    this->actor.gravity = -1.0f;

    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 15.0f);
    Actor_SetFocus(thisx, 80.0f);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);

    Collider_InitQuad(play, &this->swordCollider);
    Collider_SetQuad(play, &this->swordCollider, &this->actor, &sSwordColliderInit);

    Collider_InitCylinder(play, &this->shieldCollider);
    Collider_SetCylinder(play, &this->shieldCollider, &this->actor, &sShieldColliderInit);

    SkelAnime_InitFlex(play, &this->skelAnime, &gMilkMalonSkel, &gMilkMalonDanceAnim, this->jointTable, this->morphTable, GMILKMALONSKEL_NUM_LIMBS);

    this->actor.colChkInfo.damageTable = &sDamageTable;

    slashBlure.p1StartColor[0] = slashBlure.p1StartColor[1] = slashBlure.p1StartColor[2] = slashBlure.p1StartColor[3] =
        slashBlure.p2StartColor[0] = slashBlure.p2StartColor[1] = slashBlure.p2StartColor[2] =
            slashBlure.p1EndColor[0] = slashBlure.p1EndColor[1] = slashBlure.p1EndColor[2] = slashBlure.p2EndColor[0] =
                slashBlure.p2EndColor[1] = slashBlure.p2EndColor[2] = 255;

    slashBlure.p1EndColor[3] = 0;
    slashBlure.p2EndColor[3] = 0;
    slashBlure.p2StartColor[3] = 64;

    slashBlure.elemDuration = 4;
    slashBlure.unkFlag = 0;
    slashBlure.calcMode = 2;

    Effect_Add(play, &this->effectIndex, EFFECT_BLURE1, 0, 0, &slashBlure);

    this->actionFunc = MilkMalon_Idle;
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

// SETUP FUNCTIONS

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
    s16 angle;

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
    this->swordCollider.info.toucher.damage = 16;
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
    // this->unk_7C8 = 0x14;
    this->timer = 14;
    this->actionFunc = MilkMalon_JumpBack;

    // if (this->unk_7DE != 0) {
    //     this->unk_7DE = 3;
    // }
}

void MilkMalon_SetupShoot(MilkMalon* this) {
    this->actor.speed = 0.0f;
    Animation_PlayOnce(&this->skelAnime, &gMilkMalonShootAnim);
    this->actionFunc = MilkMalon_Shoot;
}

// MAIN

#define MILKMALON_SHOOT_RADIUS 250.0f
#define MILKMALON_ATTACK_RADIUS 150.0f

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
    // } else if ((this->animFlagAndTimer > 1) && Animation_OnFrame(&this->skelAnime, 10.0f)) {
    //     Animation_MorphToPlayOnce(&this->skelAnime, &gMilkMalonShootAnim, -5.0f);
    //     if (this->animFlagAndTimer != 0) {
    //         this->animFlagAndTimer--;
    //     }
    // }
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

#define MILKMALON_NOTICE_RADIUS 300.0f

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

#define MILKMALON_HOME_RADIUS 450.0f

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

void MilkMalon_Damaged(MilkMalon* this, PlayState* play) {
    this->swordState = 0;
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 3.0f, 0.5f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        MilkMalon_SetupRun(this, play);
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
            Item_DropCollectible(play, &this->actor.world.pos, ITEM00_RECOVERY_HEART);
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

    MilkMalon_CheckDamage(this, play);
    this->actionFunc(this, play);

    Collider_UpdateCylinder(&this->actor, &this->collider);

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
    if (this->actionFunc != MilkMalon_StopAndBlock) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->shieldCollider.base);
    }

    if (this->swordState >= 1) {
        if (!(this->swordCollider.base.atFlags & AT_BOUNCED)) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->swordCollider.base);
        } else {
            this->swordCollider.base.atFlags &= ~AT_BOUNCED;
        }
    }
}

s32 MilkMalon_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    MilkMalon* this = (MilkMalon*)thisx;

    switch (limbIndex) {
        case GMILKMALONSKEL_HAMMER_LIMB:
            if (this->actionFunc == MilkMalon_Shoot) {
                *dList = NULL;
            }
            break;
        case GMILKMALONSKEL_CANNON_LIMB:
            if (this->actionFunc != MilkMalon_Shoot) {
                *dList = NULL;
            }
            break;
    }

    return false;
}

void MilkMalon_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    static Vec3f swordTipOffset = { -300.0f, 4000.0f, 500.0f };
    static Vec3f swordHiltOffset = { 400.0f, 0.0f, 0.0f };
    static Vec3f swordQuadOffset1 = { 1600.0f, 4000.0f, 0.0f };
    static Vec3f swordQuadOffset0 = { -3000.0f, 2000.0f, 1300.0f };
    static Vec3f swordQuadOffset3 = { -3000.0f, 2000.0f, -1300.0f };
    static Vec3f swordQuadOffset2 = { 1000.0f, -1000.0f, 0.0f };
    static Color_RGBA8 lightningPrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 lightningEnvColor = { 200, 255, 255, 255 };
    static Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    Vec3f vel = { 0.0f, 1.0f, 0.0f };
    Vec3f accel = { 0.0f, 0.0f, 0.0f };
    Vec3f shieldFace;
    Vec3f swordTip;
    Vec3f swordHilt;

    MilkMalon* this = (MilkMalon*)thisx;

    if (limbIndex == GMILKMALONSKEL_HAMMER_LIMB) {
        Matrix_MultVec3f(&swordQuadOffset1, &this->swordCollider.dim.quad[1]);
        Matrix_MultVec3f(&swordQuadOffset0, &this->swordCollider.dim.quad[0]);
        Matrix_MultVec3f(&swordQuadOffset3, &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&swordQuadOffset2, &this->swordCollider.dim.quad[2]);
        Collider_SetQuadVertices(&this->swordCollider, &this->swordCollider.dim.quad[0],
                                 &this->swordCollider.dim.quad[1], &this->swordCollider.dim.quad[2],
                                 &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&swordTipOffset, &swordTip);
        Matrix_MultVec3f(&swordHiltOffset, &swordHilt);

        Matrix_MultVec3f(&zeroVec, &shieldFace);

        this->shieldCollider.dim.pos.x = shieldFace.x;
        this->shieldCollider.dim.pos.y = shieldFace.y;
        this->shieldCollider.dim.pos.z = shieldFace.z;

        if (this->swordState >= 1) {
            // EffectSsIceSmoke_Spawn(play, &swordTip, &vel, &accel, 150);
            EffectSsFhgFlash_SpawnShock(play, &this->actor, &swordTip, 40, 0);
            EffectBlure_AddVertex(Effect_GetByIndex(this->effectIndex), &swordTip, &swordHilt);

            if (Animation_OnFrame(&this->skelAnime, 18.0f)) {
                EffectSsBlast_SpawnWhiteShockwave(play, &swordTip, &zeroVec, &zeroVec);
            }
        } else if (this->swordState >= 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->effectIndex));
            this->swordState = -1;
        }
    }
    
    if (limbIndex == GMILKMALONSKEL_HEAD_LIMB) {
        Vec3f src = { 0.0f, 10.0f, 0.0f };
        Vec3f dest;

        Matrix_MultVec3f(&src, &dest);
        this->actor.focus.pos.x = dest.x;
        this->actor.focus.pos.y = dest.y;
        this->actor.focus.pos.z = dest.z;
    }
};

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

    // OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    // gfx = POLY_OPA_DISP + 1;
    // gSPDisplayList(OVERLAY_DISP++, gfx);

    // GfxPrint_Init(&printer);
    // GfxPrint_Open(&printer, gfx);

    // GfxPrint_SetColor(&printer, 255, 0, 255, 255);
    // GfxPrint_SetPos(&printer, 10, 10);
    // GfxPrint_Printf(&printer, &this->actionFunc);

    // gfx = GfxPrint_Close(&printer);
    // GfxPrint_Destroy(&printer);

    // gSPEndDisplayList(gfx++);
    // gSPBranchList(POLY_OPA_DISP, gfx);
    // POLY_OPA_DISP = gfx;

    // CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

}
