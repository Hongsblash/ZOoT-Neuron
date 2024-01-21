#ifndef Z_MOLLY_NPC_H
#define Z_MOLLY_NPC_H

#include "ultra64.h"
#include "global.h"

struct MollyNpc;

typedef void (*MollyNpcActionFunc)(struct MollyNpc*, PlayState* play);

typedef struct MollyNpc {
    Actor actor;
    MollyNpcActionFunc actionFunc;
    NpcInteractInfo interactInfo;
    SkelAnime skelAnime;
    Vec3s jointTable[11];
    Vec3s morphTable[11];
    s16 headYRotation;
    s16 upperBodyYRotation;
    s16 alpha;
    ColliderCylinder collider;
} MollyNpc; 

#endif
