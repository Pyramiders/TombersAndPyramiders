#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform sampler2D fogOfWarMask;

void main( ) {
    gl_Position = vec4(position * 2.0, 1.0);
    TexCoord = texCoord.xy;
}

