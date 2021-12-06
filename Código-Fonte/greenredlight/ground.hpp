#ifndef GROUND_HPP_
#define GROUND_HPP_

#include <vector>

#include "abcg.hpp"
#include "camera.hpp"

struct Vertex {
  glm::vec3 position{};
  glm::vec3 normal{};
  glm::vec2 texCoord{};
  glm::vec4 tangent{};

  bool operator==(const Vertex& other) const noexcept {
    static const auto epsilon{std::numeric_limits<float>::epsilon()};
    return glm::all(glm::epsilonEqual(position, other.position, epsilon)) &&
           glm::all(glm::epsilonEqual(normal, other.normal, epsilon)) &&
           glm::all(glm::epsilonEqual(texCoord, other.texCoord, epsilon));
  }
};

class Ground {
 public:
  void loadDiffuseTexture(std::string_view path);
  void loadNormalTexture(std::string_view path);
  void createBuffers(GLuint program);
  void loadObj(std::string_view path, bool standardize = true);
  void render(Camera m_camera);
  void terminateGL();

 private:
  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};
  GLuint m_program{};
  GLuint m_diffuseTexture{};
  GLuint m_normalTexture{};

  int m_mappingMode = 3;

  bool m_hasNormals{false};
  bool m_hasTexCoords{false};

  // material properties

  glm::vec4 m_Ka;
  glm::vec4 m_Kd;
  glm::vec4 m_Ks;
  float m_shininess{25.0f};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  void standardize();
  void computeNormals();
  void computeTangents();
};

#endif