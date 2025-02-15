#include "blockactions.h"

#include "../engine/audio.h"

#include "../sfx.h"

bool actBlock(Chunk* chunk, Block* block)
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
        
        CHUNK_SET_FLAG(chunk, CHUNK_MODIFIED);

        playSample(SFX_DOOR);

        return true;
    }
    else if(block->type == BLOCK_LEVER)
    {
        if(block->data & BLOCK_DATA_POWER)
        {
            block->data &= ~BLOCK_DATA_POWER;
        }
        else
        {
            block->data |= BLOCK_DATA_POWER;
        }
        CHUNK_SET_FLAG(chunk, CHUNK_MODIFIED);

        playSample(SFX_LEVER);

        return true;
    }
    else if(block->type == BLOCK_COMPUTER)
    {
        return true;
    }
    else if(block->type == BLOCK_FURNACE)
    {
        //Turn furnace on (if off)
        if(!(block->data & BLOCK_DATA_TEXTURE))
        {
            block->data |= BLOCK_DATA_TEXTURE1;
            CHUNK_SET_FLAG(chunk, CHUNK_MODIFIED);
        }

        return true;
    }
    return false;
}