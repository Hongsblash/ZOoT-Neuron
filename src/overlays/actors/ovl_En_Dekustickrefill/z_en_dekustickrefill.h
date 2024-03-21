#ifndef Z_EN_DEKUSTICKREFILL_H
#define Z_EN_DEKUSTICKREFILL_H

#include "ultra64.h"
#include "global.h"

struct En_Dekustickrefill;

typedef void (*En_DekustickrefillActionFunc)(struct En_Dekustickrefill*, PlayState*);

typedef struct En_Dekustickrefill {
    Actor actor;
    En_DekustickrefillActionFunc actionFunc;
    s16 timer;
    u8 stickAvailable;
    u8 collected;
    f32 stickScale;
    f32 baseHeightAdjustment;
} En_Dekustickrefill;

#endif
