#include "doublependulum.h"

DoublePendulum::DoublePendulum(
  float length1, float length2,
  float mass1, float mass2,
  float angle1, float angle2,
  sf::Vector2f position)
{
  bob1.angle = angle1;
  bob1.damp = 0.999;
  bob1.length = length1;
  bob1.mass = mass1;

  bob2.angle = angle2;
  bob2.damp = 0.999;
  bob2.length = length2;
  bob2.mass = mass2;

  vb.create(3);
  vb.setPrimitiveType(sf::LineStrip);
  auto rod_color = this->rod_color.GetAsSFML();
  rod_vertices[0].position = position;
  for (int i { 0 }; i < 3; ++i) {
    rod_vertices[i].color = rod_color;
  }
}

void DoublePendulum::ChangeState() {
  hold = !hold;
}

void DoublePendulum::Update() {
  if (hold) return;

  // Изменение цвета rod
  auto rod_color = this->rod_color.GetAsSFML();
  for (int i { 0 }; i < 3; ++i) {
    rod_vertices[i].color = rod_color;
  }
  
  // Вычисление ускорений
  float n11 = -gravity*(2*bob1.mass + bob2.mass)*std::sin(bob1.angle);
  float n12 = -bob2.mass*gravity*std::sin(bob1.angle - 2*bob2.angle);
  float n13 = -2*std::sin(bob1.angle - bob2.angle) * bob2.mass;
  float n14 = std::pow(bob2.velocity, 2)*bob2.length +
    std::pow(bob1.velocity, 2)*bob1.length*std::cos(bob1.angle - bob2.angle);
  float n21 = 2*std::sin(bob1.angle - bob2.angle);
  float n22 = std::pow(bob1.velocity, 2)*bob1.length*(bob1.mass + bob2.mass);
  float n23 = gravity*(bob1.mass + bob2.mass)*std::cos(bob1.angle);
  float n24 = std::pow(bob2.velocity, 2)*bob2.length*bob2.mass*
    std::cos(bob1.angle - bob2.angle);
  float den = 2*bob1.mass + bob2.mass -
    bob2.mass*std::cos(2*bob1.angle - 2*bob2.angle);
  bob1.acceleration = (n11 + n12 + n13*n14)/(bob1.length*den*FPS*FPS);
  bob2.acceleration = (n21*(n22 + n23 + n24))/(bob2.length*den*FPS*FPS);
  
  // Обновление скоростей
  bob1.velocity += bob1.acceleration;
  bob2.velocity += bob2.acceleration;
  
  // Обновление углов
  bob1.angle += bob1.velocity;
  bob2.angle += bob2.velocity;
  
  // Умножение скоростей на коэффициенты затухания
  bob1.velocity *= bob1.damp;
  bob2.velocity *= bob2.damp;
  
  // Вычисление позиций
  pos1.x = bob1.length*std::sin(bob1.angle);
  pos1.y = bob1.length*std::cos(bob1.angle); 
  pos2.x = pos1.x + bob2.length*std::sin(bob2.angle);
  pos2.y = pos1.y + bob2.length*std::cos(bob2.angle);
  end_pos1.x = pos1.x*100 + rod_vertices[0].position.x;
  end_pos1.y = pos1.y*100 + rod_vertices[0].position.y;
  end_pos2.x = pos2.x*100 + rod_vertices[0].position.x;
  end_pos2.y = pos2.y*100 + rod_vertices[0].position.y;
  
  // Обновление отвесов
  rod_vertices[1].position = end_pos1;
  rod_vertices[2].position = end_pos2;
  vb.update(rod_vertices);
  bob1.Update(end_pos1);
  bob2.Update(end_pos2);
}

void DoublePendulum::draw(
  sf::RenderTarget& target,
  sf::RenderStates states) const
{
  target.draw(bob1.trail);
  target.draw(bob2.trail);
  target.draw(vb, states);
  target.draw(bob1);
  target.draw(bob2);
}