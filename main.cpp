#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>
#include <random>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Paddle.hpp"

//function to detect whether or not the ball intersects with either players paddle
bool intersects(sf::RectangleShape rectangle1, sf::RectangleShape rectagnle2)
{
    sf::FloatRect r1 = rectangle1.getGlobalBounds();
    sf::FloatRect r2 = rectagnle2.getGlobalBounds();
    return r1.intersects(r2);
}

int main()
{
    //dimensions for window size and background
    int windowWidth = 1000, windowHeight = 500;
    
    //create window
    sf::Vector2f screenSize(windowWidth, windowHeight);
    sf::RenderWindow window(sf::VideoMode(screenSize.x,screenSize.y), "Pong");
    
    //importing font for the score
    sf::Font font;
    if(!font.loadFromFile("/Users/gilescarlos/Desktop/Bellerose.ttf")) {
        std::cout << "Error loading file" << std::endl;
    }
   
    //creating the text for each players' score
    sf::Text playerOneScore;
    playerOneScore.setFont(font);
    playerOneScore.setString("0");
    playerOneScore.setCharacterSize(100);
    sf::FloatRect textRect1 = playerOneScore.getLocalBounds();
    playerOneScore.setOrigin(textRect1.left + textRect1.width/2.0f, 0);
    playerOneScore.setPosition(sf::Vector2f(3.0f * windowWidth / 4.0f, 0));

    sf::Text playerTwoScore;
    playerTwoScore.setFont(font);
    playerTwoScore.setString("0");
    playerTwoScore.setCharacterSize(100);
    sf::FloatRect textRect2 = playerTwoScore.getLocalBounds();
    playerTwoScore.setOrigin(textRect2.left + textRect2.width/2.0f, 0);
    playerTwoScore.setPosition(sf::Vector2f(windowWidth / 4.0f, 0));
    
    //create paddles
    Paddle playerOne(screenSize,1);
    Paddle playerTwo(screenSize,2);
    
    //create ball and speed
    float ballWidth = 15.0, ballHeight = 15.0;
    sf::RectangleShape ball(sf::Vector2f(ballWidth, ballHeight));
    ball.setOrigin(ballWidth / 2, ballHeight / 2);
    ball.setPosition(windowWidth / 2, windowHeight / 2);
    float originalXYSpeed = .25;
    sf::Vector2f ballSpeed(originalXYSpeed, originalXYSpeed);
    
    //timer and delay to update screen while window is open
    float delay = 0.0001f;
    sf::Clock clock;
    float timer = 0.0f;
    
    //middle divider
    sf::RectangleShape middle(sf::Vector2f(10 / 2, windowHeight));
    middle.setOrigin(5 / 2, windowHeight / 2);
    middle.setPosition(windowWidth / 2, windowHeight / 2);

    //create borders (points of collision)
    sf::RectangleShape top(sf::Vector2f(windowWidth, 10));
    top.setOrigin(windowWidth / 2, 5);
    top.setPosition(windowWidth / 2, 0);
    
    sf::RectangleShape bottom(sf::Vector2f(windowWidth, 10));
    bottom.setOrigin(windowWidth / 2, 5);
    bottom.setPosition(windowWidth / 2, windowHeight);
    
    sf::RectangleShape left(sf::Vector2f(10, windowHeight));
    left.setOrigin(5, windowHeight / 2);
    left.setPosition(0, windowHeight / 2);
    
    sf::RectangleShape right(sf::Vector2f(10, windowHeight));
    right.setOrigin(5, windowHeight / 2);
    right.setPosition(windowWidth, windowHeight / 2);

    while(window.isOpen())
    {
        //variables to update screen while window is open
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerOne.Up();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerOne.Down();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) playerTwo.Up();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) playerTwo.Down();
        
        if (timer > delay)
        {
            timer = 0; //reset timer
            ball.move(ballSpeed.x, ballSpeed.y);
        }
        
        //if the ball gets passed either players' paddle
        if (intersects(ball, left)){
            playerOne.scorePoint();
            ball.setPosition(windowWidth / 2, windowHeight / 2);
            ballSpeed.x = -originalXYSpeed;
            playerOneScore.setString(std::to_string(playerOne.getScore()));
        }
        if (intersects(ball, right)) {
            playerTwo.scorePoint();
            ball.setPosition(windowWidth / 2, windowHeight / 2);
            ballSpeed.x = originalXYSpeed;
            playerTwoScore.setString(std::to_string(playerTwo.getScore()));
        }
        //if the ball hits the top or bottom borders
        if (intersects(ball, top) || intersects(ball, bottom))
            ballSpeed.y = -ballSpeed.y;
        //if the ball hits either players' paddle
        if (intersects(ball, playerOne.shape) || intersects(ball, playerTwo.shape))
            ballSpeed.x = -ballSpeed.x * 1.10; //increase speed in x direction if players don't score
        
        //clear window
        window.clear();
        
        //draw all the objects
        window.draw(middle);
        
        //draw players paddles
        window.draw(playerOne.shape);
        window.draw(playerTwo.shape);
        
        //draw ball
        window.draw(ball);
        
        //draw borders
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);

        window.draw(playerOneScore);
        window.draw(playerTwoScore);
        
        //if a player scores 7 points that player wins
        if (playerOne.getScore() >= 7) {
            sf::Text winningText;
            winningText.setFont(font);
            winningText.setCharacterSize(100);
            winningText.setString("Player One Wins!");
            winningText.setPosition(windowWidth/2, windowHeight/2);
            sf::FloatRect winningtextRect1 = winningText.getLocalBounds();
            winningText.setOrigin(winningtextRect1.left + winningtextRect1.width/2.0f, 0);
            window.draw(winningText);
            //stop ball from moving
            ballSpeed.x = 0;
            ballSpeed.y = 0;
        }
        
        if (playerTwo.getScore() >= 7) {
            sf::Text winningText;
            winningText.setFont(font);
            winningText.setCharacterSize(100);
            winningText.setString("Player Two Wins!");
            winningText.setPosition(windowWidth/2, windowHeight/2);
            sf::FloatRect winningtextRect2 = winningText.getLocalBounds();
            winningText.setOrigin(winningtextRect2.left + winningtextRect2.width/2.0f, 0);
            window.draw(winningText);
            //stop ball from moving
            ballSpeed.x = 0;
            ballSpeed.y = 0;
        }
        
        //display everything
        window.display();
    }
    return 0;
}
