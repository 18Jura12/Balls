#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ball : public sf::Drawable, public sf::Transformable {
public:
    Ball();
    sf::Vector2f mVelocity;
    void setRadius(float r) { mRadius = r; mCircle.setRadius(r); }
    void setChar(char c) { mChar = c; mText.setString(mChar);}
    float getRadius() const { return mRadius; }
    sf::Vector2f getPosition() { return mCircle.getPosition(); }
    sf::Vector2f getOrigin() { return mCircle.getOrigin(); }
    void setPosition();
    void update(sf::Time dt);
private:
    sf::CircleShape mCircle;
    sf::Font mFont;
    sf::Text mText;
    float mRadius;
    char mChar;


    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
};





