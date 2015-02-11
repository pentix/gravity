#include "block.h"

// Constructor
block::block()
{
    sprite.setTexture(blockTexture);

    speed.x = 0;
    speed.y = 5;
    stable = false;
}
