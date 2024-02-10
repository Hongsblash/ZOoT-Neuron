#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "sand_room_scene.h"
#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

/**
 * Header Child Day (Default)
*/
#define LENGTH_SAND_ROOM_ROOM_0_HEADER00_OBJECTLIST 2
#define LENGTH_SAND_ROOM_ROOM_0_HEADER00_ACTORLIST 1
SceneCmd sand_room_room_0_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 0),
    SCENE_CMD_ROOM_SHAPE(&sand_room_room_0_shapeHeader),
    SCENE_CMD_OBJECT_LIST(LENGTH_SAND_ROOM_ROOM_0_HEADER00_OBJECTLIST, sand_room_room_0_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_SAND_ROOM_ROOM_0_HEADER00_ACTORLIST, sand_room_room_0_header00_actorList),
    SCENE_CMD_END(),
};

s16 sand_room_room_0_header00_objectList[LENGTH_SAND_ROOM_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_BOX,
    OBJECT_MOLLY_NPC,
};

ActorEntry sand_room_room_0_header00_actorList[LENGTH_SAND_ROOM_ROOM_0_HEADER00_ACTORLIST] = {
    // Custom Actor
    {
        /* Actor ID   */ ACTOR_MOLLY_NPC,
        /* Position   */ { 0, 0, -205 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0000
    },
};

RoomShapeNormal sand_room_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(sand_room_room_0_shapeDListEntry),
    sand_room_room_0_shapeDListEntry,
    sand_room_room_0_shapeDListEntry + ARRAY_COUNT(sand_room_room_0_shapeDListEntry)
};

RoomShapeDListsEntry sand_room_room_0_shapeDListEntry[1] = {
    { sand_room_room_0_entry_0_opaque, sand_room_room_0_entry_0_transparent },
};

