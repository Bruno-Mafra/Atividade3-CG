#include "openglwindow.hpp"

#include <fmt/core.h>
#include <tiny_obj_loader.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

std::string restarting ="RESTARTING IN: ";
std::string tempo = " SECONDS";
int segundos = 5;

void OpenGLWindow::handleEvent(SDL_Event& ev) {
  if (ev.type == SDL_KEYDOWN) {
    if (ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) {
      m_gameData.m_input.set(static_cast<size_t>(Input::Up));
      m_dollySpeed = 1.0f;
    }
    if (ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) {
      m_gameData.m_input.set(static_cast<size_t>(Input::Down));
      m_dollySpeed = -1.0f;
      }

    if (ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a)
      m_panSpeed = -1.0f;
    if (ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) 
      m_panSpeed = 1.0f;

    if (ev.key.keysym.sym == SDLK_q) {
      m_gameData.m_input.set(static_cast<size_t>(Input::Left));
      m_truckSpeed = -1.0f;
    }
    if (ev.key.keysym.sym == SDLK_e) {
      m_gameData.m_input.set(static_cast<size_t>(Input::Right));
      m_truckSpeed = 1.0f;
    }
  }
  if (ev.type == SDL_KEYUP) {
    if ((ev.key.keysym.sym == SDLK_UP || ev.key.keysym.sym == SDLK_w) && m_dollySpeed > 0) {
      m_gameData.m_input.reset(static_cast<size_t>(Input::Up));
      m_dollySpeed = 0.0f;
    }
    if ((ev.key.keysym.sym == SDLK_DOWN || ev.key.keysym.sym == SDLK_s) && m_dollySpeed < 0) {
      m_gameData.m_input.reset(static_cast<size_t>(Input::Down));
      m_dollySpeed = 0.0f;
    }

    if ((ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_a) && m_panSpeed < 0)
      m_panSpeed = 0.0f;  
    if ((ev.key.keysym.sym == SDLK_RIGHT || ev.key.keysym.sym == SDLK_d) && m_panSpeed > 0)
      m_panSpeed = 0.0f;

    if (ev.key.keysym.sym == SDLK_q && m_truckSpeed < 0) {
      m_gameData.m_input.reset(static_cast<size_t>(Input::Left));
      m_truckSpeed = 0.0f;
    }
    if (ev.key.keysym.sym == SDLK_e && m_truckSpeed > 0) {
      m_gameData.m_input.reset(static_cast<size_t>(Input::Right));
      m_truckSpeed = 0.0f;
    }
  }
}

void OpenGLWindow::initializeGL() {
  // Load a new font
  ImGuiIO &io{ImGui::GetIO()};
  auto filename{getAssetsPath() + "Inconsolata-Medium.ttf"};
  m_font = io.Fonts->AddFontFromFileTTF(filename.c_str(), 50.0f);
  if (m_font == nullptr) {
    throw abcg::Exception{abcg::Exception::Runtime("Cannot load font file")};
  }

  abcg::glClearColor(0.486f, 0.796f, 0.992, 1);

  // Enable depth buffering
  abcg::glEnable(GL_DEPTH_TEST);

  // Create program
  m_programTextureNormal = createProgramFromFile(getAssetsPath() + "shaders/" + "normalmapping.vert",
                                    getAssetsPath() + "shaders/" + "normalmapping.frag");

  m_programTexture = createProgramFromFile(getAssetsPath() + "shaders/" + "texture.vert",
                                    getAssetsPath() + "shaders/" + "texture.frag");

  m_program = createProgramFromFile(getAssetsPath() + "shaders/" + "lookat.vert",
                                    getAssetsPath() + "shaders/" + "lookat.frag");

  // Load model
  m_listra.initializeGL(m_program);

  m_ground.loadObj(getAssetsPath() + "ground.obj", true);
  m_ground.createBuffers(m_programTextureNormal);
 
  m_parede.loadObj(getAssetsPath() + "wall.obj", true);
  m_parede.createBuffers(m_programTextureNormal);

  m_boneca.loadObj(getAssetsPath() + "doll.obj", false);
  m_boneca.createBuffers(m_programTexture);

  m_soldado.loadObj(getAssetsPath() + "PinkSoldier.obj", false);
  m_soldado.createBuffers(m_programTextureNormal);

  m_tronco.loadObj(getAssetsPath() + "tronco.obj", false);
  m_tronco.createBuffers(m_programTextureNormal);

  m_folhas.loadObj(getAssetsPath() + "folhas.obj", false);
  m_folhas.createBuffers(m_programTextureNormal);

  m_bonecos.loadObj(getAssetsPath() + "among us.obj", true);
  m_bonecos.createBuffers(m_programTextureNormal);

  resizeGL(getWindowSettings().width, getWindowSettings().height);
}

void OpenGLWindow::paintGL() {
  update();

  // Clear color buffer and depth buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  // Draw ground
  m_ground.render(m_camera);
  m_parede.render(m_camera);
  m_boneca.render(m_camera);
  m_soldado.render(m_camera);
  m_tronco.render(m_camera);
  m_folhas.render(m_camera);
  m_bonecos.render(m_camera);
  m_listra.paintGL(m_camera);
}

