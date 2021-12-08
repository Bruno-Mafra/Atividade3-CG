#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

void Camera::init(GLuint m_program, glm::mat4 m_modelMatrix) {
  // Get location of uniform variables
  const GLint viewMatrixLoc{abcg::glGetUniformLocation(m_program, "viewMatrix")};
  const GLint projMatrixLoc{abcg::glGetUniformLocation(m_program, "projMatrix")};
  const GLint modelMatrixLoc{abcg::glGetUniformLocation(m_program, "modelMatrix")};
  const GLint normalMatrixLoc{abcg::glGetUniformLocation(m_program, "normalMatrix")};
  const GLint lightDirLoc{abcg::glGetUniformLocation(m_program, "lightDirWorldSpace")};
  const GLint IaLoc{abcg::glGetUniformLocation(m_program, "Ia")};
  const GLint IdLoc{abcg::glGetUniformLocation(m_program, "Id")};
  const GLint IsLoc{abcg::glGetUniformLocation(m_program, "Is")};

  // Set uniform variables used by every scene object
  abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);

  abcg::glUniform4fv(IaLoc, 1, &m_Ia.x);
  abcg::glUniform4fv(IdLoc, 1, &m_Id.x);
  abcg::glUniform4fv(IsLoc, 1, &m_Is.x);

  glm::vec4 m_lightDir{-3.0f, -4.0f, -3.0f, 0.0f};
  glm::mat4 m_rotation{1.0f};
  const auto lightDirRotated{m_rotation * m_lightDir};
  abcg::glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);

  // Set uniform variables of the current object
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

  const auto modelViewMatrix{glm::mat3(m_viewMatrix * m_modelMatrix)};
  glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  abcg::glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);
}

void Camera::reinitModel(GLuint m_program, glm::mat4 m_modelMatrix){
  const GLint modelMatrixLoc{abcg::glGetUniformLocation(m_program, "modelMatrix")};
  const GLint normalMatrixLoc{abcg::glGetUniformLocation(m_program, "normalMatrix")};

  // Set uniform variables of the current object
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

  const auto modelViewMatrix{glm::mat3(m_viewMatrix * m_modelMatrix)};
  glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  abcg::glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);
}

void Camera::computeProjectionMatrix(int width, int height) {
  m_projMatrix = glm::mat4(1.0f);
  const auto aspect{static_cast<float>(width) / static_cast<float>(height)};
  m_projMatrix = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);
}

void Camera::computeViewMatrix() {
  m_viewMatrix = glm::lookAt(m_eye, m_at, m_up);
}

void Camera::dolly(float speed, const GameData &gameData) {
  if(gameData.m_state == State::Playing || gameData.m_state == State::Win) {
    // Compute forward vector (view direction)
    const glm::vec3 forward{glm::normalize(m_at - m_eye)};

    glm::vec3 old_m_at = m_at;

    // Move eye and center forward (speed > 0) or backward (speed < 0)
    m_eye += forward * speed;
    m_at += forward * speed;

    if(m_eye.x > 2.5f) { // colisão com as paredes
      m_eye.x = 2.5f;
      m_at = old_m_at;
    }

    if( m_eye.x < -2.5f) {
      m_eye.x = -2.5f;
      m_at = old_m_at;
    }

    if(m_eye.z > 4.5f) {
      m_eye.z = 4.5f;
      m_at = old_m_at;
    }

    if(m_eye.z < -4.5f) {
      m_eye.z = -4.5f;
      m_at = old_m_at;
    }

    computeViewMatrix();
  }
}

void Camera::truck(float speed, const GameData &gameData) {
  if(gameData.m_state == State::Playing || gameData.m_state == State::Win) {
    // Compute forward vector (view direction)
    const glm::vec3 forward{glm::normalize(m_at - m_eye)};
    // Compute vector to the left
    const glm::vec3 left{glm::cross(m_up, forward)};

    glm::vec3 old_m_at = m_at;

    // Move eye and center to the left (speed < 0) or to the right (speed > 0)
    m_at -= left * speed;
    m_eye -= left * speed;

    if(m_eye.x > 2.5f) { // colisão com as paredes
      m_eye.x = 2.5f;
      m_at = old_m_at;
    }

    if( m_eye.x < -2.5f) {
      m_eye.x = -2.5f;
      m_at = old_m_at;
    }

    if(m_eye.z > 4.5f) {
      m_eye.z = 4.5f;
      m_at = old_m_at;
    }

    if(m_eye.z < -4.5f) {
      m_eye.z = -4.5f;
      m_at = old_m_at;
    }

    computeViewMatrix();
  }
}

void Camera::pan(float speed) {
  glm::mat4 transform{glm::mat4(1.0f)};

  // Rotate camera around its local y axis
  transform = glm::translate(transform, m_eye);
  transform = glm::rotate(transform, -speed, m_up);
  transform = glm::translate(transform, -m_eye);

  m_at = transform * glm::vec4(m_at, 1.0f);

  computeViewMatrix();
}
