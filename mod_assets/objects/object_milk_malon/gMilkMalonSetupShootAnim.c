#include "ultra64.h"
#include "global.h"

s16 gMilkMalonSkelGmilkmalonshootanimAnimFrameData[982] = {
	0x0000, 0x0f55, 0x0352, 0xffff, 0xf482, 0x1dcd, 0xfec5, 0xeed5, 0xbe5f, 0x451a, 0xfa28, 0x62e8, 0x0fdd, 0xfffc, 0x7b0e, 0xbfff, 
	0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 0xff74, 
	0xfe22, 0xfcd1, 0xfd80, 0xfec5, 0xff74, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 
	0x2201, 0x2201, 0x2201, 0x2201, 0x2201, 0x3009, 0x3ecd, 0x36df, 0x295d, 0x2201, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 
	0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0x0e27, 0xfd83, 0xed2f, 0xf557, 0x05c2, 0x0e27, 0xa249, 
	0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa249, 0xa45a, 
	0xa06b, 0xa33f, 0xa415, 0xa249, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x2deb, 
	0x2deb, 0x2deb, 0x2deb, 0x2deb, 0x42ee, 0x52d5, 0x4b0b, 0x3999, 0x2deb, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 
	0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x1c19, 0x0fe5, 0x00cf, 0x08a8, 0x167a, 0x1c19, 0x9235, 0x9235, 
	0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9235, 0x9d4f, 0xa0a4, 
	0x9fbb, 0x990b, 0x9235, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 0xe61d, 
	0xe61d, 0xe61d, 0xe61d, 0xf10f, 0x04f6, 0xfb3f, 0xeaf6, 0xe61d, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 
	0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x138e, 0x19b6, 0x1ed6, 0x1cdc, 0x1694, 0x138e, 0xb6df, 0xb6df, 0xb6df, 
	0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xb6df, 0xbc94, 0xcaee, 0xc3d9, 
	0xb902, 0xb6df, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 0x1722, 
	0x1722, 0x1722, 0x1095, 0x0036, 0x072a, 0x14e7, 0x1722, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 
	0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdf05, 0xdfa7, 0xe058, 0xe037, 0xdf42, 0xdf05, 0x0675, 0x0675, 0x0675, 0x0675, 
	0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x0675, 0x04be, 0x0010, 0x0218, 0x05e4, 
	0x0675, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 0xfd83, 
	0xfd83, 0xfa72, 0xfedd, 0xfd83, 0xfb16, 0xfd83, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 
	0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf37b, 0xf1b5, 0xeef1, 0xf0b8, 0xf297, 0xf37b, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 
	0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xf7aa, 0xfbb4, 0xfd70, 0xfc92, 0xf9ec, 0xf7aa, 
	0xf9da, 0xf81f, 0xf365, 0xecbf, 0xe594, 0xdf0f, 0x59bb, 0x5598, 0x5274, 0x5013, 0x4e44, 0x4ce3, 0x4bd5, 0x4b09, 0x4a73, 0x4a0a, 
	0x49cc, 0x49b6, 0x49b6, 0x49b6, 0x49b6, 0xc77c, 0xc78e, 0xc7d5, 0xc874, 0xc98e, 0xcb2c, 0xb2bf, 0xb04f, 0xada2, 0xaad6, 0xa807, 
	0xa552, 0xa2cd, 0xa091, 0x9eb3, 0x9d46, 0x9c5d, 0x9c0b, 0x9c0b, 0x9c0b, 0x9c0b, 0x482a, 0x49e6, 0x4e9d, 0x5540, 0x5c67, 0x62e6, 
	0xe835, 0xec51, 0xef6e, 0xf1c8, 0xf390, 0xf4eb, 0xf5f2, 0xf6b9, 0xf74a, 0xf7af, 0xf7eb, 0xf7ff, 0xf7ff, 0xf7ff, 0xf7ff, 0x41a0, 
	0x3d9a, 0x38e2, 0x351b, 0x323f, 0x3087, 0x3033, 0x31bc, 0x3622, 0x3ec4, 0x4c1c, 0xdb09, 0xe6aa, 0xee28, 0xf256, 0xf3bd, 0xf31f, 
	0x74e3, 0x737c, 0xf342, 0xf3c8, 0x0a50, 0x0ec0, 0x1448, 0x1934, 0x1db0, 0x21b4, 0x252f, 0x284f, 0x2b23, 0x2d5a, 0x2e27, 0x531e, 
	0x5589, 0x57b9, 0x5918, 0x5994, 0x5dcf, 0x1cc5, 0x1fc8, 0x5bc0, 0x599b, 0x35e3, 0x3597, 0x3446, 0x3248, 0x2ff7, 0x2db4, 0x2bd7, 
	0x2af1, 0x2bf5, 0x3016, 0x3790, 0xbf39, 0xc30c, 0xc34c, 0xc1d7, 0xc041, 0xb2c6, 0x1f57, 0x2a78, 0xb8af, 0xbeee, 0x002d, 0x0992, 
	0x1496, 0x1d8c, 0x2500, 0x2b0c, 0x2fc1, 0x336e, 0x3636, 0x37ff, 0x3873, 0x372a, 0x3458, 0x30d4, 0x2db9, 0x2c38, 0x1d73, 0x002d, 
	0x121b, 0x2516, 0x2be5, 0xf710, 0xf635, 0xf319, 0xeee4, 0xea55, 0xe60d, 0xe27c, 0xdfa4, 0xdd80, 0xdc25, 0xdbcd, 0xdcc5, 0xdeef, 
	0xe1a8, 0xe40b, 0xe52d, 0xeef2, 0xf710, 0xf3ff, 0xea46, 0xe56c, 0x0023, 0x076b, 0x0fbc, 0x1619, 0x1ae8, 0x1e53, 0x2094, 0x2206, 
	0x22e9, 0x235f, 0x237a, 0x232b, 0x2256, 0x2108, 0x1fa8, 0x1eed, 0x1607, 0x0023, 0x0de6, 0x1af6, 0x1ec3, 0x5568, 0x5785, 0xd8e5, 
	0xd7ab, 0x50d2, 0x36e6, 0x0c0f, 0xfc8d, 0xf6f5, 0xf3b8, 0xf102, 0xeee6, 0xeea0, 0xf0ff, 0xf534, 0xf7e6, 0x0564, 0x2678, 0x1406, 
	0xfd5e, 0xf854, 0x1276, 0x188f, 0x5f06, 0x568e, 0x31cc, 0x3816, 0x3607, 0x2e9d, 0x26ce, 0x2013, 0x1ba1, 0x1aeb, 0x1de0, 0x22a2, 
	0x26d5, 0x28b6, 0x2c97, 0x27b9, 0x2cc8, 0x2b15, 0x2915, 0x4f3d, 0x4bd1, 0xc689, 0xbfa2, 0x33f1, 0x15ff, 0xe7e8, 0xd609, 0xcf47, 
	0xcc83, 0xcc43, 0xce5a, 0xd276, 0xd82c, 0xde65, 0xe1d4, 0xf47a, 0x1deb, 0x0687, 0xe9e3, 0xe259, 0xcced, 0xcced, 0xcced, 0xcced, 
	0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xcced, 0xd044, 0xd1cd, 0xd14a, 0xced7, 
	0xcced, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 0x093a, 
	0x093a, 0x09aa, 0x0965, 0x09a5, 0x0986, 0x093a, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 
	0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79ef, 0x79a7, 0x793b, 0x797e, 0x79c8, 0x79ef, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 
	0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xec73, 0xed85, 0xf1ad, 0xef09, 0xecaf, 0xec73, 
	0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 0xff4c, 
	0xff91, 0x007b, 0xffed, 0xff5c, 0xff4c, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 
	0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf5a2, 0xf62c, 0xf84d, 0xf6f1, 0xf5c0, 0xf5a2, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 
	0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x3baa, 0x369f, 0x305e, 0x33cc, 0x392f, 0x3baa, 0xe969, 
	0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xe969, 0xea3e, 
	0xec07, 0xeaf8, 0xe9bb, 0xe969, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 0x1057, 
	0x1057, 0x1057, 0x1057, 0x1057, 0x118e, 0x1271, 0x120a, 0x10ff, 0x1057, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 
	0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd230, 0xd5b1, 0xd7f4, 0xd6f5, 0xd424, 0xd230, 0x0169, 0x0169, 
	0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0169, 0x0297, 0x0357, 
	0x0301, 0x0214, 0x0169, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 0x711c, 
	0x711c, 0x711c, 0x711c, 0x7281, 0x7388, 0x730c, 0x71e1, 0x711c, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 
	0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe430, 0xe4c4, 0xe7a7, 0xe5d6, 0xe438, 0xe430, 0xfe6f, 0xfe6f, 0xfe6f, 
	0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe6f, 0xfe8a, 0xff07, 0xfeba, 
	0xfe70, 0xfe6f, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 0xf8ad, 
	0xf8ad, 0xf8ad, 0xf8ce, 0xf979, 0xf90d, 0xf8af, 0xf8ad, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 
	0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x4156, 0x3e57, 0x3a3d, 0x3c83, 0x3feb, 0x4156, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 
	0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xf8e6, 0xfbf5, 0xff36, 0xfd7f, 0xfa77, 
	0xf8e6, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 0x1735, 
	0x1735, 0x1643, 0x14d5, 0x15a6, 0x16c4, 0x1735, };

