/*
 * File: z_player_geldb.c
 * Overlay: ovl_Player_Geldb
 * Description: Gerudo Fighter Transformation
 */

#include "z_player_geldb.h"
#include "assets/objects/object_geldb/object_geldb.h"

#define FLAGS (0)

void Player_Geldb_Init(Actor* thisx, PlayState* play);
void Player_Geldb_Destroy(Actor* thisx, PlayState* play);
void Player_Geldb_Update(Actor* thisx, PlayState* play);
void Player_Geldb_Draw(Actor* thisx, PlayState* play);

void Player_Geldb_Idle(Player_Geldb* this, PlayState* play);
void Player_Geldb_Run(Player_Geldb* this, PlayState* play);
void Player_Geldb_Attack(Player_Geldb* this, PlayState* play);
void Player_Geldb_SpinAttack(Player_Geldb* this, PlayState* play);
void Player_Geldb_Block(Player_Geldb* this, PlayState* play);
void Player_Geldb_Sidewalk(Player_Geldb* this, PlayState* play);
void Player_Geldb_Jump(Player_Geldb* this, PlayState* play);

ActorInit Player_Geldb_InitVars = {
    ACTOR_PLAYER_GELDB,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GELDB,
    sizeof(Player_Geldb),
    (ActorFunc)Player_Geldb_Init,
    (ActorFunc)Player_Geldb_Destroy,
    (ActorFunc)Player_Geldb_Update,
    (ActorFunc)Player_Geldb_Draw,
};

typedef enum {
    /* 0x0 */ GELDB_DMG_NORMAL,
    /* 0x1 */ GELDB_DMG_STUN,
    /* 0x6 */ GELDB_DMG_UNK_6 = 0x6,
    /* 0xD */ GELDB_DMG_UNK_D = 0xD,
    /* 0xE */ GELDB_DMG_UNK_E,
    /* 0xF */ GELDB_DMG_FREEZE
} Player_GeldbDamageEffects;

static ColliderQuadInit sSwordQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000100, 0x00, 0x01 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static DamageTable sDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, GELDB_DMG_STUN),
    /* Deku stick    */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Slingshot     */ DMG_ENTRY(1, GELDB_DMG_NORMAL),
    /* Explosive     */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Boomerang     */ DMG_ENTRY(0, GELDB_DMG_STUN),
    /* Normal arrow  */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Hammer swing  */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Hookshot      */ DMG_ENTRY(0, GELDB_DMG_STUN),
    /* Kokiri sword  */ DMG_ENTRY(1, GELDB_DMG_NORMAL),
    /* Master sword  */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Giant's Knife */ DMG_ENTRY(4, GELDB_DMG_NORMAL),
    /* Fire arrow    */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Ice arrow     */ DMG_ENTRY(2, GELDB_DMG_FREEZE),
    /* Light arrow   */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Unk arrow 1   */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Unk arrow 2   */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Unk arrow 3   */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Fire magic    */ DMG_ENTRY(4, GELDB_DMG_UNK_E),
    /* Ice magic     */ DMG_ENTRY(0, GELDB_DMG_UNK_6),
    /* Light magic   */ DMG_ENTRY(3, GELDB_DMG_UNK_D),
    /* Shield        */ DMG_ENTRY(0, GELDB_DMG_NORMAL),
    /* Mirror Ray    */ DMG_ENTRY(0, GELDB_DMG_NORMAL),
    /* Kokiri spin   */ DMG_ENTRY(1, GELDB_DMG_NORMAL),
    /* Giant spin    */ DMG_ENTRY(4, GELDB_DMG_NORMAL),
    /* Master spin   */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Kokiri jump   */ DMG_ENTRY(2, GELDB_DMG_NORMAL),
    /* Giant jump    */ DMG_ENTRY(8, GELDB_DMG_NORMAL),
    /* Master jump   */ DMG_ENTRY(4, GELDB_DMG_NORMAL),
    /* Unknown 1     */ DMG_ENTRY(4, GELDB_DMG_NORMAL),
    /* Unblockable   */ DMG_ENTRY(0, GELDB_DMG_NORMAL),
    /* Hammer jump   */ DMG_ENTRY(4, GELDB_DMG_NORMAL),
    /* Unknown 2     */ DMG_ENTRY(0, GELDB_DMG_NORMAL),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3000, ICHAIN_STOP),
};

