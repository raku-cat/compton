#define GL_GLEXT_PROTOTYPES
#include "texture.h"

#include <stdio.h>

static inline GLuint generate_texture(GLenum tex_tgt, const Vector2* size) {
  GLuint tex = 0;

  glGenTextures(1, &tex);
  if (!tex)
      return 0;

  glBindTexture(tex_tgt, tex);
  glTexParameteri(tex_tgt, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(tex_tgt, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(tex_tgt, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(tex_tgt, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(tex_tgt, 0, GL_RGB, size->x, size->y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glBindTexture(tex_tgt, 0);

  return tex;
}

int texture_init(struct Texture* texture, GLenum target, const Vector2* size) {
    texture->gl_texture = generate_texture(target, size);
    if(texture->gl_texture == 0) {
        return 1;
    }

    texture->target = target;
    texture->size = *size;

    return 0;
}

void texture_delete(struct Texture* texture) {
    glDeleteTextures(1, &texture->gl_texture);
    texture->gl_texture = 0;
    texture->target = 0;
    texture->size.x = 0;
    texture->size.y = 0;
}

bool texture_initialized(const struct Texture* texture) {
    return texture->gl_texture != 0;
}

int texture_read_from(struct Texture* texture, GLuint framebuffer,
        GLenum buffer, const Vector2* pos, const Vector2* size) {
    if(texture->size.x < size->x || texture->size.y < size->y) {
        printf("Tried to copy an area too large into a texture\n");
        return 1;
    }

    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glReadBuffer(buffer);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(texture->target, texture->gl_texture);

    if (size->x <= 0 && size->y <= 0) {
        return 1;
    }

    Vector2 offset = {{0, 0}};
    glCopyTexSubImage2D(texture->target, 0, offset.x, offset.y,
            pos->x, pos->y, size->x, size->y);

    return 0;
}

int texture_bind_to_framebuffer(struct Texture* texture, GLuint framebuffer,
        GLenum buffer) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            texture->target, texture->gl_texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
            GL_FRAMEBUFFER_COMPLETE) {
        printf("Framebuffer attachment failed\n");
        return 1;
    }

    return 0;
}

void texture_bind(const struct Texture* texture, GLenum unit) {
    glActiveTexture(unit);
    glBindTexture(texture->target, texture->gl_texture);
}
