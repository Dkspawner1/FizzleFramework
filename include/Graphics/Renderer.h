
#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer();
    void Clear() const;
    void SetClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
private:
    void InitializeGlad();
};

#endif //RENDERER_H
