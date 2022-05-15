#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "constaints.h"

class DoublePendulum : public sf::Sprite {
public:
  DoublePendulum(
    float length1, float length2,
    float mass1, float mass2,
    float angle1, float angle2);

  void SetupRenderObjects(float width, float height);
  void Update();
  void Render();
  void ChangeState();
  void MoveBob(sf::Vector2i mouse_position);
  void Clicked(sf::Vector2i mouse_position);
  void RodVisibility();

private:
  // Params defining the state of pendulum
  float angle1, angle2;
  float length1, length2;
  float angular_acc1, angular_acc2;
  float angular_vel1, angular_vel2;
  float mass1, mass2;
  sf::Vector2f position1, position2;
  bool hold = false;
  bool moving1 = false;
  bool moving2 = false;
  bool show_rod = true;

  // Render objects
  sf::RenderTexture texture;
  sf::Vertex rod_vertices[3];
  sf::VertexBuffer vb;
  sf::CircleShape bob1, bob2;
  std::vector<sf::Vertex> trails;

  // Functions
  void UpdateXY();
  int BobClicked(sf::Vector2i mouse_position);
};
