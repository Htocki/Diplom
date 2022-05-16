#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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

  float gravity = pendulum.GetGravity();
  float bob1_length = pendulum.GetBob1Length();
  float bob1_mass = pendulum.GetBob1Mass();
  float bob1_damp = pendulum.GetBob1Damp();
  int bob1_trailsize = pendulum.GetBob1TrailSize();
  float bob2_length = pendulum.GetBob2Length();
  float bob2_mass = pendulum.GetBob2Mass();
  float bob2_damp = pendulum.GetBob2Damp();
  int bob2_trailsize = pendulum.GetBob2TrailSize();

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
    
    ImGui::Begin("Settings");
      ImGui::SliderFloat("Gravity", &gravity, 0.1f, 20.0f);
      ImGui::SliderFloat("Bob1.Length", &bob1_length, 0.1f, 5.0f);
      ImGui::SliderFloat("Bob1.Mass", &bob1_mass, 0.1f, 50.0f);
      ImGui::SliderFloat("Bob1.Damp", &bob1_damp, 0.99f, 1.0f);
      ImGui::SliderInt("Bob1.Trail.Size", &bob1_trailsize, 0, 500);
      ImGui::SliderFloat("Bob2.Length", &bob2_length, 0.1f, 5.0f);
      ImGui::SliderFloat("Bob2.Mass", &bob2_mass, 0.1f, 50.0f);
      ImGui::SliderFloat("Bob2.Damp", &bob2_damp, 0.99f, 1.0f);
      ImGui::SliderInt("Bob2.Trail.Size", &bob2_trailsize, 0, 500);
    ImGui::End();

    pendulum.SetGravity(gravity);
    pendulum.SetBob1Length(bob1_length);
    pendulum.SetBob1Mass(bob1_mass);
    pendulum.SetBob1Damp(bob1_damp);
    pendulum.SetBob1TrailSize(bob1_trailsize);
    pendulum.SetBob2Length(bob2_length);
    pendulum.SetBob2Mass(bob2_mass);
    pendulum.SetBob2Damp(bob2_damp);
    pendulum.SetBob2TrailSize(bob2_trailsize);

    window.clear(sf::Color::White);
    window.draw(pendulum);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
