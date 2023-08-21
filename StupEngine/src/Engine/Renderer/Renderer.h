#pragma once

#include "stuppch.h"
#include <glm/glm.hpp>
#include "Engine/GameObjects/Components/Sprite.h"

namespace Stup {

class Renderer {
  public:
    static Renderer &shared_instance()
    {
        static Renderer renderer;
        return renderer;
    }

    void Init();

    void DrawSprite(Sprite& sprite);

    //Should be in another
    void DrawFromVAO(const std::shared_ptr<uint32_t> &vertexArray,
                     uint32_t indexCount);
    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void SetClearColor(const glm::vec4 &color);
    void Clear();

    //Should be in another
    void BeginScene(/* camera */);

//    const glm::mat4& GetVPMatrix() { return m_viewProjectionMatrix; }
  private:
    glm::mat4 m_viewProjectionMatrix;
    uint32_t m_vao, m_vbo, m_ebo;
    Renderer();
    ~Renderer(); 
};

} // namespace Stup
