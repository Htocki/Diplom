#include "normalization.h"

#include <cstdint>

void ToImGuiColor(const sf::Color& sfml_c, float* imgui_c) {
  imgui_c[0] = float(sfml_c.r)/255.f;
  imgui_c[1] = float(sfml_c.g)/255.f;
  imgui_c[2] = float(sfml_c.b)/255.f;
  imgui_c[3] = float(sfml_c.a)/255.f;
}

sf::Color ToSFMLColor(const float* imgui_c) {
  return sf::Color {
    uint8_t(imgui_c[0]*255),
    uint8_t(imgui_c[1]*255),
    uint8_t(imgui_c[2]*255),
    uint8_t(imgui_c[3]*255) 
  };
}

sf::Color ToSFML(const ImVec4& color) {
  return sf::Color(
    uint8_t(color.x*255),
    uint8_t(color.y*255),
    uint8_t(color.z*255),
    uint8_t(color.w*255) 
  );
}

ImVec4 ToImGui(const sf::Color& color) {
  return ImVec4(
    float(color.r)/255.f, 
    float(color.g)/255.f,
    float(color.b)/255.f,
    float(color.a)/255.f
  );
}

NormalizedColor::NormalizedColor()
  : channels { new float[4] }
{
  channels[0] = 0.f;
  channels[1] = 0.f;
  channels[2] = 0.f;
  channels[3] = 1.f;
}

NormalizedColor::NormalizedColor(const sf::Color& color) 
  : channels { new float[4] }
{
  channels[0] = float(color.r)/255.f;
  channels[1] = float(color.g)/255.f;
  channels[2] = float(color.b)/255.f;
  channels[3] = float(color.a)/255.f;
}

NormalizedColor::~NormalizedColor() {
  delete[] channels;
}

void NormalizedColor::SetAsSFML(const sf::Color& color) {
  channels[0] = float(color.r)/255.f;
  channels[1] = float(color.g)/255.f;
  channels[2] = float(color.b)/255.f;
  channels[3] = float(color.a)/255.f;
}

sf::Color NormalizedColor::GetAsSFML() const {
  return sf::Color {
    uint8_t(channels[0]*255),
    uint8_t(channels[1]*255),
    uint8_t(channels[2]*255),
    uint8_t(channels[3]*255) 
  };
}