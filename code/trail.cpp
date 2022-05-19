#include "trail.h"

void Trail::SetColor(const sf::Color& color) {
  trail_color = color;
  for (auto& trail : trails) {
    trail.color = color;
  }
}

void Trail::SetPosition(const sf::Vector2f& position) {
  this->position = position;
}

void Trail::SetSize(int size) {
  required_size = size;
};

void Trail::Update() {
  int current_size = static_cast<int>(trails.size());
  auto position { GetPosition() };
  if (current_size < required_size) {
    trails.push_back(sf::Vertex(position, trail_color));
  } else if (current_size > required_size) {
    for (int i { 0 }; i < current_size - 1; i++) {
      trails[i].position = trails[i + 1].position;
    }
    trails[current_size - 1].position = position;
    trails.erase(trails.begin());
  } else {
    for (int i { 0 }; i < current_size - 1; i++) {
      trails[i].position = trails[i + 1].position;
    }
    trails[current_size - 1].position = position;
  } 
}

void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(&trails[0], trails.size(), sf::LineStrip);
}