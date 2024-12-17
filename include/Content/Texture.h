#ifndef TEXTURE_H
#define TEXTURE_H
#include <Content/Asset.h>
#include <glad/glad.h>
#include <string>

class Texture final : public Asset {
public:
    Texture(const std::string& name, const std::string& path);
    ~Texture() override;

    void Bind() const;

    GLuint GetTextureID() const { return m_textureID; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    GLuint m_textureID;
    int m_width;
    int m_height;
};
#endif //TEXTURE_H