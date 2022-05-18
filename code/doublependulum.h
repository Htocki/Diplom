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

  void SetGravity(float gravity) { this->gravity = gravity; }
  // First bob
  void SetBob1Length(float length) { bob1.SetLength(length); }
  void SetBob1Mass(float mass) { bob1.SetMass(mass); }
  void SetBob1Damp(float damp) { bob1.SetDamp(damp); }
  void SetBob1TrailSize(int trail_size) { required_size = trail_size; }
  void SetBob1FillColor(const sf::Color& color) { bob1.SetFillColor(color); }
  // Second bob
  void SetBob2Length(float length) { bob2.SetLength(length); }
  void SetBob2Mass(float mass) { bob2.SetMass(mass); }
  void SetBob2Damp(float damp) { bob2.SetDamp(damp); }
  void SetBob2TrailSize(int trail_size) { required_size = trail_size; }
  void SetBob2FillColor(const sf::Color& color) { bob2.SetFillColor(color); }

  float GetGravity() const { return gravity; }
  // First bob
  float GetBob1Length() const { return bob1.GetLength(); }
  float GetBob1Mass() const { return bob1.GetMass(); }
  float GetBob1Damp() const { return bob1.GetDamp(); }
  int GetBob1TrailSize() const { return required_size; }
  const sf::Color& GetBob1FillColor() const { return bob1.GetFillColor(); }
  // Second bob
  float GetBob2Length() const { return bob2.GetLength(); }
  float GetBob2Mass() const { return bob2.GetMass(); }
  float GetBob2Damp() const { return bob2.GetDamp(); }
  int GetBob2TrailSize() const { return required_size; }
  const sf::Color& GetBob2FillColor() const { return bob2.GetFillColor(); }

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
