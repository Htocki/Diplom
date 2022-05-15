#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "doublependulum.h"

const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;

int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double pendulum");
  window.setFramerateLimit(FPS);
  ImGui::SFML::Init(window);
  sf::Clock deltaClock;

  DoublePendulum pendulum(1, 0.8, 10, 4, 90*PI/180, 90*PI/180);
  pendulum.SetupRenderObjects(WIDTH, HEIGHT);

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
    pendulum.Render();

    ImGui::SFML::Update(window, deltaClock.restart());
    ImGui::Begin("Controller");
      ImGui::SliderFloat("Gravity", &GRAVITY, 0.0f, 20.0f);
      ImGui::SliderFloat("Damp1", &DAMP1, 0.0f, 1.0f);
      ImGui::SliderFloat("Damp2", &DAMP2, 0.0f, 1.0f);
      ImGui::SliderInt("Trailsize", &TRAILSIZE, 0, 500);
    ImGui::End();

    window.clear(sf::Color::White);
    window.draw(pendulum);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
