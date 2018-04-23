#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D fboTexture;

void main( ) {
    vec4 sceneColor = texture(fboTexture, TexCoord);
    float grayscale = (sceneColor.r + sceneColor.g + sceneColor.b) / 4.0;
	vec4 grayscaled = vec4((grayscale * 2 + sceneColor.r) / 3.0, (grayscale * 2 + sceneColor.g) / 3.0, (grayscale * 2 + sceneColor.b) / 3.0, sceneColor.a); 
	color = vec4(grayscaled.r , grayscaled.g, (grayscaled.b + grayscaled.b + 0.9) / 3.0, 0.5);
}