#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <glad/glad.h>

class Texture {
public:
    Texture(const std::string &path);

    ~Texture();

    void Bind() const;

private:
    GLuint m_textureID;
};
#endif //TEXTURE_H
