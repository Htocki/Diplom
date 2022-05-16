#pragma once

#include <SFML/Graphics.hpp>

#include "constaints.h"

class Bob : public sf::Drawable {
public:
  float angle { 0.f };
  float acceleration { 0.f };  // angular acceleration 
  float velocity { 0.f };  // angular velocity
 
  void SetDamp(float damp);
  void SetFillColor(const sf::Color& color);
  void SetLength(float length);
  void SetMass(float mass);
  void SetPosition(const sf::Vector2f& position); 

  float GetDamp() const { return damp; }
  float GetLength() const { return length; }
  float GetMass() const { return mass; } 
  const sf::Vector2f& GetPosition() const { return circle.getPosition(); }
  
  bool IsClicked(const sf::Vector2i& position);

private:
  sf::CircleShape circle;
  float damp { 0.f };
  float length { 0.f };
  float mass { 0.f }; 

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
