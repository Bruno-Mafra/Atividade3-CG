#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <imgui.h>
#include <vector>

#include "gamedata.hpp"
#include "abcg.hpp"
#include "camera.hpp"
#include "ground.hpp"
#include "paredes.hpp"
#include "boneca.hpp"
#include "soldado.hpp"
#include "tronco.hpp"
#include "folhas.hpp"
#include "listra.hpp"
#include "bonecos.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& ev) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
  GLuint m_program{};
  GLuint m_programTexture{};
  GLuint m_programTextureNormal{};

  int m_viewportWidth{};
  int m_viewportHeight{};

  Camera m_camera;
  float m_dollySpeed{0.0f};
  float m_truckSpeed{0.0f};
  float m_panSpeed{0.0f};


  GameData m_gameData;
  Ground m_ground;
  Paredes m_parede;
  Boneca m_boneca;
  Soldado m_soldado;
  Tronco m_tronco;
  Folhas m_folhas;
  Listra m_listra;
  Bonecos m_bonecos;

  ImFont* m_font;

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  abcg::ElapsedTimer m_segundosTimer;
  abcg::ElapsedTimer m_restartWaitTimer;

  void update();
  void textCentered(std::string text);
  void checkWinCondition();
  void checkEndGameCondition();
  void restart();
};

#endif