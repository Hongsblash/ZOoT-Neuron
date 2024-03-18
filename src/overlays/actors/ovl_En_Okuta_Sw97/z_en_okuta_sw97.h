#ifndef Z_EN_OKUTA_SW97_H
#define Z_EN_OKUTA_SW97_H

#include "ultra64.h"
#include "global.h"

struct En_Okuta_Sw97;

typedef void (*En_Okuta_Sw97ActionFunc)(struct En_Okuta_Sw97*, PlayState*);

typedef struct En_Okuta_Sw97 {
    Actor actor;
    En_Okuta_Sw97ActionFunc actionFunc;
    SkelAnime skelAnime;
    s16 timer;
    s16 numShots;
    Vec3s jointTable[38];
    Vec3s morphTable[38];
    f32 jumpHeight;
    Vec3f headScale;
    ColliderCylinder collider;
} En_Okuta_Sw97;

#endif
