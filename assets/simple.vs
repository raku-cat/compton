#version 130
in vec3 vertex;
in vec2 uv;
out vec2 fragmentUV;

uniform mat4 mvp;
uniform vec2 uvscale = vec2(1.0, 1.0);

void main() {
    fragmentUV = uv * uvscale;
    gl_Position = mvp * vec4(vertex, 1.0);
}
