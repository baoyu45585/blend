

#ifndef TEXTUREBLEND_RENDERENGINE_H
#define TEXTUREBLEND_RENDERENGINE_H

#include <memory>
#include "function.h"
enum effectType
{
    STARMIRROR,
};
class AAssetManager;

class RenderEngine
{
protected:
    class Imp;
    std::unique_ptr<Imp> mImpUPtr;
    struct ImagestarPos starPos;
    float bound[40], max_block_size;
public:
    static RenderEngine& GetInstance();

private:
    RenderEngine();
    ~RenderEngine();

public:
    bool setupGraphics(int w,int h,AAssetManager* assetMgr);
    void renderFrame();
    void resetTime();
    void genTextureId(unsigned int idNum,char* path);
    void createTexture(unsigned int textureIndex,unsigned char* pData1,int w,int h);
    void transformT(float y);
    void transformStrength(float y);
    void transformStarCount(float y);
    void transformDimWidth(float y);
    void transformHoldTime(float y);
    void transformFRadius(float y);
    void transformZoomIn(float y);
    void transformWaveWidth(float mWidth);
    void transformArrowCount(float mWidth);
    void transformDistance(float mWidth);
    void transformSmoothness(float mWidth);
    void transformStripe_num(int mWidth);
    void transformBlockNum(int mWidth);
    void transformBlockWidth(float mWidth);
    void transformSizeScale(float mWidth);
    void transformBlurRadius(float mWidth);
    void transformJitterY(float mWidth);
    void transformType(int mWidth);
    void transformTime2(float mWidth);
    void shutDown();
    void getPic(char* path);


    void changeCurFrame(bool flag);

    bool isChanged();

    void calculateMaxBlockSize();
};

#endif //TEXTUREBLEND_RENDERENGINE_H
