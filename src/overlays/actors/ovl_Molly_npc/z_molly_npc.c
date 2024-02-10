/*
 * File: z_molly_npc.c
 * Overlay: ovl_Molly_npc
 * Description: Molly NPC - Undead Girl
 */

#include "z_molly_npc.h"
#include "assets/objects/object_molly_npc/object_molly_npc.h"

// Makes it Z target-able: (ACTOR_FLAG_0)
#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4)

void MollyNpc_Init(Actor* thisx, PlayState* play);
void MollyNpc_Destroy(Actor* thisx, PlayState* play);
void MollyNpc_Update(Actor* thisx, PlayState* play);
void MollyNpc_Draw(Actor* thisx, PlayState* play);

void MollyNpc_Idle(MollyNpc* this, PlayState* play);
void MollyNpc_Notice(MollyNpc* this, PlayState* play);
void MollyNpc_StartRunFromNotice(MollyNpc* this, PlayState* play);
void MollyNpc_Run(MollyNpc* this, PlayState* play);
void MollyNpc_EndRun(MollyNpc* this, PlayState* play);
void MollyNpc_Attack(MollyNpc* this, PlayState* play);
void MollyNpc_Damaged(MollyNpc* this, PlayState* play);
void MollyNpc_Stunned(MollyNpc* this, PlayState* play);
void MollyNpc_Die(MollyNpc* this, PlayState* play);


typedef enum {
    MOLLYNPC_DMGEFF_NONE,
    MOLLYNPC_DMGEFF_STUN,
    MOLLYNPC_DMGEFF_DEFAULT,
} MollyNpcDamageEffect;

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_STUN),
    /* Deku stick    */ DMG_ENTRY(3, MOLLYNPC_DMGEFF_DEFAULT),
    /* Slingshot     */ DMG_ENTRY(2, MOLLYNPC_DMGEFF_DEFAULT),
    /* Explosive     */ DMG_ENTRY(4, MOLLYNPC_DMGEFF_DEFAULT),
    /* Boomerang     */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_STUN),
    /* Normal arrow  */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Hammer swing  */ DMG_ENTRY(3, MOLLYNPC_DMGEFF_DEFAULT),
    /* Hookshot      */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_STUN),
    /* Kokiri sword  */ DMG_ENTRY(2, MOLLYNPC_DMGEFF_DEFAULT),
    /* Master sword  */ DMG_ENTRY(3, MOLLYNPC_DMGEFF_DEFAULT),
    /* Giant's Knife */ DMG_ENTRY(4, MOLLYNPC_DMGEFF_DEFAULT),
    /* Fire arrow    */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Ice arrow     */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Light arrow   */ DMG_ENTRY(10, MOLLYNPC_DMGEFF_DEFAULT),
    /* Unk arrow 1   */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Unk arrow 2   */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Unk arrow 3   */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Fire magic    */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Ice magic     */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Light magic   */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Shield        */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Mirror Ray    */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Kokiri spin   */ DMG_ENTRY(2, MOLLYNPC_DMGEFF_DEFAULT),
    /* Giant spin    */ DMG_ENTRY(4, MOLLYNPC_DMGEFF_DEFAULT),
    /* Master spin   */ DMG_ENTRY(3, MOLLYNPC_DMGEFF_DEFAULT),
    /* Kokiri jump   */ DMG_ENTRY(3, MOLLYNPC_DMGEFF_DEFAULT),
    /* Giant jump    */ DMG_ENTRY(5, MOLLYNPC_DMGEFF_DEFAULT),
    /* Master jump   */ DMG_ENTRY(4, MOLLYNPC_DMGEFF_DEFAULT),
    /* Unknown 1     */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Unblockable   */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
    /* Hammer jump   */ DMG_ENTRY(4, MOLLYNPC_DMGEFF_DEFAULT),
    /* Unknown 2     */ DMG_ENTRY(0, MOLLYNPC_DMGEFF_NONE),
};