JointIndex gMilkMalonSkelGmilkmalonshootanimAnimJointIndices[24] = {
	{ 0x0000, 0x0001, 0x0010, },
	{ 0x0002, 0x0003, 0x0000, },
	{ 0x0004, 0x0000, 0x0003, },
	{ 0x0025, 0x003a, 0x004f, },
	{ 0x0064, 0x0079, 0x008e, },
	{ 0x0005, 0x0003, 0x0000, },
	{ 0x0006, 0x0007, 0x0008, },
	{ 0x00a3, 0x00b8, 0x00cd, },
	{ 0x00e2, 0x00f7, 0x010c, },
	{ 0x0121, 0x0136, 0x014b, },
	{ 0x0009, 0x000a, 0x000b, },
	{ 0x0160, 0x0175, 0x018a, },
	{ 0x019f, 0x01b4, 0x01c9, },
	{ 0x01de, 0x01f3, 0x0208, },
	{ 0x021d, 0x0232, 0x0247, },
	{ 0x000c, 0x000d, 0x000e, },
	{ 0x000f, 0x0000, 0x0000, },
	{ 0x025c, 0x0271, 0x0286, },
	{ 0x029b, 0x02b0, 0x02c5, },
	{ 0x02da, 0x02ef, 0x0304, },
	{ 0x000f, 0x0000, 0x0000, },
	{ 0x0319, 0x032e, 0x0343, },
	{ 0x0358, 0x036d, 0x0382, },
	{ 0x0397, 0x03ac, 0x03c1, },
};

AnimationHeader gMilkMalonSetupShootAnim = { { 21 }, gMilkMalonSkelGmilkmalonshootanimAnimFrameData, gMilkMalonSkelGmilkmalonshootanimAnimJointIndices, 16 };

