#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Vertex.h"
#include "Engine/Texture.h"
#include "Engine/Shader.h"

#include <vector>
#include <string>

namespace Engine {
    class Mesh {
        public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
        void draw(const Shader& shader);
        const std::vector<Texture>& getTextures();

        private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<Texture> m_textures;
        unsigned int m_VAO, m_VBO, m_EBO;
    };
}