ActorInit Molly_npc_InitVars = {
    /**/ ACTOR_MOLLY_NPC,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_MOLLY_NPC,
    /**/ sizeof(MollyNpc),
    /**/ (ActorFunc)MollyNpc_Init,
    /**/ (ActorFunc)MollyNpc_Destroy,
    /**/ (ActorFunc)MollyNpc_Update,
    /**/ (ActorFunc)MollyNpc_Draw,
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
        COLTYPE_NONE,
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

void MollyNpc_Init(Actor* thisx, PlayState* play) {
    EffectBlureInit1 slashBlure;
    MollyNpc* this = (MollyNpc*)thisx;

    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.colChkInfo.health = 10;
    this->actor.gravity = -1.0f;

    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 15.0f);
    Actor_SetFocus(thisx, 80.0f);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sCylinderInit);
    Collider_InitQuad(play, &this->swordCollider);
    Collider_SetQuad(play, &this->swordCollider, &this->actor, &sSwordColliderInit);
    SkelAnime_InitFlex(play, &this->skelAnime, &gMollyNpcSkel, &gMollyNpcWalkAnim, this->jointTable, this->morphTable, GMOLLYNPCSKEL_NUM_LIMBS);

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

    this->actionFunc = MollyNpc_Idle;
}

void MollyNpc_Destroy(Actor* thisx, PlayState* play) {
    MollyNpc* this = (MollyNpc*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
    Collider_DestroyQuad(play, &this->swordCollider);
}

// HELPERS

void MollyNpc_RotateTowardPoint(MollyNpc* this, Vec3f* point, s16 step) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, Actor_WorldYawTowardPoint(&this->actor, point), 3, step, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

// SETUP FUNCTIONS

void MollyNpc_SetupIdle(MollyNpc* this, PlayState* play) {
    this->actor.speed = 0.0f;
    this->actor.velocity.y = 0.0f;
    Animation_MorphToLoop(&this->skelAnime, &gMollyNpcWalkAnim, -3.0f);
    this->actionFunc = MollyNpc_Idle;
}

#define MOLLYNPC_FLEE_RADIUS 200.0f

void MollyNpc_SetupNotice(MollyNpc* this, PlayState* play) {
    Animation_PlayOnce(&this->skelAnime, &gMollyNpcWalkAnim);
    this->actionFunc = MollyNpc_Notice;
}

void MollyNpc_SetupStartRunFromNotice(MollyNpc* this, PlayState* play) {
    Animation_PlayOnce(&this->skelAnime, &gMollyNpcWalkAnim);
    this->actionFunc = MollyNpc_StartRunFromNotice;
}

void MollyNpc_SetupRun(MollyNpc* this, PlayState* play) {
    s16 angle;

    if (this->fleeTimer != 0) {
        angle = this->actor.yawTowardsPlayer + DEG_TO_BINANG(180.0f) +
                Rand_S16Offset(DEG_TO_BINANG(-45.0f), DEG_TO_BINANG(90.0f));
        this->fleePos.x = (Math_CosS(angle) * MOLLYNPC_FLEE_RADIUS) + this->actor.home.pos.x;
        this->fleePos.z = (Math_SinS(angle) * MOLLYNPC_FLEE_RADIUS) + this->actor.home.pos.z;
    }

    Animation_MorphToLoop(&this->skelAnime, &gMollyNpcWalkAnim, 0.0f);
    this->actionFunc = MollyNpc_Run;
}

void MollyNpc_SetupEndRun(MollyNpc* this, PlayState* play) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gMollyNpcWalkAnim, 0.0f);
    this->actor.speed = 0.0f;
    this->actionFunc = MollyNpc_EndRun;
}

void MollyNpc_SetupAttack(MollyNpc* this, PlayState* play) {
    this->swordCollider.base.atFlags &= ~AT_BOUNCED;
    this->actor.speed = 8.0f;
    this->actor.velocity.y = 2.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMollyNpcWalkAnim, 0.0f);
    Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_YOUNG_DAMAGE);
    this->actionFunc = MollyNpc_Attack;
    this->swordCollider.info.toucher.damage = 16;
}

void MollyNpc_SetupDamaged(MollyNpc* this, PlayState* play) {
    this->actor.speed = -4.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMollyNpcWalkAnim, 0.0f);
    this->actionFunc = MollyNpc_Damaged;
}

void MollyNpc_SetupStunned(MollyNpc* this, PlayState* play) {
    this->actor.speed = 0.0f;
    Animation_Change(&this->skelAnime, &gMollyNpcWalkAnim, 0.0f, 3.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
    this->actionFunc = MollyNpc_Stunned;
}

void MollyNpc_SetupDie(MollyNpc* this, PlayState* play) {
    this->actor.speed = 0.0f;
    this->actor.flags &= ~ACTOR_FLAG_0;
    this->actor.world.rot.y = this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMollyNpcWalkAnim, 0.0f);
    this->actionFunc = MollyNpc_Die;
}

// MAIN

#define MOLLYNPC_NOTICE_RADIUS 300.0f

void MollyNpc_Idle(MollyNpc* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    SkelAnime_Update(&this->skelAnime);

    if (this->actor.xzDistToPlayer < MOLLYNPC_NOTICE_RADIUS) {
        MollyNpc_SetupNotice(this, play);
    }
}

