#include "trail.h"

void Trail::Update() {
  // Изменение цвета
  auto c = this->color.GetAsSFML();
  if (!trails.empty() && trails[0].color != c) {
    for (auto& trail : trails) {
      trail.color = c;
    }
  }

  // Изменение размера
  int current_size = static_cast<int>(trails.size());
  if (current_size < required_size) {
    trails.push_back(sf::Vertex(position, c));
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