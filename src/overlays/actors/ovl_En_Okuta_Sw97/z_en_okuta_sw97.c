/*
 * File: z_en_okuta_sw97.c
 * Overlay: ovl_En_Okuta_Sw97
 * Description: Custom Actor
 */

#include "z_en_okuta_sw97.h"
#include "assets/objects/object_oc/object_oc.h"

#define FLAGS (0)

void En_Okuta_Sw97_Init(Actor* thisx, PlayState* play);
void En_Okuta_Sw97_Destroy(Actor* thisx, PlayState* play);
void En_Okuta_Sw97_Update(Actor* thisx, PlayState* play);
void En_Okuta_Sw97_Draw(Actor* thisx, PlayState* play);

void En_Okuta_Sw97_SetupWaitToShoot(En_Okuta_Sw97* thisx);
void En_Okuta_Sw97_WaitToAppear(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_Appear(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_Hide(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_WaitToShoot(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_Shoot(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_WaitToDie(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_Die(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_Freeze(En_Okuta_Sw97* thisx, PlayState* play);
void En_Okuta_Sw97_ProjectileFly(En_Okuta_Sw97* thisx, PlayState* play);

void En_Okuta_Sw97_DoNothing(En_Okuta_Sw97* this, PlayState* play);

ActorInit En_Okuta_Sw97_InitVars = {
    ACTOR_EN_OKUTA_SW97,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OC,
    sizeof(En_Okuta_Sw97),
    (ActorFunc)En_Okuta_Sw97_Init,
    (ActorFunc)En_Okuta_Sw97_Destroy,
    (ActorFunc)En_Okuta_Sw97_Update,
    (ActorFunc)En_Okuta_Sw97_Draw,
};

static ColliderCylinderInit sProjectileColliderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xFFCFFFFF, 0x00, 0x08 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 13, 20, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sOctorockColliderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, -30, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 30, 15, 60, 100 };

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, 0x0),
    /* Deku stick    */ DMG_ENTRY(2, 0x0),
    /* Slingshot     */ DMG_ENTRY(1, 0x0),
    /* Explosive     */ DMG_ENTRY(2, 0x0),
    /* Boomerang     */ DMG_ENTRY(1, 0x0),
    /* Normal arrow  */ DMG_ENTRY(2, 0x0),
    /* Hammer swing  */ DMG_ENTRY(2, 0x0),
    /* Hookshot      */ DMG_ENTRY(2, 0x0),
    /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
    /* Master sword  */ DMG_ENTRY(2, 0x0),
    /* Giant's Knife */ DMG_ENTRY(4, 0x0),
    /* Fire arrow    */ DMG_ENTRY(2, 0x0),
    /* Ice arrow     */ DMG_ENTRY(4, 0x3),
    /* Light arrow   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 1   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 2   */ DMG_ENTRY(2, 0x0),
    /* Unk arrow 3   */ DMG_ENTRY(2, 0x0),
    /* Fire magic    */ DMG_ENTRY(0, 0x0),
    /* Ice magic     */ DMG_ENTRY(0, 0x0),
    /* Light magic   */ DMG_ENTRY(0, 0x0),
    /* Shield        */ DMG_ENTRY(0, 0x0),
    /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
    /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
    /* Giant spin    */ DMG_ENTRY(4, 0x0),
    /* Master spin   */ DMG_ENTRY(2, 0x0),
    /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
    /* Giant jump    */ DMG_ENTRY(8, 0x0),
    /* Master jump   */ DMG_ENTRY(4, 0x0),
    /* Unknown 1     */ DMG_ENTRY(0, 0x0),
    /* Unblockable   */ DMG_ENTRY(0, 0x0),
    /* Hammer jump   */ DMG_ENTRY(4, 0x0),
    /* Unknown 2     */ DMG_ENTRY(0, 0x0),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(naviEnemyId, 66, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6500, ICHAIN_STOP),
};


static Vtx zelda_rock_zelda_rockVtx_000058_mod[4] = {
    VTX(1000, -1000, 0, 1024, 1024, 255, 255, 255, 255),
    VTX(1000, 999, 0, 1024, 0, 255, 255, 255, 255),
    VTX(-999, 999, 0, 0, 0, 255, 255, 255, 255),
    VTX(-999, -1000, 0, 0, 1024, 255, 255, 255, 255),
};

Gfx gOctorokProjectileDL_mod[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(ostone_txt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPVertex(&zelda_rock_zelda_rockVtx_000058_mod[0], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

void En_Okuta_Sw97_Init(Actor* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;
    s32 pad;
    // WaterBox* outWaterBox;
    // f32 ySurface;
    UNK_TYPE sp30;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->numShots = (thisx->params >> 8) & 0xFF;
    thisx->params &= 0xFF;
    if (thisx->params == 0) {
        SkelAnime_Init(play, &this->skelAnime, &okuta_wait_mdl_info, &okuta_wait_soft_anim_tbl_info, NULL, NULL,
                       0);
        Collider_InitCylinder(play, &this->collider);
        Collider_SetCylinder(play, &this->collider, thisx, &sOctorockColliderInit);
        CollisionCheck_SetInfo(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);
        if ((this->numShots == 0xFF) || (this->numShots == 0)) {
            this->numShots = 1;
        }
        thisx->floorHeight =
            BgCheck_EntityRaycastDown4(&play->colCtx, &thisx->floorPoly, &sp30, thisx, &thisx->world.pos);
        //! @bug calls WaterBox_GetSurfaceImpl directly
        /*if (!WaterBox_GetSurfaceImpl(play, &play->colCtx, thisx->world.pos.x, thisx->world.pos.z, &ySurface,
                                     &outWaterBox) ||
            (ySurface <= thisx->floorHeight)) {
            Actor_Kill(thisx);
        } else {
            thisx->home.pos.y = ySurface;
        }*/
        // En_Okuta_Sw97_SetupWaitToAppear(this);
        En_Okuta_Sw97_SetupWaitToShoot(this);
    } else {
        ActorShape_Init(&thisx->shape, 1100.0f, ActorShadow_DrawCircle, 18.0f);
        thisx->flags &= ~1;
        thisx->flags |= 0x10;
        Collider_InitCylinder(play, &this->collider);
        Collider_SetCylinder(play, &this->collider, thisx, &sProjectileColliderInit);
        Actor_ChangeCategory(play, &play->actorCtx, thisx, ACTORCAT_PROP);
        this->timer = 30;
        thisx->shape.rot.y = 0;
        this->actionFunc = En_Okuta_Sw97_ProjectileFly;
        thisx->speed = 10.0f;
    }
}

void En_Okuta_Sw97_Destroy(Actor* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void En_Okuta_Sw97_SpawnBubbles(En_Okuta_Sw97* thisx, PlayState* play) {
    /*s32 i;

    for (i = 0; i < 10; i++) {
        EffectSsBubble_Spawn(play, &this->actor.world.pos, -10.0f, 10.0f, 30.0f, 0.25f);
    }*/
}

void En_Okuta_Sw97_SpawnDust(Vec3f* pos, Vec3f* velocity, s16 scaleStep, PlayState* play) {
    static Vec3f accel = { 0.0f, 0.0f, 0.0f };
    static Color_RGBA8 primColor = { 255, 255, 255, 255 };
    static Color_RGBA8 envColor = { 150, 150, 150, 255 };

    func_8002829C(play, pos, velocity, &accel, &primColor, &envColor, 0x190, scaleStep);
}

void En_Okuta_Sw97_SpawnSplash(En_Okuta_Sw97* thisx, PlayState* play) {
    // EffectSsGSplash_Spawn(play, &this->actor.home.pos, NULL, NULL, 0, 1300);
}

void En_Okuta_Sw97_SpawnRipple(En_Okuta_Sw97* this, PlayState* play) {
    /*Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.home.pos.y;
    pos.z = this->actor.world.pos.z;
    if ((play->gameplayFrames % 7) == 0 &&
        ((this->actionFunc != En_Okuta_Sw97_Shoot) || ((this->actor.world.pos.y - this->actor.home.pos.y) < 50.0f))) {
        EffectSsGRipple_Spawn(play, &pos, 250, 650, 0);
    }*/
}

void En_Okuta_Sw97_SetupWaitToAppear(En_Okuta_Sw97* thisx) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    this->actor.draw = NULL;
    this->actor.flags &= ~1;
    this->actionFunc = En_Okuta_Sw97_WaitToAppear;
    this->actor.world.pos.y = this->actor.home.pos.y;
}

void En_Okuta_Sw97_SetupAppear(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    this->actor.draw = En_Okuta_Sw97_Draw;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.flags |= 1;
    Animation_PlayOnce(&this->skelAnime, &okuta_damage_wait_soft_anim_tbl_info);
    En_Okuta_Sw97_SpawnBubbles(this, play);
    this->actionFunc = En_Okuta_Sw97_Appear;
}

void En_Okuta_Sw97_SetupHide(En_Okuta_Sw97* thisx) {
    /*Animation_PlayOnce(&this->skelAnime, &okuta_wait_soft_anim_tbl_info);
    this->actionFunc = En_Okuta_Sw97_Hide;*/
}

void En_Okuta_Sw97_SetupWaitToShoot(En_Okuta_Sw97* thisx) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Animation_PlayLoop(&this->skelAnime, &okuta_move_soft_anim_tbl_info);
    this->timer = /*(this->actionFunc == En_Okuta_Sw97_Shoot) ? 2 :*/ 0;
    this->actionFunc = En_Okuta_Sw97_WaitToShoot;
}

void En_Okuta_Sw97_SetupShoot(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Animation_PlayOnce(&this->skelAnime, &okuta_shot_soft_anim_tbl_info);
    if (this->actionFunc != En_Okuta_Sw97_Shoot) {
        this->timer = this->numShots;
    }
    this->jumpHeight = this->actor.yDistToPlayer + 20.0f;
    this->jumpHeight = CLAMP_MIN(this->jumpHeight, 10.0f);
    if (this->jumpHeight > 50.0f) {
        En_Okuta_Sw97_SpawnSplash(this, play);
    }
    if (this->jumpHeight > 50.0f) {
        // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
    }
    this->actionFunc = En_Okuta_Sw97_Shoot;
}

void En_Okuta_Sw97_SetupWaitToDie(En_Okuta_Sw97* thisx) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Animation_MorphToPlayOnce(&this->skelAnime, &okuta_damage_soft_anim_tbl_info, -5.0f);
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 0xB);
    this->collider.base.acFlags &= ~AC_HIT;
    Actor_SetScale(&this->actor, 0.01f);
    Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_DEAD1);
    this->actionFunc = En_Okuta_Sw97_WaitToDie;
}

void En_Okuta_Sw97_SetupDie(En_Okuta_Sw97* thisx) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Animation_MorphToPlayOnce(&this->skelAnime, &okuta_damage_soft_anim_tbl_info, -3.0f);
    this->timer = 0;
    this->actionFunc = En_Okuta_Sw97_Die;
}

void En_Okuta_Sw97_SetupFreeze(En_Okuta_Sw97* thisx) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    this->timer = 80;
    Actor_SetColorFilter(&this->actor, 0, 0xFF, 0, 0x50);
    this->actionFunc = En_Okuta_Sw97_Freeze;
}


void En_Okuta_Sw97_SpawnProjectile(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Vec3f pos;
    Vec3f velocity;
    f32 sin = Math_SinS(this->actor.shape.rot.y);
    f32 cos = Math_CosS(this->actor.shape.rot.y);

    pos.x = this->actor.world.pos.x + (25.0f * sin);
    pos.y = this->actor.world.pos.y - 6.0f;
    pos.z = this->actor.world.pos.z + (25.0f * cos);
    if (Actor_Spawn(&play->actorCtx, play, ACTOR_EN_OKUTA_SW97, pos.x, pos.y, pos.z, this->actor.shape.rot.x,
                    this->actor.shape.rot.y, this->actor.shape.rot.z, 0x10) != NULL) {
        pos.x = this->actor.world.pos.x + (40.0f * sin);
        pos.z = this->actor.world.pos.z + (40.0f * cos);
        pos.y = this->actor.world.pos.y;
        velocity.x = 1.5f * sin;
        velocity.y = 0.0f;
        velocity.z = 1.5f * cos;
        En_Okuta_Sw97_SpawnDust(&pos, &velocity, 20, play);
    }
    Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_THROW);
}

