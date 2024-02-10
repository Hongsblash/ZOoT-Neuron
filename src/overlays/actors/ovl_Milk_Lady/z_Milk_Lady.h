#ifndef Z_MILK_LADY_H
#define Z_MILK_LADY_H

#include "ultra64.h"
#include "global.h"
#include "assets/objects/object_milk_lady/object_milk_lady.h"

struct MilkLady;

typedef void (*MilkLadyActionFunc)(struct MilkLady*, PlayState* play);

typedef struct MilkLady {
    Actor actor;
    MilkLadyActionFunc actionFunc;
    NpcInteractInfo interactInfo;
    SkelAnime skelAnime;
    Vec3s firePos[10];
    Vec3s jointTable[GMILKLADYSKEL_NUM_LIMBS];
    Vec3s morphTable[GMILKLADYSKEL_NUM_LIMBS];
    s16 headYRotation;
    s16 upperBodyYRotation;
    s16 alpha;
    ColliderCylinder collider;
} MilkLady; 

#endif
