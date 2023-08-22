#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include "RenderEngine.h"
#define  NativeBridge_TAG  "NativeBridge"
#define  Bridge_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,NativeBridge_TAG,__VA_ARGS__)

extern "C" {
JNIEXPORT void JNICALL
Java_com_example_blend_JNILib_init(JNIEnv *env, jclass obj, jint width, jint height,
                                          jobject jAssetMgr);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_resetTime(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_step(JNIEnv *env, jclass obj);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_shutDown(JNIEnv* env,jclass obj);
JNIEXPORT void JNICALL
Java_com_example_blend_JNILib_setTextures(JNIEnv *env, jclass obj, jintArray texture);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformT(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformWaveWidth(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformZoomIn(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformStrength(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformFRadius(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformHoldTime(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformDimWidth(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformArrowCount(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformSmoothness(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformBlockWidth(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformDistance(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformStripeNum(JNIEnv* env,jclass obj,jint jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformBlockNum(JNIEnv* env,jclass obj,jint jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformSizeScale(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformBlurRadius(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformtransformJitterY(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformType(JNIEnv* env,jclass obj,jint jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformTime2(JNIEnv* env,jclass obj,jfloat jfloatY);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_genTextureId(JNIEnv *env, jclass obj,jint idNum,jstring jpath);
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_setTextureByte(JNIEnv *env, jclass obj,jbyteArray data,jint textureIndex,jint w,jint h);

//JNIEXPORT void JNICALL
//Java_com_example_blend_JNILib_setTextureData(JNIEnv *env, jobject obj, int col, int row,
//                                                    jintArray textureData);
JNIEXPORT void JNICALL
Java_com_example_blend_JNILib_setTextureBitmap(JNIEnv *env, jclass obj, jobject jbitmap1,jint textureIndex);
JNIEXPORT void JNICALL
Java_com_example_blend_JNILib_init(JNIEnv *env, jclass obj, jint width, jint height,
                                          jobject jAssetMgr) {
    Bridge_LOGE("Java_com_example_blend_JNILib_init");
    auto assetManager = AAssetManager_fromJava(env, jAssetMgr);

    RenderEngine::GetInstance().setupGraphics(width, height, assetManager);
}


JNIEXPORT void JNICALL Java_com_example_blend_JNILib_setTextureByte(JNIEnv *env, jclass obj,jbyteArray data,jint textureIndex,jint w,jint h)
{
    int len = env->GetArrayLength (data);
    unsigned char* buf = new unsigned char[len];
    unsigned int* rgbbuf = new unsigned int[w *h ];
    Bridge_LOGE("数据长度%i",len);
    env->GetByteArrayRegion(data, 0, len, reinterpret_cast<jbyte*>(buf));
//    RenderEngine::GetInstance().YV12ToBGR24_Native(buf,rgbbuf,w,h);
    RenderEngine::GetInstance().createTexture(textureIndex,buf,w, h);
    delete[] buf;
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformT(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformT(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformHoldTime(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformHoldTime(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformZoomIn(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformZoomIn(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformFRadius(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformFRadius(jfloatY);
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformStrength(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformStrength(jfloatY);
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformDimWidth(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformDimWidth(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformSizeScale(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformSizeScale(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformBlurRadius(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformBlurRadius(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformType(JNIEnv* env,jclass obj,jint jfloatY)
{
    RenderEngine::GetInstance().transformType(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformTime2(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformTime2(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformJitterY(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformJitterY(jfloatY);
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformWaveWidth(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformWaveWidth(jfloatY);
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformArrowCount(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformArrowCount(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformSmoothness(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformSmoothness(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformDistance(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformDistance(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformBlockWidth(JNIEnv* env,jclass obj,jfloat jfloatY)
{
    RenderEngine::GetInstance().transformBlockWidth(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformStripeNum(JNIEnv* env,jclass obj,jint jfloatY)
{
    RenderEngine::GetInstance().transformStripe_num(jfloatY);
}JNIEXPORT void JNICALL Java_com_example_blend_JNILib_transformBlockNum(JNIEnv* env,jclass obj,jint jfloatY)
{
    RenderEngine::GetInstance().transformBlockNum(jfloatY);
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_shutDown(JNIEnv* env,jclass obj)
{
    RenderEngine::GetInstance().shutDown();
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_step(JNIEnv *env, jclass obj) {
    RenderEngine::GetInstance().renderFrame();
}
JNIEXPORT void JNICALL Java_com_example_blend_JNILib_genTextureId(JNIEnv *env, jclass obj,jint idNum,jstring jpath) {
    char *path=(char*)env->GetStringUTFChars(jpath, 0);
    RenderEngine::GetInstance().genTextureId(idNum,path);
    Bridge_LOGE("id数量%i",idNum);

}

JNIEXPORT void JNICALL
Java_com_example_blend_JNILib_setTextureBitmap(JNIEnv *env, jclass obj, jobject jbitmap,jint textureIndex) {
    Bridge_LOGE("Java_com_example_blend_JNILib_setTextureBimap");
    int ret = 0;
    AndroidBitmapInfo bitmapInfo;
    void *pixels = NULL;
    int imgWidth = 2;
    int imgHeight = 2;

    if ((ret = AndroidBitmap_getInfo(env, jbitmap, &bitmapInfo)) < 0) {
        Bridge_LOGE("AndroidBitmap_getInfo error");
    }

    imgWidth = bitmapInfo.width;
    imgHeight = bitmapInfo.height;

    if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Bridge_LOGE("Java_com_example_hellojni_HelloJni_showBitmap invalid rgb format");
    }


    if ((ret = AndroidBitmap_lockPixels(env, jbitmap, &pixels)) < 0) {
        Bridge_LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

//    Imp& imp_ = *RenderEngine::GetInstance().mImpUPtr;
    RenderEngine::GetInstance().createTexture(textureIndex,(unsigned char *) pixels,imgWidth, imgHeight);

    AndroidBitmap_unlockPixels(env, jbitmap);
} ;
}

//JNIEXPORT void JNICALL
//Java_com_example_blend_JNILib_setTextureBitmap(JNIEnv *env, jclass obj, jobject jbitmap1,
//                                                     jobject jbitmap2) {
//    Bridge_LOGE("Java_com_example_blend_JNILib_setTextureBimap");
//
//    int ret = 0;
//    AndroidBitmapInfo bitmapInfo1;
//    void *pixels1 = NULL;
//    AndroidBitmapInfo bitmapInfo2;
//    void *pixels2 = NULL;
//    int imgWidth = 2;
//    int imgHeight = 2;
//
//    if ((ret = AndroidBitmap_getInfo(env, jbitmap1, &bitmapInfo1)) < 0) {
//        Bridge_LOGE("AndroidBitmap_getInfo error");
//    }
//    if ((ret = AndroidBitmap_getInfo(env, jbitmap2, &bitmapInfo2)) < 0) {
//        Bridge_LOGE("AndroidBitmap_getInfo error");
//    }
//
//    imgWidth = bitmapInfo1.width;
//    imgHeight = bitmapInfo1.height;
//
//    if (bitmapInfo1.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
//        Bridge_LOGE("Java_com_example_hellojni_HelloJni_showBitmap invalid rgb format");
//    }
//    if (bitmapInfo2.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
//        Bridge_LOGE("Java_com_example_hellojni_HelloJni_showBitmap invalid rgb format");
//    }
//
//    if ((ret = AndroidBitmap_lockPixels(env, jbitmap1, &pixels1)) < 0) {
//        Bridge_LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
//    }
//    if ((ret = AndroidBitmap_lockPixels(env, jbitmap2, &pixels2)) < 0) {
//        Bridge_LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
//    }
//
////    Imp& imp_ = *RenderEngine::GetInstance().mImpUPtr;
//    RenderEngine::GetInstance().createTexture((unsigned char *) pixels1, (unsigned char *) pixels2,
//                                              imgWidth, imgHeight);
//
//    AndroidBitmap_unlockPixels(env, jbitmap1);
//    AndroidBitmap_unlockPixels(env, jbitmap2);
//} ;
//}

//JNIEXPORT void JNICALL
//Java_com_example_blend_JNILib_setTextures(JNIEnv *env, jobject obj, jintArray texture) {
//    auto mTexture = (GLuint *) env->GetIntArrayElements(texture, 0);
//    RenderEngine::GetInstance().setTexture(*mTexture);
//}

//JNIEXPORT void JNICALL
//Java_com_example_blend_JNILib_setTextureData(JNIEnv *env, jobject obj, int col, int row,
//                                                    jintArray textureData) {
//    Bridge_LOGE("Java_com_example_blend_JNILib_setTextureData");
//
//    jint *cbuf;
//    cbuf = env->GetIntArrayElements(textureData, NULL);
//    RenderEngine::GetInstance().createTexture((unsigned char *) cbuf1, (unsigned char *) cbuf2, col,
//                                              row);
//}