void En_Okuta_Sw97_WaitToAppear(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    this->actor.world.pos.y = this->actor.home.pos.y;
    if ((this->actor.xzDistToPlayer < 480.0f) /*&& (this->actor.xzDistToPlayer > 200.0f)*/) {
        En_Okuta_Sw97_SetupAppear(this, play);
    }
}

void En_Okuta_Sw97_Appear(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;
    s32 pad;

    if (SkelAnime_Update(&this->skelAnime)) {
        /*if (this->actor.xzDistToPlayer < 160.0f) {
            En_Okuta_Sw97_SetupHide(this);
        } else*/
        { En_Okuta_Sw97_SetupWaitToShoot(this); }
    } else if (this->skelAnime.curFrame <= 4.0f) {
        Actor_SetScale(&this->actor, this->skelAnime.curFrame * 0.25f * 0.01f);
    } else if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_SetScale(&this->actor, 0.01f);
    }
    if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
    }
    if (Animation_OnFrame(&this->skelAnime, 12.0f)) {
        // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_LAND);
    }
    if (Animation_OnFrame(&this->skelAnime, 3.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
        En_Okuta_Sw97_SpawnSplash(this, play);
    }
}

void En_Okuta_Sw97_Hide(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    s32 pad;

    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 30.0f);
    if (SkelAnime_Update(&this->skelAnime)) {
        // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_BUBLE);
        En_Okuta_Sw97_SpawnBubbles(this, play);
        En_Okuta_Sw97_SetupWaitToAppear(this);
    } else if (this->skelAnime.curFrame >= 4.0f) {
        Actor_SetScale(&this->actor, (6.0f - this->skelAnime.curFrame) * 0.5f * 0.01f);
    }
    if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_SINK);
    }
    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        En_Okuta_Sw97_SpawnSplash(this, play);
    }
}

