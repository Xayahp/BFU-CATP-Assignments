#ifndef ASSIGNMENT_FRAMEWORK_SHADER_H
#define ASSIGNMENT_FRAMEWORK_SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Eigen/Eigen"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geometryPath = "");

    void use() const;

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, const Eigen::Vector2f &value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, const Eigen::Vector3f &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, const Eigen::Vector4f &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat2(const std::string &name, const Eigen::Matrix2f &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat3(const std::string &name, const Eigen::Matrix3f &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

    void setMat4(const std::string &name, const Eigen::Matrix4f &mat) const;

private:
    static void checkCompileErrors(GLuint shader, const std::string &type);
};

#endif //OPENGLFRAMEWORK_SHADER_HPP
