#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "doublependulum.h"

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 600;

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

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double pendulum");
  window.setFramerateLimit(FPS);
  window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(window);
  sf::Clock deltaClock;

  DoublePendulum pendulum(1, 0.8, 10, 4, 90*PI/180, 90*PI/180);
  pendulum.SetupRenderObjects(WIDTH, HEIGHT);

  float gravity { pendulum.GetGravity() };
  float* background_color = new float[4];
  ToImGuiColor(sf::Color::White, background_color);
  // First bob
  float bob1_length { pendulum.bob1.GetLength() };
  float bob1_mass { pendulum.bob1.GetMass() };
  float bob1_damp { pendulum.bob1.GetDamp() };
  int bob1_trail_size { pendulum.bob1.trail.GetSize() };
  float* bob1_color = new float[4];
  ToImGuiColor(pendulum.bob1.GetFillColor(), bob1_color);
  float* bob1_trail_color = new float[4];
  ToImGuiColor(pendulum.bob1.trail.GetColor(), bob1_trail_color);
  // Second bob
  float bob2_length { pendulum.bob2.GetLength() };
  float bob2_mass { pendulum.bob2.GetMass() };
  float bob2_damp { pendulum.bob2.GetDamp() };
  int bob2_trail_size { pendulum.bob2.trail.GetSize() };
  float* bob2_color = new float[4];
  ToImGuiColor(pendulum.bob2.GetFillColor(), bob2_color);
  float* bob2_trail_color = new float[4];
  ToImGuiColor(pendulum.bob2.trail.GetColor(), bob2_trail_color);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::MouseButtonPressed) {
        pendulum.Clicked(sf::Mouse::getPosition(window));
      }

      if (event.type == sf::Event::MouseMoved) {
        pendulum.MoveBob(sf::Mouse::getPosition(window));
      }

      if (event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
          case sf::Keyboard::Escape:
            window.close();
            break;
          case sf::Keyboard::Space:
            pendulum.ChangeState();
            break;
          case sf::Keyboard::R:
            pendulum.RodVisibility();
            break;
        }
      }
    }
  
    pendulum.Update();
    ImGui::SFML::Update(window, deltaClock.restart());

  gravity = pendulum.GetGravity();
  // First bob
  bob1_length = pendulum.bob1.GetLength();
  bob1_mass = pendulum.bob1.GetMass();
  bob1_damp = pendulum.bob1.GetDamp();
  bob1_trail_size = pendulum.bob1.trail.GetSize();
  ToImGuiColor(pendulum.bob1.GetFillColor(), bob1_color);
  ToImGuiColor(pendulum.bob1.trail.GetColor(), bob1_trail_color);
  // Second bob
  bob2_length = pendulum.bob2.GetLength();
  bob2_mass = pendulum.bob2.GetMass();
  bob2_damp = pendulum.bob2.GetDamp();
  bob2_trail_size = pendulum.bob2.trail.GetSize();
  ToImGuiColor(pendulum.bob2.GetFillColor(), bob2_color);
  ToImGuiColor(pendulum.bob2.trail.GetColor(), bob2_trail_color);
    
    ImGui::Begin("State Settings");
      ImGui::SliderFloat("Gravity", &gravity, 0.1f, 20.0f);
      ImGui::SliderFloat("Bob1.Length", &bob1_length, 0.1f, 5.0f);
      ImGui::SliderFloat("Bob1.Mass", &bob1_mass, 0.1f, 50.0f);
      ImGui::SliderFloat("Bob1.Damp", &bob1_damp, 0.99f, 1.0f);
      ImGui::SliderInt("Bob1.Trail.Size", &bob1_trail_size, 0, 500);
      ImGui::SliderFloat("Bob2.Length", &bob2_length, 0.1f, 5.0f);
      ImGui::SliderFloat("Bob2.Mass", &bob2_mass, 0.1f, 50.0f);
      ImGui::SliderFloat("Bob2.Damp", &bob2_damp, 0.99f, 1.0f);
      ImGui::SliderInt("Bob2.Trail.Size", &bob2_trail_size, 0, 500);
    ImGui::End();

    ImGui::Begin("View Settings");
      ImGui::ColorEdit4("Background.Color", background_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
      ImGui::ColorEdit4("Bob1.FillColor", bob1_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
      ImGui::ColorEdit4("Bob1.Trail.Color", bob1_trail_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
      ImGui::ColorEdit4("Bob2.FillColor", bob2_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
      ImGui::ColorEdit4("Bob2.Trail.Color", bob2_trail_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    pendulum.SetGravity(gravity);
    // First bob
    pendulum.bob1.SetLength(bob1_length);
    pendulum.bob1.SetMass(bob1_mass);
    pendulum.bob1.SetDamp(bob1_damp);
    pendulum.bob1.trail.SetSize(bob1_trail_size);
    pendulum.bob1.SetFillColor(ToSFMLColor(bob1_color));
    pendulum.bob1.trail.SetColor(ToSFMLColor(bob1_trail_color));
    // Second bob
    pendulum.bob2.SetLength(bob2_length);
    pendulum.bob2.SetMass(bob2_mass);
    pendulum.bob2.SetDamp(bob2_damp);
    pendulum.bob2.trail.SetSize(bob2_trail_size);
    pendulum.bob2.SetFillColor(ToSFMLColor(bob2_color));
    pendulum.bob2.trail.SetColor(ToSFMLColor(bob2_trail_color));

    window.clear(ToSFMLColor(background_color));
    window.draw(pendulum);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
