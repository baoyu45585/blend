package com.example.blend;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.util.Log;


import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyRender implements GLSurfaceView.Renderer {

    private static final String TAG = "TextureBlendRender";
    private final Context context;
    private int[] textureID = new int[1];
    private String path;
    private Bitmap bitmap1;
    private Bitmap bitmap2;
    private Bitmap bitmap3;
    private Bitmap bitmap4;
    private int col;
    private int row;
    private int[] pix;
    private int i=1;
    private long curTime;
    private long cosTime;
    private OnCallBackListener onCallBackListener;



    public MyRender(Context context, String path) {
        this.context = context;
        this.path = path;
        if (path.equals("tilt_shift_lens")) {
            bitmap1 = loadBitmap(context, R.drawable.a4);
        }
        else {
            bitmap1 = loadBitmap(context, R.drawable.a1);
        }
        if (path.equals("star_mirror")){
            bitmap2 = loadBitmap(context, R.drawable.a3);
            Log.e(TAG, "TextureBlendRender: 星星图" );
        }else if(path.equals("final")){
            bitmap2 = loadBitmap(context, R.drawable.the_end);
        }else if(path.equals("snow")){
            bitmap2 = loadBitmap(context, R.drawable.a2);
            bitmap3 = loadBitmap(context, R.drawable.snow2);
            bitmap4 = loadBitmap(context, R.drawable.snow1);
        }else if(path.equals("dispersion_switch")){
            bitmap1 = loadBitmap(context, R.drawable.dis1);
            bitmap2 = loadBitmap(context, R.drawable.dis2);
            bitmap3 = loadBitmap(context, R.drawable.dis3);
        }else {
            bitmap2 = loadBitmap(context, R.drawable.a2);
        }
        col = bitmap1.getWidth();
        row = bitmap1.getHeight();
        pix = new int[col * row];
    }

    public void onDrawFrame(GL10 gl) {
        long start = System.currentTimeMillis();
        JNILib.step();
        long end = System.currentTimeMillis();
        long costTime = end - start;
        Log.d("costtime = " , String.valueOf(costTime));

//        cosTime=System.currentTimeMillis()-curTime;
//        curTime=System.currentTimeMillis();
        onCallBackListener.onCallBack(costTime);
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        //JNILib.setTextureData(col,row,pix);
        Log.e(TAG, "onSurfaceChanged: "+width+height );

        JNILib.init(width, height, context.getResources().getAssets());
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        //setTextureObjID();
        //bitmap.getPixels(pix,0,col,0,0,col,row);
//        if (path.equals("water_drop")||path.equals("star_mirror")){
        if(path.equals("snow")){
            i=4;
            JNILib.genTextureId(i,path);
            JNILib.setTextureBitmap(bitmap1,0);
            JNILib.setTextureBitmap(bitmap2,1);
            JNILib.setTextureBitmap(bitmap3,2);
            JNILib.setTextureBitmap(bitmap4,3);
        }
        else if (path.equals("dispersion_switch")){
            i=3;
            JNILib.genTextureId(i,path);
            JNILib.setTextureBitmap(bitmap1,0);
            JNILib.setTextureBitmap(bitmap2,1);
            JNILib.setTextureBitmap(bitmap3,3);
        }else {
            i=2;
            JNILib.genTextureId(i,path);
            JNILib.setTextureBitmap(bitmap1,0);
            JNILib.setTextureBitmap(bitmap2,1);}
//        }
//        for (int j=0;j<i;j++){
//
//        }
    }

//    private void setTextureObjID() //设置纹理ID的方式
//    {
//        Bitmap bitmap = loadBitmap(context,R.drawable.wall);
//
//        glGenTextures(1,textureID,0);
//        if (textureID[0] == 0) {
//            Log.e(TAG, "Could not generate a new OpenGL texture object.");
//            return ;
//        }
//
//        glBindTexture(GL_TEXTURE_2D,textureID[0]);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        texImage2D(GL_TEXTURE_2D, 0, bitmap, 0);
//
//        glGenerateMipmap(GL_TEXTURE_2D);
//        bitmap.recycle();
//
//        JNILib.setTextures(textureID);
//
//        // Unbind from the texture.
//        glBindTexture(GL_TEXTURE_2D, 0);
//    }

    private static Bitmap loadBitmap(Context context, int resID) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;

        final Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), resID, options);

        if (bitmap == null) {
            Log.e(TAG, "loadBitmap failed!");
        }

        return bitmap;
    }
    public interface OnCallBackListener {
        void onCallBack(long position);
    }
    public void setOnCallBackListener(OnCallBackListener callBackListener) {
        this.onCallBackListener = callBackListener;
    }
}
