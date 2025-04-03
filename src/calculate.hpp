#pragma once
#include<vector>
#include<cmath>
#include <SFML/Graphics.hpp>
#include<iostream>
struct ball{
    sf::Vector2f position;
    sf::Vector2f position_prev;
    sf::Vector2f acceleration;
    float radius = 10.0f;
    sf::Color color = sf::Color::Blue;
    
    ball() = default;
    ball(sf::Vector2f posit, float radi){
        position = posit;
        position_prev = posit;
        radius = radi;
        acceleration ={0.0f,0.0f};
    }

    void updatePos(float changeinT){
        sf::Vector2f velocity = position - position_prev;
        sf::Vector2f accelCalc = {(acceleration.x *(changeinT * changeinT)),(acceleration.y *(changeinT * changeinT))};
        position_prev = position;
        position = position + velocity + accelCalc;
        acceleration = {};
    }

    void cAccel(sf::Vector2f a){
        acceleration += a;
    }

};

class calculate{
    public:
    calculate() = default;
    void createBall(sf::Vector2f a,float radius){

        ball test(a,radius);
        ballList.push_back(test);
    }
    std::vector<ball>& getList(){
        return ballList;
    }
    void update(float time){
        for(int i =0;i<subSteps;i++){//This adds 5 substeps to the calculation to prev mishaps with collisions
        applyGravity();
        checkCollision();
        checkOutOfBounds();
        updateObjectPositions(time/subSteps);
        }
    }

    void checkCollision(){
        for(int i =0;i<ballList.size();i++){
            ball& circle1 = ballList[i];
            for(int j =i+1;j<ballList.size();j++){
                ball& circle2 = ballList[j];
                sf::Vector2f v = circle1.position - circle2.position;
                float distanceBetweenPreSquareRoot = v.x * v.x + v.y*v.y;
                float radiusSum = circle1.radius + circle2.radius;
                //if the distance between the two centers is less than the sum of the radius, they are overlapping
                if(distanceBetweenPreSquareRoot < radiusSum * radiusSum){
                    //update position here
                    //divide the vector that is the distance between circles by its length to get 
                    //a unit vector aligned with the circle centers
                    sf::Vector2f unitV = v / sqrt(distanceBetweenPreSquareRoot);
                    //This is the distance between the circles overlapping we need to remove
                    float dist = radiusSum - sqrt(distanceBetweenPreSquareRoot);
                    //now update the positions
//                    std::cout<<circle1.position.x<< " "<<circle1.position.y<<" AFTER-->";
                    circle1.position += 0.5f * dist * unitV;
                    circle2.position -= 0.5f * dist * unitV;
                    // std::cout<<circle1.position.x<< " "<<circle1.position.y<<std::endl;
                    // std::cout<<circle2.position.x<< " "<<circle2.position.y<<std::endl<<std::endl;

                }
            }
        }
    };

    void checkOutOfBounds(){
        for(int i =0;i<ballList.size();i++){
            ball & circle = ballList[i];
            //get the distance between current circle and center, if its greater than radius
            //then it is out of bounds
            sf::Vector2f distanceV = circle.position - center;
            float distance = sqrt(distanceV.x * distanceV.x + distanceV.y * distanceV.y);
            if(distance > radius - circle.radius){
                sf::Vector2f unitV = distanceV / distance;
                //to get new position for circle back inside the sphere, multiple the unit vector
                //that indicates direction of the center of the circle by the 
                //radius of the constrant - the radius of circle and add to the position of the center constraint
                circle.position = center + unitV * (radius - circle.radius);
            }
        }
    };

    void applyGravity(){
        for(auto& i:ballList){
            i.cAccel(gravity);
        }
    }
    void updateObjectPositions(float changeInTime){
        for(auto& i:ballList){
            i.updatePos(changeInTime);
        }
    }
    private:
    std::vector<ball> ballList;
    float time = 0.0f;
    sf::Vector2f gravity = {0.0f,500.0f};
    sf::Vector2f center = {450.0f,450.0f};
    float subSteps = 5.0f;
    float radius = 300.0f;
};




