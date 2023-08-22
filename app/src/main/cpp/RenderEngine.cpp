#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "RenderEngine.h"
#include "Shader.h"

#include<iostream>
#include <string>
#define  RenderEngine_TAG  "InitEngine"
#define  Render_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,RenderEngine_TAG,__VA_ARGS__)
float moveDeltaY = 1.0f;
float mProgress=0.0f;
float mTime = 2300.0f;
float strength=0.8f;
float starCount=0.01f;
float pause_point = 0.5; // 0.4 ~ 0.7
float pause_time = 0.6; // 0.1 ~ 1.2
float dimWidth=0.8f;
float max_zoom_in = 2.0f;
float arrowCount = 4.0;  // 箭头个数，范围1-10整数
int arrow_switch = 1; //1表示打开箭头转场参数代码块，0表示关闭
float waveWidth=1.0f;
float smoothness = 0.05f; // 特效快慢，越小越快,范围:（0，无穷）
float mDistance = 0.05f;  // 特效色彩距离，即振幅控制,范围:[0.1-1.0]
float size_scale = 0.5f;  // 范围:[0.5-2.0]
int stripe_num = 50;  // 范围:[50 - 200]
int block_num = 7;  // 范围:[7-33]
int move_dir = 0;  // 范围:[1-0]
float block_width = 1.0;  // 范围:[0-1]
float blur_radius = 1.0;  // 范围:[0-100]
float jitter_y = 0.1;  // 范围:[0-1]
float time2 = 0.45;  // 范围:[0.4-0.5]
int type = 1;  // 范围:[1-6]
char* typeNameChar;
unsigned int CurFrame = 0;
unsigned int maxFrame = 0;
float ImageLocateData[70][3] = {
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.076 , 0.009 , 1.011,
        1.125 , 0.020 , 1.001,
        1.171 , 0.031 , 0.991,
        1.209 , 0.047 , 0.976,
        1.244 , 0.064 , 0.959,
        1.275 , 0.082 , 0.941,
        1.303 , 0.102 , 0.922,
        1.328 , 0.121 , 0.903,
        1.350 , 0.142 , 0.883,
        1.369 , 0.164 , 0.861,
        1.387 , 0.187 , 0.839,
        1.404 , 0.209 , 0.817,
        1.418 , 0.232 , 0.794,
        1.431 , 0.255 , 0.772,
        1.439 , 0.280 , 0.747,
        1.450 , 0.304 , 0.723,
        1.457 , 0.329 , 0.698,
        1.463 , 0.354 , 0.673,
        1.468 , 0.378 , 0.650,
        1.472 , 0.405 , 0.623,
        1.475 , 0.430 , 0.597,
        1.477 , 0.458 , 0.570,
        1.477 , 0.484 , 0.544,
        1.477 , 0.512 , 0.515,
        1.475 , 0.540 , 0.488,
        1.472 , 0.570 , 0.458,
        1.470 , 0.598 , 0.429,
        1.463 , 0.629 , 0.398,
        1.459 , 0.658 , 0.369,
        1.452 , 0.688 , 0.339,
        1.444 , 0.718 , 0.309,
        1.435 , 0.747 , 0.279,
        1.424 , 0.776 , 0.251,
        1.414 , 0.805 , 0.221,
        1.399 , 0.832 , 0.194,
        1.385 , 0.858 , 0.168,
        1.368 , 0.882 , 0.143,
        1.348 , 0.906 , 0.119,
        1.326 , 0.928 , 0.096,
        1.301 , 0.947 , 0.077,
        1.275 , 0.966 , 0.057,
        1.244 , 0.981 , 0.042,
        1.209 , 0.996 , 0.026,
        1.169 , 1.008 , 0.014,
        1.125 , 1.015 , 0.006,
        1.077 , 1.022 , -0.002,
        1.004 , 1.002 , 0.017,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
};
class RenderEngine::Imp {
public:
    GLuint mSurfaceWidth;
    GLuint mSurfaceHeight;
    Shader mShader;
    unsigned int mVAO;
    unsigned int mVBO;
    unsigned int mEBO;
    GLuint *mTexture1;
    GLfloat vVertices[20];
    GLushort indices[6];

public:

};

