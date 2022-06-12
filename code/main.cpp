#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "doublependulum.h"
#include "normalization.h"

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 600;

void LoadState(
  const std::string& file_name,
  DoublePendulum& pendulum,
  NormalizedColor& background_color)
{
  std::ifstream fin(file_name);
  if (!fin.is_open()) {
    std::cout << "Файл \"" << file_name << "\" не найдкн." << std::endl;
  } else {
    fin >> background_color.channels[0];
    fin >> background_color.channels[1];
    fin >> background_color.channels[2];
    fin >> background_color.channels[3];
    fin >> *pendulum.LinkGravity();
    fin >> pendulum.LinkRodColor()[0];  
    fin >> pendulum.LinkRodColor()[1];
    fin >> pendulum.LinkRodColor()[2];
    fin >> pendulum.LinkRodColor()[3];
    fin >> *pendulum.bob1.LinkLength();
    fin >> *pendulum.bob1.LinkMass();
    fin >> *pendulum.bob1.LinkDamp();
    fin >> pendulum.bob1.LinkColor()[0];
    fin >> pendulum.bob1.LinkColor()[1];
    fin >> pendulum.bob1.LinkColor()[2];
    fin >> pendulum.bob1.LinkColor()[3];
    fin >> *pendulum.bob1.trail.LinkSize();
    fin >> pendulum.bob1.trail.LinkColor()[0];
    fin >> pendulum.bob1.trail.LinkColor()[1];
    fin >> pendulum.bob1.trail.LinkColor()[2];
    fin >> pendulum.bob1.trail.LinkColor()[3];
    fin >> *pendulum.bob2.LinkLength();
    fin >> *pendulum.bob2.LinkMass();
    fin >> *pendulum.bob2.LinkDamp();
    fin >> pendulum.bob2.LinkColor()[0];
    fin >> pendulum.bob2.LinkColor()[1];
    fin >> pendulum.bob2.LinkColor()[2];
    fin >> pendulum.bob2.LinkColor()[3];
    fin >> *pendulum.bob2.trail.LinkSize();
    fin >> pendulum.bob2.trail.LinkColor()[0];
    fin >> pendulum.bob2.trail.LinkColor()[1];
    fin >> pendulum.bob2.trail.LinkColor()[2];
    fin >> pendulum.bob2.trail.LinkColor()[3];
  }
}

void SaveState(
  const std::string& file_name,
  DoublePendulum& pendulum,
  const NormalizedColor& background_color)
{
  std::ofstream fout(file_name);
  if (!fout.is_open()) {
    std::cout << "Файл \"" << file_name << "\" не найден." << std::endl;
  } else {
    fout << background_color.channels[0] << std::endl;
    fout << background_color.channels[1] << std::endl;
    fout << background_color.channels[2] << std::endl;
    fout << background_color.channels[3] << std::endl;
    fout << *pendulum.LinkGravity() << std::endl;
    fout << pendulum.LinkRodColor()[0] << std::endl;
    fout << pendulum.LinkRodColor()[1] << std::endl;
    fout << pendulum.LinkRodColor()[2] << std::endl;
    fout << pendulum.LinkRodColor()[3] << std::endl;
    fout << *pendulum.bob1.LinkLength() << std::endl;
    fout << *pendulum.bob1.LinkMass() << std::endl;
    fout << *pendulum.bob1.LinkDamp() << std::endl;
    fout << pendulum.bob1.LinkColor()[0] << std::endl;
    fout << pendulum.bob1.LinkColor()[1] << std::endl;
    fout << pendulum.bob1.LinkColor()[2] << std::endl;
    fout << pendulum.bob1.LinkColor()[3] << std::endl;
    fout << *pendulum.bob1.trail.LinkSize() << std::endl;
    fout << pendulum.bob1.trail.LinkColor()[0] << std::endl;
    fout << pendulum.bob1.trail.LinkColor()[1] << std::endl;
    fout << pendulum.bob1.trail.LinkColor()[2] << std::endl;
    fout << pendulum.bob1.trail.LinkColor()[3] << std::endl;
    fout << *pendulum.bob2.LinkLength() << std::endl;
    fout << *pendulum.bob2.LinkMass() << std::endl;
    fout << *pendulum.bob2.LinkDamp() << std::endl;
    fout << pendulum.bob2.LinkColor()[0] << std::endl;
    fout << pendulum.bob2.LinkColor()[1] << std::endl;
    fout << pendulum.bob2.LinkColor()[2] << std::endl;
    fout << pendulum.bob2.LinkColor()[3] << std::endl;
    fout << *pendulum.bob2.trail.LinkSize() << std::endl;
    fout << pendulum.bob2.trail.LinkColor()[0] << std::endl;
    fout << pendulum.bob2.trail.LinkColor()[1] << std::endl;
    fout << pendulum.bob2.trail.LinkColor()[2] << std::endl;
    fout << pendulum.bob2.trail.LinkColor()[3] << std::endl;
  }
}

int main() {
  try {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double pendulum");
    window.setFramerateLimit(FPS);
    window.setVerticalSyncEnabled(true);
    if (!ImGui::SFML::Init(window)) { return 0; }
    sf::Clock deltaClock;
    DoublePendulum pendulum(1, 0.8, 10, 4, 90*PI/180, 90*PI/180,
      sf::Vector2f(WIDTH/2 + 150, HEIGHT/2 - 40));
    NormalizedColor background_color(sf::Color::White);
    
    // Восстановление состояния предыдущей сессии
    LoadState("state.txt", pendulum, background_color);

    while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window, event);

        if (event.type == sf::Event::KeyPressed) {
          switch(event.key.code) {
            case sf::Keyboard::Escape:
              window.close();
              break;
            case sf::Keyboard::Space:
              pendulum.ChangeState();
              break;
            default:
              ; // nothing
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

      ImGui::Begin("Field.Rod");
        ImGui::ColorEdit4("Color", pendulum.LinkRodColor(),
          ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel);
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
    
    // Сохранение состояния текущей сессии
    SaveState("state.txt", pendulum, background_color);

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}