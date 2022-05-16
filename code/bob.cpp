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

bool Bob::IsClicked(const sf::Vector2i& position) {
  return circle.getGlobalBounds().contains(position.x, position.y);
}

void Bob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(circle, states);
}
