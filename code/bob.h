#pragma once

#include <SFML/Graphics.hpp>

#include "constaints.h"

class Bob : public sf::Drawable {
public:
  float angle { 0.f };
  float length { 0.f };
  float acceleration { 0.f };  // angular acceleration 
  float velocity { 0.f };  // angular velocity
  float mass { 0.f };
  float damp { 0.f };

  void SetRadius(float radius);
  void SetFillColor(const sf::Color& color);
  void SetPosition(const sf::Vector2f& position);
  const sf::Vector2f& GetPosition() const;
  bool IsClicked(const sf::Vector2i& position);

  float* Damp() { return &damp; }

private:
  sf::CircleShape m_circle;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
