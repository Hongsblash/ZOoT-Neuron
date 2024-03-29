#ifndef Z_EN_AEVUMTULIP_H
#define Z_EN_AEVUMTULIP_H

#include "ultra64.h"
#include "global.h"
#include "assets/objects/object_en_aevumtulip/object_en_aevumtulip.h"

struct En_Aevumtulip;

typedef void (*En_AevumtulipActionFunc)(struct En_Aevumtulip*, PlayState*);

typedef struct En_Aevumtulip {
    Actor actor;
    En_AevumtulipActionFunc actionFunc;
    LightInfo lightInfoGlow;
    LightNode* lightNodeGlow;
    LightInfo lightInfoNoGlow;
    LightNode* lightNodeNoGlow;
    s16 despawnTimer;
    s16 getItemId;
    u8 collected;
    u8 itemDropped;
    s16 collectibleFlag;
} En_Aevumtulip;

#endif