void En_Okuta_Sw97_WaitToShoot(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    s16 temp_v0_2;
    s32 phi_v1;

    this->actor.world.pos.y = this->actor.home.pos.y;
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (this->timer != 0) {
            this->timer--;
        }
    }
    if (Animation_OnFrame(&this->skelAnime, 0.5f)) {
        // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_FLOAT);
    }
    if (/*this->actor.xzDistToPlayer < 160.0f ||*/ this->actor.xzDistToPlayer > 560.0f) {
        En_Okuta_Sw97_SetupHide(this);
    } else {
        temp_v0_2 = Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x71C, 0x38E);
        phi_v1 = ABS(temp_v0_2);
        if ((phi_v1 < 0x38E) && (this->timer == 0) && (this->actor.yDistToPlayer < 200.0f)) {
            En_Okuta_Sw97_SetupShoot(this, play);
        }
    }
}

void En_Okuta_Sw97_Shoot(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x71C);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->timer != 0) {
            this->timer--;
        }
        if (this->timer == 0) {
            En_Okuta_Sw97_SetupWaitToShoot(this);
        } else {
            En_Okuta_Sw97_SetupShoot(this, play);
        }
    } else {
        f32 curFrame = this->skelAnime.curFrame;

        if (curFrame < 13.0f) {
            this->actor.world.pos.y = (sinf((0.08333f * M_PI) * curFrame) * this->jumpHeight) + this->actor.home.pos.y;
        }
        if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
            En_Okuta_Sw97_SpawnProjectile(this, play);
        }
        if ((this->jumpHeight > 50.0f) && Animation_OnFrame(&this->skelAnime, 13.0f)) {
            En_Okuta_Sw97_SpawnSplash(this, play);
        }
        if ((this->jumpHeight > 50.0f) && Animation_OnFrame(&this->skelAnime, 13.0f)) {
            // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_LAND);
        }
    }
    /*if (this->actor.xzDistToPlayer < 160.0f) {
        En_Okuta_Sw97_SetupHide(this);
    }*/
}

