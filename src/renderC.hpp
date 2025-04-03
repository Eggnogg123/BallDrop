#include<SFML/Graphics.hpp>
#include "calculate.hpp"
class renderC{
    public:
    renderC(sf::RenderTarget& window)
       : targetWindow{window} //done this way to bound targetWindow before constructor
        {}

    void render(calculate c){
        sf::CircleShape circle(300.0f);
        //circle.setPosition({targetWindow.getSize().x / 8.0f,targetWindow.getSize().y / 8.0f});
        
        sf::CircleShape circleConstraint(300.0f);
        circleConstraint.setOrigin({300.0f,300.0f});
        circleConstraint.setPosition({450.0f,450.0f});
        circleConstraint.setFillColor(sf::Color::Magenta);
        targetWindow.draw(circleConstraint);
        // std::cout<<circle.getOrigin().x<<" "<<circle.getOrigin().y<<std::endl;
        // std::cout<<circle.getPosition().x<<" "<<circle.getPosition().y<<std::endl;
        
        auto& balls = c.getList();
        for(auto& test:balls){
            circle.setFillColor(test.color);
            circle.setRadius(test.radius);
            circle.setOrigin({test.radius,test.radius});
            circle.setPosition(test.position);
            targetWindow.draw(circle);
        }
    }


    private:
    sf::RenderTarget& targetWindow;
};