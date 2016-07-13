#pragma once

#define REDUCED_DIM 100

typedef struct tagRECT{
	int left;
	int top;
	int right;
	int bottom;
}RECT;

typedef struct tagPointF {
	float x;
	float y;
} TPointF;

typedef struct tagLiveness{
	RECT rtFace;
	TPointF ptEyes[2];
	float score;
	float XAngle;
	float YAngle;
	float ZAngle;
} TLiveness;

