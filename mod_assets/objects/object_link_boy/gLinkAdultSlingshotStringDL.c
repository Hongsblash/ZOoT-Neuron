#include "ultra64.h"
#include "global.h"

Vtx gLinkAdultSlingshotStringDL_gLinkAdultSlingshotStringDL_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-23, -1875, -343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-23, -1875, 343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-23, 4, 343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-23, 4, -343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {13, -1875, -343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {13, -1875, 343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {13, 4, 343}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {13, 4, -343}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx gLinkAdultSlingshotStringDL_gLinkAdultSlingshotStringDL_mesh_layer_Opaque_vtx_0[12] = {
	{{ {4, -1868, 55}, 0, {32, 32}, {238, 73, 103, 255} }},
	{{ {13, 4, -343}, 0, {32, 32}, {248, 26, 124, 255} }},
	{{ {-14, -2, -343}, 0, {32, 32}, {248, 26, 124, 255} }},
	{{ {4, -1868, 55}, 0, {32, 32}, {239, 73, 103, 255} }},
	{{ {-14, -2, -343}, 0, {32, 32}, {249, 26, 124, 255} }},
	{{ {-23, -1875, 55}, 0, {32, 32}, {236, 81, 161, 255} }},
	{{ {-23, -1875, 55}, 0, {32, 32}, {239, 67, 149, 255} }},
	{{ {-14, -2, 343}, 0, {32, 32}, {252, 19, 131, 255} }},
	{{ {13, 4, 343}, 0, {32, 32}, {252, 19, 131, 255} }},
	{{ {-23, -1875, 55}, 0, {32, 32}, {239, 67, 149, 255} }},
	{{ {13, 4, 343}, 0, {32, 32}, {252, 19, 131, 255} }},
	{{ {4, -1868, 55}, 0, {32, 32}, {235, 87, 90, 255} }},
};

Gfx gLinkAdultSlingshotStringDL_gLinkAdultSlingshotStringDL_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(gLinkAdultSlingshotStringDL_gLinkAdultSlingshotStringDL_mesh_layer_Opaque_vtx_0 + 0, 12, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gLinkAdultSlingshotStringDL_f3dlite_material_001_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(SHADE, 0, PRIMITIVE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(0, 0, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 205, 255),
	gsSPEndDisplayList(),
};

Gfx gLinkAdultSlingshotStringDL[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(gLinkAdultSlingshotStringDL_gLinkAdultSlingshotStringDL_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_gLinkAdultSlingshotStringDL_f3dlite_material_001_layerOpaque),
	gsSPDisplayList(gLinkAdultSlingshotStringDL_gLinkAdultSlingshotStringDL_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