void Player_Geldb_Init(Actor* thisx, PlayState* play) {
    Player_Geldb* this = (Player_Geldb*)thisx;

    s32 pad;
    EffectBlureInit1 blureInit;

    Actor_ProcessInitChain(thisx, sInitChain);
    thisx->colChkInfo.damageTable = &sDamageTable;
    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawFeet, 100.0f);
    this->actor.colChkInfo.mass = MASS_HEAVY;
    thisx->colChkInfo.health = 20;
    thisx->colChkInfo.cylRadius = 50;
    thisx->colChkInfo.cylHeight = 100;
    thisx->naviEnemyId = NAVI_ENEMY_GERUDO_THIEF;
    this->blinkState = 0;
    SkelAnime_InitFlex(play, &this->skelAnime, &gGerudoRedSkel, &gGerudoRedNeutralAnim, this->jointTable,
                       this->morphTable, GELDB_LIMB_MAX);
    // Collider_InitCylinder(play, &this->bodyCollider);
    // Collider_SetCylinder(play, &this->bodyCollider, thisx, &sBodyCylInit);

    Collider_InitQuad(play, &this->swordCollider);
    Collider_SetQuad(play, &this->swordCollider, thisx, &sSwordQuadInit);

    blureInit.p1StartColor[0] = blureInit.p1StartColor[1] = blureInit.p1StartColor[2] = blureInit.p1StartColor[3] =
        blureInit.p2StartColor[0] = blureInit.p2StartColor[1] = blureInit.p2StartColor[2] = blureInit.p1EndColor[0] =
            blureInit.p1EndColor[1] = blureInit.p1EndColor[2] = blureInit.p2EndColor[0] = blureInit.p2EndColor[1] =
                blureInit.p2EndColor[2] = 255;
    blureInit.p2StartColor[3] = 64;
    blureInit.p1EndColor[3] = blureInit.p2EndColor[3] = 0;
    blureInit.elemDuration = 8;
    blureInit.unkFlag = 0;
    blureInit.calcMode = 2;

    Effect_Add(play, &this->blureIndex, EFFECT_BLURE1, 0, 0, &blureInit);

    Player_Geldb_SetupIdle(this, play);
}

void Player_Geldb_Destroy(Actor* thisx, PlayState* play) {
    Player_Geldb* this = (Player_Geldb*)thisx;

    Effect_Delete(play, this->blureIndex);
    Collider_DestroyQuad(play, &this->swordCollider);
}

void Player_Geldb_SetupIdle(Player_Geldb* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedNeutralAnim, 4.0f);
    this->actionFunc = Player_Geldb_Idle;
}

void Player_Geldb_SetupRun(Player_Geldb* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedWalkAnim, -1.0f);
    this->actionFunc = Player_Geldb_Run;
}

void Player_Geldb_SetupAttack(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->speedXZ = 0.0f;
    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedSlashAnim, -1.0f);
    this->actionFunc = Player_Geldb_Attack;
}

void Player_Geldb_SetupSpinAttack(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedSpinAttackAnim, -1.0f);
    this->actionFunc = Player_Geldb_SpinAttack;
}

void Player_Geldb_SetupBlock(Player_Geldb* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedBlockAnim, -1.0f);
    this->actionFunc = Player_Geldb_Block;
}

void Player_Geldb_SetupSidewalk(Player_Geldb* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedSidestepAnim, -1.0f);
    this->actionFunc = Player_Geldb_Sidewalk;
}

void Player_Geldb_SetupJump(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.velocity.y += 4.0f;

    Animation_MorphToLoop(&this->skelAnime, &gGerudoRedJumpAnim, -1.0f);
    this->actionFunc = Player_Geldb_Jump;
}

void Player_Geldb_Idle(Player_Geldb* this, PlayState* play) {
    // If not already in the idle animation, switch to it.
    if (this->skelAnime.animation != &gGerudoRedNeutralAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gGerudoRedNeutralAnim, 4.0f);
    }
}

