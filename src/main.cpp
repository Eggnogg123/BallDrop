#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "calculate.hpp"
#include "renderC.hpp"
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({900, 900}), "SFML window");
 
    calculate calc;
    renderC renderer(window);
    sf::Vector2f spawnPos = {400.0f,200.0f};
    // Start the game loop
    sf::Clock clock;
    sf::Time c = clock.getElapsedTime();
    sf::Time t = clock.getElapsedTime();
    window.setFramerateLimit(30);
    std::srand(std::time({}));
    float x;
    while (window.isOpen())
    {   
        const std::optional ev = window.pollEvent();
        
        if (ev && ev->is<sf::Event::Closed>()){
            window.close();
        }
        if(clock.getElapsedTime().asSeconds() > c.asSeconds()+ 0.5){
            x = (rand() % 25) + 5;
            spawnPos.x = (rand() % 100) + 350;
            spawnPos.y = (rand() % 50) + 250;
            c = clock.getElapsedTime();
            calc.createBall(spawnPos,x);
            // x = (rand() % 25) + 5;
            // spawnPos.x = (rand() % 200) + 300;
            // spawnPos.y = (rand() % 100) + 150;
            // calc.createBall(spawnPos,x);
        }     
        // Clear screen
        window.clear();
        renderer.render(calc);
        // Draw the sprite
        calc.update(float(clock.getElapsedTime().asSeconds() - t.asSeconds()));
        t = clock.getElapsedTime();
        window.display();

        // Draw the string
 //       window.draw(text);
 
        // Update the window
        
    }
}
