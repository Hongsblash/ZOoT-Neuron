#ifndef Z_MOLLY_NPC_H
#define Z_MOLLY_NPC_H

#include "ultra64.h"
#include "global.h"
#include "assets/objects/object_molly_npc/object_molly_npc.h"

struct MollyNpc;

typedef void (*MollyNpcActionFunc)(struct MollyNpc*, PlayState* play);

typedef struct MollyNpc {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[GMOLLYNPCSKEL_NUM_LIMBS];
    Vec3s morphTable[GMOLLYNPCSKEL_NUM_LIMBS];
    ColliderCylinder collider;
    ColliderQuad swordCollider;
    s8 swordState;
    s32 effectIndex;
    Vec3f targetPos;
    s16 targetYaw;
    MollyNpcActionFunc actionFunc;
    s16 alpha;

} MollyNpc; 

#endif
