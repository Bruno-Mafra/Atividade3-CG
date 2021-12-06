#ifndef BONECA_HPP_
#define BONECA_HPP_

#include <vector>
#include <random>

#include "abcg.hpp"
#include "camera.hpp"
#include "gamedata.hpp"

struct Vertex3 {
  glm::vec3 position{};
  glm::vec3 normal{};
  glm::vec2 texCoord{};

  bool operator==(const Vertex3& other) const noexcept {
    static const auto epsilon{std::numeric_limits<float>::epsilon()};
    return glm::all(glm::epsilonEqual(position, other.position, epsilon)) &&
           glm::all(glm::epsilonEqual(normal, other.normal, epsilon)) &&
           glm::all(glm::epsilonEqual(texCoord, other.texCoord, epsilon));
  }
};

class OpenGLWindow;

class Boneca {
 public:
  void loadDiffuseTexture(std::string_view path);
  void createBuffers(GLuint program);
  void loadObj(std::string_view path, bool standardize = true);
  void render(Camera m_camera);
  void update(const GameData &gameData, float deltaTime);
  void terminateGL();

 private:
  friend OpenGLWindow;

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};
  GLuint m_diffuseTexture{};

  int m_mappingMode = 3;

  float m_angle = glm::radians(0.0f);

  abcg::ElapsedTimer m_segundosTimer;
  abcg::ElapsedTimer m_deFrenteTimer;

  bool m_hasNormals{false};
  bool m_hasTexCoords{false};

  bool changeTimer = true;
  bool girarPraTras = false;
  bool girarPraFrente = false;
  bool greenLight = false;
  bool timerFoiResetado = false;

  // Light and material properties
  glm::vec4 m_Ka;
  glm::vec4 m_Kd;
  glm::vec4 m_Ks;
  float m_shininess{25.0f};

  int timer;

  std::vector<Vertex3> m_vertices;
  std::vector<GLuint> m_indices;

  void standardize();
  void computeNormals();
};

#endif