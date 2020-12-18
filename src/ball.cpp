#include "game.h"

// Ovdje dolazi vaš kod.

Ball::Ball()
{
    mCircle.setFillColor(sf::Color::Green);
    mFont.loadFromFile("Comfortaa-Bold.ttf");
    mText.setFont(mFont);
    mText.setStyle(sf::Text::Style::Bold);
}

void Ball::setPosition()
{
    std::default_random_engine r;
    r.seed(std::time(nullptr));
    std::uniform_int_distribution<int> dist(11+(int)(mCircle.getRadius()), 589-(int)(mCircle.getRadius()));

    mCircle.setPosition(sf::Vector2f(dist(r),dist(r)));
    mCircle.setOrigin(mCircle.getRadius(),mCircle.getRadius());
    mText.setOrigin(mText.getLocalBounds().width/1.8f,mText.getLocalBounds().height/1.3f);
    mText.setPosition(mCircle.getPosition());
}

void Ball::update(sf::Time dt)
{
    mText.rotate(2*dt.asSeconds());
    mCircle.move(mVelocity*dt.asSeconds());
    mText.move(mVelocity*dt.asSeconds());
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mCircle, states);
    target.draw(mText, states);
}


