#pragma once

#include "stuppch.h"

namespace Stup {

class Texture
{
    public:
        Texture(const std::string& textureFilePath);
        ~Texture();

        void Bind(uint32_t slot = 0);
        void Unbind();

        uint32_t GetWidth() const { return m_width; }
        uint32_t GetHeight() const { return m_width; }

        uint32_t GetID() const { return m_id; }

        bool operator==(const Texture& other) const 
        {
            return m_id == other.GetID();
        }

    private:
        uint32_t m_id;
        uint32_t m_width, m_height;
};
}
