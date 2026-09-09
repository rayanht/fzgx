#ifndef SOFDEC_MPV_H
#define SOFDEC_MPV_H

#include "sofdec/sj.h"

int MPV_MoveChunk(SJ* stream, int channel, int size);
int MPV_GoNextDelimSj(SJ* stream);

#endif
