#include "global.h"
#include "terminal.h"

u32 gIsCtrlr2Valid = false;

NORETURN void func_800D31A0(void) {
    osSyncPrintf(VT_FGCOL(RED) "\n**** Freeze!! ****\n" VT_RST);
    while (true) {
        Sleep_Msec(1000);
    }
}

void func_800D31F0(void) {
    #ifdef ENABLE_DEBUG_FEATURES
    gIsCtrlr2Valid = (gPadMgr.validCtrlrsMask & 2) != 0;
    #endif
}

void func_800D3210(void) {
    gIsCtrlr2Valid = false;
}
