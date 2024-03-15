#include "ultra64.h"
#include "global.h"

s16 gSpectralFistGspectralfistactionAnimFrameData[3] = {
	0x0000, 0xfa9e, 0xffff, };

JointIndex gSpectralFistGspectralfistactionAnimJointIndices[2] = {
	{ 0x0000, 0x0001, 0x0000, },
	{ 0x0002, 0x0000, 0x0002, },
};

AnimationHeader gSpectralFistStillAnim = { { 2 }, gSpectralFistGspectralfistactionAnimFrameData, gSpectralFistGspectralfistactionAnimJointIndices, 3 };

