#include "blockactions.h"

uint8_t actBlock(Chunk* chunk, Block* block)
{
    if(block->type == BLOCK_DOOR)
    {
        uint8_t rotation;

        if(block->data & BLOCK_DATA_STATE)
        {
            //Door is closed, open it
            switch(block->data & BLOCK_DATA_DIRECTION)
            {
                case BLOCK_DATA_DIR_FRONT:
                {
                    rotation = BLOCK_DATA_DIR_RIGHT;
                    break;
                }
                case BLOCK_DATA_DIR_RIGHT:
                {
                    rotation = BLOCK_DATA_DIR_BACK;
                    break;
                }
                case BLOCK_DATA_DIR_BACK:
                {
                    rotation = BLOCK_DATA_DIR_LEFT;
                    break;
                }
                case BLOCK_DATA_DIR_LEFT:
                {
                    rotation = BLOCK_DATA_DIR_FRONT;
                    break;
                }
            }
        }
        else
        {
            //Door is open, close it
            switch(block->data & BLOCK_DATA_DIRECTION)
            {
                case BLOCK_DATA_DIR_FRONT:
                {
                    rotation = BLOCK_DATA_DIR_LEFT;
                    break;
                }
                case BLOCK_DATA_DIR_LEFT:
                {
                    rotation = BLOCK_DATA_DIR_BACK;
                    break;
                }
                case BLOCK_DATA_DIR_BACK:
                {
                    rotation = BLOCK_DATA_DIR_RIGHT;
                    break;
                }
                case BLOCK_DATA_DIR_RIGHT:
                {
                    rotation = BLOCK_DATA_DIR_FRONT;
                    break;
                }
            }
        }

        //Set new direction
        block->data = (block->data & ~BLOCK_DATA_DIRECTION) + rotation;
        //Invert state
        block->data ^= BLOCK_DATA_STATE;
        
        chunk->modified = 1;
        return 1;
    }
    return 0;
}