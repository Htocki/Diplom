#include "bob.h"

void Bob::SetPosition(const sf::Vector2f& position) {
  circle.setPosition(position);
  trail.position = position;
}

bool Bob::IsClicked(const sf::Vector2i& position) {
  return circle.getGlobalBounds().contains(position.x, position.y);
}

void Bob::Update() {
  // Изменение цвета
  auto color = this->color.GetAsSFML();
  if (color != circle.getFillColor()) {
    circle.setFillColor(color);
  }

  // Изменение массы
  if (circle.getRadius() != mass) {
    circle.setRadius(mass);
    circle.setOrigin(sf::Vector2f(mass, mass));
  }

  // Обновление следа
  trail.Update();
}

void Bob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(circle, states);
}