void Player_Geldb_Run(Player_Geldb* this, PlayState* play) {
    // If not already in the run animation, switch to it.
    if (this->skelAnime.animation != &gGerudoRedWalkAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gGerudoRedWalkAnim, -4.0f);
    }
}

void Player_Geldb_Attack(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->speedXZ = 0.0f;
    
    if (this->skelAnime.animation != &gGerudoRedSlashAnim) {
        Animation_PlayOnce(&this->skelAnime, &gGerudoRedSlashAnim);
    }
    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GERUDOFT_ATTACK);
        this->swordState = 1;
    }
    if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
        this->swordState = -1;
    }
    if (Animation_OnFrame(&this->skelAnime, Animation_GetLastFrame(&gGerudoRedSlashAnim))) {
        Player_Geldb_SetupIdle(this, play);
    }
}

void Player_Geldb_SpinAttack(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->skelAnime.animation != &gGerudoRedSpinAttackAnim) {
        Animation_Change(&this->skelAnime, &gGerudoRedSpinAttackAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGerudoRedSpinAttackAnim), ANIMMODE_ONCE, 0.0f);
    }

    if (player->chargeGerudoSpinAttack == 1) {
        player->speedXZ = 0.0f;
        if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
            // If we've reached frame 11.0f, pause the animation
            this->skelAnime.playSpeed = 0.0f;
        }
    } else if (player->chargeGerudoSpinAttack == 2) {
        // When the B button is released, resume the animation
        this->skelAnime.playSpeed = 1.0f;
        player->chargeGerudoSpinAttack = 0; // Reset to avoid repeating this block
    }

    if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
        this->swordState = 1;
    }

    if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GERUDOFT_ATTACK);
    }

    if (this->skelAnime.curFrame > 11.0f && this->skelAnime.curFrame <= 23.0f) {
        player->speedXZ = 6.0f;
    } else if (this->skelAnime.curFrame > 23.0f) {
        player->speedXZ = 0.0f;
        if (player->chargeGerudoSpinAttack == 0) {
            this->swordState = -1;
        }
    }

    if (Animation_OnFrame(&this->skelAnime, Animation_GetLastFrame(&gGerudoRedSpinAttackAnim))) {
        // if (player->chargeGerudoSpinAttack == 0) {
        //     this->swordState = -1;
        // }
        player->chargeGerudoSpinAttack = 0;
        Player_Geldb_SetupIdle(this, play);
    }
}

void Player_Geldb_Block(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    // If not already in the block animation, switch to it.
    if (this->skelAnime.animation != &gGerudoRedBlockAnim) {
        Animation_PlayOnce(&this->skelAnime, &gGerudoRedBlockAnim);
    }

    if (Animation_OnFrame(&this->skelAnime, Animation_GetLastFrame(&gGerudoRedBlockAnim)) && player->gerudoBlock == 0) {
        Player_Geldb_SetupIdle(this, play);
    }
}

void Player_Geldb_Sidewalk(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    // If not already in the sidestep animation, switch to it.
    if (this->skelAnime.animation != &gGerudoRedSidestepAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gGerudoRedSidestepAnim, 0.0f);
    }

    if (Animation_OnFrame(&this->skelAnime, Animation_GetLastFrame(&gGerudoRedSidestepAnim)) && player->gerudoSideWalk == 0) {
        Player_Geldb_SetupIdle(this, play);
    }
}

void Player_Geldb_Jump(Player_Geldb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    // If not already in the sidestep animation, switch to it.
    if (this->skelAnime.animation != &gGerudoRedJumpAnim) {
        Animation_PlayOnce(&this->skelAnime, &gGerudoRedJumpAnim);
    }

    if (Animation_OnFrame(&this->skelAnime, Animation_GetLastFrame(&gGerudoRedJumpAnim))) {
        player->gerudoJump = 0;
    }

    if (Animation_OnFrame(&this->skelAnime, Animation_GetLastFrame(&gGerudoRedJumpAnim)) && player->gerudoJump == 0) {
        Player_Geldb_SetupIdle(this, play);
    }
}

