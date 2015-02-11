#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "block.h"

// 25 Pixel = 1m
#define G 25*9.81f

using namespace std;


sf::Texture blockTexture;


int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "Physics :)");

    // Create the world
    float ground[800] = {600};

    // Renderlist
    vector<sf::Drawable *> renderList;


    // Load a sprite to display
    if (!blockTexture.loadFromFile("block.png"))
        return EXIT_FAILURE;




    vector<block *> blocks;


    // Prevent key spamming
    sf::Clock eventTimer;


	// Start the game loop
    while(app.isOpen())
    {
        /* ----------- Input ----------- */

        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }


        // Mouse
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && eventTimer.getElapsedTime().asMilliseconds() > 100)
        {
            blocks.push_back(new block);
            renderList.push_back(&blocks[blocks.size()-1]->sprite);

            eventTimer.restart();
        }




        #ifdef DEBUG
            sf::Clock physicsTimer;
        #endif


        /* ----------- Physics ----------- */

        /* Movement */
        for(auto block : blocks)
        {
            // Skip stable blocks
            if(block->stable)
                continue;



            // Movement
            // Check for ground collision
            float xPos = block->sprite.getPosition().x;
            float yPos = block->sprite.getPosition().y;


            // Check for each pixel
            sf::Vector2f highest(0, 0);
            for(int x=xPos; x<xPos+100; x++)
            {
                if(ground[x] > highest.y)
                {
                    highest.x = x;
                    highest.y = ground[x];
                }
            }

            float deltaY;
            if(highest.y < yPos+50+block->speed.y)
            {
                // Move on top of the next block
                deltaY = highest.y - yPos - 50;
                block->stable = true;

                // Set new ground
                for(int x=xPos; x<xPos+100; x++)
                {
                    ground[x] -= 50;
                }
            }
            else
            {
                // Move further down
                deltaY = block->speed.y;
            }



            block->sprite.move(0, deltaY);

            #ifdef DEBUG
                cerr << "New Position: x " << block->sprite.getPosition().x << " y " << block->sprite.getPosition().y << "  (deltaY " << deltaY << ")" << endl;
            #endif


            // Acceleration
            if(block->t.getElapsedTime().asSeconds() > 1/20)
            {
                block->speed.y = block->time0.getElapsedTime().asSeconds() * G;
                block->t.restart();
            }
        }



        #ifdef DEBUG
            cerr << "Time for calculating physics: " << physicsTimer.getElapsedTime().asMicroseconds() << "us" << endl;
        #endif


        /* ----------- Rendering ----------- */


        // Clear screen
        app.clear();


        // Draw the sprites
        for(auto obj : renderList)
            app.draw(*obj);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
