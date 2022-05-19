#pragma once

#include "imgui.h"

#include <SFML/Graphics.hpp>

void ToImGuiColor(const sf::Color& sfml_c, float* imgui_c);
sf::Color ToSFMLColor(const float* imgui_c);
sf::Color ToSFML(const ImVec4& color);
ImVec4 ToImGui(const sf::Color& color);

struct NormalizedColor {
  NormalizedColor();
  NormalizedColor(const sf::Color& color);
  ~NormalizedColor();

  NormalizedColor(const NormalizedColor&) = delete;
  NormalizedColor& operator=(const NormalizedColor& other) = delete;
  NormalizedColor(const NormalizedColor&&) noexcept = delete;
  NormalizedColor& operator=(const NormalizedColor&& other) noexcept = delete;
  
  void SetAsSFML(const sf::Color& color);
  sf::Color GetAsSFML() const;

  float* channels = nullptr;
};
