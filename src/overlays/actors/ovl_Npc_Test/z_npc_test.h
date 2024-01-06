#ifndef Z_NPC_TEST_H
#define Z_NPC_TEST_H

#include "ultra64.h"
#include "global.h"

struct NpcTest;

typedef void (*NpcTestActionFunc)(struct NpcTest*, PlayState* play);

typedef struct NpcTest {
    Actor actor;
    NpcTestActionFunc actionFunc;
    NpcInteractInfo interactInfo;
} NpcTest; 

#endif
