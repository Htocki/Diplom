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
    float angle1, float angle2,
    sf::Vector2f position);

  void Update();
  void ChangeState();

  float* LinkGravity() { return &gravity; }

private:
  float gravity { 9.8 };
  sf::Vector2f pos1, pos2;
  sf::Vector2f end_pos1, end_pos2;

  // Params defining the state of pendulum
  bool hold { false };

  // Render objects
  sf::Vertex rod_vertices[3];
  sf::VertexBuffer vb;

  // Functions
  void UpdateRod();
  void PrintInfo();
  virtual void draw(
    sf::RenderTarget& target,
    sf::RenderStates states) const;
};