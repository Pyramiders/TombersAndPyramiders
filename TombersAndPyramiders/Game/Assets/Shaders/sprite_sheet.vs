#version 410 core

layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transform;
uniform float aspectRatio;
uniform ivec3 texData; //columnCount, rowCount, index

void main() {
	vec4 pos = transform * vec4(position, 1.0);
	pos.y *= aspectRatio;
	gl_Position = pos;

	//Current row/column in the spritesheet
	vec2 currentPos = vec2(texData.z % texData.x, texData.z / texData.x);

	//Must flip texCoord.y 
	TexCoord = (currentPos + vec2(texCoord.x, 1.0 - texCoord.y)) / vec2(texData.x, texData.y);
	
	//Hacky fix. TODO please fix this it's so ugly
	if (texCoord.x == 0) {
		TexCoord.x += 0.0125;
	}
	if (texCoord.x == 1) {
		TexCoord.x -= 0.0125;
	}
	if (texCoord.y == 0) {
		TexCoord.y -= 0.0125;		
	}
	if (texCoord.y == 1) {
		TexCoord.y += 0.0125;
	}
	//TexCoord = vec2(texCoord.x, texCoord.y);
}

