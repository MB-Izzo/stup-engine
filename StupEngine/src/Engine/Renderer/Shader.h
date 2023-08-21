#pragma once

#include "stuppch.h"
#include <glad/glad.h>

namespace Stup {
class Shader {
  public:
    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);

    void Use() const { glUseProgram(ID); }

    void SetBool(const std::string &name, bool value) const;

    void SetInt(const std::string &name, int value) const;

    void SetFloat(const std::string &name, float value) const;

  private:
    int GetUniformLocation(const std::string &name) const;
};

} // namespace Stup
