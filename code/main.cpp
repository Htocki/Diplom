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

  float* background_color = new float[4];
  ToImGuiColor(sf::Color::White, background_color);
  // First bob
  float* bob1_color = new float[4];
  ToImGuiColor(pendulum.bob1.GetFillColor(), bob1_color);
  float* bob1_trail_color = new float[4];
  ToImGuiColor(pendulum.bob1.trail.GetColor(), bob1_trail_color);
  // Second bob
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

  // First bob
  ToImGuiColor(pendulum.bob1.GetFillColor(), bob1_color);
  ToImGuiColor(pendulum.bob1.trail.GetColor(), bob1_trail_color);
  // Second bob
  ToImGuiColor(pendulum.bob2.GetFillColor(), bob2_color);
  ToImGuiColor(pendulum.bob2.trail.GetColor(), bob2_trail_color);
    
    ImGui::Begin("Field");
      ImGui::ColorEdit4("Background.Color", background_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum");
      ImGui::SliderFloat("Gravity", pendulum.LinkGravity(), 0.1f, 20.0f);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob1");
      ImGui::SliderFloat("Length", pendulum.bob1.LinkLength(), 0.1f, 5.0f);
      ImGui::SliderFloat("Mass", pendulum.bob1.LinkMass(), 0.1f, 50.0f);
      ImGui::SliderFloat("Damp", pendulum.bob1.LinkDamp(), 0.99f, 1.0f);
      ImGui::ColorEdit4("Color", bob1_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob1.Trail");
      ImGui::SliderInt("Size", pendulum.bob1.trail.LinkSize(), 0, 500);
      ImGui::ColorEdit4("Color", bob1_trail_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob2");
      ImGui::SliderFloat("Length", pendulum.bob2.LinkLength(), 0.1f, 5.0f);
      ImGui::SliderFloat("Mass", pendulum.bob2.LinkMass(), 0.1f, 50.0f);
      ImGui::SliderFloat("Damp", pendulum.bob2.LinkDamp(), 0.99f, 1.0f);
      ImGui::ColorEdit4("Color", bob2_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob2.Trail");
      ImGui::SliderInt("Size", pendulum.bob2.trail.LinkSize(), 0, 500);
      ImGui::ColorEdit4("Color", bob2_trail_color,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    // First bob
    pendulum.bob1.SetFillColor(ToSFMLColor(bob1_color));
    pendulum.bob1.trail.SetColor(ToSFMLColor(bob1_trail_color));
    // Second bob
    pendulum.bob2.SetFillColor(ToSFMLColor(bob2_color));
    pendulum.bob2.trail.SetColor(ToSFMLColor(bob2_trail_color));

    window.clear(ToSFMLColor(background_color));
    window.draw(pendulum);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
