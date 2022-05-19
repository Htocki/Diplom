#include "doublependulum.h"

DoublePendulum::DoublePendulum(
  float length1, float length2,
  float mass1, float mass2,
  float angle1, float angle2,
  sf::Vector2f position)
{
  bob1.angle = angle1;
  bob1.damp = 0.999;
  bob1.SetFillColor(sf::Color::Black);
  bob1.length = length1;
  bob1.mass = mass1;

  bob2.angle = angle2;
  bob2.damp = 0.999;
  bob2.SetFillColor(sf::Color::Black);
  bob2.length = length2;
  bob2.mass = mass2;

  vb.create(3);
  vb.setPrimitiveType(sf::LineStrip);
  rod_vertices[0].position = position;
  for (int i { 0 }; i < 3; ++i) {
    rod_vertices[i].color = sf::Color::Black;
  }
}

void DoublePendulum::ChangeState() {
  hold = !hold;
}

void DoublePendulum::RodVisibility() {
  show_rod = !show_rod;
}

void DoublePendulum::Update() {
  if (hold) return;
  
  float n11 = -gravity*(2*bob1.mass + bob2.mass)*std::sin(bob1.angle);
  float n12 = -bob2.mass*gravity*std::sin(bob1.angle - 2*bob2.angle);
  float n13 = -2*std::sin(bob1.angle - bob2.angle) * bob2.mass;
  float n14 = bob2.velocity*bob2.velocity*bob2.length +
    bob1.velocity*bob1.velocity*bob1.length*std::cos(bob1.angle -
    bob2.angle);
  
  float n21 = 2*std::sin(bob1.angle - bob2.angle);
  float n22 = bob1.velocity*bob1.velocity*bob1.length*(bob1.mass + bob2.mass);
  float n23 = gravity*(bob1.mass + bob2.mass)*std::cos(bob1.angle);
  float n24 = bob2.velocity*bob2.velocity*bob2.length*bob2.mass*
    std::cos(bob1.angle - bob2.angle);
  
  float den = 2*bob1.mass + bob2.mass -
    bob2.mass*std::cos(2*bob1.angle - 2*bob2.angle);

  bob1.acceleration = (n11 + n12 + n13*n14)/(bob1.length*den*FPS*FPS);
  bob2.acceleration = (n21*(n22 + n23 + n24))/(bob2.length*den*FPS*FPS);
  bob1.velocity += bob1.acceleration;
  bob2.velocity += bob2.acceleration;
  bob1.angle += bob1.velocity;
  bob2.angle += bob2.velocity;
  bob1.velocity *= bob1.damp;
  bob2.velocity *= bob2.damp;
  
  UpdatePositions();
  UpdateRod();
  
  bob1.SetPosition(end_pos1);
  bob2.SetPosition(end_pos2);
  bob1.Update();
  bob2.Update();

  //PrintInfo();
}

void DoublePendulum::UpdateRod() {
  rod_vertices[1].position = end_pos1;
  rod_vertices[2].position = end_pos2;
  vb.update(rod_vertices);
}

void DoublePendulum::PrintInfo() {
  std::system("clear");
  std::cout
    << "Bob1" << std::endl
    << "  Acceleration: " << bob1.acceleration << std::endl
    << "  Velocity: " << bob1.velocity << std::endl
    << "  Angle: " << bob1.angle << std::endl
    << std::endl
    << "Bob2" << std::endl
    << "  Acceleration: " << bob2.acceleration << std::endl
    << "  Velocity: " << bob2.velocity << std::endl
    << "  Angle: " << bob2.angle << std::endl
    << std::endl;
}

void DoublePendulum::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (show_rod) { target.draw(vb, states); }
  target.draw(bob1.trail);
  target.draw(bob2.trail);
  target.draw(bob1);
  target.draw(bob2);
}

void DoublePendulum::UpdatePositions() {
  pos1.x = bob1.length*std::sin(bob1.angle);
  pos1.y = bob1.length*std::cos(bob1.angle); 
  pos2.x = pos1.x + bob2.length*std::sin(bob2.angle);
  pos2.y = pos1.y + bob2.length*std::cos(bob2.angle);
  
  end_pos1.x = pos1.x*100 + rod_vertices[0].position.x;
  end_pos1.y = pos1.y*100 + rod_vertices[0].position.y;
  end_pos2.x = pos2.x*100 + rod_vertices[0].position.x;
  end_pos2.y = pos2.y*100 + rod_vertices[0].position.y;
}

void DoublePendulum::Clicked(sf::Vector2i mouse_position) {
  if (bob1.IsClicked(mouse_position)) { moving1 = !moving1; }
  if (bob2.IsClicked(mouse_position)) { moving2 = !moving2; }
}

namespace {
void MoveBob(Bob& bob, const sf::Vector2f& del) {
  bob.angle = std::atan(del.x / del.y);
  if (del.y < 0) { bob.angle += PI; }
  bob.length = std::sqrt(del.x*del.x + del.y*del.y)/100;
}
} // namespace

void DoublePendulum::MoveBob(sf::Vector2i mouse_position) {
  if (moving1) {
    ::MoveBob(bob1, sf::Vector2f(
      mouse_position.x - rod_vertices[0].position.x,
      mouse_position.y - rod_vertices[0].position.y));
  } else if (moving2) {
    ::MoveBob(bob1, sf::Vector2f(
      mouse_position.x - rod_vertices[1].position.x,
      mouse_position.y - rod_vertices[1].position.y));
  } else { return; }
  bob1.velocity = 0;
  bob2.velocity = 0;
  UpdatePositions();
}
