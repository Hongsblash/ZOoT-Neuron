#ifndef Z_EN_SPECTRAL_FIST_H
#define Z_EN_SPECTRAL_FIST_H

#include "ultra64.h"
#include "global.h"
#include "assets/objects/object_en_spectral_fist/object_en_spectral_fist.h"

struct En_Spectral_Fist;

typedef void (*En_Spectral_FistActionFunc)(struct En_Spectral_Fist*, PlayState*);

typedef struct En_Spectral_Fist {
    Actor actor;
    En_Spectral_FistActionFunc actionFunc;
} En_Spectral_Fist;

#endif