void OpenGLWindow::paintUI() { 
  abcg::OpenGLWindow::paintUI();
  {
    const auto size{ImVec2(m_viewportWidth, 400)};
    const auto position{ImVec2((m_viewportWidth - size.x) / 2.0f,
                               (m_viewportHeight - size.y) / 2.0f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
                           ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoInputs};

    if (m_gameData.m_state != State::Playing) { 
      if(m_segundosTimer.elapsed() > 1000.0 /1000) { // Timer de recomeço 
        segundos -= 1;
        m_segundosTimer.restart();
      }
    }

    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
    ImGui::PushFont(m_font);
    if(m_gameData.m_state == State::Playing) {
      if(m_boneca.greenLight) textCentered("GREEN LIGHT!");
    }
    ImGui::PopFont();
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
    ImGui::PushFont(m_font);
    if(m_gameData.m_state == State::Playing) {
      if(m_boneca.greenLight == false) textCentered("RED LIGHT!"); 
    }
    ImGui::PopFont();
    ImGui::PopStyleColor();
    ImGui::End();

    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);
    if(m_gameData.m_state == State::Win) {
      textCentered(" ");
      textCentered("*CONGRATULATIONS*");
      textCentered(" ");
      textCentered("YOU WIN!");
      textCentered(" ");
      textCentered((restarting + std::to_string(segundos).c_str() + tempo)); 
    }
    ImGui::PopFont();
    ImGui::End();

    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);
    if(m_gameData.m_state == State::GameOver) {
      textCentered(" ");
      textCentered("*GAME OVER*");
      textCentered(" ");
      textCentered("YOU LOST! :("); 
      textCentered(" ");
      textCentered((restarting + std::to_string(segundos).c_str() + tempo));  
    }
    ImGui::PopFont();
    ImGui::End();

    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);
    if(m_gameData.m_state == State::Start) {
      textCentered(" ");
      textCentered(" ");
      textCentered("HELLO!");
      textCentered(" "); 
      textCentered("*STARTING SOON*"); 
    }
    ImGui::PopFont();
    ImGui::End();
  }
 }

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_camera.computeProjectionMatrix(width, height);
}

void OpenGLWindow::terminateGL() {
  m_listra.terminateGL();
  m_ground.terminateGL();
  m_parede.terminateGL();
  m_boneca.terminateGL();
  m_soldado.terminateGL();
  m_tronco.terminateGL();
  m_folhas.terminateGL();
  m_bonecos.terminateGL();
  abcg::glDeleteProgram(m_program);
  abcg::glDeleteProgram(m_programTextureNormal);
  abcg::glDeleteProgram(m_programTexture);
}

void OpenGLWindow::update() {
  const float deltaTime{static_cast<float>(getDeltaTime())};

  m_boneca.update(m_gameData, deltaTime);

  // Update LookAt camera
  m_camera.dolly(m_dollySpeed * deltaTime, m_gameData);
  m_camera.truck(m_truckSpeed * deltaTime, m_gameData);
  m_camera.pan(m_panSpeed * deltaTime);

  if(m_gameData.m_state != State::Playing && m_restartWaitTimer.elapsed() > 5) {
    restart();
    return;
  }

  if(m_gameData.m_state == State::Playing) {
    checkWinCondition();
    checkEndGameCondition();
  }
}

void OpenGLWindow::textCentered(std::string text) { // centraliza texto do ImGui
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}

void OpenGLWindow::checkWinCondition() { // Verifica se passou a linha de chegada
    if(m_camera.m_eye.z <= -2.0f) {
      m_gameData.m_state = State:: Win;
      m_restartWaitTimer.restart();
    }
}

void OpenGLWindow::checkEndGameCondition() { // Verifica se algum botao é clickado quando não pode
  if((m_gameData.m_input[static_cast<size_t>(Input::Up)] || m_gameData.m_input[static_cast<size_t>(Input::Down)] ||
      m_gameData.m_input[static_cast<size_t>(Input::Left)] || m_gameData.m_input[static_cast<size_t>(Input::Right)]) 
      && m_boneca.greenLight == false) {
    m_camera.m_eye.y = 0.1f;
    m_gameData.m_state = State:: GameOver;
    m_restartWaitTimer.restart();
  }
}

void OpenGLWindow::restart() { // Redefine variaveis pra recomeçar
  segundos = 5;
  m_boneca.m_angle = glm::radians(0.0f);
  m_boneca.changeTimer = true;
  m_boneca.girarPraTras = false;
  m_boneca.girarPraFrente = false;
  m_boneca.greenLight = false;
  m_boneca.timerFoiResetado = false;
  m_camera.m_eye = {-0.3f, 0.5f, 4.0f};
  m_camera.m_at = {-0.3f, 0.5f, 0.0f};
  m_gameData.m_state = State::Playing;
}