void En_Okuta_Sw97_WaitToDie(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    if (SkelAnime_Update(&this->skelAnime)) {
        En_Okuta_Sw97_SetupDie(this);
    }
    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 5.0f);
}

void En_Okuta_Sw97_Die(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    static Vec3f accel = { 0.0f, -0.5f, 0.0f };
    static Color_RGBA8 primColor = { 255, 255, 255, 255 };
    static Color_RGBA8 envColor = { 150, 150, 150, 0 };
    Vec3f velocity;
    Vec3f pos;
    s32 i;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->timer++;
    }
    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 5.0f);
    if (this->timer == 5) {
        pos.x = this->actor.world.pos.x;
        pos.y = this->actor.world.pos.y + 40.0f;
        pos.z = this->actor.world.pos.z;
        velocity.x = 0.0f;
        velocity.y = -0.5f;
        velocity.z = 0.0f;
        En_Okuta_Sw97_SpawnDust(&pos, &velocity, -0x14, play);
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_DEAD2);
    }
    if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
        En_Okuta_Sw97_SpawnSplash(this, play);
        // Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_LAND);
    }
    if (this->timer < 3) {
        Actor_SetScale(&this->actor, ((this->timer * 0.25f) + 1.0f) * 0.01f);
    } else if (this->timer < 6) {
        Actor_SetScale(&this->actor, (1.5f - ((this->timer - 2) * 0.2333f)) * 0.01f);
    } else if (this->timer < 11) {
        Actor_SetScale(&this->actor, (((this->timer - 5) * 0.04f) + 0.8f) * 0.01f);
    } else {
        if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.0005f)) {
            // Sfx_PlaySfxAtPos(play, &this->actor.world.pos, 30, NA_SE_EN_OCTAROCK_BUBLE);
            Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0x70);
            for (i = 0; i < 20; i++) {
                velocity.x = (Rand_ZeroOne() - 0.5f) * 7.0f;
                velocity.y = Rand_ZeroOne() * 7.0f;
                velocity.z = (Rand_ZeroOne() - 0.5f) * 7.0f;
                /*EffectSsDtBubble_SpawnCustomColor(play, &this->actor.world.pos, &velocity, &accel, &primColor,
                                                  &envColor, Rand_S16Offset(100, 50), 25, 0);*/
            }
            Actor_Kill(&this->actor);
        }
        this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
    }
}

