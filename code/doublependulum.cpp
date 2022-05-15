#include "doublependulum.h"

DoublePendulum::DoublePendulum(
  float length1, float length2,
  float mass1, float mass2,
  float angle1, float angle2)
{
  this->length1 = length1;
  this->length2 = length2;
  this->mass1 = mass1;
  this->mass2 = mass2;
  this->angle1 = angle1;
  this->angle2 = angle2;

  angular_acc1 = 0;
  angular_acc2 = 0;
  angular_vel1 = 0;
  angular_vel2 = 0;
}

void DoublePendulum::SetupRenderObjects(float width, float height) {
  texture.create(width, height);
  this->setTexture(texture.getTexture());

  vb.create(3);
  vb.setPrimitiveType(sf::LineStrip);

  rod_vertices[0].position = sf::Vector2f(width/2, height/2);
  for (int i = 0; i < 3; i++) {
    rod_vertices[i].color = sf::Color::Black;
  }

  bob1.setRadius(mass1);
  bob1.setOrigin(sf::Vector2f(bob1.getRadius(), bob1.getRadius()));
  bob1.setFillColor(sf::Color::Black);

  bob2.setRadius(mass2);
  bob2.setOrigin(sf::Vector2f(bob2.getRadius(), bob2.getRadius()));
  bob2.setFillColor(sf::Color::Black);
}

void DoublePendulum::ChangeState() {
  hold = !hold;
}

void DoublePendulum::RodVisibility() {
  show_rod = !show_rod;
}

void DoublePendulum::Update() {
  if (hold) return;
  
  float n11 = -GRAVITY*(2*mass1 + mass2)*std::sin(angle1);
  float n12 = -mass2*GRAVITY*std::sin(angle1 - 2*angle2);
  float n13 = -2*std::sin(angle1 - angle2) * mass2;
  float n14 =
    angular_vel2*angular_vel2*length2 +
    angular_vel1*angular_vel1*length1*std::cos(angle1 - angle2);
  float den = 2*mass1 + mass2 - mass2*std::cos(2*angle1 - 2*angle2);
  float n21 = 2*std::sin(angle1 - angle2);
  float n22 = angular_vel1*angular_vel1*length1*(mass1 + mass2);
  float n23 = GRAVITY*(mass1 + mass2)*std::cos(angle1);
  float n24 = angular_vel2*angular_vel2*length2*mass2*std::cos(angle1 - angle2);

  angular_acc1 = (n11 + n12 + n13*n14)/(length1*den*FPS*FPS);
  angular_acc2 = (n21*(n22 + n23 + n24))/(length2*den*FPS*FPS);

  angular_vel1 += angular_acc1;
  angular_vel2 += angular_acc2;

  angle1 += angular_vel1;
  angle2 += angular_vel2;

  UpdateXY();

  angular_vel1 *= DAMP1;
  angular_vel2 *= DAMP2;
}

void DoublePendulum::Render() {
  sf::Vector2f end_pos1 = sf::Vector2f(
    position1.x*100 + rod_vertices[0].position.x,
    position1.y*100 + rod_vertices[0].position.y);
  sf::Vector2f end_pos2 = sf::Vector2f(
    position2.x*100 + rod_vertices[0].position.x,
    position2.y*100 + rod_vertices[0].position.y);

  rod_vertices[1].position = end_pos1;
  rod_vertices[2].position = end_pos2;
  vb.update(rod_vertices);

  bob1.setPosition(end_pos1);
  bob2.setPosition(end_pos2);

  //Trails
  int s = trails.size();
  if (s < TRAILSIZE){
    trails.push_back(sf::Vertex(
      end_pos2,
      sf::Color(0, 255, 200, (s + 1)*255/TRAILSIZE)));
  } else {
    for (int i = 0; i < s - 1; i++){
      trails[i].position = trails[i + 1].position;
    }
    trails[s - 1].position = end_pos2;
  }

  texture.clear(sf::Color::White);
  if (show_rod) texture.draw(vb);
  texture.draw(bob1);
  texture.draw(bob2);
  texture.draw(&trails[0], trails.size(), sf::LineStrip);
  texture.display();

  std::system("clear");
  std::cout
    << "Bob1" << std::endl
    << "  Acceleration: " << angular_acc1 << std::endl
    << "  Velocity: " << angular_vel1 << std::endl
    << "  Angle: " << angle1 << std::endl
    << std::endl
    << "Bob2" << std::endl
    << "  Acceleration: " << angular_acc2 << std::endl
    << "  Velocity: " << angular_vel2 << std::endl
    << "  Angle: " << angle2 << std::endl
    << std::endl;
}

void DoublePendulum::UpdateXY() {
  position1.x = length1*std::sin(angle1);
  position1.y = length1*std::cos(angle1);
  position2.x = position1.x + length2*std::sin(angle2);
  position2.y = position1.y + length2*std::cos(angle2);
}

int DoublePendulum::BobClicked(sf::Vector2i mouse_position) {
  if (bob1.getGlobalBounds().contains(
      sf::Vector2f(mouse_position.x, mouse_position.y)))
    return 1;
  else if (bob2.getGlobalBounds().contains(
           sf::Vector2f(mouse_position.x, mouse_position.y)))
    return 2;
  else
    return 0;
}

void DoublePendulum::Clicked(sf::Vector2i mouse_position) {
  int id = BobClicked(mouse_position);
  if (id == 0) return;
  hold = true;
  if (id == 1) moving1 = !moving1;
  if (id == 2) moving2 = !moving2;
}

void DoublePendulum::MoveBob(sf::Vector2i mouse_position) {
  if (!moving1 && !moving2) return;
  float x = mouse_position.x;
  float y = mouse_position.y;
  if (moving1) {
    float delx = x - rod_vertices[0].position.x;
    float dely = y - rod_vertices[0].position.y;
    angle1 = std::atan(delx / dely);
    if (dely < 0) angle1 += PI;
    length1 = std::sqrt(delx*delx + dely*dely)/100;
  }
  if (moving2) {
    float delx = x - rod_vertices[1].position.x;
    float dely = y - rod_vertices[1].position.y;
    angle2 = std::atan(delx / dely);
    if (dely < 0) angle2 += PI;
      length2 = std::sqrt(delx*delx + dely*dely)/100;
  }
  angular_vel1 = 0;
  angular_vel2 = 0;
  UpdateXY();
}
