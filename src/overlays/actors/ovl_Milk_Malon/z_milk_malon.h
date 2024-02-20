#ifndef Z_MILK_MALON_H
#define Z_MILK_MALON_H

#include "ultra64.h"
#include "global.h"
#include "rainbow.h"
#include "assets/objects/object_milk_malon/object_milk_malon.h"

struct MilkMalon;

typedef void (*MilkMalonActionFunc)(struct MilkMalon*, PlayState* play);

typedef struct MilkMalon {
    Actor actor;
    s32 animObjectSlot;
    SkelAnime skelAnime;
    Vec3s jointTable[GMILKMALONSKEL_NUM_LIMBS];
    Vec3s morphTable[GMILKMALONSKEL_NUM_LIMBS];
    ColliderCylinder collider;
    ColliderQuad swordCollider;
    ColliderCylinder shieldCollider;
    s8 swordState;
    s32 effectIndex;
    Vec3f targetPos;
    s16 targetYaw;
    MilkMalonActionFunc actionFunc;
    s16 alpha;
    s32 timer;
    s16 animFlagAndTimer;
    s16 shotsPerRound;
    f32 floatTimer; // Replace csTimer with a custom float timer
    f32 floatMagnitude; // Custom variable to replace fwork[GDF_FWORK_0]
    s16 lightBallTimer;
    f32 lightBallMag;
    f32 handLightBallScale;
    s8 envLightMode;
} MilkMalon; 

#endif
