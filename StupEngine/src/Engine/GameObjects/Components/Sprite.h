#pragma once

#include "Engine/GameObjects/Components/Component.h"
#include "Engine/GameObjects/GameObject.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"
#include "stuppch.h"
#include <glm/glm.hpp>

namespace Stup {

class Sprite : public Component {
  public:
    Sprite(const std::string &imagePath, uint32_t width, uint32_t height,
           const Transform &transform);
    ~Sprite();
    virtual void Update(float dt) override;

  public:
    void SetScale(const glm::vec2 &scale) { m_scale = scale; }
    void SetRotation(float angle) { m_angle = angle; }

    const glm::vec2 &GetScale() const { return m_scale; }
    const Shader& GetShader() { return *m_shader; }
    const Texture& GetTexture() { return *m_texture; }

    const Transform &GetTransform() { return m_transform; }

    uint32_t GetWidth() { return m_width; }
    uint32_t GetHeight() { return m_height; }
    float GetAngle() { return m_angle; }

  private:
    std::unique_ptr<Texture> m_texture;
    std::unique_ptr<Shader> m_shader;

    const Transform &m_transform;

    uint32_t m_id;
    uint32_t m_vao, m_vbo, m_ebo;
    uint32_t m_width, m_height;

    glm::vec2 m_scale = glm::vec2(1, 1);

    float m_angle = 0.0f;
};

} // namespace Stup
