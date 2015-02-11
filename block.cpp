#include "block.h"

#include <iostream>

// Constructor
block::block(sf::Vector2i pos)
{
    sprite.setTexture(blockTexture);
    sprite.setPosition(pos.x, pos.y);

    std::cerr << "Created: x " << pos.x << "   y " << pos.y << std::endl;

    speed.x = 0;
    speed.y = 0;

    stable = false;

    //std::cerr << "POX " << sprite.getPosition().x << "   POY " << sprite.getPosition().y << std::endl;
}
