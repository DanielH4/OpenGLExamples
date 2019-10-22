#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
        
#include "Engine/Mesh.h"
#include "Engine/Shader.h"
#include "Engine/Texture.h"

#include <string>
#include <vector>

namespace Engine {
    class Model {
    public:
        Model(const std::string& path);
        void draw(const Shader& shader);

    private:
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        void loadModel(const std::string& path);
        void processNode(const aiNode* node, const aiScene* scene);
        Mesh processMesh(const aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(const aiMaterial* mat, const aiTextureType& type, const std::string& typeName);
    };
}