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

private:
    GLuint m_textureID;
};
#endif //TEXTURE_H