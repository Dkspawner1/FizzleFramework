#include <stdlib.h>
#include <Core/Texture.h>

#include "Core/Logger.h"


Texture *Texture_Create(const char *id, SDL_Texture *sdl_texture,
                        const float x, const float y, float scale) {
    // Validate inputs
    if (id == NULL) {
        LOG_ERROR("Texture_Create failed: ID cannot be NULL");
        return NULL;
    }

    if (sdl_texture == NULL) {
        LOG_ERROR("Texture_Create failed: SDL_Texture cannot be NULL");
        return NULL;
    }

    if (scale <= 0.0f) {
        LOG_WARN("Texture_Create: Invalid scale %.2f for texture '%s', using 1.0", scale, id);
        scale = 1.0f;
    }

    // Allocate Texture struct
    Texture *texture = malloc(sizeof(Texture));
    if (!texture) {
        LOG_CRITICAL("Texture_Create failed: Could not allocate memory for Texture '%s'", id);
        return NULL;
    }

    // Allocate and copy ID string
    texture->id = malloc(strlen(id) + 1);
    if (!texture->id) {
        LOG_CRITICAL("Texture_Create failed: Could not allocate memory for ID string '%s'", id);
        free(texture);
        return NULL;
    }
    strcpy(texture->id, id);

    // Get texture dimensions from SDL
    SDL_GetTextureSize(sdl_texture, &texture->width, &texture->height);

    if (texture->width <= 0.0f || texture->height <= 0.0f) {
        LOG_ERROR("Texture_Create: SDL_Texture '%s' has invalid dimensions %.0fx%.0f",
                  id, texture->width, texture->height);
        free(texture->id);
        free(texture);
        return NULL;
    }

    // Store texture pointer
    texture->texture = sdl_texture;

    // Apply scale to dimensions
    const float scaled_width = texture->width * scale;
    const float scaled_height = texture->height * scale;

    // Set position and size
    texture->rectangle = (SDL_FRect){x, y, scaled_width, scaled_height};

    // Initialize ref count to 1 (asset is created, so it has one owner)
    texture->ref_count = 1;

    LOG_DEBUG("Texture created: id='%s', native_size=%.0fx%.0f, scaled_size=%.0fx%.0f, position=(%.0f,%.0f)",
              id, texture->width, texture->height, scaled_width, scaled_height, x, y);
    return texture;
}

const char *Texture_GetID(const Texture *texture) {
    if (texture == NULL) {
        LOG_WARN("Texture_GetID called with NULL texture");
        return "";
    }
    return texture->id;
}

SDL_FRect Texture_GetRect(const Texture *texture) {
    if (texture == NULL) {
        LOG_WARN("Texture_GetRect called with NULL texture");
        return (SDL_FRect){0, 0, 0, 0};
    }
    return texture->rectangle;
}

SDL_Texture *Texture_GetSDLTexture(const Texture *texture) {
    if (texture == NULL) {
        LOG_WARN("Texture_GetSDLTexture called with NULL texture");
        return NULL;
    }
    return texture->texture;
}

void Texture_SetPosition(Texture *texture, float x, float y) {
    if (texture == NULL) {
        LOG_WARN("Texture_SetPosition called with NULL texture");
        return;
    }
    texture->rectangle.x = x;
    texture->rectangle.y = y;
    LOG_TRACE("Texture '%s' position set to (%.0f, %.0f)", texture->id, x, y);
}

void Texture_SetSize(Texture *texture, float width, float height) {
    if (texture == NULL) {
        LOG_WARN("Texture_SetSize called with NULL texture");
        return;
    }

    if (width <= 0 || height <= 0) {
        LOG_WARN("Texture_SetSize: Invalid dimensions %.0fx%.0f for '%s', ignoring",
                 width, height, texture->id);
        return;
    }

    texture->rectangle.w = width;
    texture->rectangle.h = height;
    LOG_TRACE("Texture '%s' size set to %.0fx%.0f", texture->id, width, height);
}


void Texture_SetScale(Texture *texture, const float scale) {
    if (texture == NULL) {
        LOG_WARN("Texture_SetScale called with NULL texture");
        return;
    }

    if (scale <= 0.0f) {
        LOG_WARN("Texture_SetScale: Invalid scale %.2f for '%s', ignoring", scale, texture->id);
        return;
    }

    texture->rectangle.w = (float) texture->width * scale;
    texture->rectangle.h = (float) texture->height * scale;
    LOG_TRACE("Texture '%s' scaled by %.2f (new size: %.0fx%.0f)",
              texture->id, scale, texture->rectangle.w, texture->rectangle.h);
}

void Texture_AddRef(Texture *texture) {
    if (texture == NULL) {
        LOG_WARN("Texture_AddRef called with NULL texture");
        return;
    }
    texture->ref_count++;
    LOG_TRACE("Texture '%s' ref_count incremented to %d", texture->id, texture->ref_count);
}

void Texture_RemoveRef(Texture *texture) {
    if (texture == NULL) {
        LOG_WARN("Texture_RemoveRef called with NULL texture");
        return;
    }

    if (texture->ref_count <= 0) {
        LOG_ERROR("Texture_RemoveRef: '%s' ref_count already zero or negative (%d)",
                  texture->id, texture->ref_count);
        return;
    }

    texture->ref_count--;
    LOG_TRACE("Texture '%s' ref_count decremented to %d", texture->id, texture->ref_count);
}

int Texture_GetRefCount(const Texture *texture) {
    if (texture == NULL) {
        LOG_WARN("Texture_GetRefCount called with NULL texture");
        return 0;
    }
    return texture->ref_count;
}

void Texture_Destroy(Texture *texture) {
    if (texture == NULL) {
        LOG_TRACE("Texture_Destroy called with NULL texture (no-op)");
        return;
    }

    LOG_DEBUG("Destroying Texture: '%s' (ref_count=%d)", texture->id, texture->ref_count);

    if (texture->ref_count > 0) {
        LOG_WARN("Destroying Texture '%s' with active references (ref_count=%d)",
                 texture->id, texture->ref_count);
    }

    // Don't free SDL_Texture here—it belongs to AssetManager
    // The manager handles GPU resource lifetime
    texture->texture = NULL;

    free(texture->id);
    free(texture);
}
