#version 410 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D fogOfWarMask;
uniform sampler2D gameRendering;

vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  color += texture(image, uv) * 0.1964825501511404;
  color += texture(image, uv + (off1 / resolution)) * 0.2969069646728344;
  color += texture(image, uv - (off1 / resolution)) * 0.2969069646728344;
  color += texture(image, uv + (off2 / resolution)) * 0.09447039785044732;
  color += texture(image, uv - (off2 / resolution)) * 0.09447039785044732;
  color += texture(image, uv + (off3 / resolution)) * 0.010381362401148057;
  color += texture(image, uv - (off3 / resolution)) * 0.010381362401148057;
  return color;
}

void main( ) {
    vec2 iResolution = vec2(1280.0 / 4, 768.0 / 4);
    vec4 fogColor = texture(fogOfWarMask, TexCoord);
    vec4 gameColor = texture(gameRendering, TexCoord);
    vec4 blurFog = (blur13(fogOfWarMask, TexCoord, iResolution, vec2(4, 0)) + blur13(fogOfWarMask, TexCoord, iResolution, vec2(0, 4)) +
            blur13(fogOfWarMask, TexCoord, iResolution, vec2(2, 2)) + blur13(fogOfWarMask, TexCoord, iResolution, vec2(-2, 2)) +
            blur13(fogOfWarMask, TexCoord, iResolution, vec2(-2, -2)) + blur13(fogOfWarMask, TexCoord, iResolution, vec2(2, -2))) / 6.0;
    
    color = blurFog * blurFog.a + texture(gameRendering, TexCoord) * (1.0 - blurFog.a);
    //color = texture(gameRendering, TexCoord);
}

