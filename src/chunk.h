#ifndef _CHUNK_H
#define _CHUNK_H

#include <GL/gl.h>

#include "block.h"

#define CHUNK_SIZE 8

typedef struct {
    Block blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    uint8_t modified;
    GLuint drawList;
} Chunk;

#define CHUNK_BLOCK(chunk, i, j, k) chunk->blocks[(i) + ((j) * CHUNK_SIZE) + ((k) * CHUNK_SIZE * CHUNK_SIZE)]

void calcChunk(Chunk* chunk, uint32_t ticks);
void drawChunk(Chunk* chunk);

void destroyChunk(Chunk* chunk);

#endif