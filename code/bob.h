#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "constaints.h"
#include "trail.h"

class Bob : public sf::Drawable {
public:
  float acceleration { 0.f };  // angular acceleration 
  float angle { 0.f };
  float damp { 0.f };
  float length { 0.f };
  float mass { 0.f };
  Trail trail;
  float velocity { 0.f };  // angular velocity
  

  void SetFillColor(const sf::Color& color);
  void SetPosition(const sf::Vector2f& position);

  const sf::Color& GetFillColor() const { return circle.getFillColor(); }
  const sf::Vector2f& GetPosition() const { return circle.getPosition(); }

  float* LinkDamp() { return &damp; }
  float* LinkMass() { return &mass; }
  float* LinkLength() { return &length; }

  void Update();
  
  bool IsClicked(const sf::Vector2i& position);

private:
  sf::CircleShape circle;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