void Player_Geldb_Update(Actor* thisx, PlayState* play) {
    Player_Geldb* this = (Player_Geldb*)thisx;
    Player* player = GET_PLAYER(play);

    // Always check for speedXZ to transition states immediately.
    if (player->speedXZ > 0.0f && 
        this->actionFunc == Player_Geldb_Idle &&
        player->gerudoSideWalk == 0) {
        Player_Geldb_SetupRun(this, play);
    } else if (player->speedXZ == 0.0f && 
                this->actionFunc == Player_Geldb_Run &&
                this->actionFunc != Player_Geldb_Attack) {
        Player_Geldb_SetupIdle(this, play);
    }

    if (player->gerudoSideWalk == 1 && 
        this->actionFunc != Player_Geldb_Sidewalk &&
        this->actionFunc != Player_Geldb_SpinAttack &&
        this->actionFunc != Player_Geldb_Attack) {

        Player_Geldb_SetupSidewalk(this, play);
    }

    if (player->gerudoJump == 1 && this->actionFunc != Player_Geldb_Jump) {
        Player_Geldb_SetupJump(this, play);
    }

    if (player->startGerudoAttack == 1 && 
        this->actionFunc != Player_Geldb_SpinAttack && 
        this->actionFunc != Player_Geldb_Attack) {

        Player_Geldb_SetupAttack(this, play);
        player->startGerudoAttack = 0;
    }

    if (player->chargeGerudoSpinAttack == 1 && this->actionFunc != Player_Geldb_SpinAttack) {
        Player_Geldb_SetupSpinAttack(this, play);
    }

    if (player->gerudoBlock == 1) {
        Player_Geldb_SetupBlock(this, play);
    }

    // Then, proceed to update the animation.
    SkelAnime_Update(&this->skelAnime);

    // Call the current action function.
    this->actionFunc(this, play);

    // Synchronize position and rotation with the player.
    this->actor.world.pos = player->actor.world.pos;
    this->actor.shape.rot.y = player->actor.shape.rot.y;

    if (this->swordState > 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->swordCollider.base);
    }

    if (this->blinkState == 0) {
        if ((Rand_ZeroOne() < 0.1f) && ((play->gameplayFrames % 4) == 0)) {
            this->blinkState++;
        }
    } else {
        this->blinkState = (this->blinkState + 1) & 3;
    }
}

void Player_Geldb_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    Player_Geldb* this = (Player_Geldb*)thisx;

    static Vec3f footOffset = { 300.0f, 0.0f, 0.0f };
    static Vec3f swordTipOffset = { 0.0f, -3000.0f, 0.0f };
    static Vec3f swordHiltOffset = { 400.0f, 0.0f, 0.0f };
    static Vec3f swordQuadOffset1 = { 1600.0f, -4000.0f, 0.0f };
    static Vec3f swordQuadOffset0 = { -3000.0f, -2000.0f, 1300.0f };
    static Vec3f swordQuadOffset3 = { -3000.0f, -2000.0f, -1300.0f };
    static Vec3f swordQuadOffset2 = { 1000.0f, 1000.0f, 0.0f };
    static Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    Vec3f swordTip;
    Vec3f swordHilt;
    s32 bodyPart = -1;

    if (limbIndex == GELDB_LIMB_R_SWORD) {
        Matrix_MultVec3f(&swordQuadOffset1, &this->swordCollider.dim.quad[1]);
        Matrix_MultVec3f(&swordQuadOffset0, &this->swordCollider.dim.quad[0]);
        Matrix_MultVec3f(&swordQuadOffset3, &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&swordQuadOffset2, &this->swordCollider.dim.quad[2]);
        Collider_SetQuadVertices(&this->swordCollider, &this->swordCollider.dim.quad[0],
                                 &this->swordCollider.dim.quad[1], &this->swordCollider.dim.quad[2],
                                 &this->swordCollider.dim.quad[3]);
        Matrix_MultVec3f(&swordTipOffset, &swordTip);
        Matrix_MultVec3f(&swordHiltOffset, &swordHilt);

        if (this->swordState > 0) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->blureIndex), &swordTip, &swordHilt);
        } else if (this->swordState < 0 || (this->actionFunc != Player_Geldb_Attack && this->actionFunc != Player_Geldb_SpinAttack)) {
            // Clear the blure effect only if the swordState indicates to do so or if we're not in an attack function
            EffectBlure_AddSpace(Effect_GetByIndex(this->blureIndex));
            this->swordState = 0;
        }
    } else {
        Actor_SetFeetPos(&this->actor, limbIndex, GELDB_LIMB_L_FOOT, &footOffset, GELDB_LIMB_R_FOOT, &footOffset);
    }

    if (bodyPart >= 0) {
        Vec3f limbPos;

        Matrix_MultVec3f(&zeroVec, &limbPos);
        this->bodyPartsPos[bodyPart].x = limbPos.x;
        this->bodyPartsPos[bodyPart].y = limbPos.y;
        this->bodyPartsPos[bodyPart].z = limbPos.z;
    }

}