#define MOLLYNPC_ATTACK_RADIUS 100.0f

void MollyNpc_Notice(MollyNpc* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 animDone = SkelAnime_Update(&this->skelAnime);

    MollyNpc_RotateTowardPoint(this, &player->actor.world.pos, DEG_TO_BINANG(15.0f));

    if (Actor_IsFacingPlayer(&this->actor, DEG_TO_BINANG(20.0f))) {
        if (animDone) {
            if (this->actor.xzDistToPlayer < MOLLYNPC_ATTACK_RADIUS) {
                MollyNpc_SetupAttack(this, play);
            } else {
                MollyNpc_SetupStartRunFromNotice(this, play);
            }
        }
    }
}

void MollyNpc_StartRunFromNotice(MollyNpc* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Math_SmoothStepToF(&this->actor.speed, 4.0f, 0.1f, 1.0f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        MollyNpc_SetupRun(this, play);
    }
}

#define MOLLYNPC_HOME_RADIUS 450.0f

void MollyNpc_Run(MollyNpc* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 playerOutsideHomeRadius = Actor_WorldDistXYZToPoint(&player->actor, &this->actor.home.pos) > MOLLYNPC_HOME_RADIUS;
    u8 MollyNpcOutsideHomeRadius = Actor_WorldDistXYZToPoint(&this->actor, &this->actor.home.pos) > MOLLYNPC_HOME_RADIUS;
    u8 MollyNpcAtHome = Actor_WorldDistXYZToPoint(&this->actor, &this->actor.home.pos) <= 100.0f;
    u8 playerOutsideNoticeRadius = this->actor.xzDistToPlayer > MOLLYNPC_NOTICE_RADIUS;
    u8 readyToAttack = Actor_IsFacingAndNearPlayer(&this->actor, MOLLYNPC_ATTACK_RADIUS, DEG_TO_BINANG(35.0f)) ||
                       Actor_IsFacingAndNearPlayer(&this->actor, MOLLYNPC_ATTACK_RADIUS * 0.5f, DEG_TO_BINANG(75.0f));

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToF(&this->actor.speed, 4.0f, 0.1f, 1.0f, 0.0f);

    MollyNpc_RotateTowardPoint(this, &this->targetPos, DEG_TO_BINANG(10.0f));

    if (MollyNpcAtHome && playerOutsideNoticeRadius) {
        MollyNpc_SetupEndRun(this, play);
        return;
    }

    if (MollyNpcOutsideHomeRadius || playerOutsideHomeRadius) {
        this->targetPos = this->actor.home.pos;
        return;
    }

    if (DECR(this->fleeTimer) == 0 || Actor_WorldDistXZToPoint(&this->actor, &this->fleePos) < 100.0f) {
        this->fleeTimer = 0;
        this->targetPos = player->actor.world.pos;
    } else {
        this->targetPos = this->fleePos;
    }

    if (readyToAttack && this->fleeTimer == 0) {
        MollyNpc_SetupAttack(this, play);
    }
}

void MollyNpc_EndRun(MollyNpc* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (SkelAnime_Update(&this->skelAnime)) {
        MollyNpc_SetupIdle(this, play);
    }
}

void MollyNpc_Attack(MollyNpc* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->swordState = 1;
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 0.1f, 1.0f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        this->fleeTimer = 2 * 20;
        this->swordState = 0;
        MollyNpc_SetupRun(this, play);
    }
}

void MollyNpc_Damaged(MollyNpc* this, PlayState* play) {
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 3.0f, 0.5f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        this->fleeTimer = 6 * 20;
        MollyNpc_SetupRun(this, play);
    }
}

void MollyNpc_Stunned(MollyNpc* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            MollyNpc_SetupDie(this, play);
        } else {
            MollyNpc_SetupRun(this, play);
        }
    }
}

