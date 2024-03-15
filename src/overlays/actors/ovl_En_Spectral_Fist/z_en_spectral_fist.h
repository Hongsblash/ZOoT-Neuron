#ifndef Z_EN_SPECTRAL_FIST_H
#define Z_EN_SPECTRAL_FIST_H

#include "ultra64.h"
#include "global.h"
#include "assets/objects/object_en_spectral_fist/object_en_spectral_fist.h"

struct En_Spectral_Fist;

typedef enum {
    FIST_CHARGING, // Moving up
    FIST_ATTACKING, // Moving down
    FIST_COOLDOWN
} FistAttackPhase;

typedef void (*En_Spectral_FistActionFunc)(struct En_Spectral_Fist*, PlayState*);

typedef struct En_Spectral_Fist {
    Actor actor;
    En_Spectral_FistActionFunc actionFunc;
    SkelAnime skelAnime;
    Vec3s jointTable[GSPECTRALFISTSKEL_NUM_LIMBS];
    Vec3s morphTable[GSPECTRALFISTSKEL_NUM_LIMBS];
    s16 alpha;
    FistAttackPhase attackPhase;
    u8 attackTimer;
    ColliderCylinder collider;
    u8 shockwaveTriggered;
    f32 newYPosition;
} En_Spectral_Fist;

#endif
