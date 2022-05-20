#include "bob.h"

void Bob::Update(const sf::Vector2f& position) {
  // Изменение позиции
  circle.setPosition(position);

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
  trail.Update(position);
}

void Bob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(circle, states);
}