#ifndef Z_MILK_MALON_H
#define Z_MILK_MALON_H

#include "ultra64.h"
#include "global.h"
#include "rainbow.h"
#include "assets/objects/object_milk_malon/object_milk_malon.h"

struct MilkMalon;

typedef void (*MilkMalonActionFunc)(struct MilkMalon*, PlayState* play);

typedef enum {
    /* 0 */ MM_FLY_PAINTING,
    /* 1 */ MM_FLY_NEUTRAL,
    /* 2 */ MM_FLY_VOLLEY,
    /* 3 */ MM_FLY_RETURN,
    /* 4 */ MM_FLY_CHARGE
} MilkmalonFlyMode;

typedef enum {
    /*  0 */ MM_FLOAT_SPEED,
    /*  1 */ MM_END_FRAME,
    /*  2 */ MM_EYE_BRIGHTNESS,
    /*  3 */ MM_CAMERA_ZOOM,
    /*  4 */ MM_CAMERA_ANGLE,
    /*  5 */ MM_EYE_ALPHA,
    /* 13 */ MM_FLOAT_COUNT = 13
} MilkMalonF32Var;

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
    f32 floatMagnitude; // Custom variable to replace fwork[GDF_FWORK_0]
    s16 lightBallTimer;
    f32 lightBallMag;
    f32 handLightBallScale;
    s8 envLightMode;
    s32 throwFrame;
    Vec3f ballPos;
    u8 returnCount;
    u8 returnSuccess;
    u8 flyMode;
    Vec3f bodyPartsPos[27]; 
    f32 returnEndFrame;
    u8 returnFlag;
    u8 energyBallActive;
    u8 shockTimer;
    u8 vulnerableTimer;
    s16 damageState;
    f32 fwork[MM_FLOAT_COUNT];
    f32 vulnerableEndFrame;
} MilkMalon; 

#endif