s32 Player_Geldb_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    Player_Geldb* this = (Player_Geldb*)thisx;
    return 0; 
}

void Player_Geldb_Draw(Actor* thisx, PlayState* play) {
    static void* eyeTextures[] = { gGerudoRedEyeOpenTex, gGerudoRedEyeHalfTex, gGerudoRedEyeShutTex,
                                   gGerudoRedEyeHalfTex };

    Player_Geldb* this = (Player_Geldb*)thisx;
    GfxPrint printer;
    Gfx* gfx;
    Player* player = GET_PLAYER(play);


    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    // Setup render settings for drawing. This might need to stay depending on your needs.
    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    
    // Load the appropriate eye texture based on the character's blink state.
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(eyeTextures[this->blinkState]));
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, player->tunicColor->g, player->tunicColor->b, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, player->tunicColor->r, player->tunicColor->g, player->tunicColor->b, 255);
    // gSPDisplayList(POLY_XLU_DISP++, this->gfx);

    // Draw the character's skeleton.
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          Player_Geldb_OverrideLimbDraw, Player_Geldb_PostLimbDraw, this);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    // OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    // gfx = POLY_OPA_DISP + 1;
    // gSPDisplayList(OVERLAY_DISP++, gfx);

    // GfxPrint_Init(&printer);
    // GfxPrint_Open(&printer, gfx);

    // GfxPrint_SetColor(&printer, 150, 0, 0, 255);
    // GfxPrint_SetPos(&printer, 1, 7);
    // GfxPrint_Printf(&printer, "speedXZ: %.2f", player->speedXZ);

    // GfxPrint_SetColor(&printer, 0, 150, 0, 255);
    // GfxPrint_SetPos(&printer, 1, 8);
    // GfxPrint_Printf(&printer, "gerudoJump: %u", player->gerudoJump);

    // GfxPrint_SetColor(&printer, 150, 0, 150, 255);
    // GfxPrint_SetPos(&printer, 1, 9);
    // GfxPrint_Printf(&printer, "startAttack: %u", player->startGerudoAttack);

    // GfxPrint_SetColor(&printer, 200, 200, 0, 255);
    // GfxPrint_SetPos(&printer, 1, 10);
    // GfxPrint_Printf(&printer, "chargeSpin: %u", player->chargeGerudoSpinAttack);

    // GfxPrint_SetColor(&printer, 200, 200, 0, 255);
    // GfxPrint_SetPos(&printer, 1, 11);
    // GfxPrint_Printf(&printer, "bHoldDuration: %.2f", player->bButtonHoldDuration);

    // GfxPrint_SetColor(&printer, 50, 50, 200, 255);
    // GfxPrint_SetPos(&printer, 1, 12);
    // GfxPrint_Printf(&printer, "gerudoBlock: %u", player->gerudoBlock);

    // gfx = GfxPrint_Close(&printer);
    // GfxPrint_Destroy(&printer);

    // gSPEndDisplayList(gfx++);
    // gSPBranchList(POLY_OPA_DISP, gfx);
    // POLY_OPA_DISP = gfx;

    // CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}