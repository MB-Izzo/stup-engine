#include "Renderer.h"
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Stup {

static glm::vec4 s_mvp;

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Init() 
{
    float quadVertices[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    };
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao); // always bind vao first.

    // upload vertices data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices,
                 GL_STATIC_DRAW);

    // upload indices data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                 // layout location
        2,                 // number of vertex attribute (vec3)
        GL_FLOAT,          // type of data
        GL_FALSE,          // normalized
        4 * sizeof(float), // stride (space between 2 vertex attribute)
        (void *)0); // offset where position data is (because we are binding
                    // vertex pos here)
    // Then, do not forget to enable at layout location
    glEnableVertexAttribArray(0);

    // do the same for texCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
}

void Renderer::DrawSprite(Sprite& sprite)
{

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    std::cout << "drawing sprite";
    sprite.GetShader().Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite.GetTexture().GetID());

    // should be in cam
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, 64.0f, 0.0f, 64.0f, -1.0f,
                            1.0f); // Orthographic projection

    // Combine the matrices
    int projectionLoc = glGetUniformLocation(sprite.GetShader().ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view;
    view = glm::mat4(1.0f); // m_camera->GetViewMatrix();
    int viewLoc = glGetUniformLocation(sprite.GetShader().ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(sprite.GetTransform().GetPosition().x, sprite.GetTransform().GetPosition().y, 0.0f));

    model =
        glm::translate(model, glm::vec3(0.5f * sprite.GetWidth(), 0.5f * sprite.GetHeight(), 0.0f));

    model = glm::rotate(model, glm::radians(glm::round(sprite.GetAngle())), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model,
                           glm::vec3(-0.5f * sprite.GetWidth(), -0.5f * sprite.GetHeight(), 0.0f));

    model = glm::scale(model, glm::vec3(sprite.GetWidth() * sprite.GetScale().x, sprite.GetHeight() * sprite.GetScale().y, 1.0f));

    int modelLoc = glGetUniformLocation(sprite.GetShader().ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(m_vao);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::DrawFromVAO(const std::shared_ptr<uint32_t> &vertexArray,
                           uint32_t indexCount)
{
    



    glBindVertexArray(*vertexArray);
//    uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

}

void Renderer::BeginScene(/* camera */)
{
    /*
    glm::mat4 projection = glm::mat4(1.0f);
    s_mvp = glm::ortho(0.0f, 64.0f, 0.0f, 64.0f, -1.0f,
                            1.0f); // Orthographic projection
    */
}


void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width,
                           uint32_t height)
{
    glViewport(x, y, width, height);
}

void Renderer::SetClearColor(const glm::vec4 &color)
{
    glClearColor(0, 0.5,0,1);
}

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

} // namespace Stup
