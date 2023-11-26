#version 460 core

in vec2 vpos;

out vec4 FragColor;

void main() {
    FragColor = vec4(vpos, 1.0, 1.0);
}
