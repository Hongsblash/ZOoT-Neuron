#ifndef Z_MILK_MALON_H
#define Z_MILK_MALON_H

#include "ultra64.h"
#include "global.h"
#include "assets/objects/object_milk_malon/object_milk_malon.h"

struct MilkMalon;

typedef void (*MilkMalonActionFunc)(struct MilkMalon*, PlayState* play);

typedef struct MilkMalon {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[GMILKMALONSKEL_NUM_LIMBS];
    Vec3s morphTable[GMILKMALONSKEL_NUM_LIMBS];
    ColliderCylinder collider;
    ColliderQuad swordCollider;
    s8 swordState;
    s32 effectIndex;
    Vec3f targetPos;
    s16 targetYaw;
    MilkMalonActionFunc actionFunc;
    s16 alpha;
    s32 timer;
} MilkMalon; 

#endif
