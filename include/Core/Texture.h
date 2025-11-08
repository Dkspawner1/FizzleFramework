#ifndef FIZZLEFRAMEWORK_TEXTURE_H
#define FIZZLEFRAMEWORK_TEXTURE_H
#include <SDL3/SDL_render.h>

typedef struct {
    char *id; // Identifier (e.g., "board", "ball", "paddle")
    SDL_Texture *texture; // The actual GPU texture
    SDL_FRect rectangle; // Position and dimensions
    float width; // Width in pixels
    float height; // Height in pixels
    int ref_count; // Reference count (for caching)
} Texture;

// Ctor:
Texture *Texture_Create(const char *id, SDL_Texture *sdl_texture,
                        float x, float y, float scale);

// Getters:
const char *Texture_GetID(const Texture *texture);
SDL_FRect Texture_GetRect(const Texture *texture);

SDL_Texture *Texture_GetSDLTexture(const Texture *texture);

// Position/Size utilities
void Texture_SetPosition(Texture *texture, float x, float y);

void Texture_SetSize(Texture *texture, float width, float height);

void Texture_SetScale(Texture *texture, float scale);

// Reference counting
void Texture_AddRef(Texture *texture);

void Texture_RemoveRef(Texture *texture);

int Texture_GetRefCount(const Texture *texture);

//Dtor:
void Texture_Destroy(Texture *texture);


#endif //FIZZLEFRAMEWORK_TEXTURE_H
