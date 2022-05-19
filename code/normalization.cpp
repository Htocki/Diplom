#include "normalization.h"

#include <cstdint>

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