#version 130

in vec2 fragmentUV;
uniform sampler2D tex_scr;

uniform vec3 color;

void main() {
    vec2 uv = fragmentUV;
    gl_FragColor = vec4(color, 1);
}
