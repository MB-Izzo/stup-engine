#include "Sprite.h"

#include <glad/glad.h>
#include "Engine/Renderer/Renderer.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Stup {

Sprite::Sprite(const std::string &imagePath, uint32_t width, uint32_t height, const Transform& transform)
    : m_width(width), m_height(height), m_shader(std::make_unique<Stup::Shader>("/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/basicShader.vs", "/home/mathieu/personal/opengl/stup_engine/StupEngine/assets/basicShader.fs")), m_texture(std::make_unique<Texture>(imagePath)), m_transform(transform)
{
}

void Sprite::Update(float dt) 
{
    Renderer::shared_instance().DrawSprite(*this);
}


Sprite::~Sprite() {}

} // namespace Stup
