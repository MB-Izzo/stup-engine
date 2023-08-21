#pragma once

#include "stuppch.h"

namespace Stup {
class Framebuffer {
  public:
    Framebuffer();
    ~Framebuffer() = default;

    void Blit();
    void Bind();

  private:
    uint32_t m_fboId;
    uint32_t m_rboId;
};

} // namespace Stup
