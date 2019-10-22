#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {
	class Shader {
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		void use() const;
		void setBool(const std::string name, const bool value) const;
		void setInt(const std::string name, const int value) const;
		void setFloat(const std::string name, const float value) const;
		void setVec3(const std::string name, const glm::vec3 &vec) const;
		void setMat4(const std::string name, const glm::mat4 &mat) const;

	private:
		const unsigned int m_ID;
	};
}