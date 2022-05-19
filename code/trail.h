#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "normalization.h"

class Trail : public sf::Drawable {
public:
  void SetPosition(const sf::Vector2f& position);

  const sf::Vector2f& GetPosition() const { return position; }

  int* LinkSize() { return &required_size; }
  float* LinkColor() { return color.channels; }

  void Update();

private:
  int required_size { 300 };
  std::vector<sf::Vertex> trails;
  NormalizedColor color;
  sf::Vector2f position;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};