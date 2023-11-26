#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

out vec2 vpos;

void main() {
    vpos = uv;

    vec4 position = vec4(pos, 1.0);
    // normalize to the first quadrant (origin at bottom left)
    position.xy  = position.xy * 2.0 - 1.0;

    // normalize to the fourth quadrant (origin at top left)
    // position.xy = -position.xy * 2.0 + 1.0;

    gl_Position = position;
}
