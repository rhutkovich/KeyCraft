#ifndef _WORLD_H
#define _WORLD_H

#include <stdint.h>

#include "engine/includes/3dMath.h"

#include "blocks/blockutils.h"
#include "blocks/block.h"
#include "aabb.h"
#include "chunk.h"

#define VIEW_DISTANCE 5

//Translation to make handling chunk indices easier (0 - VIEW_DISTANCE) while centering the player
#define VIEW_TRANSLATION ((VIEW_DISTANCE * CHUNK_SIZE) / 2)

#define MAX_RAY_DISTANCE 5

#define TICK_RATE 250

void initWorld(uint32_t seed);
void quitWorld();

void calcWorld(vec3* playerPos, uint32_t ticks);
void drawWorld(vec3* playerPosition, vec3* playerRotation);

Block* getWorldBlock(BlockPos* pos);
void setWorldBlock(BlockPos* pos, Block block);
uint8_t actWorldBlock(BlockPos* pos);

AABBSide intersectsRayWorld(vec3* origin, vec3* direction, BlockPos* block, float* distance);
uint8_t intersectsAABBWorld(AABB* aabb);

void saveWorld();
void loadWorld();

#endif