Gfx sand_room_room_0_entry_0_opaque[] = {
	gsSPDisplayList(sand_room_dl_Ground_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Gfx sand_room_room_0_entry_0_transparent[] = {
	gsSPDisplayList(sand_room_dl_Ground_001_mesh_layer_Transparent),
	gsSPEndDisplayList(),
};

u64 sand_room_dl_dead_grass_path5_ci4[] = {
	0x0123450020054301, 0x2345002005432103, 0x0110130050031001, 0x1013005003101102, 0x5646702111207656, 0x4670211120764652, 0x2525533434335525, 0x2553343433552523, 
	0x6512524535425265, 0x1252453542521564, 0x4531158434851145, 0x3115843485113542, 0x4202302535203242, 0x0230253520320245, 0x4104533515335441, 0x0453351533540146, 
	0x22553109a9013522, 0x553109a901355224, 0x0312000010000203, 0x1200001000021304, 0x1222107232701212, 0x2210723270122214, 0x4212522525225242, 0x125225252252124b, 
	0x6aa151155511516a, 0xa15115551151aa65, 0x5001625444526150, 0x0162544452610052, 0x1334455444554413, 0x3445544455443310, 0x9015525555525590, 0x1552555552551090, 
	0x0303504454405303, 0x0350445440530300, 0x10a5421222124510, 0xa54212221245a015, 0x0a0615101015160a, 0x0615101015160a05, 0x0122c2321232c201, 0x22c2321232c22103, 
	0xa0544292829244a0, 0x54429282924450a9, 0xdd255005450055dd, 0x2550054500552dd0, 0x030a9d00000d9a03, 0x0a9d00000d9a030d, 0x3030912030219030, 0x309120302190303a, 
	0x11199036c6309911, 0x199036c630991114, 0x4553092424290345, 0x5309242429035546, 0x552109a222a90155, 0x2109a222a9012550, 0x3200500323005032, 0x0050032300500232, 
	0x2c30172a2a27102c, 0x30172a2a27103c20, 0x4c2532099902354c, 0x2532099902352c43, 0xc635109a0a9015c6, 0x35109a0a901536c5, 0x4535439909934545, 0x3543990993453545, 
	
};

u64 sand_room_dl_dead_grass_path5_pal_rgba16[] = {
	0x7b9573536b537355, 0x62d16b1363117395, 0x5ad183d783d55a8f, 0x5a918c1700000000
};

u64 sand_room_dl_dead_grass_path2_ci8[] = {
	0x0001020304050607, 0x060809070a0b0606, 0x09090a0b0b0a0908, 0x0709060c0d090b09, 0x0001030e040f0609, 0x0608080608070606, 0x0b0b080809070706, 0x0808060d0d060a10, 
	0x0004040e00110909, 0x0b120a1210060908, 0x0808080606060607, 0x060c08090806060b, 0x000e010000130b07, 0x090b090b0b07070a, 0x07090b0707090b06, 0x0606080909060609, 
	0x1414030e1403150a, 0x120b08090b090a0b, 0x070d06060c070806, 0x0808090a0a090707, 0x1614030e02171109, 0x0a0b0708080b150a, 0x071806070d0c0606, 0x0c0607090a080c06, 
	0x0316010401140e0b, 0x0a0906090706090b, 0x07070b0b08090909, 0x09090908090b080b, 0x16160e0401040412, 0x0a08060a0b07070b, 0x0807070b0b0b070d, 0x06090b0b0712120a, 
	0x010214010000010a, 0x09090b0b0708060c, 0x0d0706080a060b07, 0x090a0b0b08120806, 0x0e03040e1901140a, 0x0607080906060606, 0x08080b090608080c, 0x0a0a0a0b1208060c, 
	0x040005040102170a, 0x0809090908061009, 0x07060a08090a070c, 0x090c080b0a090d06, 0x0005051901011411, 0x0a0908090b09090b, 0x0906090709060612, 0x080c0d070a080709, 
	0x041a00140319000b, 0x120d0d080b08080b, 0x0b09090b060d0809, 0x09090906080b1212, 0x0000031614041b09, 0x0b06060812090b0a, 0x0a0b0a0a0807070b, 0x0d070606070b0808, 
	0x1a04011602011c06, 0x0807070a0a0b0b0a, 0x0a0a0b0b0b090607, 0x060c0c070b090d0d, 0x1a00001414000606, 0x0c06080b0b090b0b, 0x0b0b0a0a0a100608, 0x0d18180607070906, 
	0x040e0e1401050d06, 0x060706070b060a0a, 0x0b090b0a0b0b0607, 0x090d0d07060c060d, 0x040103040000090b, 0x08060d0b0a090809, 0x090809120b090908, 0x07060b070c080808, 
	0x040000140e190a0b, 0x060d0612080b0806, 0x08080b0a060d0907, 0x060c0807060a0b08, 0x17020301010e0a07, 0x060809091d090709, 0x08080b0906080b08, 0x0b0a120908080b09, 
	0x16170300001e080c, 0x0d060b0a0a090c09, 0x15120b060c08150b, 0x0b0a0b0707080d08, 0x02020204050c0706, 0x1818090b0b06060b, 0x0a0b090706060908, 0x0709120b120b0a0b, 
	0x161f140e09080618, 0x0607060d0c180606, 0x06060607090b0b07, 0x070606080b0b120b, 0x141414050607060d, 0x070607060c080906, 0x070c06080b0a0b09, 0x09060909080a090b, 
	0x1414140e080c060a, 0x0808080c0c060712, 0x1d0c0c0808100709, 0x090b0b0b08070b09, 0x1401030108060712, 0x0a0b0b07060c090a, 0x090606080b080809, 0x07060b090b07070a, 
	0x0e01010e200b0806, 0x0b0b0908060c0d09, 0x090807090b0b0b06, 0x0d0606060b080c0b, 0x01020303110b1209, 0x070906060b060607, 0x0908070908060707, 0x0b0908080b070b0b, 
	0x0101010e0a0a0b06, 0x091d07060810090d, 0x090c0c0c06070c08, 0x0b08080807090a0b, 0x0301010a080a0907, 0x0a1d090b0709060c, 0x0c0c0707070c1806, 0x070d0607080a0b0b, 
	0x140304200b0b0b0b, 0x1d12070b08060c0d, 0x0607060706060c0d, 0x06060608080a0906, 0x02160e0a0706060b, 0x0a0b070b0a070c0c, 0x060b08080b080612, 0x0b0b0606060b0907, 
	
};

u64 sand_room_dl_dead_grass_path2_pal_rgba16[] = {
	0x5a4d49cb394941c9, 0x520b628f7b957355, 0x73536b5362d16b13, 0x83d783d54a0b6ad1, 0x73955a8f63115a4f, 0x41895ad139893147, 0x8c17520d624d7b53, 0x83955a9162cf2907, 
	0x6b11000000000000
};

u64 sand_room_dl_dark_brick_wall_ci8[] = {
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

u64 sand_room_dl_dark_brick_wall_pal_rgba16[] = {
	0x0001084300430003, 0x0845088510c78463, 0x73e173df6b9d6b9f, 0x635d635b5b1b318d, 0x5b197c63294d8ca7, 0x429542554a973a53, 0x321129cf298f18c9, 0x7c2331d1218d214d, 
	0x84653a133213298d, 0x1909742152d7214b, 0x31cf42534a953a11, 0x1087210b108539d1, 0x2109318f190b18c7, 0x639d52d952976bdf, 0x5319531b4ad95b5d, 0x5b5b74236be1635f, 
	0x294b000000000000
};

Vtx sand_room_dl_Ground_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-299, 0, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-299, 206, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-299, 206, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-299, 0, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 0, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 206, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 206, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {299, 0, -299}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx sand_room_dl_Ground_mesh_layer_Opaque_vtx_0[10] = {
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

Gfx sand_room_dl_Ground_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(sand_room_dl_Ground_mesh_layer_Opaque_vtx_0 + 0, 10, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(7, 8, 4, 0, 8, 9, 4, 0),
	gsSPEndDisplayList(),
};

Vtx sand_room_dl_Ground_mesh_layer_Opaque_vtx_1[18] = {
	{{ {-246, 0, 246}, 0, {615, -2371}, {255, 255, 255, 255} }},
	{{ {-246, 0, -246}, 0, {615, 3251}, {255, 255, 255, 255} }},
	{{ {-299, 0, -299}, 0, {12, 3854}, {255, 255, 255, 255} }},
	{{ {-299, 0, 299}, 0, {12, -2974}, {255, 255, 255, 255} }},
	{{ {299, 0, 299}, 0, {3, 3824}, {255, 255, 255, 255} }},
	{{ {246, 0, 246}, 0, {615, 3213}, {255, 255, 255, 255} }},
	{{ {-246, 0, 246}, 0, {615, -2485}, {255, 255, 255, 255} }},
	{{ {30, 0, 299}, 0, {3, 711}, {255, 255, 255, 255} }},
	{{ {-30, 0, 299}, 0, {3, 17}, {255, 255, 255, 255} }},
	{{ {-299, 0, 299}, 0, {3, -3096}, {255, 255, 255, 255} }},
	{{ {246, 0, -246}, 0, {570, 3051}, {255, 255, 255, 255} }},
	{{ {246, 0, 246}, 0, {570, -2187}, {255, 255, 255, 255} }},
	{{ {299, 0, 299}, 0, {8, -2750}, {255, 255, 255, 255} }},
	{{ {299, 0, -299}, 0, {8, 3614}, {255, 255, 255, 255} }},
	{{ {-246, 0, -246}, 0, {527, -1975}, {255, 255, 255, 255} }},
	{{ {246, 0, -246}, 0, {527, 2967}, {255, 255, 255, 255} }},
	{{ {299, 0, -299}, 0, {-4, 3498}, {255, 255, 255, 255} }},
	{{ {-299, 0, -299}, 0, {-4, -2506}, {255, 255, 255, 255} }},
};

Gfx sand_room_dl_Ground_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(sand_room_dl_Ground_mesh_layer_Opaque_vtx_1 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
	gsSP2Triangles(6, 8, 7, 0, 6, 9, 8, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
	gsSPEndDisplayList(),
};

Vtx sand_room_dl_Ground_mesh_layer_Opaque_vtx_2[70] = {
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

Gfx sand_room_dl_Ground_mesh_layer_Opaque_tri_2[] = {
	gsSPVertex(sand_room_dl_Ground_mesh_layer_Opaque_vtx_2 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
	gsSP2Triangles(5, 4, 6, 0, 5, 6, 7, 0),
	gsSP2Triangles(7, 6, 8, 0, 7, 8, 9, 0),
	gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(19, 20, 16, 0, 20, 21, 16, 0),
	gsSP2Triangles(22, 23, 24, 0, 25, 22, 24, 0),
	gsSP2Triangles(24, 26, 25, 0, 26, 27, 25, 0),
	gsSP2Triangles(26, 28, 27, 0, 26, 29, 28, 0),
	gsSPVertex(sand_room_dl_Ground_mesh_layer_Opaque_vtx_2 + 30, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
	gsSP2Triangles(12, 11, 8, 0, 12, 13, 11, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
	gsSP2Triangles(17, 16, 18, 0, 17, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSP2Triangles(23, 22, 24, 0, 23, 24, 25, 0),
	gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
	gsSPVertex(sand_room_dl_Ground_mesh_layer_Opaque_vtx_2 + 60, 10, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(1, 3, 4, 0, 3, 5, 4, 0),
	gsSP2Triangles(3, 6, 5, 0, 6, 7, 5, 0),
	gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(8, 1, 9, 0, 1, 4, 9, 0),
	gsSP2Triangles(5, 9, 4, 0, 5, 7, 9, 0),
	gsSPEndDisplayList(),
};

Vtx sand_room_dl_Ground_001_mesh_layer_Transparent_vtx_cull[8] = {
	{{ {-30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 459}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {30, 1, 319}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx sand_room_dl_Ground_001_mesh_layer_Transparent_vtx_0[4] = {
	{{ {30, 1, 319}, 0, {1014, -715}, {0, 127, 0, 255} }},
	{{ {-30, 1, 319}, 0, {29, -715}, {0, 127, 0, 255} }},
	{{ {-30, 1, 459}, 0, {29, 1581}, {0, 127, 0, 255} }},
	{{ {30, 1, 459}, 0, {1014, 1581}, {0, 127, 0, 255} }},
};

Gfx sand_room_dl_Ground_001_mesh_layer_Transparent_tri_0[] = {
	gsSPVertex(sand_room_dl_Ground_001_mesh_layer_Transparent_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_sand_room_dl_floor_centre_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sand_room_dl_dead_grass_path5_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 13),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, sand_room_dl_dead_grass_path5_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 255, 1024),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_sand_room_dl_floor_edges_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sand_room_dl_dead_grass_path2_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 32),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, sand_room_dl_dead_grass_path2_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_sand_room_dl_darkstone_brick_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sand_room_dl_dark_brick_wall_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 64),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, sand_room_dl_dark_brick_wall_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_sand_room_dl_main_exit_001_layerTransparent[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 0, 187, 60),
	gsSPEndDisplayList(),
};

Gfx sand_room_dl_Ground_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(sand_room_dl_Ground_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_sand_room_dl_floor_centre_layerOpaque),
	gsSPDisplayList(sand_room_dl_Ground_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_sand_room_dl_floor_edges_layerOpaque),
	gsSPDisplayList(sand_room_dl_Ground_mesh_layer_Opaque_tri_1),
	gsSPDisplayList(mat_sand_room_dl_darkstone_brick_layerOpaque),
	gsSPDisplayList(sand_room_dl_Ground_mesh_layer_Opaque_tri_2),
	gsSPEndDisplayList(),
};

Gfx sand_room_dl_Ground_001_mesh_layer_Transparent[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(sand_room_dl_Ground_001_mesh_layer_Transparent_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_sand_room_dl_main_exit_001_layerTransparent),
	gsSPDisplayList(sand_room_dl_Ground_001_mesh_layer_Transparent_tri_0),
	gsSPEndDisplayList(),
};

