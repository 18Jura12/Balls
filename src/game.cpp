#include "game.h"
#include <math.h>

// Ovdje dolazi vaš kod



Game::Game() : mWindow(sf::VideoMode(600, 600), "SFML window")
{
    mRectangle.setSize(sf::Vector2f(580,580));
    mRectangle.setPosition(10,10);
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setFillColor(sf::Color::Transparent);
    mRectangle.setOutlineThickness(2);

    initPositions(7,25);
    initVelocity(30);


}

void Game::run()
{
    sf::Time dt = sf::seconds(1.0f/60.0f);
    // Start the game loop
    while (mWindow.isOpen())
    {
        processEvents();
        update(dt);

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Game::update(sf::Time dt)
{

    for(auto &x : mBall){
        checkForCollisionsWithBalls(x.get(),dt);
        checkForCollisionsWithWalls(x.get(),dt);
        (*x).update(dt);
    }
}

void Game::render()
{
    mWindow.clear();

    mWindow.draw(mRectangle);
    for(auto &x : mBall){
        mWindow.draw(*x);
    }

    mWindow.display();
}

void Game::initPositions(std::size_t nBalls, float radius)
{
    char c = 'A';
    while(nBalls){
        auto b=std::unique_ptr<Ball>(new Ball());
        b->setRadius(radius);
        b->setChar(c);
       // b->setPosition();
        do {b->setPosition();}
        while (!checkPosition(b.get()));
        mBall.push_back(std::move(b));
        c++;
        nBalls--;
    }
}

bool Game::checkPosition(Ball *pball)
{
    if(mBall.empty()) return true;
    for(auto &x : mBall)
        if((x->getPosition().x-pball->getPosition().x)*(x->getPosition().x-pball->getPosition().x)+(x->getPosition().y-pball->getPosition().y)*(x->getPosition().y-pball->getPosition().y)<(2*x->getRadius())*(2*x->getRadius()))
            return false;
    return true;
}

void Game::initVelocity(float maxVel)
{
    std::default_random_engine r_x;
    r_x.seed(std::time(nullptr));
    std::normal_distribution<float> nd(0.0,1.0);

    for(auto &x : mBall) (*x).mVelocity = sf::Vector2f(nd(r_x)*maxVel,nd(r_x)*maxVel);
}

void Game::checkForCollisionsWithWalls(Ball *pball, sf::Time dt) const
{

    sf::Vector2f b=pball->mVelocity*dt.asSeconds();
    if((pball->getPosition().x-pball->getRadius()+b.x)<10) pball->mVelocity.x=-pball->mVelocity.x;
    else if((pball->getPosition().x+pball->getRadius()+b.x)>590) pball->mVelocity.x=-pball->mVelocity.x;
    else if((pball->getPosition().y-pball->getRadius()+b.y)<10) pball->mVelocity.y=-pball->mVelocity.y;
    else if((pball->getPosition().y+pball->getRadius()+b.y)>590) pball->mVelocity.y=-pball->mVelocity.y;

}

void Game::checkForCollisionsWithBalls(Ball *pball, sf::Time dt) const
{
    for(auto &x : mBall){
        sf::Vector2f vp=pball->mVelocity;
        sf::Vector2f vx=x->mVelocity;
        if(sqrt((x->getPosition().x-pball->getPosition().x+vx.x*dt.asSeconds()-vp.x*dt.asSeconds())*(x->getPosition().x-pball->getPosition().x+vx.x*dt.asSeconds()-vp.x*dt.asSeconds())+(x->getPosition().y-pball->getPosition().y+vx.y*dt.asSeconds()-vp.y*dt.asSeconds())*(x->getPosition().y-pball->getPosition().y+vx.y*dt.asSeconds()-vp.y*dt.asSeconds()))<2*pball->getRadius())
        {
            if(x->getPosition()!=pball->getPosition()){
            pball->mVelocity.x=vp.x-( (vp.x-vx.x)*(pball->getPosition().x-x->getPosition().x) + (vp.y-vx.y)*(pball->getPosition().y-x->getPosition().y) )*(pball->getPosition().x-x->getPosition().x)/( (pball->getPosition().x - x->getPosition().x)*(pball->getPosition().x - x->getPosition().x) + (pball->getPosition().y - x->getPosition().y)*(pball->getPosition().y - x->getPosition().y) );
            pball->mVelocity.y=vp.y-( (vp.x-vx.x)*(pball->getPosition().x-x->getPosition().x) + (vp.y-vx.y)*(pball->getPosition().y-x->getPosition().y) )*(pball->getPosition().y-x->getPosition().y)/( (pball->getPosition().x - x->getPosition().x)*(pball->getPosition().x - x->getPosition().x) + (pball->getPosition().y - x->getPosition().y)*(pball->getPosition().y - x->getPosition().y) );
            x->mVelocity.x=vx.x-( (vx.x-vp.x)*(x->getPosition().x-pball->getPosition().x) + (vx.y-vp.y)*(x->getPosition().y-pball->getPosition().y) )*(x->getPosition().x-pball->getPosition().x)/( (pball->getPosition().x-x->getPosition().x)*(pball->getPosition().x-x->getPosition().x) + (pball->getPosition().y-x->getPosition().y)*(pball->getPosition().y-x->getPosition().y) );
            x->mVelocity.y=vx.y-( (vx.x-vp.x)*(x->getPosition().x-pball->getPosition().x) + (vx.y-vp.y)*(x->getPosition().y-pball->getPosition().y) )*(x->getPosition().y-pball->getPosition().y)/( (pball->getPosition().x-x->getPosition().x)*(pball->getPosition().x-x->getPosition().x) + (pball->getPosition().y-x->getPosition().y)*(pball->getPosition().y-x->getPosition().y) );
            break;
            }
        }
    }
}