RenderEngine::RenderEngine() : mImpUPtr(std::make_unique<Imp>()) {
    auto &imp_ = *mImpUPtr;
    GLfloat temp0[] = {-1.0f, 1.0f, 0.0f,  // Position 0 ↖
                       0.0f, 0.0f,        // TexCoord 0
                       -1.0f, -1.0f, 0.0f,  // Position 1 ↙
                       0.0f, 1.0f,        // TexCoord 1
                       1.0f, -1.0f, 0.0f,  // Position 2 ↘
                       1.0f, 1.0f,        // TexCoord 2
                       1.0f, 1.0f, 0.0f,  // Position 3 ↗
                       1.0f, 0.0f         // TexCoord 3
    };
//    GLfloat temp0[] = {-1.0f, 1.0f, 0.0f,  // Position 0 ↖
//                           1.0f, 0.0f,        // TexCoord 0
//                           -1.0f, -1.0f, 0.0f,  // Position 1 ↙
//                           1.0f, 1.0f,        // TexCoord 1
//                           1.0f, -1.0f, 0.0f,  // Position 2 ↘
//                           0.0f, 1.0f,        // TexCoord 2
//                           1.0f, 1.0f, 0.0f,  // Position 3 ↗
//                           0.0f, 0.0f         // TexCoord 3
//    };
    for(int i = 0; i < 20; ++i)imp_.vVertices[i] = temp0[i];
    GLushort temp1[] = {0, 1, 2, 0, 2, 3};
    for(int i = 0; i < 6; ++i)imp_.indices[i] = temp1[i];

}

RenderEngine::~RenderEngine() {
}

RenderEngine &RenderEngine::GetInstance() {
    static RenderEngine renderEngine;
    return renderEngine;
}

bool RenderEngine::setupGraphics(int w, int h, AAssetManager *assetMgr) {
    auto &imp_ = *mImpUPtr;
    if (0 == w || 0 == h || NULL == assetMgr) {
        Render_LOGE("setupGraphics param illegal");
        return false;
    }
    char buff[128] = {0};
    char buff2[128] = {0};
    sprintf(buff, "%s%s", typeNameChar, "/vsh.glsl");
    sprintf(buff2, "%s%s", typeNameChar, "/fsh.glsl");
    imp_.mShader.init(buff, buff2, assetMgr);
//    imp_.initVAO(assetMgr);
    imp_.mSurfaceWidth = w;
    imp_.mSurfaceHeight = h;

    glViewport(0, 0, w, h);
    Render_LOGE("mProgress %i,%i", w,h);
    CurFrame=0;
    calculateMaxBlockSize();
    return true;
}
void RenderEngine::renderFrame() {
    auto &imp_ = *mImpUPtr;
    glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(imp_.mVAO);
    imp_.mShader.use();


    float increase = mTime / 25;
    // ||
    //        !strcmp(typeNameChar, "dispersion_switch")
    if (!strcmp(typeNameChar, "final") || !strcmp(typeNameChar, "arrow_switch")) {
        if (mProgress >= 2.0f) {
            mProgress = 0.0f;
        } else {
            mProgress += 1 / increase;
        }
    } else {
        if (mProgress >= 1.0f) {
            mProgress = 0.0f;
        } else {
            mProgress += 1 / increase;
        }
    }
    Render_LOGE("mProgress %f", mProgress);
    GLuint elapsedTimeUniformLocation = glGetUniformLocation(imp_.mShader.mProgram, "progress");
    glUniform1f(elapsedTimeUniformLocation, mProgress);
    GLuint SpeedUniformLocation = glGetUniformLocation(imp_.mShader.mProgram, "speed");
    glUniform1f(SpeedUniformLocation, (GLfloat) moveDeltaY);
    GLuint widthUniformLocation = glGetUniformLocation(imp_.mShader.mProgram, "win_width");
    glUniform1f(widthUniformLocation, (GLfloat) imp_.mSurfaceWidth);
    GLuint heightUniformLocation = glGetUniformLocation(imp_.mShader.mProgram, "win_height");
    glUniform1f(heightUniformLocation, (GLfloat) imp_.mSurfaceHeight);
    glVertexAttribPointer(glGetAttribLocation(imp_.mShader.mProgram, "a_position"), 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), imp_.vVertices);
    glVertexAttribPointer(glGetAttribLocation(imp_.mShader.mProgram, "a_texCoord"), 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &imp_.vVertices[3]);
    GLuint radiusUniformLocation = glGetUniformLocation(imp_.mShader.mProgram, "radius");
    glUniform1f(radiusUniformLocation, (GLfloat) (0.4));
    Render_LOGE("宽高 %i,%i", imp_.mSurfaceWidth,imp_.mSurfaceHeight);
    glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "strength"), strength);
    glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "ratio"),
                1.0 * imp_.mSurfaceWidth / imp_.mSurfaceHeight);
    glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "pause_point"), pause_point);
    glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "pause_time"), pause_time);
    glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "max_zoom_in"), max_zoom_in);
    glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "wave_width"), waveWidth);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