void En_Okuta_Sw97_Freeze(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Vec3f pos;
    s16 temp_v1;

    if (this->timer != 0) {
        this->timer--;
    }
    if (this->timer == 0) {
        En_Okuta_Sw97_SetupDie(this);
    }
    if ((this->timer >= 64) && (this->timer & 1)) {
        temp_v1 = (this->timer - 64) >> 1;
        pos.y = (this->actor.world.pos.y - 32.0f) + (8.0f * (8 - temp_v1));
        pos.x = this->actor.world.pos.x + ((temp_v1 & 2) ? 10.0f : -10.0f);
        pos.z = this->actor.world.pos.z + ((temp_v1 & 1) ? 10.0f : -10.0f);
        EffectSsEnIce_SpawnFlyingVec3f(play, &this->actor, &pos, 150, 150, 150, 250, 235, 245, 255,
                                       (Rand_ZeroOne() * 0.2f) + 1.9f);
    }
    Math_ApproachF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.5f, 5.0f);
}

void En_Okuta_Sw97_ProjectileFly(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    Vec3f pos;
    Player* player = GET_PLAYER(play);
    Vec3s sp40;

    this->timer--;
    if (this->timer == 0) {
        this->actor.gravity = -1.0f;
    }
    this->actor.home.rot.z += 0x1554;
    if (this->actor.bgCheckFlags & 0x20) {
        this->actor.gravity = -1.0f;
        this->actor.speed -= 0.1f;
        this->actor.speed = CLAMP_MIN(this->actor.speed, 1.0f);
    }
    if ((this->actor.bgCheckFlags & 8) || (this->actor.bgCheckFlags & 1) || (this->collider.base.atFlags & AT_HIT) ||
        this->collider.base.acFlags & AC_HIT || this->collider.base.ocFlags1 & OC1_HIT ||
        this->actor.floorHeight == BGCHECK_Y_MIN) {
        if ((player->currentShield == PLAYER_SHIELD_DEKU ||
             (player->currentShield == PLAYER_SHIELD_HYLIAN && LINK_IS_ADULT)) &&
            this->collider.base.atFlags & AT_HIT && this->collider.base.atFlags & AT_TYPE_ENEMY &&
            this->collider.base.atFlags & AT_BOUNCED) {
            this->collider.base.atFlags &= ~(AT_HIT | AT_BOUNCED | AT_TYPE_ENEMY);
            this->collider.base.atFlags |= AT_TYPE_PLAYER;
            this->collider.info.toucher.dmgFlags = 2;
            Matrix_MtxFToYXZRotS(&player->shieldMf, &sp40, 0);
            this->actor.world.rot.y = sp40.y + 0x8000;
            this->timer = 30;
        } else {
            pos.x = this->actor.world.pos.x;
            pos.y = this->actor.world.pos.y + 11.0f;
            pos.z = this->actor.world.pos.z;
            EffectSsHahen_SpawnBurst(play, &pos, 6.0f, 0, 1, 2, 15, 7, 10, gOctorokProjectileDL_mod);
            Sfx_PlaySfxAtPos(&this->actor.world.pos, NA_SE_EN_OCTAROCK_ROCK);
            Actor_Kill(&this->actor);
        }
    } else if (this->timer == -300) {
        Actor_Kill(&this->actor);
    }
}


