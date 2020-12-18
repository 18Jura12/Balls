#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

#include "ball.h"


class Game{
public:
    Game();
    void run();
private:
    sf::RenderWindow mWindow;
    // Vanjski okvir
    sf::RectangleShape mRectangle;
    // Kugle.
    std::vector<std::unique_ptr<Ball> > mBall;

    void processEvents();
    void update(sf::Time dt);
    void render();

    // Postavi kugle u inicijalne pozicije
    void initPositions(std::size_t nBalls, float radius);
    bool checkPosition(Ball * pball);
    // Daj kuglama inicijalne brzine. maxVel je maksimalna moguća brzina. 
    void initVelocity(float maxVel);

    // Provjeri koliziju sa zidom i promjeni brzinu kuglice na adekvatan način
    void checkForCollisionsWithWalls(Ball * pball, sf::Time dt) const;
    // Provjeri koliziju kuglice pball s ostali kuglicama i promjeni brzine 
    // na odgovarajući način.
    void checkForCollisionsWithBalls(Ball * pball, sf::Time dt) const;

};



