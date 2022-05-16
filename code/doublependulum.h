#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "constaints.h"
#include "bob.h"

class DoublePendulum : public sf::Drawable {
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
  Bob bob1, bob2;

  // Params defining the state of pendulum
  bool hold = false;
  bool moving1 = false;
  bool moving2 = false;
  bool show_rod = true;

  // Render objects
  sf::Vertex rod_vertices[3];
  sf::VertexBuffer vb;
  std::vector<sf::Vertex> trails;

  // Functions
  void UpdateXY();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