void MollyNpc_Die(MollyNpc* this, PlayState* play) {
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    Vec3f effectVel = { 0.0f, 4.0f, 0.0f };
    Vec3f effectPos = this->actor.world.pos;

    if (SkelAnime_Update(&this->skelAnime) || this->drowned) {
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

void MollyNpc_CheckDrowned(MollyNpc* this, PlayState* play) {
    if (!this->drowned && (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && (this->actor.yDistToWater > 5.0f)) {
        Actor_SetDropFlag(&this->actor, &this->collider.info, true);
        Actor_PlaySfx(&this->actor, NA_SE_EN_EIER_ATTACK);
        Enemy_StartFinishingBlow(play, &this->actor);
        this->drowned = true;
        this->actor.gravity = -0.1f;
        this->actionFunc = MollyNpc_SetupDie;
        return;
    }
}

void MollyNpc_CheckDamage(MollyNpc* this, PlayState* play) {
    MollyNpc_CheckDrowned(this, play);

    if (!this->drowned && this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.info, true);

        if ((this->actionFunc != MollyNpc_Die) && (this->actionFunc != MollyNpc_Damaged)) {
            switch (this->actor.colChkInfo.damageEffect) {
                case MOLLYNPC_DMGEFF_STUN:
                    if (this->actor.colChkInfo.health > 1) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
                        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_BLUE, 255, COLORFILTER_BUFFLAG_OPA,
                                             80);
                        this->actionFunc = MollyNpc_SetupStunned;
                        break;
                    }
                    break;
                case MOLLYNPC_DMGEFF_DEFAULT:
                    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 200, COLORFILTER_BUFFLAG_OPA, 20);
                    Actor_ApplyDamage(&this->actor);
                    if (this->actor.colChkInfo.health == 0) {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_YOUNG_DAMAGE2);
                        Enemy_StartFinishingBlow(play, &this->actor);
                        this->actionFunc = MollyNpc_SetupDie;
                    } else {
                        Actor_PlaySfx(&this->actor, NA_SE_EN_TWINROBA_CUTBODY);
                        this->actionFunc = MollyNpc_SetupDamaged;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void MollyNpc_Update(Actor* thisx, PlayState* play) {
    MollyNpc* this = (MollyNpc*)thisx;

    MollyNpc_CheckDamage(this, play);
    this->actionFunc(this, play);

    Collider_UpdateCylinder(&this->actor, &this->collider);

    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 20.0f, 35.0f, 
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | 
                                UPDBGCHECKINFO_FLAG_4);

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    if (this->actionFunc != MollyNpc_Damaged && this->actionFunc != MollyNpc_Die) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->actionFunc == MollyNpc_Attack) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->swordState >= 1) {
        if (!(this->swordCollider.base.atFlags & AT_BOUNCED)) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->swordCollider.base);
        } else {
            this->swordCollider.base.atFlags &= ~AT_BOUNCED;
        }
    }
}

void MollyNpc_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    static Vec3f sMultVec = { 800.0f, 500.0f, 0.0f };
    static Vec3f D_80864658 = { 300.0f, 0.0f, 0.0f };
    static Vec3f D_80864664 = { 3400.0f, 0.0f, 0.0f };
    static Vec3f D_80864670 = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_8086467C = { 7000.0f, 1000.0f, 0.0f };
    static Vec3f D_80864688 = { 3000.0f, -2000.0f, -1000.0f };
    static Vec3f D_80864694 = { 3000.0f, -2000.0f, 1000.0f };
    static Vec3f D_808646A0 = { -1300.0f, 1100.0f, 0.0f };
    Vec3f sp70;
    Vec3f sp64;
    MollyNpc* this = (MollyNpc*)thisx;

    if (limbIndex == GMOLLYNPCSKEL_SWORD_LIMB) {
        Matrix_MultVec3f(&D_8086467C, &this->swordCollider.dim.quad[1]);
        Matrix_MultVec3f(&D_80864688, &this->swordCollider.dim.quad[0]);
        Matrix_MultVec3f(&D_80864694, &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&D_808646A0, &this->swordCollider.dim.quad[2]);

        Collider_SetQuadVertices(&this->swordCollider, &this->swordCollider.dim.quad[0],
                                 &this->swordCollider.dim.quad[1], &this->swordCollider.dim.quad[2],
                                 &this->swordCollider.dim.quad[3]);
        
        Matrix_MultVec3f(&D_80864664, &sp70);
        Matrix_MultVec3f(&D_80864670, &sp64);

        if (this->swordState >= 1) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->effectIndex), &sp70, &sp64);
        } else if (this->swordState >= 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->effectIndex));
            this->swordState = -1;
        }
    }
    
    if (limbIndex == GMOLLYNPCSKEL_HEAD_LIMB) {
        Vec3f src = { 0.0f, 10.0f, 0.0f };
        Vec3f dest;

        Matrix_MultVec3f(&src, &dest);
        this->actor.focus.pos.x = dest.x;
        this->actor.focus.pos.y = dest.y;
        this->actor.focus.pos.z = dest.z;
    }
};

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
                            NULL, MollyNpc_PostLimbDraw, this, POLY_OPA_DISP);

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
