/*
 * File: z_en_spectral_fist.c
 * Overlay: ovl_En_Spectral_Fist
 * Description: Custom Actor
 */

#include "z_en_spectral_fist.h"

#define FLAGS (0)

void En_Spectral_Fist_Init(Actor* thisx, PlayState* play);
void En_Spectral_Fist_Destroy(Actor* thisx, PlayState* play);
void En_Spectral_Fist_Update(Actor* thisx, PlayState* play);
void En_Spectral_Fist_Draw(Actor* thisx, PlayState* play);

void En_Spectral_Fist_DoNothing(En_Spectral_Fist* this, PlayState* play);

ActorInit En_Spectral_Fist_InitVars = {
    ACTOR_EN_SPECTRAL_FIST,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_EN_SPECTRAL_FIST,
    sizeof(En_Spectral_Fist),
    (ActorFunc)En_Spectral_Fist_Init,
    (ActorFunc)En_Spectral_Fist_Destroy,
    (ActorFunc)En_Spectral_Fist_Update,
    (ActorFunc)En_Spectral_Fist_Draw,
};

void En_Spectral_Fist_Init(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;

    this->actionFunc = En_Spectral_Fist_DoNothing;
}

void En_Spectral_Fist_Destroy(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;
}

void En_Spectral_Fist_Update(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;

    this->actionFunc(this, play);
}

void En_Spectral_Fist_Draw(Actor* thisx, PlayState* play) {
    En_Spectral_Fist* this = (En_Spectral_Fist*)thisx;
}

void En_Spectral_Fist_DoNothing(En_Spectral_Fist* this, PlayState* play) {

}
