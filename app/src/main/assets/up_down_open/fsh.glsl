precision mediump float;

varying vec2 v_texCoord;

const int textureSize = 1;
const float float_half = 0.5;
const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);

uniform float progress;
uniform sampler2D s_texture[textureSize];

void main() {
    vec4 tmp_color = texture2D(s_texture[0], v_texCoord);
    float cur_y = clamp (smoothstep (0., 1., progress) / 2., smoothstep (0., 1., progress) / 2., float_half);
    gl_FragColor = mix(tmp_color, black, step(cur_y, abs(v_texCoord.y - float_half)));
}                                          
