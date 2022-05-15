#include "bob.h"

void Bob::SetRadius(float radius) {
  m_circle.setRadius(radius);
  m_circle.setOrigin(sf::Vector2f(radius, radius));
}

void Bob::SetFillColor(const sf::Color& color) {
  m_circle.setFillColor(color);
}

void Bob::SetPosition(const sf::Vector2f& position) {
  m_circle.setPosition(position);
}

const sf::Vector2f& Bob::GetPosition() const {
  return m_circle.getPosition();
}

bool Bob::IsClicked(const sf::Vector2i& position) {
  return m_circle.getGlobalBounds().contains(position.x, position.y);
}

void Bob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_circle, states);
}
