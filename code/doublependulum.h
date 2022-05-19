#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "constaints.h"
#include "bob.h"

class DoublePendulum : public sf::Drawable {
public:
  Bob bob1, bob2;

  DoublePendulum(
    float length1, float length2,
    float mass1, float mass2,
    float angle1, float angle2);

  void SetupRenderObjects(float width, float height);
  void Update();
  void ChangeState();
  void MoveBob(sf::Vector2i mouse_position);
  void Clicked(sf::Vector2i mouse_position);
  void RodVisibility();

  void SetGravity(float gravity) { this->gravity = gravity; }

  float GetGravity() const { return gravity; }

private:
  float gravity { 9.8 };
  sf::Vector2f pos1, pos2;
  sf::Vector2f end_pos1, end_pos2;

  // Params defining the state of pendulum
  bool hold = false;
  bool moving1 = false;
  bool moving2 = false;
  bool show_rod = true;

  // Render objects
  sf::Vertex rod_vertices[3];
  sf::VertexBuffer vb;

  // Functions
  void UpdatePositions();
  void UpdateRod();
  void PrintInfo();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