void En_Okuta_Sw97_UpdateHeadScale(En_Okuta_Sw97* thisx) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    f32 curFrame = this->skelAnime.curFrame;

    if (this->actionFunc == En_Okuta_Sw97_Appear) {
        if (curFrame < 8.0f) {
            this->headScale.x = this->headScale.y = this->headScale.z = 1.0f;
        } else if (curFrame < 10.0f) {
            this->headScale.x = this->headScale.z = 1.0f;
            this->headScale.y = ((curFrame - 7.0f) * 0.4f) + 1.0f;
        } else if (curFrame < 14.0f) {
            this->headScale.x = this->headScale.z = ((curFrame - 9.0f) * 0.075f) + 1.0f;
            this->headScale.y = 1.8f - ((curFrame - 9.0f) * 0.25f);
        } else {
            this->headScale.x = this->headScale.z = 1.3f - ((curFrame - 13.0f) * 0.05f);
            this->headScale.y = ((curFrame - 13.0f) * 0.0333f) + 0.8f;
        }
    } else if (this->actionFunc == En_Okuta_Sw97_Hide) {
        if (curFrame < 3.0f) {
            this->headScale.y = 1.0f;
        } else if (curFrame < 4.0f) {
            this->headScale.y = (curFrame - 2.0f) + 1.0f;
        } else {
            this->headScale.y = 2.0f - ((curFrame - 3.0f) * 0.333f);
        }
        this->headScale.x = this->headScale.z = 1.0f;
    } else if (this->actionFunc == En_Okuta_Sw97_Shoot) {
        if (curFrame < 5.0f) {
            this->headScale.x = this->headScale.y = this->headScale.z = (curFrame * 0.125f) + 1.0f;
        } else if (curFrame < 7.0f) {
            this->headScale.x = this->headScale.y = this->headScale.z = 1.5f - ((curFrame - 4.0f) * 0.35f);
        } else if (curFrame < 17.0f) {
            this->headScale.x = this->headScale.z = ((curFrame - 6.0f) * 0.05f) + 0.8f;
            this->headScale.y = 0.8f;
        } else {
            this->headScale.x = this->headScale.z = 1.3f - ((curFrame - 16.0f) * 0.1f);
            this->headScale.y = ((curFrame - 16.0f) * 0.0666f) + 0.8f;
        }
    } else if (this->actionFunc == En_Okuta_Sw97_WaitToShoot) {
        this->headScale.x = this->headScale.z = 1.0f;
        this->headScale.y = (sinf((M_PI / 16) * curFrame) * 0.2f) + 1.0f;
    } else {
        this->headScale.x = this->headScale.y = this->headScale.z = 1.0f;
    }
}

