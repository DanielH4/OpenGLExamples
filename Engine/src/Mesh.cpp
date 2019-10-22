#include "Engine/Mesh.h"

namespace Engine {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
    : m_vertices(vertices), m_indices(indices), m_textures(textures)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        //vertex positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
        glEnableVertexAttribArray(0);

        //vertex normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        //vertex texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);

        //vertex tangents
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
        glEnableVertexAttribArray(3);

        //vertex bitangents
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, biTangent));
        glEnableVertexAttribArray(4);

        glBindVertexArray(0);
    }

    void Mesh::draw(const Shader& shader) {
        unsigned int diffNum = 1;
        unsigned int specNum = 1;
        unsigned int normNum = 1;
        unsigned int heightNum = 1;

        //bind each texture of mesh to a target and uniform variable
        //ex. target:GL_TEXTURE0 uniform:tex_diff1
        for(unsigned int i = 0; i < m_textures.size(); i++) {

            glActiveTexture(GL_TEXTURE0 + i);   //specify texture unit

            std::string number;
            std::string type = m_textures[i].getType();
            if(type == "tex_diff")
                number = std::to_string(diffNum++);
            else if(type == "tex_spec")
                number = std::to_string(specNum++);
            else if(type == "tex_norm")
                number = std::to_string(normNum++);
            else if(type == "tex_height")
                number = std::to_string(heightNum++);
            
            //shader.setFloat({"material." + type + number}, i);      //set uniform to value i corresponding to a texture
            shader.setFloat({type + number}, i);
            glBindTexture(GL_TEXTURE_2D, m_textures[i].getID());    //bind id of texture[i] to target
        }

        //draw mesh
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

        //restore defaults
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

    const std::vector<Texture>& Mesh::getTextures() {
        return m_textures;
    }
}