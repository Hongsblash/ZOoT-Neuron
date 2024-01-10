#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "test_room_scene.h"
#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

/**
 * Header Child Day (Default)
*/
#define LENGTH_TEST_ROOM_ROOM_0_HEADER00_OBJECTLIST 1
#define LENGTH_TEST_ROOM_ROOM_0_HEADER00_ACTORLIST 1
SceneCmd test_room_room_0_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 0),
    SCENE_CMD_ROOM_SHAPE(&test_room_room_0_shapeHeader),
    SCENE_CMD_OBJECT_LIST(LENGTH_TEST_ROOM_ROOM_0_HEADER00_OBJECTLIST, test_room_room_0_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_TEST_ROOM_ROOM_0_HEADER00_ACTORLIST, test_room_room_0_header00_actorList),
    SCENE_CMD_END(),
};

s16 test_room_room_0_header00_objectList[LENGTH_TEST_ROOM_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_BOX,
};

ActorEntry test_room_room_0_header00_actorList[LENGTH_TEST_ROOM_ROOM_0_HEADER00_ACTORLIST] = {
    // Treasure Chest
    {
        /* Actor ID   */ ACTOR_EN_BOX,
        /* Position   */ { 0, 0, 33 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0BC1
    },
};

RoomShapeNormal test_room_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(test_room_room_0_shapeDListEntry),
    test_room_room_0_shapeDListEntry,
    test_room_room_0_shapeDListEntry + ARRAY_COUNT(test_room_room_0_shapeDListEntry)
};

RoomShapeDListsEntry test_room_room_0_shapeDListEntry[1] = {
    { test_room_room_0_entry_0_opaque, test_room_room_0_entry_0_transparent },
};

