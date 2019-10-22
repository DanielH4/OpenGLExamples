#include <glm/glm.hpp>

namespace Engine {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 biTangent;
    };
}