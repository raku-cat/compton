#pragma once

#include <GL/glx.h>

#include "vmath.h"

struct Texture {
    GLuint gl_texture;
    GLenum target;
    Vector2 size;
};

int texture_init(struct Texture* texture, GLenum target, const Vector2* size);
void texture_delete(struct Texture* texture);
bool texture_initialized(const struct Texture* texture);

int texture_read_from(struct Texture* texture, GLuint framebuffer, 
        GLenum buffer, const Vector2* pos, const Vector2* size);

int texture_bind_to_framebuffer(struct Texture* texture, GLuint framebuffer,
        GLenum buffer);

void texture_bind(const struct Texture* texture, GLenum unit);