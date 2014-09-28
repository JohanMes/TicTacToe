#include "JohanEngine\Renderer.h"
#include "Movement.h"

Key* forwardkey = NULL;
Key* backwardkey = NULL;
Key* leftkey = NULL;
Key* rightkey = NULL;

void Forward(void* data) {
	camera->Move(camera->dir);
}

void Left(void* data) {
	camera->Move(-camera->right);
}

void Backward(void* data) {
	camera->Move(-camera->dir);
}

void Right(void* data) {
	camera->Move(camera->right);
}
