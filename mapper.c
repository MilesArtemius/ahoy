#include "mapper.h"

char** create(int width, int height) {
	char** map = NULL;
	map = calloc(height, sizeof(int*));
	for (int i = 0; i < height; i++) {
		map[i] = calloc(width, sizeof(int));
	}
	return map;
}
