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
  void ChangeState();
  void MoveBob(sf::Vector2i mouse_position);
  void Clicked(sf::Vector2i mouse_position);
  void RodVisibility();

  // All
  float* Gravity() { return &gravity; }
  // First bob
  float* Bob1Length() { return bob1.Length(); }
  float* Bob1Mass() { return bob1.Mass(); }
  float* Bob1Damp() { return bob1.Damp(); }
  int* Bob1TrailSize() { return &required_size; }
  // Second bob
  float* Bob2Length() { return bob2.Length(); }
  float* Bob2Mass() { return bob2.Mass(); }
  float* Bob2Damp() { return bob2.Damp(); }
  int* Bob2TrailSize() { return &required_size; }

private:
  Bob bob1, bob2;
  int required_size { 300 };
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
  std::vector<sf::Vertex> trails;

  // Functions
  void UpdatePositions();
  void UpdateRod();
  void UpdateBobs();
  void UpdateTrails(const sf::Vector2f& position);
  void PrintInfo();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
