#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "doublependulum.h"
#include "normalization.h"

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 600;

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double pendulum");
  window.setFramerateLimit(FPS);
  window.setVerticalSyncEnabled(true);
  ImGui::SFML::Init(window);
  sf::Clock deltaClock;

  DoublePendulum pendulum(1, 0.8, 10, 4, 90*PI/180, 90*PI/180,
    sf::Vector2f(WIDTH/2 + 150, HEIGHT/2 - 40));

  NormalizedColor background_color(sf::Color::White);

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
    
    ImGui::Begin("Field");
      ImGui::ColorEdit4("Background.Color", background_color.channels,
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum");
      ImGui::SliderFloat("Gravity", pendulum.LinkGravity(), 0.1f, 20.0f);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob1");
      ImGui::SliderFloat("Length", pendulum.bob1.LinkLength(), 0.1f, 5.0f);
      ImGui::SliderFloat("Mass", pendulum.bob1.LinkMass(), 0.1f, 50.0f);
      ImGui::SliderFloat("Damp", pendulum.bob1.LinkDamp(), 0.99f, 1.0f);
      ImGui::ColorEdit4("Color", pendulum.bob1.LinkColor(),
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob1.Trail");
      ImGui::SliderInt("Size", pendulum.bob1.trail.LinkSize(), 0, 500);
      ImGui::ColorEdit4("Color", pendulum.bob1.trail.LinkColor(),
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob2");
      ImGui::SliderFloat("Length", pendulum.bob2.LinkLength(), 0.1f, 5.0f);
      ImGui::SliderFloat("Mass", pendulum.bob2.LinkMass(), 0.1f, 50.0f);
      ImGui::SliderFloat("Damp", pendulum.bob2.LinkDamp(), 0.99f, 1.0f);
      ImGui::ColorEdit4("Color", pendulum.bob2.LinkColor(),
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    ImGui::Begin("Field.Pendulum.Bob2.Trail");
      ImGui::SliderInt("Size", pendulum.bob2.trail.LinkSize(), 0, 500);
      ImGui::ColorEdit4("Color", pendulum.bob2.trail.LinkColor(),
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
    ImGui::End();

    window.clear(background_color.GetAsSFML());
    window.draw(pendulum);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
