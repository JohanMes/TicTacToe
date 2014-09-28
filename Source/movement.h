#ifndef MOVEMENT_INCLUDED
#define MOVEMENT_INCLUDED

#include "JohanEngine\Interface.h"

extern Key* forwardkey;
extern Key* backwardkey;
extern Key* leftkey;
extern Key* rightkey;

void Forward(void* data);
void Left(void* data);
void Backward(void* data);
void Right(void* data);

#endif
