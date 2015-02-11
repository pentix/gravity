#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


extern sf::Texture blockTexture;


class block
{
public:
    sf::Sprite sprite;
    sf::Vector2f speed;

    sf::Clock time0;
    sf::Clock t;

    bool stable;

    block();
};


#endif // BLOCK_H_INCLUDED
