#ifndef Z_EFF_SS_MMMILK_H
#define Z_EFF_SS_MMMilk_H

#include "ultra64.h"
#include "global.h"

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ s16 scale;
    /* 0x26 */ u8 param;
    /* 0x28 */ Actor* actor;
    /* 0x2C */ u8 type;
} EffectSsMmMilkInitParams; // size = 0x30

typedef enum {
    /* 0x00 */ MMMILK_MILKBALL,
    /* 0x01 */ MMMILK_SPLASH
} MmMilkType;

typedef enum {
    /* 0x00 */ MMMILK_MILKBALL_GREEN,
    /* 0x01 */ MMMILK_MILKBALL_LIGHTBLUE,
    /* 0x02 */ MMMILK_MILKBALL_RED,
    /* 0x03 */ MMMILK_MILKBALL_YELLOW,
    /* 0x04 */ MMMILK_MILKBALL_BLUE,
    /* 0x05 */ MMMILK_MILKBALL_PURPLE,
    /* 0x06 */ MMMILK_MILKBALL_ORANGE,
    /* 0x07 */ MMMILK_MILKBALL_WHITE1,
    /* 0x08 */ MMMILK_MILKBALL_WHITE2
} MmMilkMilkBallParam;

typedef enum {
    /* 0x00 */ MMMILK_SPLASH_NO_ACTOR, // Don't attach to any actor. Stays at a fixed position.
    /* 0x01 */ MMMILK_SPLASH_PLAYER,   // Move to a random Player body part every frame.
    /* 0x02 */ MMMILK_SPLASH_MM        // Move to a random Phantom Ganon body part every frame.
} MmMilkSplashParam;

#endif