void En_Okuta_Sw97_ColliderCheck(En_Okuta_Sw97* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    // Detect if being attacked (AT collider has collision with AC collider)
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT; // Reset AC flag
        Actor_SetDropFlag(&this->actor, &this->collider.info, 1); // Flag for item drops (magic, heart, etc.)

        // Apply damage without setting health to 0
        Actor_ApplyDamage(&this->actor); // Adjusts health based on damage received
        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 200, COLORFILTER_BUFFLAG_OPA, 20);

        // Check if the octorok's health has dropped to 0
        if (this->actor.colChkInfo.health == 0) {
            this->actor.flags &= ~1; // Unsetting a flag (probably related to being targetable/alive)
            En_Okuta_Sw97_SetupWaitToDie(this);
        } else if (this->actor.colChkInfo.damageEffect == 3) {
            // If ice arrows are used used, freeze it.
            En_Okuta_Sw97_SetupFreeze(this);
        } else {
            Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_DEAD1);
            En_Okuta_Sw97_SetupWaitToShoot(this);
        }
        
    }
}

void En_Okuta_Sw97_Update(Actor* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;
    Player* player = GET_PLAYER(play);
    PlayState* play2 = play;
    // WaterBox* outWaterBox;
    // f32 ySurface;
    Vec3f sp38;
    s32 sp34;

    if (!(player->stateFlags1 & 0x300000C0)) {
        if (this->actor.params == 0) {
            En_Okuta_Sw97_ColliderCheck(this, play2);
            /* if (!WaterBox_GetSurfaceImpl(play2, &play2->colCtx, this->actor.world.pos.x,
                                         this->actor.world.pos.z, &ySurface, &outWaterBox) ||
                (ySurface < this->actor.floorHeight)) {
                if (this->actor.colChkInfo.health != 0) {
                    Actor_Kill(&this->actor);
                    return;
                }
            } else {
                this->actor.home.pos.y = ySurface;
            } */
        }
        this->actionFunc(this, play2);
        if (this->actor.params == 0) {
            En_Okuta_Sw97_UpdateHeadScale(this);
            this->collider.dim.height =
                (((sOctorockColliderInit.dim.height * this->headScale.y) - this->collider.dim.yShift) *
                 this->actor.scale.y * 100.0f);
        } else {
            sp34 = false;
            Actor_MoveXZGravity(&this->actor);
            Math_Vec3f_Copy(&sp38, &this->actor.world.pos);
            Actor_UpdateBgCheckInfo(play2, &this->actor, 10.0f, 15.0f, 30.0f, 5);
            if ((this->actor.bgCheckFlags & 8) &&
                SurfaceType_IsIgnoredByProjectiles(&play2->colCtx, this->actor.wallPoly, this->actor.wallBgId)) {
                sp34 = true;
                this->actor.bgCheckFlags &= ~8;
            }
            if ((this->actor.bgCheckFlags & 1) &&
                SurfaceType_IsIgnoredByProjectiles(&play2->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
                sp34 = true;
                this->actor.bgCheckFlags &= ~1;
            }
            if (sp34 && !(this->actor.bgCheckFlags & 9)) {
                Math_Vec3f_Copy(&this->actor.world.pos, &sp38);
            }
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        if ((this->actionFunc == En_Okuta_Sw97_Appear) || (this->actionFunc == En_Okuta_Sw97_Hide)) {
            this->collider.dim.pos.y = this->actor.world.pos.y + (this->skelAnime.jointTable->y * this->actor.scale.y);
            this->collider.dim.radius = sOctorockColliderInit.dim.radius * this->actor.scale.x * 100.0f;
        }
        if (this->actor.params == 0x10) {
            this->actor.flags |= 0x1000000;
            CollisionCheck_SetAT(play2, &play2->colChkCtx, &this->collider.base);
        }
        if (this->actionFunc != En_Okuta_Sw97_WaitToAppear) {
            if ((this->actionFunc != En_Okuta_Sw97_Die) && (this->actionFunc != En_Okuta_Sw97_WaitToDie) &&
                (this->actionFunc != En_Okuta_Sw97_Freeze)) {
                CollisionCheck_SetAC(play2, &play2->colChkCtx, &this->collider.base);
            }
            CollisionCheck_SetOC(play2, &play2->colChkCtx, &this->collider.base);
        }
        Actor_SetFocus(&this->actor, 15.0f);
        if ((this->actor.params == 0) && (this->actor.draw != NULL)) {
            En_Okuta_Sw97_SpawnRipple(this, play2);
        }
    }
}

s32 En_Okuta_Sw97_GetSnoutScale(En_Okuta_Sw97* thisx, f32 curFrame, Vec3f* scale) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;

    if (this->actionFunc == En_Okuta_Sw97_WaitToShoot) {
        scale->x = scale->z = 1.0f;
        scale->y = (sinf((M_PI / 16) * curFrame) * 0.4f) + 1.0f;
    } else if (this->actionFunc == En_Okuta_Sw97_Shoot) {
        if (curFrame < 5.0f) {
            scale->x = 1.0f;
            scale->y = scale->z = (curFrame * 0.25f) + 1.0f;
        } else if (curFrame < 7.0f) {
            scale->x = (curFrame - 4.0f) * 0.5f + 1.0f;
            scale->y = scale->z = 2.0f - (curFrame - 4.0f) * 0.5f;
        } else {
            scale->x = 2.0f - ((curFrame - 6.0f) * 0.0769f);
            scale->y = scale->z = 1.0f;
        }
    } else if (this->actionFunc == En_Okuta_Sw97_Die) {
        if (curFrame >= 35.0f || curFrame < 25.0f) {
            return false;
        }
        if (curFrame < 27.0f) {
            scale->x = 1.0f;
            scale->y = scale->z = ((curFrame - 24.0f) * 0.5f) + 1.0f;
        } else if (curFrame < 30.0f) {
            scale->x = (curFrame - 26.0f) * 0.333f + 1.0f;
            scale->y = scale->z = 2.0f - (curFrame - 26.0f) * 0.333f;
        } else {
            scale->x = 2.0f - ((curFrame - 29.0f) * 0.2f);
            scale->y = scale->z = 1.0f;
        }
    } else {
        return false;
    }

    return true;
}

s32 En_Okuta_Sw97_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             void* thisx) {
    /*En_Okuta_Sw97* this = THIS;
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f scale;
    s32 doScale = false;

    if (this->actionFunc == En_Okuta_Sw97_Die) {
        curFrame += this->timer;
    }
    if (limbIndex == 5) {
        if ((this->headScale.x != 1.0f) || (this->headScale.y != 1.0f) || (this->headScale.z != 1.0f)) {
            scale = this->headScale;
            doScale = true;
        }
    } else if (limbIndex == 8) {
        doScale = En_Okuta_Sw97_GetSnoutScale(this, curFrame, &scale);
    }
    if (doScale) {
        Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);
    }*/
    return false;
}

void En_Okuta_Sw97_Draw(Actor* thisx, PlayState* play) {
    En_Okuta_Sw97* this = (En_Okuta_Sw97*)thisx;
    s32 pad;

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    if (this->actor.params == 0) {
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, En_Okuta_Sw97_OverrideLimbDraw,
                          NULL, this);
    } else {
        OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

        Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
        Matrix_RotateZ(this->actor.home.rot.z * (M_PI / 0x8000), MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_okuta.c", 1657),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gOctorokProjectileDL_mod);

        CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    }
}
