#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "normalization.h"

class Trail : public sf::Drawable {
public:
  sf::Vector2f position;
  
  int* LinkSize() { return &required_size; }
  float* LinkColor() { return color.channels; }

  void Update();

private:
  int required_size { 300 };
  std::vector<sf::Vertex> vertexes;
  NormalizedColor color;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};