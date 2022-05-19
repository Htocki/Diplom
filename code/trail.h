#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Trail : public sf::Drawable {
public:
  void SetColor(const sf::Color& color);
  void SetPosition(const sf::Vector2f& position);

  const sf::Color& GetColor() const { return trail_color; }
  const sf::Vector2f& GetPosition() const { return position; }

  int* LinkSize() { return &required_size; }

  void Update();

private:
  int required_size { 300 };
  std::vector<sf::Vertex> trails;
  sf::Color trail_color { sf::Color::Green };
  sf::Vector2f position;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};