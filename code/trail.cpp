#include "trail.h"

void Trail::Update(const sf::Vector2f& position) {
  // Изменение цвета
  auto color { this->color.GetAsSFML() };
  if (!vertexes.empty() && vertexes[0].color != color) {
    for (auto& trail : vertexes) {
      trail.color = color;
    }
  }

  // Изменение размера
  int current_size = static_cast<int>(vertexes.size());
  if (current_size < required_size) {
    vertexes.push_back(sf::Vertex(position, color));
  } else if (current_size > required_size) {
    for (int i { 0 }; i < current_size - 1; i++) {
      vertexes[i].position = vertexes[i + 1].position;
    }
    vertexes[current_size - 1].position = position;
    vertexes.erase(vertexes.begin());
  } else {
    for (int i { 0 }; i < current_size - 1; i++) {
      vertexes[i].position = vertexes[i + 1].position;
    }
    vertexes[current_size - 1].position = position;
  } 
}

void Trail::draw(
  sf::RenderTarget& target,
  sf::RenderStates states) const
{
  target.draw(&vertexes[0], vertexes.size(), sf::LineStrip);
}