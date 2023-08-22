#define texture_count 1
#define half1 0.5
#define float_zero 0.0

precision mediump float;

varying vec2 v_texCoord;

const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);

uniform float progress;
// texture may more than 2
uniform sampler2D s_texture[texture_count];
uniform float speed;

void main() {
    vec4 tmp_color = texture2D(s_texture[0], v_texCoord);
    float time = progress *speed* half1 > half1 ? float_zero : half1 - progress * speed*half1;
    gl_FragColor = mix(tmp_color, black, step(time, abs(v_texCoord.x - half1)));
}                                          
