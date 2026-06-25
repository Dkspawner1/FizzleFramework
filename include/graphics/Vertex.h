#pragma once 


struct Vertex {
	float x, y, z;
	float r, g, b, a;
};


// 2D Square/Quad (Color only)
static Vertex g_vertices[]{
    // Triangle 1 (Bottom-Left half)
    {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},   // Top-Left (Red)
    {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},   // Bottom-Left (Green)
    { 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},   // Bottom-Right (Blue)

    // Triangle 2 (Top-Right half)
    {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},   // Top-Left (Red)
    { 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},   // Bottom-Right (Blue)
    { 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f}    // Top-Right (Yellow)
};

