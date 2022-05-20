#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "constaints.h"
#include "normalization.h"
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
  
  void SetPosition(const sf::Vector2f& position);

  const sf::Vector2f& GetPosition() const { return circle.getPosition(); }

  float* LinkColor() { return color.channels; }
  float* LinkDamp() { return &damp; }
  float* LinkMass() { return &mass; }
  float* LinkLength() { return &length; }

  void Update();

private:
  sf::CircleShape circle;
  NormalizedColor color;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
