#include "bob.h"

void Bob::SetDamp(float damp) {
  this->damp = damp;
}

void Bob::SetFillColor(const sf::Color& color) {
  circle.setFillColor(color);
}

void Bob::SetLength(float length) {
  this->length = length;
}

void Bob::SetMass(float mass) {
  this->mass = mass;
  circle.setRadius(mass);
  circle.setOrigin(sf::Vector2f(mass, mass));
}

void Bob::SetPosition(const sf::Vector2f& position) {
  circle.setPosition(position);
}

void Bob::SetTrailSize(int size) {
  required_size = size;
};

void Bob::SetTrailColor(const sf::Color& color) {
  trail_color = color;
  for (auto& trail : trails) {
    trail.color = color;
  }
}

bool Bob::IsClicked(const sf::Vector2i& position) {
  return circle.getGlobalBounds().contains(position.x, position.y);
}

void Bob::Update() {
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

void Bob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(&trails[0], trails.size(), sf::LineStrip);
  target.draw(circle, states);
}
