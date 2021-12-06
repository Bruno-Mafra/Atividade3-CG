#include "listra.hpp"

#include <cppitertools/itertools.hpp>

void Listra::initializeGL(GLuint program) {
  m_program = program;

  // Delete previous buffers
  abcg::glDeleteBuffers(1, &m_VBO);

  // Line on the xz plane
  std::array vertices{glm::vec3(-4.0f, 0.005f, -3.15f), 
                      glm::vec3(-4.0f, 0.005f, -3.0f),
                      glm::vec3( 3.0f, 0.005f, -3.15f),
                      glm::vec3( 3.0f, 0.005f, -3.0f)};

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Create VAO and bind vertex attributes
  abcg::glGenVertexArrays(1, &m_VAO);
  abcg::glBindVertexArray(m_VAO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  const GLint posAttrib{abcg::glGetAttribLocation(program, "inPosition")};
  abcg::glEnableVertexAttribArray(posAttrib);
  abcg::glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);
  abcg::glBindVertexArray(0);

  // Save location of uniform variables
  m_modelMatrixLoc = abcg::glGetUniformLocation(program, "modelMatrix");
  m_colorLoc = abcg::glGetUniformLocation(program, "color");
}

void Listra::paintGL(Camera m_camera) {
  glUseProgram(m_program);
  abcg::glBindVertexArray(m_VAO);

  // Set model matrix
  glm::mat4 model{1.0f};
  model = glm::translate(model, glm::vec3(1, 0.0f, 1));
  abcg::glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &model[0][0]);

  m_camera.init(m_program, model);

  // Set color (checkerboard pattern)
  abcg::glUniform4f(m_colorLoc, 1, 1, 1, 1.0f);
  abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  abcg::glBindVertexArray(0);
  glUseProgram(0);
}

void Listra::terminateGL() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}