//    for (int i = 0; i < 2; i++) {
//        glActiveTexture(GL_TEXTURE0 + i);
//        glBindTexture(GL_TEXTURE_2D, imp_.mTexture1[i]);
//    }
    if (!strcmp(typeNameChar, "snow") ) {
        GLint fs_SamplerValue[4] = {0, 1, 2, 3};
        glUniform1iv(glGetUniformLocation(imp_.mShader.mProgram, "s_texture"), 4, fs_SamplerValue);
    }else{
        GLint fs_SamplerValue[3] = {0, 1, 2};
        glUniform1iv(glGetUniformLocation(imp_.mShader.mProgram, "s_texture"), 3, fs_SamplerValue);
    }
    if(!strcmp(typeNameChar, "dispersion_switch")){

//        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "smoothness"), smoothness);
//        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "distance"), mDistance);
    }
    if (!strcmp(typeNameChar, "arrow_switch")) {

        float smoothness = 0.5;  // 特效快慢，越小越快
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "count"), arrowCount);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "smoothness"), smoothness);
    }
    if (!strcmp(typeNameChar, "lr_blur")) {
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "time2"), time2);
    }
    if (!strcmp(typeNameChar, "spin_focus")) {
        float strength = 7.0; //模拟光圈大小参数，即全局模糊程度，[0-无穷大],越大越模糊，建议为3.0
        float spinCnt = 10.0;  //周边径向模糊程度，即旋转次数[0-无穷大]，越大越模糊
        float radius = 0.4; //中间主体物范围程度参数，即旋焦中心不变区域半径[0-0.5]，中间区域为圆形
        float tmpK = 0.5; //过渡羽化参数,即高斯渐变参数，[0-1.0]，越小越自然过渡，建议为0.8
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "strength"), strength);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "spinCnt"), spinCnt);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "radius"), radius);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "tmpK"), tmpK);
    }

    if (!strcmp(typeNameChar, "animationTrans")) {
        Render_LOGE("in animationTrans");
        changeCurFrame(isChanged());
    }
    if (!strcmp(typeNameChar, "FilmSlide")) {
//        Render_LOGE("in FilmSlide");
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "ScareSize"), ImageLocateData[CurFrame][0]);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "RedY_offset"), ImageLocateData[CurFrame][1]);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "GreenY_offset"), ImageLocateData[CurFrame][2]);
        changeCurFrame(isChanged());
    }
    if (!strcmp(typeNameChar, "mosaic")) {
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "block_width"),block_width);

    }if (!strcmp(typeNameChar, "snow")) {
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "size_scale"),size_scale);
        Render_LOGE("切割个数%f",size_scale);

    }if (!strcmp(typeNameChar, "color_stripe")) {
        glUniform1i(glGetUniformLocation(imp_.mShader.mProgram, "stripe_num"),stripe_num);

    }if (!strcmp(typeNameChar, "cut_horizontal")||!strcmp(typeNameChar, "cut_vertical")||!strcmp(typeNameChar, "cut_zoom")) {
        glUniform1i(glGetUniformLocation(imp_.mShader.mProgram, "block_num"),block_num);
        glUniform1i(glGetUniformLocation(imp_.mShader.mProgram, "move_dir"),move_dir);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "max_block_size"),max_block_size);
        glUniform1fv(glGetUniformLocation(imp_.mShader.mProgram, "bound"), block_num, bound);
        Render_LOGE("切割个数%i",block_num);
    }if (!strcmp(typeNameChar, "blur_line")) {
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "blur_radius"), blur_radius);
        glUniform1f(glGetUniformLocation(imp_.mShader.mProgram, "jitterY"), jitter_y);
    }if (!strcmp(typeNameChar, "cut")) {
        glUniform1i(glGetUniformLocation(imp_.mShader.mProgram, "type"),type);
    }

