#define textureCnt 2
#define float_two 2.0
precision highp float;
varying vec2 v_texCoord;
uniform float progress;
uniform sampler2D s_texture[textureCnt];
const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
    float progress = progress/float_two;// * speed;

    float iTime = clamp(progress, 0.0, 1.0);
    vec4 res = vec4(0.0);
    if (v_texCoord.x >= 0.5 + iTime || v_texCoord.x <= 0.5 - iTime){
        res  = black;
    }
    else {
        res  = texture2D(s_texture[0], v_texCoord);
    }
    gl_FragColor = vec4(res.rgb, 1.0);
}
//刷新率*每次加的时间=需要的时间
