#ifndef Z_PLAYER_GELDB_H
#define Z_PLAYER_GELDB_H

#include "ultra64.h"
#include "global.h"

struct Player_Geldb;

typedef enum {
    /* 0x00 */ GELDB_LIMB_NONE,
    /* 0x01 */ GELDB_LIMB_ROOT,
    /* 0x02 */ GELDB_LIMB_TORSO,
    /* 0x03 */ GELDB_LIMB_NECK,
    /* 0x04 */ GELDB_LIMB_PONYTAIL,
    /* 0x05 */ GELDB_LIMB_VEIL,
    /* 0x06 */ GELDB_LIMB_HEAD,
    /* 0x07 */ GELDB_LIMB_R_UPPER_ARM,
    /* 0x08 */ GELDB_LIMB_R_FOREARM,
    /* 0x09 */ GELDB_LIMB_R_WRIST,
    /* 0x0A */ GELDB_LIMB_R_HAND,
    /* 0x0B */ GELDB_LIMB_R_SWORD,
    /* 0x0C */ GELDB_LIMB_L_UPPER_ARM,
    /* 0x0D */ GELDB_LIMB_L_FOREARM,
    /* 0x0E */ GELDB_LIMB_L_WRIST,
    /* 0x0F */ GELDB_LIMB_L_HAND,
    /* 0x10 */ GELDB_LIMB_L_SWORD,
    /* 0x11 */ GELDB_LIMB_L_THIGH,
    /* 0x12 */ GELDB_LIMB_L_SHIN,
    /* 0x13 */ GELDB_LIMB_L_FOOT,
    /* 0x14 */ GELDB_LIMB_R_THIGH,
    /* 0x15 */ GELDB_LIMB_R_SHIN,
    /* 0x16 */ GELDB_LIMB_R_FOOT,
    /* 0x17 */ GELDB_LIMB_WAIST,
    /* 0x18 */ GELDB_LIMB_MAX
} EnGeldBLimb;

typedef void (*Player_GeldbActionFunc)(struct Player_Geldb*, PlayState*);

typedef struct Player_Geldb {
    Actor actor;
    Player_GeldbActionFunc actionFunc;
    SkelAnime skelAnime;
    Vec3s jointTable[GELDB_LIMB_MAX];
    Vec3s morphTable[GELDB_LIMB_MAX];
    ColliderCylinder collider;
    ColliderQuad swordCollider;
    s32 blureIndex;
    s16 swordState;
    Vec3s bodyPartsPos[10];
    u8 blinkState;
} Player_Geldb;

#endif
