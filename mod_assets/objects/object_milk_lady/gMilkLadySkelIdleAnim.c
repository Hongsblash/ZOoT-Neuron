#include "ultra64.h"
#include "global.h"

s16 gMollyNpcSkelGmollynpcskelactionAnimFrameData[269] = {
	0x0062, 0x0187, 0x0e07, 0x3d04, 0xffff, 0xe62e, 0x0000, 0x0e47, 0xf9f0, 0xf182, 0x0060, 0xd7a2, 0xbd4a, 0x4901, 0x14fc, 0x313f, 
	0x3b5f, 0xb3c3, 0x1dcc, 0x1c8d, 0xdeb2, 0x14b0, 0x004d, 0xde98, 0x422c, 0x3975, 0x0927, 0x0cfb, 0x09c1, 0x10bf, 0xadca, 0x0feb, 
	0x0d90, 0x0a14, 0xbfff, 0xc280, 0x06bd, 0x76a2, 0xea9a, 0x0055, 0xf6c1, 0x3f85, 0xe7a8, 0x1100, 0xc4b7, 0xf8e5, 0x766d, 0xeb3a, 
	0xfca8, 0xfea9, 0x487f, 0x00a9, 0x1b6a, 0x327a, 0x3195, 0x2f77, 0x2cf7, 0x2ae0, 0x29fe, 0x2a88, 0x2bf0, 0x2de7, 0x3023, 0x325c, 
	0x345b, 0x3628, 0x37e0, 0x39a3, 0x3b94, 0x3dcb, 0x401f, 0x4245, 0x43dc, 0xc47b, 0x43fc, 0x42a0, 0x40a1, 0x3e38, 0x3b94, 0x38e0, 
	0x365e, 0x344c, 0x32e3, 0x325c, 0x325f, 0x3267, 0x3270, 0x3277, 0x327a, 0xf87b, 0xf9be, 0xfcc4, 0x0066, 0x036f, 0x04b3, 0x03ed, 
	0x01e5, 0xff09, 0xfbcd, 0xf8a6, 0xf5e9, 0xf388, 0xf15c, 0xef40, 0xed0f, 0xeabc, 0xe880, 0xe6a0, 0xe557, 0x9b21, 0xe53f, 0xe654, 
	0xe80b, 0xea50, 0xed0f, 0xf027, 0xf343, 0xf5fc, 0xf7ea, 0xf8a6, 0xf8a1, 0xf897, 0xf88a, 0xf880, 0xf87b, 0xa6fa, 0xa721, 0xa760, 
	0xa776, 0xa75d, 0xa746, 0xa755, 0xa76f, 0xa774, 0xa750, 0xa700, 0xa693, 0xa615, 0xa585, 0xa4dc, 0xa409, 0xa2fc, 0xa1c5, 0xa08f, 
	0x9f9c, 0x1f3b, 0x9f88, 0xa059, 0xa17d, 0xa2c5, 0xa409, 0xa528, 0xa605, 0xa697, 0xa6e6, 0xa700, 0xa6ff, 0xa6fe, 0xa6fc, 0xa6fb, 
	0xa6fa, 0x4822, 0x46df, 0x43c4, 0x3fda, 0x3c62, 0x3ae1, 0x3bce, 0x3e2b, 0x4158, 0x44c5, 0x47f8, 0x4aa8, 0x4cf1, 0x4f02, 0x5102, 
	0x5315, 0x554f, 0x577e, 0x5960, 0x5ab5, 0xdb35, 0x5ace, 0x59ae, 0x57f2, 0x55b8, 0x5315, 0x5027, 0x4d34, 0x4a95, 0x48b1, 0x47f8, 
	0x47fc, 0x4806, 0x4813, 0x481d, 0x4822, 0x0d2b, 0x0e25, 0x106d, 0x130a, 0x1519, 0x15ec, 0x156c, 0x1411, 0x1213, 0x0fb5, 0x0d4c, 
	0x0b21, 0x0932, 0x0763, 0x0597, 0x03af, 0x019e, 0xff92, 0xfdcf, 0xfc93, 0x83e3, 0xfc7b, 0xfd87, 0xff25, 0x013c, 0x03af, 0x065c, 
	0x08f8, 0x0b30, 0x0cb9, 0x0d4c, 0x0d48, 0x0d40, 0x0d36, 0x0d2e, 0x0d2b, 0x9c33, 0x9bc9, 0x9aa6, 0x98ff, 0x975b, 0x9699, 0x9711, 
	0x9838, 0x99a7, 0x9b09, 0x9c26, 0x9cf1, 0x9d82, 0x9ded, 0x9e3e, 0x9e7a, 0x9e9f, 0x9ea8, 0x9e98, 0x9e81, 0x1e76, 0x9e7f, 0x9e94, 
	0x9ea6, 0x9ea3, 0x9e7a, 0x9e1e, 0x9d91, 0x9cec, 0x9c60, 0x9c26, 0x9c27, 0x9c2b, 0x9c2f, 0x9c32, 0x9c33, };

JointIndex gMollyNpcSkelGmollynpcskelactionAnimJointIndices[22] = {
	{ 0x0000, 0x0001, 0x0002, },
	{ 0x0003, 0x0004, 0x0004, },
	{ 0x0005, 0x0006, 0x0004, },
	{ 0x0035, 0x0059, 0x007d, },
	{ 0x00a1, 0x00c5, 0x00e9, },
	{ 0x0007, 0x0008, 0x0009, },
	{ 0x000a, 0x000b, 0x000c, },
	{ 0x000d, 0x000e, 0x000f, },
	{ 0x0010, 0x0011, 0x0012, },
	{ 0x0013, 0x0014, 0x0015, },
	{ 0x0016, 0x0017, 0x0018, },
	{ 0x0019, 0x001a, 0x001b, },
	{ 0x001c, 0x001d, 0x001e, },
	{ 0x001f, 0x0020, 0x0021, },
	{ 0x0022, 0x0006, 0x0004, },
	{ 0x0023, 0x0024, 0x0025, },
	{ 0x0026, 0x0027, 0x0028, },
	{ 0x0029, 0x002a, 0x002b, },
	{ 0x0022, 0x0006, 0x0004, },
	{ 0x002c, 0x002d, 0x002e, },
	{ 0x002f, 0x0030, 0x0031, },
	{ 0x0032, 0x0033, 0x0034, },
};

AnimationHeader gMollyNpcSkelGmollynpcskelactionAnim = { { 36 }, gMollyNpcSkelGmollynpcskelactionAnimFrameData, gMollyNpcSkelGmollynpcskelactionAnimJointIndices, 53 };

