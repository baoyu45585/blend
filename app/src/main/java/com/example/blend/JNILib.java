package com.example.blend;

import android.content.res.AssetManager;
import android.graphics.Bitmap;


public class JNILib {
    static {
        System.loadLibrary("jinlib");
    }

    public static native void init(int width, int height,AssetManager assetMgr);
    public static native void step();
//    public static native void setTextures(int[] textureID);
//    public static native void setTextureData(int col,int row,int[] pix);
    public static native void setTextureBitmap(Bitmap bitmap1,int index);
    public static native void setTextureByte(byte[] data,int index,int w,int h);
    public static native void genTextureId(int idNum,String path);
    public static native void transformT(float fy);
    public static native void transformFRadius(float fy);
    public static native void transformZoomIn(float fy);
    public static native void transformHoldTime(float fy);
    public static native void transformStrength(float fy);
    public static native void transformWaveWidth(float fy);
    public static native void transformSmoothness(float fy);
    public static native void transformBlockWidth(float fy);
    public static native void transformDistance(float fy);
    public static native void transformArrowCount(float fy);
    public static native void transformStripeNum(int fy);
    public static native void transformBlockNum(int fy);
    public static native void transformSizeScale(float fy);
    public static native void transformJitterY(float fy);
    public static native void transformBlurRadius(float fy);
    public static native void transformType(int fy);
    public static native void transformTime2(float fy);
    public static native void shutDown();
}
