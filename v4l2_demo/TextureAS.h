#ifndef TEXTURE_AS_H
#define TEXTURE_AS_H

#include "NVType.h"

typedef unsigned char BYTE;

typedef void* HTAS;

#ifdef __cplusplus
extern "C" {
#endif

HTAS TAS_Create(const char* model, const char* model2, const char* qualityModelPath);
void TAS_Free(HTAS handle);
int TAS_Detect(HTAS handle, const BYTE* image, int width, int height, int pitch, int maxCount, TLiveness* liveResults);

void TAS_Extract(HTAS handle, const BYTE* image, int width, int height, int pitch, 
	const TPointF* landmark, float* cue);


#ifdef __cplusplus
}
#endif

#endif