Gfx test_room_room_0_entry_0_opaque[] = {
	gsSPDisplayList(test_room_dl_Ground_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Gfx test_room_room_0_entry_0_transparent[] = {
	gsSPDisplayList(test_room_dl_Ground_001_mesh_layer_Transparent),
	gsSPEndDisplayList(),
};

u64 test_room_dl_red_carpet3_rgba32[] = {
	0x331419ff35171dff, 0x360e14ff3d171cff, 0x36151bff3a1218ff, 0x431e24ff4b0912ff, 0x460b15ff3b0c15ff, 0x6c0916ff5f0d18ff, 0x48111aff60111bff, 0x2f080dff3d0d14ff, 
	0x430d16ff290e14ff, 0x7d1b24ff4e191fff, 0x550d17ff6f0b17ff, 0x3c0b13ff3a070fff, 0x530b14ff431e24ff, 0x3a1218ff36151bff, 0x3d171cff360e14ff, 0x35171dff331419ff, 
	0x261f24ff2b252aff, 0x060a0eff2c272bff, 0x241e23ff251f23ff, 0x352f33ff6c1f2bff, 0x711623ff641a25ff, 0x500e18ff370e15ff, 0x380f17ff4e0b13ff, 0x4c0c14ff36070fff, 
	0x370913ff53131dff, 0x4d0912ff42151bff, 0x361017ff610d18ff, 0x620f1aff620a15ff, 0x5e121eff352f33ff, 0x251f23ff241e23ff, 0x2c272bff060a0eff, 0x2b252aff261f24ff, 
	0x312e31ff0f1014ff, 0x151114ff2f1319ff, 0x312226ff211f22ff, 0x221d21ff5e202bff, 0x671b27ff5c0712ff, 0x561f27ff5c131fff, 0x340d14ff302c31ff, 0x4b0c15ff4e0914ff, 
	0x4e0813ff480e15ff, 0x2d2325ff34171bff, 0x692026ff561c24ff, 0x5a111aff60101bff, 0x722c36ff221d21ff, 0x211f22ff312226ff, 0x2f1319ff151114ff, 0x0f1014ff312e31ff, 
	0x2e0e15ff1c0d12ff, 0x270c14ff311519ff, 0x3a101bff31181cff, 0x44232aff0a0c10ff, 0x63212aff772c35ff, 0x41242aff2c0c13ff, 0x611f2aff2d0b10ff, 0x6b131fff711722ff, 
	0x731521ff5d111bff, 0x2c0c13ff5e1920ff, 0x2d0c10ff0f0a0dff, 0x7e2330ff68212aff, 0x0d0b10ff44232aff, 0x31181cff3a101bff, 0x311519ff270c14ff, 0x1c0d12ff2e0e15ff, 
	0x151418ff141619ff, 0x360c13ff3f2127ff, 0x3a2427ff451a21ff, 0x4a1c25ff0d0d10ff, 0x0d0d10ff1e171bff, 0x211217ff232024ff, 0x580e19ff7b1524ff, 0x5e0e18ff700b17ff, 
	0x690815ff600c17ff, 0x75141fff541a20ff, 0x241e22ff1a1015ff, 0x1c1519ff101012ff, 0x0d0d11ff4a1c25ff, 0x451a21ff3a2427ff, 0x3f2127ff360c13ff, 0x141619ff151418ff, 
	0x52111eff332a30ff, 0x21070dff40131cff, 0x39181cff54101dff, 0x4c141cff3d2c32ff, 0x272125ff30282cff, 0x2f0d13ff190b10ff, 0x70252eff7f2835ff, 0x821b29ff7b0917ff, 
	0x750a17ff831723ff, 0x6e1b25ff792f38ff, 0x2b0c12ff310e13ff, 0x2f252aff272326ff, 0x251d21ff4c141cff, 0x54101dff39181cff, 0x40131cff21070dff, 0x332a30ff52111eff, 
	0x650d19ff53282dff, 0x070a0dff300b13ff, 0x420c16ff55101aff, 0x160c10ff20181cff, 0x261f24ff362c31ff, 0x371419ff470f18ff, 0x462a31ff39121aff, 0x511119ff831a28ff, 
	0x8b1926ff500c16ff, 0x350d13ff3b141aff, 0x4b1920ff3c1116ff, 0x2b2427ff302428ff, 0x1b1518ff160c10ff, 0x55101aff420c16ff, 0x300b13ff070a0dff, 0x53282dff650d19ff, 
	0x4b0912ff6c1f2bff, 0x5e202bff0a0c10ff, 0x0d0d10ff3d2c32ff, 0x20181cff4d1219ff, 0x433338ff1f191cff, 0x4a1d23ff4d2429ff, 0x341a1fff5d141dff, 0x781420ff3e080fff, 
	0x3e0f18ff872730ff, 0x701827ff34161eff, 0x2e1219ff5b2f35ff, 0x1c1d1fff383033ff, 0x461419ff20181cff, 0x3d2c32ff0d0d10ff, 0x0a0c10ff5e202bff, 0x6c1f2bff4b0912ff, 
	0x460b15ff711623ff, 0x671b27ff63212aff, 0x0d0d10ff272125ff, 0x261f24ff3c2a2fff, 0x2c191eff241316ff, 0x16080bff5f141dff, 0x55171dff3e1017ff, 0x3e171bff5b0f19ff, 
	0x5a0f19ff3b0f17ff, 0x4c131cff5a2028ff, 0x701b28ff16090eff, 0x261218ff25171cff, 0x392529ff261f24ff, 0x272125ff0d0d10ff, 0x63212aff671b27ff, 0x711623ff460b15ff, 
	0x3b0c15ff641a25ff, 0x5c0712ff772c35ff, 0x1e171bff30282cff, 0x362c31ff2f1a1eff, 0x36171cff580912ff, 0x781825ff140d13ff, 0x400f18ff610b14ff, 0x660d17ff68141dff, 
	0x650f18ff670d16ff, 0x5f0b16ff52222cff, 0x160f15ff6e131eff, 0x6e0d15ff461f25ff, 0x362126ff362c31ff, 0x30282cff1e171bff, 0x772c35ff5c0712ff, 0x641a25ff3b0c15ff, 
	0x6c0916ff500e18ff, 0x561f27ff41242aff, 0x211217ff2f0d13ff, 0x371419ff600e19ff, 0x6e0b19ff58101aff, 0x470f18ff2e0a0eff, 0x54121cff70121bff, 0x75101cff64151dff, 
	0x761a24ff831720ff, 0x6e141fff54141fff, 0x390812ff51111bff, 0x630e16ff610c15ff, 0x6c141dff371419ff, 0x2f0d13ff211217ff, 0x41242aff561f27ff, 0x500e18ff6c0916ff, 
	0x5f0d18ff370e15ff, 0x5c131fff2c0c13ff, 0x232024ff190b10ff, 0x470f18ff560e16ff, 0x670e17ff821724ff, 0x67121cff650b1aff, 0x3d0e15ff6e121cff, 0x5d0c14ff62141eff, 
	0x53141dff550e19ff, 0x600e19ff46121aff, 0x561219ff611924ff, 0x831d27ff74151eff, 0x661821ff470f18ff, 0x190b10ff232024ff, 0x2c0c13ff5c131fff, 0x370e15ff5f0d18ff, 
	0x48111aff380f17ff, 0x340d14ff611f2aff, 0x580e19ff70252eff, 0x462a31ff721822ff, 0x7d1321ff481117ff, 0x7b111aff8b2330ff, 0x540d16ff570e18ff, 0x68101aff530d16ff, 
	0x64181fff6e1e27ff, 0x57101aff491118ff, 0x7c121eff8f202aff, 0x5c1923ff7a1825ff, 0x6d1019ff462a31ff, 0x70252eff580e19ff, 0x611f2aff340d14ff, 0x380f17ff48111aff, 
	0x60111bff4e0b13ff, 0x302c31ff2d0b10ff, 0x7b1524ff7f2835ff, 0x39121aff5f2830ff, 0x130d0fff600f17ff, 0x521218ff270d10ff, 0x6e131eff7c1722ff, 0x961c28ff882e39ff, 
	0x822a33ff891420ff, 0x761a24ff7c222fff, 0x2a0a12ff510b14ff, 0x5d0912ff1d0e13ff, 0x6a2930ff39121aff, 0x7f2835ff7b1524ff, 0x2d0b10ff302c31ff, 0x4e0b13ff60111bff, 
	0x2f080dff4c0c14ff, 0x4b0c15ff6b131fff, 0x5e0e18ff821b29ff, 0x511119ff3d171dff, 0x4a1319ff941c29ff, 0x7f111fffa7293bff, 0x942733ffa52433ff, 0xb12f3bff7a1f27ff, 
	0x7f121cffa3313cff, 0x992633ff8f2a35ff, 0xac1e2cff8c1721ff, 0x841322ff60171eff, 0x472026ff511119ff, 0x821b29ff5e0e18ff, 0x6b131fff4b0c15ff, 0x4c0c14ff2f080dff, 
	0x3d0d14ff36070fff, 0x4e0914ff711722ff, 0x700b17ff7b0917ff, 0x831a28ff160f12ff, 0x801b25ff51080fff, 0x8f2b36ff53161cff, 0x5c161eff4f1017ff, 0x911f2dff801a26ff, 
	0x7d1f2aff891b25ff, 0x5a101bff591a21ff, 0x4c1017ff89262fff, 0x4b0c14ff87131eff, 0x35151cff831a28ff, 0x7b0917ff700b17ff, 0x711722ff4e0914ff, 0x36070fff3d0d14ff, 
	0x430d16ff370913ff, 0x4e0813ff731521ff, 0x690815ff750a17ff, 0x8b1926ff1a0f12ff, 0x7e131dff5e0d13ff, 0x7e1d28ff56171dff, 0x621820ff651b22ff, 0x992733ff812029ff, 
	0x7c1f2dff8b252dff, 0x6f2029ff672f34ff, 0x4d191eff882a35ff, 0x5e121cff8f1c26ff, 0x3d1820ff8b1926ff, 0x750a17ff690815ff, 0x731521ff4e0813ff, 0x370913ff430d16ff, 
	0x290e14ff53131dff, 0x480e15ff5d111bff, 0x600c17ff831723ff, 0x500c16ff481c25ff, 0x3d0d11ff81111cff, 0x871623ff991e2eff, 0x781622ff921a27ff, 0x9c2e3aff872f36ff, 
	0x8a2129ff922c37ff, 0x8f222cff7a1b25ff, 0xa41827ff800b15ff, 0x76101cff550f16ff, 0x321216ff500c16ff, 0x831723ff600c17ff, 0x5d111bff480e15ff, 0x53131dff290e14ff, 
	0x7d1b24ff4d0912ff, 0x2d2325ff2c0c13ff, 0x75141fff6e1b25ff, 0x350d13ff4a1b24ff, 0x261316ff640b14ff, 0x520c14ff3d0e15ff, 0x690c16ff7d1621ff, 0x961623ff761420ff, 
	0x7b1d26ff951926ff, 0x852d37ff711422ff, 0x3e0c15ff600d18ff, 0x6b0d18ff2f1017ff, 0x40161cff350d13ff, 0x6e1b25ff75141fff, 0x2c0c13ff2d2325ff, 0x4d0912ff7d1b24ff, 
	0x4e191fff42151bff, 0x34171bff5e1920ff, 0x541a20ff792f38ff, 0x3b141aff802d38ff, 0x73121cff371014ff, 0x79151dff88202eff, 0x5f1a26ff530812ff, 0x630f18ff550e16ff, 
	0x67131dff5d0e17ff, 0x560b15ff4d1018ff, 0x842531ff790f19ff, 0x2f0910ff731825ff, 0x88353bff3b141aff, 0x792f38ff541a20ff, 0x5e1920ff34171bff, 0x42151bff4e191fff, 
	0x550d17ff361017ff, 0x692026ff2d0c10ff, 0x241e22ff2b0c12ff, 0x4b1920ff61121dff, 0x6b151fff871423ff, 0x6d1621ff610f1aff, 0x450d15ff600e17ff, 0x640d16ff64141eff, 
	0x4f0c15ff5b151fff, 0x661420ff380a11ff, 0x703038ff5d1520ff, 0x91202dff721d26ff, 0x530e16ff4b1920ff, 0x2b0c12ff241e22ff, 0x2d0c10ff692026ff, 0x361017ff550d17ff, 
	0x6f0b17ff610d18ff, 0x561c24ff0f0a0dff, 0x1a1015ff310e13ff, 0x3c1116ff5f0d17ff, 0x71101dff4e0e16ff, 0x440b15ff37080dff, 0x611d26ff68101cff, 0x761a25ff6d1b24ff, 
	0x711822ff791620ff, 0x6c1220ff631c29ff, 0x3e0c16ff460f17ff, 0x590b13ff65121bff, 0x6c131cff3c1116ff, 0x310e13ff1a1015ff, 0x0f0a0dff561c24ff, 0x610d18ff6f0b17ff, 
	0x3c0b13ff620f1aff, 0x5a111aff7e2330ff, 0x1c1519ff2f252aff, 0x2b2427ff371c20ff, 0x44161dff600b14ff, 0x731925ff150d13ff, 0x3e0c15ff750f19ff, 0x7c131eff6d1720ff, 
	0x671019ff7e0f1aff, 0x741922ff400f19ff, 0x130e13ff701822ff, 0x730c15ff471921ff, 0x3b1d24ff2b2427ff, 0x2f252aff1c1519ff, 0x7e2330ff5a111aff, 0x620f1aff3c0b13ff, 
	0x3a070fff620a15ff, 0x60101bff68212aff, 0x101012ff272326ff, 0x302428ff2c1d20ff, 0x321d22ff2b1519ff, 0x2d0a0fff45141bff, 0x58141cff380d15ff, 0x42111aff5e111dff, 
	0x520b14ff3d141aff, 0x410f19ff531920ff, 0x54141eff2c090eff, 0x291016ff3c272dff, 0x3d2f31ff302428ff, 0x272326ff101012ff, 0x68212aff60101bff, 0x620a15ff3a070fff, 
	0x530b14ff5e121eff, 0x722c36ff0d0b10ff, 0x0d0d11ff251d21ff, 0x1b1518ff4b151bff, 0x2a1c21ff141013ff, 0x63373cff3e1219ff, 0x3b1318ff601c24ff, 0x701820ff45060eff, 
	0x450e18ff710e19ff, 0x751d2dff2c1319ff, 0x431f27ff51272dff, 0x131316ff342e31ff, 0x3e1417ff1b1518ff, 0x251d21ff0d0d11ff, 0x0d0b10ff722c36ff, 0x5e121eff530b14ff, 
	0x64121eff4e1a20ff, 0x080a0dff2d0f16ff, 0x380e16ff5d1f2aff, 0x110d0fff29161aff, 0x362c30ff292225ff, 0x381c22ff551a22ff, 0x201017ff2b0a13ff, 0x541c21ff8b202eff, 
	0x811321ff541620ff, 0x290c11ff2f1118ff, 0x4b1b23ff441d22ff, 0x231b1eff33282bff, 0x281a1eff110d0fff, 0x5d1f2aff380e16ff, 0x2d0f16ff080a0dff, 0x4e1a20ff64121eff, 
	0x4d131bff392c30ff, 0x1f090eff350e17ff, 0x3e2325ff49121cff, 0x44181eff1d191eff, 0x171518ff2c2227ff, 0x320f14ff1f0b12ff, 0x77222dff731926ff, 0x861424ff861522ff, 
	0x7e1220ff881926ff, 0x701622ff731521ff, 0x2e0c12ff390f14ff, 0x251d21ff211d20ff, 0x262023ff44181eff, 0x49121cff3e2325ff, 0x350e17ff1f090eff, 0x392c30ff4d131bff, 
	0x2c272aff171518ff, 0x3e0b13ff3e0f15ff, 0x34151aff40121aff, 0x4e1e28ff150c10ff, 0x1a161aff1d181cff, 0x28171dff1c1c20ff, 0x530b16ff730d1bff, 0x650d19ff740d1bff, 
	0x6c101bff6b0b16ff, 0x690912ff5a1c24ff, 0x161215ff1e0f15ff, 0x1b1619ff121315ff, 0x0e0c10ff4e1e28ff, 0x40121aff34151aff, 0x3e0f15ff3e0b13ff, 0x171518ff2c272aff, 
	0x23080eff1f0a0fff, 0x2d131aff320d15ff, 0x370c15ff38171eff, 0x432126ff0a0d10ff, 0x46181fff6a202bff, 0x090b0dff120d11ff, 0x5a1420ff27080fff, 0x61151eff700f1aff, 
	0x6f0d1aff671c24ff, 0x24090fff561f23ff, 0x3e2528ff0a0a0dff, 0x701a27ff46151dff, 0x0e0d12ff432126ff, 0x38171eff370c15ff, 0x320d15ff2d131aff, 0x1f0a0fff23080eff, 
	0x332c30ff18161aff, 0x1e1419ff3d131aff, 0x321e22ff1e171cff, 0x2b2326ff51131dff, 0x620b17ff650b17ff, 0x59232dff5f1924ff, 0x3b0f15ff2f2025ff, 0x5b111cff55111bff, 
	0x510a15ff4e1018ff, 0x422f31ff46131aff, 0x7c2a33ff4f1e25ff, 0x64151fff680d17ff, 0x611e27ff2b2326ff, 0x1e171cff321e22ff, 0x3d131aff1e1419ff, 0x18161aff332c30ff, 
	0x211f21ff2e2b2eff, 0x080b0eff332c30ff, 0x211a1eff1c181aff, 0x2e282cff6a1d29ff, 0x75212bff540e17ff, 0x57111cff300d14ff, 0x3f151cff5a101cff, 0x500d15ff410e17ff, 
	0x360c15ff4e1019ff, 0x5c1019ff512328ff, 0x2a0b11ff6a1721ff, 0x5f0e17ff6f1924ff, 0x661e2aff2e282cff, 0x1c181aff211a1eff, 0x332c30ff080b0eff, 0x2e2b2eff211f21ff, 
	0x34191fff331f23ff, 0x2f1217ff301a1eff, 0x341d21ff453235ff, 0x351519ff510812ff, 0x490915ff350911ff, 0x660915ff63131cff, 0x390a11ff5a141cff, 0x3a0b11ff3e0e15ff, 
	0x3f0e16ff26070dff, 0x630d16ff400e15ff, 0x510813ff680711ff, 0x420d15ff440911ff, 0x5b0b17ff351519ff, 0x453235ff341d21ff, 0x301a1eff2f1217ff, 0x331f23ff34191fff, 
	
};

u64 test_room_dl_dark_brick_wall_ci8[] = {
	0x0000010200000303, 0x0303030303030302, 0x0200000004050404, 0x0101010101020000, 0x06070808090a0b0b, 0x0b0c0c0c0d0c0c0e, 0x0e0f001011080808, 0x080808090b0e1200, 
	0x1213141415151515, 0x1515151516171819, 0x1a1b011c0e1d181d, 0x1d1d17181e1a0603, 0x1f2021222121211d, 0x171515211d1d1d1d, 0x23240025261d1a18, 0x1918171d1d1a0603, 
	0x27111d1d1d281d29, 0x1d17211d1d1a211a, 0x1f0600082a1d1d2b, 0x1d21191a1d1f2c00, 0x241c211d212b1828, 0x1d1d1d1d1d281d12, 0x1f24000b151d1d1d, 0x1d1d1a1a1d232c00, 
	0x2408211a1d1a1d1a, 0x1d1d1d1d191d1f12, 0x271b000b2a1d2b21, 0x281d2119182d2e00, 0x240a211a1d2b211d, 0x21211d281d1f2d1f, 0x2d1b000a151d1d21, 0x1d1d212b1f272c00, 
	0x1b0d281d1a1d281a, 0x211d1d21281a2312, 0x1f1b000b29232b2f, 0x1d181d1a1f302c00, 0x240c1e211d1a272b, 0x281d1d311a1f1a32, 0x271b000a212b2828, 0x1d1d231a2d242e00, 
	0x330a1721211a211d, 0x181a23281a231f27, 0x1f0603342121281d, 0x3131271f27062c00, 0x330d2128231f1d1d, 0x1a1a1a271a271b1a, 0x2d1b03342b282312, 0x12272d241b1b0400, 
	0x060e18231a1a2b23, 0x2723271f23242427, 0x3206000a28281f27, 0x271b2424302c0500, 0x06351a23271f2324, 0x2d27231f27242727, 0x1b2c00341d231f24, 0x24061b241b2c0500, 
	0x0521272d0606062c, 0x242424062406061b, 0x2c0400361227241b, 0x062e062c2c050100, 0x0001000000000002, 0x0300000303030303, 0x0000002e05010203, 0x0000000000000000, 
	0x050b0808370b0b0a, 0x0c0c381035353516, 0x352a16160e261626, 0x1515292b2f230400, 0x1d13390e3a3a3b0e, 0x3535353939353a35, 0x393535393c39380e, 0x3516161515280600, 
	0x313d211821291d2b, 0x1521181d21182117, 0x1d1d2b1d17182823, 0x231e232327242e03, 0x1f3e2b151518151d, 0x181d1d1d19281d1d, 0x1d2828211d1a2327, 0x2323231f2d1b2c00, 
	0x1f3f2b17181d2b1d, 0x2b211d191e1e231d, 0x1a2d232323122323, 0x1a1f2d2424242e00, 0x273b17231d1f1a27, 0x272327271f1f1a28, 0x1f27281223312323, 0x122d2723271b2e00, 
	0x273b271527282828, 0x12231f2727232828, 0x1223312323311f32, 0x31312d1b1b1b2e00, 0x2d0e281a2823231f, 0x2712122723272327, 0x241a1f1f24302312, 0x2d1b1b1b1b060400, 
	0x2735231a27301224, 0x0633241b241b2c2c, 0x061b0633120f3333, 0x241b0606062c0400, 0x2d39231f12302724, 0x1b24062406241b23, 0x4030122724241b1b, 0x241b1b1b2d240500, 
	0x2416272d2d242406, 0x2706242423272727, 0x331b1b1b1b06061b, 0x2424301b06060100, 0x243a2d272d122424, 0x2430272427242d33, 0x242424241b063306, 0x27241b302c2e0500, 
	0x1b16272331272d24, 0x242424122d242424, 0x27301b2406060606, 0x062e2e0505040100, 0x2c1527242d241b1b, 0x243306331b242c2c, 0x06061b330606062c, 0x2c05050505330100, 
	0x0528052e062c052c, 0x2e052c2e05040405, 0x0504050101052406, 0x0505050101010100, 0x0005000000030003, 0x0303000300000003, 0x0000000000000000, 0x0000000000000000, 
	
};

u64 test_room_dl_dark_brick_wall_pal_rgba16[] = {
	0x0001084300430003, 0x0845088510c78463, 0x73e173df6b9d6b9f, 0x635d635b5b1b318d, 0x5b197c63294d8ca7, 0x429542554a973a53, 0x321129cf298f18c9, 0x7c2331d1218d214d, 
	0x84653a133213298d, 0x1909742152d7214b, 0x31cf42534a953a11, 0x1087210b108539d1, 0x2109318f190b18c7, 0x639d52d952976bdf, 0x5319531b4ad95b5d, 0x5b5b74236be1635f, 
	0x294b000000000000
};

Vtx test_room_dl_Ground_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-299, 0, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-299, 206, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-299, 206, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-299, 0, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 0, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 206, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 206, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 0, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx test_room_dl_Ground_mesh_layer_Opaque_vtx_0[10] = {
	{{ {-246, 0, 246}, 0, {3869, -2877}, {255, 255, 255, 255} }},
	{{ {246, 0, 246}, 0, {-2877, -2877}, {255, 255, 255, 255} }},
	{{ {246, 0, -246}, 0, {-2877, 3869}, {255, 255, 255, 255} }},
	{{ {-246, 0, -246}, 0, {3869, 3869}, {255, 255, 255, 255} }},
	{{ {246, 206, 246}, 0, {-2877, -2877}, {0, 0, 0, 255} }},
	{{ {-246, 206, 246}, 0, {3869, -2877}, {0, 0, 0, 255} }},
	{{ {-246, 206, -246}, 0, {3869, 3869}, {0, 0, 0, 255} }},
	{{ {-75, 206, -246}, 0, {1520, 3869}, {0, 0, 0, 255} }},
	{{ {-9, 206, -246}, 0, {614, 3869}, {0, 0, 0, 255} }},
	{{ {246, 206, -246}, 0, {-2877, 3869}, {0, 0, 0, 255} }},
};

Gfx test_room_dl_Ground_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(test_room_dl_Ground_mesh_layer_Opaque_vtx_0 + 0, 10, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(7, 8, 4, 0, 8, 9, 4, 0),
	gsSPEndDisplayList(),
};

Vtx test_room_dl_Ground_mesh_layer_Opaque_vtx_1[88] = {
	{{ {-246, 0, 246}, 0, {-3610, 4602}, {255, 255, 255, 255} }},
	{{ {-299, 0, -299}, 0, {-4491, -4491}, {255, 255, 255, 255} }},
	{{ {-299, 0, 299}, 0, {-4491, 5483}, {255, 255, 255, 255} }},
	{{ {-246, 0, -246}, 0, {-3610, -3610}, {255, 255, 255, 255} }},
	{{ {299, 0, -299}, 0, {5483, -4491}, {255, 255, 255, 255} }},
	{{ {246, 0, -246}, 0, {4602, -3610}, {255, 255, 255, 255} }},
	{{ {299, 0, 299}, 0, {-456, 5982}, {255, 255, 255, 255} }},
	{{ {246, 0, 246}, 0, {514, 5013}, {255, 255, 255, 255} }},
	{{ {-246, 0, 246}, 0, {514, -4021}, {255, 255, 255, 255} }},
	{{ {30, 0, 299}, 0, {-456, 1046}, {255, 255, 255, 255} }},
	{{ {-30, 0, 299}, 0, {-456, -54}, {255, 255, 255, 255} }},
	{{ {-299, 0, 299}, 0, {-456, -4990}, {255, 255, 255, 255} }},
	{{ {246, 0, -246}, 0, {4654, -3610}, {255, 255, 255, 255} }},
	{{ {246, 0, 246}, 0, {4654, 4602}, {255, 255, 255, 255} }},
	{{ {299, 0, 299}, 0, {5535, 5483}, {255, 255, 255, 255} }},
	{{ {299, 0, -299}, 0, {5535, -4491}, {255, 255, 255, 255} }},
	{{ {246, 206, 246}, 0, {4602, 4602}, {0, 0, 0, 255} }},
	{{ {299, 206, 299}, 0, {5483, 5483}, {0, 0, 0, 255} }},
	{{ {-299, 206, 299}, 0, {-4491, 5483}, {0, 0, 0, 255} }},
	{{ {-246, 206, 246}, 0, {-3610, 4602}, {0, 0, 0, 255} }},
	{{ {-299, 206, -299}, 0, {-4491, -4491}, {0, 0, 0, 255} }},
	{{ {-246, 206, -246}, 0, {-3610, -3610}, {0, 0, 0, 255} }},
	{{ {-84, 206, -299}, 0, {-908, -4491}, {0, 0, 0, 255} }},
	{{ {-75, 206, -246}, 0, {-750, -3610}, {0, 0, 0, 255} }},
	{{ {-7, 206, -299}, 0, {374, -4491}, {0, 0, 0, 255} }},
	{{ {-9, 206, -246}, 0, {353, -3610}, {0, 0, 0, 255} }},
	{{ {299, 206, -299}, 0, {5483, -4491}, {0, 0, 0, 255} }},
	{{ {246, 206, -246}, 0, {4602, -3610}, {0, 0, 0, 255} }},
	{{ {246, 206, -246}, 0, {4654, -3610}, {0, 0, 0, 255} }},
	{{ {299, 206, -299}, 0, {5535, -4491}, {0, 0, 0, 255} }},
	{{ {299, 206, 299}, 0, {5535, 5483}, {0, 0, 0, 255} }},
	{{ {246, 206, 246}, 0, {4654, 4602}, {0, 0, 0, 255} }},
	{{ {-299, 0, -299}, 0, {-4011, 2058}, {255, 255, 255, 255} }},
	{{ {299, 0, -299}, 0, {5067, 2058}, {255, 255, 255, 255} }},
	{{ {299, 206, -299}, 0, {5067, -1060}, {0, 0, 0, 255} }},
	{{ {-7, 206, -299}, 0, {418, -1060}, {0, 0, 0, 255} }},
	{{ {-84, 206, -299}, 0, {-750, -1060}, {0, 0, 0, 255} }},
	{{ {-299, 206, -299}, 0, {-4011, -1060}, {0, 0, 0, 255} }},
	{{ {-30, 0, 299}, 0, {73, 2058}, {255, 255, 255, 255} }},
	{{ {-299, 0, 299}, 0, {-4011, 2058}, {255, 255, 255, 255} }},
	{{ {-299, 206, 299}, 0, {-4011, -1060}, {0, 0, 0, 255} }},
	{{ {-30, 100, 299}, 0, {73, 542}, {202, 202, 202, 255} }},
	{{ {299, 206, 299}, 0, {5067, -1060}, {0, 0, 0, 255} }},
	{{ {30, 100, 299}, 0, {983, 542}, {203, 203, 203, 255} }},
	{{ {30, 0, 299}, 0, {983, 2058}, {255, 255, 255, 255} }},
	{{ {299, 0, 299}, 0, {5067, 2058}, {255, 255, 255, 255} }},
	{{ {299, 0, 299}, 0, {-4069, 2058}, {255, 255, 255, 255} }},
	{{ {299, 206, 299}, 0, {-4069, -1060}, {0, 0, 0, 255} }},
	{{ {299, 206, -299}, 0, {5009, -1060}, {0, 0, 0, 255} }},
	{{ {299, 0, -299}, 0, {5009, 2058}, {255, 255, 255, 255} }},
	{{ {-299, 0, -299}, 0, {5009, 2058}, {255, 255, 255, 255} }},
	{{ {-299, 206, -299}, 0, {5009, -1060}, {0, 0, 0, 255} }},
	{{ {-299, 206, 299}, 0, {-4069, -1060}, {0, 0, 0, 255} }},
	{{ {-299, 0, 299}, 0, {-4069, 2058}, {255, 255, 255, 255} }},
	{{ {-30, 0, 319}, 0, {920, 386}, {255, 255, 255, 255} }},
	{{ {-30, 100, 459}, 0, {-1377, -1255}, {0, 0, 0, 255} }},
	{{ {-30, 0, 459}, 0, {-1377, 386}, {0, 0, 0, 255} }},
	{{ {-30, 100, 319}, 0, {920, -1255}, {0, 0, 0, 255} }},
	{{ {-30, 0, 299}, 0, {1248, 386}, {255, 255, 255, 255} }},
	{{ {-30, 100, 299}, 0, {1248, -1255}, {202, 202, 202, 255} }},
	{{ {30, 0, 299}, 0, {1014, -1044}, {255, 255, 255, 255} }},
	{{ {-30, 0, 299}, 0, {29, -1044}, {255, 255, 255, 255} }},
	{{ {-30, 0, 319}, 0, {29, -715}, {255, 255, 255, 255} }},
	{{ {30, 0, 319}, 0, {1014, -715}, {255, 255, 255, 255} }},
	{{ {30, 0, 319}, 0, {1014, -715}, {255, 255, 255, 255} }},
	{{ {-30, 0, 319}, 0, {29, -715}, {255, 255, 255, 255} }},
	{{ {-30, 0, 459}, 0, {29, 1581}, {0, 0, 0, 255} }},
	{{ {30, 0, 459}, 0, {1014, 1581}, {0, 0, 0, 255} }},
	{{ {30, 100, 299}, 0, {1248, -1255}, {203, 203, 203, 255} }},
	{{ {30, 0, 299}, 0, {1248, 386}, {255, 255, 255, 255} }},
	{{ {30, 0, 319}, 0, {920, 386}, {255, 255, 255, 255} }},
	{{ {30, 100, 319}, 0, {920, -1255}, {4, 4, 4, 255} }},
	{{ {30, 0, 459}, 0, {-1377, 386}, {0, 0, 0, 255} }},
	{{ {30, 100, 459}, 0, {-1377, -1255}, {0, 0, 0, 255} }},
	{{ {-30, 100, 299}, 0, {29, -1044}, {202, 202, 202, 255} }},
	{{ {30, 100, 299}, 0, {1014, -1044}, {203, 203, 203, 255} }},
	{{ {30, 100, 319}, 0, {1014, -715}, {4, 4, 4, 255} }},
	{{ {-30, 100, 319}, 0, {29, -715}, {0, 0, 0, 255} }},
	{{ {-30, 0, 459}, 0, {36, 2059}, {0, 0, 0, 255} }},
	{{ {30, 100, 459}, 0, {907, 784}, {0, 0, 0, 255} }},
	{{ {30, 0, 459}, 0, {956, 2059}, {0, 0, 0, 255} }},
	{{ {-30, 100, 459}, 0, {-13, 769}, {0, 0, 0, 255} }},
	{{ {-30, 111, 459}, 0, {-13, 769}, {0, 0, 0, 255} }},
	{{ {-30, 111, 319}, 0, {-13, 769}, {0, 0, 0, 255} }},
	{{ {-30, 100, 319}, 0, {-13, 769}, {0, 0, 0, 255} }},
	{{ {30, 111, 319}, 0, {907, 784}, {0, 0, 0, 255} }},
	{{ {30, 100, 319}, 0, {907, 784}, {4, 4, 4, 255} }},
	{{ {30, 111, 459}, 0, {907, 784}, {0, 0, 0, 255} }},
};

Gfx test_room_dl_Ground_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(test_room_dl_Ground_mesh_layer_Opaque_vtx_1 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 4, 1, 0, 3, 5, 4, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 6, 8, 0),
	gsSP2Triangles(8, 10, 9, 0, 8, 11, 10, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(19, 18, 20, 0, 19, 20, 21, 0),
	gsSP2Triangles(21, 20, 22, 0, 21, 22, 23, 0),
	gsSP2Triangles(23, 22, 24, 0, 23, 24, 25, 0),
	gsSP2Triangles(25, 24, 26, 0, 25, 26, 27, 0),
	gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
	gsSPVertex(test_room_dl_Ground_mesh_layer_Opaque_vtx_1 + 32, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 4, 0, 0, 4, 5, 0, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 6, 8, 0),
	gsSP2Triangles(8, 10, 9, 0, 10, 11, 9, 0),
	gsSP2Triangles(10, 12, 11, 0, 10, 13, 12, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
	gsSP2Triangles(22, 23, 24, 0, 22, 25, 23, 0),
	gsSP2Triangles(26, 25, 22, 0, 26, 27, 25, 0),
	gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
	gsSPVertex(test_room_dl_Ground_mesh_layer_Opaque_vtx_1 + 64, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(7, 6, 8, 0, 7, 8, 9, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 17, 15, 0),
	gsSP2Triangles(15, 17, 18, 0, 17, 19, 18, 0),
	gsSP2Triangles(17, 20, 19, 0, 20, 21, 19, 0),
	gsSP2Triangles(20, 22, 21, 0, 22, 23, 21, 0),
	gsSP2Triangles(22, 15, 23, 0, 15, 18, 23, 0),
	gsSP2Triangles(19, 23, 18, 0, 19, 21, 23, 0),
	gsSPEndDisplayList(),
};

Vtx test_room_dl_Ground_001_mesh_layer_Transparent_vtx_cull[8] = {
	{{ {-30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx test_room_dl_Ground_001_mesh_layer_Transparent_vtx_0[4] = {
	{{ {30, 1, 319}, 0, {1014, -715}, {0, 127, 0, 255} }},
	{{ {-30, 1, 319}, 0, {29, -715}, {0, 127, 0, 255} }},
	{{ {-30, 1, 459}, 0, {29, 1581}, {0, 127, 0, 255} }},
	{{ {30, 1, 459}, 0, {1014, 1581}, {0, 127, 0, 255} }},
};

Gfx test_room_dl_Ground_001_mesh_layer_Transparent_tri_0[] = {
	gsSPVertex(test_room_dl_Ground_001_mesh_layer_Transparent_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_test_room_dl_red_carpet_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, test_room_dl_red_carpet3_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 128),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_test_room_dl_darkstone_brick_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, test_room_dl_dark_brick_wall_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 64),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, test_room_dl_dark_brick_wall_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_test_room_dl_main_exit_001_layerTransparent[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 0, 187, 60),
	gsSPEndDisplayList(),
};

Gfx test_room_dl_Ground_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(test_room_dl_Ground_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_test_room_dl_red_carpet_layerOpaque),
	gsSPDisplayList(test_room_dl_Ground_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_test_room_dl_darkstone_brick_layerOpaque),
	gsSPDisplayList(test_room_dl_Ground_mesh_layer_Opaque_tri_1),
	gsSPEndDisplayList(),
};

Gfx test_room_dl_Ground_001_mesh_layer_Transparent[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(test_room_dl_Ground_001_mesh_layer_Transparent_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_test_room_dl_main_exit_001_layerTransparent),
	gsSPDisplayList(test_room_dl_Ground_001_mesh_layer_Transparent_tri_0),
	gsSPEndDisplayList(),
};

