#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "abcg.hpp"
#include "gamedata.hpp"

class OpenGLWindow;

class Camera {
 public:
  void init(GLuint m_program, glm::mat4 m_modelMatrix);
  void reinitModel(GLuint m_program, glm::mat4 m_modelMatrix);
  void computeViewMatrix();
  void computeProjectionMatrix(int width, int height);

  void dolly(float speed, const GameData &gameData);
  void truck(float speed, const GameData &gameData);
  void pan(float speed);

 private:
  friend OpenGLWindow;

  glm::vec3 m_eye{glm::vec3(-0.3f, 0.5f, 4.0f)};  // Camera position -- era 2.5 no z
  glm::vec3 m_at{glm::vec3(-0.3f, 0.5f, 0.0f)};   // Look-at point 
  glm::vec3 m_up{glm::vec3(0.0f, 1.0f, 0.0f)};   // "up" direction

  // Light properties
  glm::vec4 m_Ia{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Id{1.0f, 1.0f, 1.0f, 1.0f};
  glm::vec4 m_Is{1.0f, 1.0f, 1.0f, 1.0f};

  // Matrix to change from world space to camera soace
  glm::mat4 m_viewMatrix;

  // Matrix to change from camera space to clip space
  glm::mat4 m_projMatrix;
};

#endif