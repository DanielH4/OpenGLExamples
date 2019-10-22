#include "Engine/Model.h"
#include <iostream>

namespace Engine {

    Model::Model(const std::string& path) {
        loadModel(path);
    }

    void Model::loadModel(const std::string& path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if(!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        m_directory = path.substr(0, path.find_last_of('/')) + '/';

        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(const aiNode* node, const aiScene* scene) {

        //process meshes of the node
        for(unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back(processMesh(mesh, scene));
        }

        //repeat for each child node
        for(unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }

    }

    Mesh Model::processMesh(const aiMesh* mesh, const aiScene* scene) {

        //temporaries used to create our Mesh object
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        //process vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D pos = mesh->mVertices[i];
            aiVector3D norm = mesh->mNormals[i];
            
            glm::vec2 texCoords;
            if(mesh->mTextureCoords[0]) //if texture coords exist
                texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            else
                texCoords = glm::vec2(0.0f, 0.0f);
            
            aiVector3D tangent = mesh->mTangents[i];
            aiVector3D biTangent = mesh->mBitangents[i];

            //translate to our vertex format
            Vertex myVertex;
            myVertex.position = glm::vec3(pos.x, pos.y, pos.z);
            myVertex.normal = glm::vec3(norm.x, norm.y, norm.z);
            myVertex.texCoords = texCoords;
            myVertex.tangent = glm::vec3(tangent.x, tangent.y, tangent.z);
            myVertex.biTangent = glm::vec3(biTangent.x, biTangent.y, biTangent.z);
            vertices.push_back(myVertex);
        }

        //process indices by iterating through assimp's face objects
        for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        if(mesh->mMaterialIndex >= 0) {
            //process materials
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            //diffuse maps
            std::vector<Texture> maps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "tex_diff");
            textures.insert(textures.end(), maps.begin(), maps.end());

            //specular maps
            maps.clear();
            maps = loadMaterialTextures(material, aiTextureType_SPECULAR, "tex_spec");
            textures.insert(textures.end(), maps.begin(), maps.end());

            //normal maps
            maps.clear();
            maps = loadMaterialTextures(material, aiTextureType_HEIGHT, "tex_norm");
            textures.insert(textures.end(), maps.begin(), maps.end());

            //height maps
            maps.clear();
            maps = loadMaterialTextures(material, aiTextureType_AMBIENT, "tex_height");
            textures.insert(textures.end(), maps.begin(), maps.end());
        }

        return Mesh(vertices, indices, textures);
    }


    std::vector<Texture> Model::loadMaterialTextures(const aiMaterial* mat, const aiTextureType& type, const std::string& typeName) {
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {

            //load texture name
            aiString str;
            mat->GetTexture(type, i, &str);

            //create texture
            Texture texture(m_directory + str.C_Str());
            texture.setType(typeName);
            textures.push_back(texture);
        }

        return textures;
    }

    void Model::draw(const Shader& shader) {
        for(auto& mesh : m_meshes)
            mesh.draw(shader);
    }
}