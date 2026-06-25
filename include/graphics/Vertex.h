#pragma once 

namespace fizzle {
	struct Vertex {
		float x, y, z;
		float r, g, b, a;
	};


	// 2D Square/Quad (Color only)
	static Vertex g_vertices[]{
		// Triangle 1 (Bottom-Left half)
		{.x = -0.5f, .y = 0.5f, .z = 0.0f, .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},   // Top-Left (Red)
		{.x = -0.5f, .y = -0.5f, .z = 0.0f, .r = 0.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f},   // Bottom-Left (Green)
		{.x = 0.5f, .y = -0.5f, .z = 0.0f, .r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f},   // Bottom-Right (Blue)

		// Triangle 2 (Top-Right half)
		{.x = -0.5f, .y = 0.5f, .z = 0.0f, .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},   // Top-Left (Red)
		{.x = 0.5f, .y = -0.5f, .z = 0.0f, .r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f},   // Bottom-Right (Blue)
		{.x = 0.5f, .y = 0.5f, .z = 0.0f, .r = 1.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f}    // Top-Right (Yellow)
	};

};