#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "doublependulum.h"

const unsigned int WIDTH = 1000;
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
    ImGui::SFML::Update(window, deltaClock.restart());
    
    ImGui::Begin("Controller");
      ImGui::Text("Pendulum");
      ImGui::SliderFloat("Gravity", pendulum.Gravity(), 0.1f, 20.0f);
      ImGui::Text("Bob1");
      ImGui::SliderFloat("Length", pendulum.Bob1Length(), 0.1f, 5.0f);
      ImGui::SliderFloat("Mass", pendulum.Bob1Mass(), 0.1f, 50.0f);
      ImGui::SliderFloat("Damp", pendulum.Bob1Damp(), 0.99f, 1.0f);
      ImGui::SliderInt("Trail size", pendulum.Bob1TrailSize(), 0, 500);
      ImGui::Text("Bob2");
      ImGui::SliderFloat("Length", pendulum.Bob2Length(), 0.1f, 5.0f);
      ImGui::SliderFloat("Mass", pendulum.Bob2Mass(), 0.1f, 50.0f);
      ImGui::SliderFloat("Damp", pendulum.Bob2Damp(), 0.99f, 1.0f);
      ImGui::SliderInt("Trailsize", pendulum.Bob2TrailSize(), 0, 500);
    ImGui::End();

    window.clear(sf::Color::White);
    window.draw(pendulum);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
