#pragma once

#include <SFML/Graphics.hpp>

#include "constaints.h"

class Bob : public sf::Drawable {
public:
  float angle;
  float length;
  float acceleration;  // angular acceleration 
  float velocity;  // angular velocity
  float mass;

  void SetRadius(float radius);
  void SetFillColor(const sf::Color& color);
  void SetPosition(const sf::Vector2f& position);
  const sf::Vector2f& GetPosition() const;
  bool IsClicked(const sf::Vector2i& position);

private:
  sf::CircleShape m_circle;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
