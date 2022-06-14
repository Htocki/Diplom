#pragma once

#include "imgui.h"

#include <SFML/Graphics.hpp>

struct NormalizedColor {
  NormalizedColor();
  NormalizedColor(const sf::Color& color);
  ~NormalizedColor();

  void SetAsSFML(const sf::Color& color);
  sf::Color GetAsSFML() const;

  float* channels = nullptr;
};