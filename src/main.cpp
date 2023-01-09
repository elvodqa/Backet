#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

// Constants for the window size and tile size
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int TILE_SIZE = 16;

int main()
{
    std::srand(std::time(nullptr));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Backet");
    sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(view);

    
    int world[WINDOW_WIDTH / TILE_SIZE][WINDOW_HEIGHT / TILE_SIZE];

    for (int i = 0; i < WINDOW_WIDTH / TILE_SIZE; i++)
    {
        for (int j = 0; j < WINDOW_HEIGHT / TILE_SIZE; j++)
        {
            world[i][j] = std::rand() % 3;
        }
    }

    // 128 width x 64 height
    int chunks[128][64] = {0};
    // pick a random number between 30-45
    int prevChunkHeight = std::rand() % 15 + 30;
    int curChunk = 0;
    // fill the first chunk with 1 by only prevChunkHeight amount then add or subtract a random number between 4-8
    while (curChunk < 128) {
        for (int i = 0; i < 64; i++) {
            if (i < prevChunkHeight) {
                chunks[curChunk][i] = 1;
            } else {
                chunks[curChunk][i] = 0;
            }
        }
        curChunk++;
        prevChunkHeight += std::rand() % 5 - 2;
    }

    // Create the textures for each type of tile
    sf::Texture grassTexture;
    grassTexture.loadFromFile("./resources/grass.png");

    sf::Texture dirtTexture;
    dirtTexture.loadFromFile("./resources/dirt.png");

    sf::Texture stoneTexture;
    stoneTexture.loadFromFile("./resources/stone.png");

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check for events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the user closes it or presses the Escape key
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            if (event.type == sf::Event::Resized) {
                view.setSize(event.size.width, event.size.height);
                window.setView(view);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-3, 0);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(3, 0);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -3);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 3);
            window.setView(view);
        }

        // Clear the window
        window.clear();

        // Draw the world
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 64; j++)
            {   
                // Determine which texture to use based on the value of the tile
                sf::Texture* texture;
                if (chunks[i][j] == 0)
                    texture = &grassTexture;
                else if (chunks[i][j] == 1)
                    texture = &dirtTexture;
                //else
                    //texture = &stoneTexture;

                // Create a sprite for the tile and set its position and texture
                sf::Sprite tileSprite;
                tileSprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                tileSprite.setTexture(*texture);

                // Draw the sprite
                window.draw(tileSprite);

                /*
                // Determine which texture to use based on the value of the tile
                sf::Texture* texture;
                if (world[i][j] == 0)
                    texture = &grassTexture;
                else if (world[i][j] == 1)
                    texture = &dirtTexture;
                else
                    texture = &stoneTexture;

                // Create a sprite for the tile and set its position and texture
                sf::Sprite tileSprite;
                tileSprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                tileSprite.setTexture(*texture);

                // Draw the sprite
                window.draw(tileSprite);
                */
            }
        }

        // Display the window
        window.display();
    }
}
