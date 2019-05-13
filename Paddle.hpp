#include <SFML/Graphics.hpp>
#include <iostream>

class Paddle {
    float speed = .5; //adjusts paddle position by moving 1 pixel in the y direction
    sf::Vector2f border; //border of window
    sf::Vector2f paddleSize; //size of each paddle
    sf::Vector2f position; //position of paddle
    sf::Vector2f screenSize; //size of the window
    int score = 0;
public:
    sf::RectangleShape shape;
    
    Paddle(sf::Vector2f _screenSize, int player)
    {
        screenSize = _screenSize;
        border = sf::Vector2f(0, 0);
        paddleSize = sf::Vector2f(20, 100);

        //set position of paddle accordingly
        if (player == 1) {
            position = sf::Vector2f(0, (screenSize.y / 2) - 50);
            shape.setFillColor(sf::Color(255, 0, 0));
        } else if (player == 2) {
            position = sf::Vector2f(screenSize.x - 20, (screenSize.y / 2) - 50);
            shape.setFillColor(sf::Color(0, 0, 255));
        }
        
        shape.setSize(paddleSize);
        shape.setPosition(position);
    }
    
    int getScore() { return score; }
    
    void scorePoint() { score += 1; }
    
    void Up() {
        position.y -= speed;
        
        //if paddle hits top border stop moving up
        if (position.y < border.y)
            position.y += speed;
        
        shape.setPosition(position);
    }
    
    void Down() {
        position.y += speed;
        
        //if paddle hits bottom border stop moving down
        if(position.y > screenSize.y - paddleSize.y)
            position.y -= speed;
        
        shape.setPosition(position);
    }
};
