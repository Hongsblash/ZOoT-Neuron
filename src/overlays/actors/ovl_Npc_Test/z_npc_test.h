#ifndef Z_NPC_TEST_H
#define Z_NPC_TEST_H

#include "ultra64.h"
#include "global.h"
#include "src/overlays/actors/ovl_En_Rd/z_en_rd.h"

struct NpcTest;

typedef void (*NpcTestActionFunc)(struct NpcTest*, PlayState* play);

typedef struct NpcTest {
    Actor actor;
    NpcTestActionFunc actionFunc;
    NpcInteractInfo interactInfo;
    SkelAnime skelAnime;
    Vec3s firePos[10];
    Vec3s jointTable[REDEAD_GIBDO_LIMB_MAX];
    Vec3s morphTable[REDEAD_GIBDO_LIMB_MAX];
    s16 headYRotation;
    s16 upperBodyYRotation;
    s16 alpha;
    ColliderCylinder collider;
} NpcTest; 

#endif