//        if(!strcmp(typeNameChar, "star_mirror"))
//    {
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//        glUniform1i(glGetUniformLocation(imp_.mShader.mProgram, "func"), 1);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, imp_.indices);
//        glUniform1i(glGetUniformLocation(imp_.mShader.mProgram, "func"), 0);
//        glVertexAttribPointer(glGetAttribLocation(imp_.mShader.mProgram, "a_position"), 2, GL_FLOAT,
//                              GL_FALSE, 2 * sizeof(GLfloat), starPos.starPos.posArray);
//        glEnableVertexAttribArray(glGetAttribLocation(imp_.mShader.mProgram, "a_position"));
//        glDrawArrays(GL_POINTS, 0, starPos.starPos.cnt);
//    }
//    else
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, imp_.indices);
}

void RenderEngine::genTextureId(unsigned int idNum, char*mPath)
{
    auto& imp_ = *mImpUPtr;
    imp_.mTexture1=new GLuint[idNum];
    typeNameChar=mPath;
    if (!strcmp(mPath, "FilmSlide")) {
        maxFrame=70;
    }if (!strcmp(mPath, "animationTrans")) {
        maxFrame=41;
    }

}

void RenderEngine::createTexture(unsigned int textureIndex, unsigned char *pData, int w, int h) {
    auto &imp_ = *mImpUPtr;
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glGenTextures(1,&imp_.mTexture1[textureIndex]);
    glBindTexture(GL_TEXTURE_2D, imp_.mTexture1[textureIndex]);
    Render_LOGE("绑定图片索引%i", textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (pData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}


void RenderEngine::getPic(char *path) {
    auto &imp_ = *mImpUPtr;
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, imp_.mTexture1[2]);

    AAsset *pathAsset = AAssetManager_open(imp_.mShader.mAssetMgr, path, AASSET_MODE_UNKNOWN);

    off_t assetLength = AAsset_getLength(pathAsset);

    unsigned char *fileData = (unsigned char *) AAsset_getBuffer(pathAsset);

    int w, h, n;

    unsigned char *content = stbi_load_from_memory(fileData, assetLength, &w, &h, &n, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, content);

    // Set the filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    Render_LOGE("宽%i,高%i,某%i", w, h, n);
//    mTextureId = loadTexture(w, h, content);
//
//    drawer->onTextureChange(mTextureId);
    AAsset_close(pathAsset);
}

void RenderEngine::changeCurFrame(bool flag) {
    if (flag) {
        Render_LOGE("changeCurFrame=true");
        string path1="";
        string path2="";
        CurFrame += 1;
        if (CurFrame > maxFrame - 1)
            CurFrame = 0;
        if (!strcmp(typeNameChar, "FilmSlide")) {
            path1 = "FilmEffect/胶片_000.jpg";
            if(CurFrame < 10){
                path2 = path1.replace(20,1,to_string(CurFrame));
            }else{
                path2 = path1.replace(19,2,to_string(CurFrame));
            }
        }if (!strcmp(typeNameChar, "animationTrans")) {
            path2="animation/dh_"+to_string(CurFrame)+".jpg";
        }
//        Render_LOGE("changeCurFrame当前帧 %d", CurFrame);


        Render_LOGE("changeCurFrame路径 %s", path2.c_str());
        getPic(const_cast<char *>(path2.c_str()));
    }
}

bool RenderEngine::isChanged() {
    if (mProgress > CurFrame * (1.0f / maxFrame)) {
        return true;
    }
    return false;

}
void RenderEngine::transformT(float fy)
{
    mTime=fy;
}
//void RenderEngine::transformStarCount(float mStarCount)
//{
//    starCount=mStarCount;
//   starPos.init(80 * starCount, pData,w , h, 50 * (1.0 - starCount));
//}
void RenderEngine::transformStrength(float mStrength)
{
    strength=mStrength;
}
void RenderEngine::transformFRadius(float mPause_point)
{
    pause_point=mPause_point;
}void RenderEngine::transformZoomIn(float mZoomIn)
{
    max_zoom_in = mZoomIn;
}
void RenderEngine::transformHoldTime(float mPause_time)
{
    pause_time=mPause_time;
}
void RenderEngine::transformDimWidth(float mDimWidth)
{
    dimWidth=mDimWidth;
}
void RenderEngine::transformWaveWidth(float mWidth)
{
    waveWidth=mWidth;
}void RenderEngine::transformArrowCount(float mWidth)
{
    arrowCount=mWidth;
}void RenderEngine::transformSmoothness(float mWidth)
{
    smoothness=mWidth;
}void RenderEngine::transformDistance(float mWidth)
{
    mDistance=mWidth;
}void RenderEngine::transformStripe_num(int mWidth)
{
    stripe_num=mWidth;
}void RenderEngine::transformBlockNum(int mWidth)
{
    block_num=mWidth;
    calculateMaxBlockSize();
}void RenderEngine::transformBlockWidth(float mWidth)
{
    block_width=mWidth;
}void RenderEngine::transformSizeScale(float mWidth)
{
    size_scale=mWidth;
}void RenderEngine::transformBlurRadius(float mWidth)
{
    blur_radius=mWidth;
}void RenderEngine::transformJitterY(float mWidth)
{
    jitter_y=mWidth;
}void RenderEngine::transformType(int mWidth)
{
    type=mWidth;
}void RenderEngine::transformTime2(float mWidth)
{
    time2=mWidth;
}

void RenderEngine::calculateMaxBlockSize(){
    float remain_size = 1.0;
    max_block_size = 0.0;
    int remain_block = block_num;
    srand(clock());
    float mmin, mmax;
    if(!strcmp(typeNameChar, "cut_horizontal"))mmin = 0.03, mmax = 0.16;
    if(!strcmp(typeNameChar, "cut_vertical"))mmin = 0.05, mmax = 0.27;
    for (int i = 0; i < block_num; ++i)
    {
        --remain_block;
        bound[i] = float(1.0 )- floor(remain_size * 100) / 100;
        if (remain_block == 0)break;
        float l = max(mmin, remain_size - remain_block * mmax), r =min(remain_size/(remain_block + 1) * 2, min(mmax, remain_size - remain_block * mmin));
        int ll = int(round(l * 100)), rr = int(round(r * 100));
        int temp = rand() % (rr - ll + 1) + ll;
        remain_size -= temp / 100.0;
        max_block_size = max(max_block_size, float(temp / 100.0));
    }
}
void RenderEngine::shutDown()
{
    auto &imp_ = *mImpUPtr;
    glDeleteTextures(1, imp_.mTexture1);
    glDeleteProgram(imp_.mShader.mProgram);
    CurFrame=0;
}



