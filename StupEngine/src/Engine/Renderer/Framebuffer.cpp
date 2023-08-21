#include "Framebuffer.h"

#include <glad/glad.h>

namespace Stup {
Framebuffer::Framebuffer()
{
    GLuint m_fboId = 0;
    glGenFramebuffers(1, &m_fboId);

    GLuint m_rboId = 0;
    glGenRenderbuffers(1, &m_rboId);
    // Need to bind this once so object is created.
    glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboId);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, m_rboId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 64, 64);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

void Framebuffer::Blit()
{

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fboId);
    glBlitFramebuffer(0, 0, 64, 64, 0, 0, 640, 640, GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

} // namespace Stup
