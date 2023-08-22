package com.example.blend;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;

import java.util.concurrent.TimeUnit;

import io.reactivex.Observable;
import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;


public class TextureActivity extends Activity implements MyRender.OnCallBackListener{
    private static final String TAG = "TriangleActivity";
    private MyGLSurfaceView mView;
    private SeekBar seekBarTime;
    private SeekBar seekBarStrength;
    private SeekBar seekBarWidth;
    private SeekBar seekBarDimWidth;
    private SeekBar seekBarStarCount;
    private SeekBar seekBarFRadius;
    private SeekBar seekBarHoldTime;
    private SeekBar seekBarZoomIn;
    private SeekBar seekBarArrowCount;
    private SeekBar seekBarSmoothness;
    private SeekBar seekBarDistance;
    private SeekBar seekBarStripeNum;
    private SeekBar seekBarBlockNum;
    private SeekBar seekBarBlockWidth;
    private SeekBar seekBarSizeScale;
    private SeekBar seekBarBlurRadius;
    private SeekBar seekBarJitterY;
    private SeekBar seekBarType;
    private SeekBar seekBarTime2;
    private TextView tvTime,tvblurWidth,tvStrenth,tvTime2,tvWaveWidth,tvHoldTime,tvRadius,tvZoomIn,tvArrowCount,tvDistance,tvSmoothness,tvStripeNum,tvBlockNum,tvBlockWidth,tvSizeScale,tvJitterY,tvBlurRadius,tvCosTime,tvType;
//    private Button replay;
    String path = "";
    MyRender myRender;
    private static Disposable mDisposable;
    @Override
    protected void onCreate(Bundle saveInstanceState) {
        super.onCreate(saveInstanceState);
        setContentView(R.layout.activity_show);
        mView = (MyGLSurfaceView) findViewById(R.id.mGLSurfaceView);
        path = getIntent().getStringExtra("path");
        myRender=new MyRender(this, path);
        myRender.setOnCallBackListener(this);
        mView.setRenderer(myRender);
        mView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        seekBarTime = (SeekBar) findViewById(R.id.seekBarTime);
        seekBarHoldTime = (SeekBar) findViewById(R.id.seekBarHoldTime);
        seekBarFRadius = (SeekBar) findViewById(R.id.seekBarFRadius);
        seekBarStarCount= (SeekBar) findViewById(R.id.seekBarStarCount);
        seekBarZoomIn= (SeekBar) findViewById(R.id.seekBarZoomIn);
        seekBarStrength = (SeekBar) findViewById(R.id.seekBarStrength);
        seekBarWidth = (SeekBar) findViewById(R.id.seekBarWidth);
        seekBarArrowCount = (SeekBar) findViewById(R.id.seekBarArrowCount);
        seekBarSmoothness = (SeekBar) findViewById(R.id.seekBarSmoothness);
        seekBarDistance = (SeekBar) findViewById(R.id.seekBarDistance);
        seekBarStripeNum = (SeekBar) findViewById(R.id.seekBarStripeNum);
        seekBarBlockNum = (SeekBar) findViewById(R.id.seekBarBlockNum);
        seekBarBlockWidth = (SeekBar) findViewById(R.id.seekBarBlockWidth);
        seekBarSizeScale = (SeekBar) findViewById(R.id.seekBarSizeScale);
        seekBarBlurRadius = (SeekBar) findViewById(R.id.seekBarBlurRadius);
        seekBarJitterY = (SeekBar) findViewById(R.id.seekBarJitterY);
        seekBarType = (SeekBar) findViewById(R.id.seekBarType);
        seekBarTime2 = (SeekBar) findViewById(R.id.seekBarTime2);

        tvTime=findViewById(R.id.tvTime);
        tvCosTime=findViewById(R.id.tvCosTime);
        tvArrowCount=findViewById(R.id.tvArrowCount);
       // tvblurWidth=findViewById(R.id.tvblurWidth);
        tvZoomIn = findViewById(R.id.tvZoomIn);
        tvStrenth=findViewById(R.id.tvStrenth);
        tvRadius=findViewById(R.id.tvFRadius);
        tvHoldTime=findViewById(R.id.tvHoldTime);
        tvWaveWidth=findViewById(R.id.tvWaveWidth);
        tvDistance=findViewById(R.id.tvDistance);
        tvSmoothness=findViewById(R.id.tvSmoothness);
        tvStripeNum=findViewById(R.id.tvStripeNum);
        tvBlockNum=findViewById(R.id.tvBlockNum);
        tvBlockWidth=findViewById(R.id.tvBlockWidth);
        tvSizeScale=findViewById(R.id.tvSizeScale);
        tvJitterY=findViewById(R.id.tvJitterY);
        tvBlurRadius=findViewById(R.id.tvBlurRadius);
        tvTime2=findViewById(R.id.tvTime2);
        tvType=findViewById(R.id.tvType);
        showSeekBar(path);
        seekBarTime.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvTime.setText("转场时长:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress() < 10 ? 10 : seekBar.getProgress();
                Log.e(TAG, "onStopTrackingTouch 时长: "+progress );

                if (path.equals("lr_close") || path.equals("lr_open")||path.equals("up_down_close")||path.equals("up_down_open")) {
                    JNILib.transformT(progress * 30f);
                }
                else if(path.equals("snow")){
                    JNILib.transformT(progress * 51f);

                }else {
//                    JNILib.transformT(progress * 80f);
                    JNILib.transformT(progress * 23f);
                }
            }
        });
        seekBarZoomIn.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvZoomIn.setText("放大倍数:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformZoomIn(seekBar.getProgress() / 100f);
            }
        });seekBarTime2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvTime2.setText("模糊速度:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformTime2(seekBar.getProgress() / 100f);
            }
        });seekBarSizeScale.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvSizeScale.setText("颗粒大小:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformSizeScale(seekBar.getProgress() / 200f);
            }
        });seekBarBlurRadius.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvBlurRadius.setText("模糊半径:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformBlurRadius(seekBar.getProgress() / 1f);
            }
        });seekBarJitterY.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvJitterY.setText("波线程度:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformJitterY(seekBar.getProgress() / 100f);
            }
        });
        seekBarStripeNum.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvStripeNum.setText("彩条个数:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformStripeNum(seekBar.getProgress());
            }
        });
        seekBarBlockNum.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvBlockNum.setText("切割个数:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int process=seekBar.getProgress();
                if (path.equals("cut_horizontal")){
                    if (process<7){
                        process=7;
                    }
                }else {
                    if (process>20){
                        process=20;
                    }
                }
                JNILib.transformBlockNum(process);
            }
        });
        seekBarArrowCount.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvArrowCount.setText("箭头个数:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformArrowCount(seekBar.getProgress()/1f);
            }
        });
        seekBarBlockWidth.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvBlockWidth.setText("像素大小:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformBlockWidth(seekBar.getProgress()/100f);
            }
        });

        seekBarFRadius.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvRadius.setText("圆圈半径:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformFRadius(0.4f+(100-seekBar.getProgress()) * 0.004f);
            }
        });

        seekBarHoldTime.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvHoldTime.setText("停留时间:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                JNILib.transformHoldTime(0.2f+seekBar.getProgress()*0.01f);
            }
        });
//        seekBarStarCount.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
//            @Override
//            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
//                tvTime.setText("星星数量:"+i+"%");
//            }
//
//            @Override
//            public void onStartTrackingTouch(SeekBar seekBar) {
//
//            }
//
//            @Override
//            public void onStopTrackingTouch(SeekBar seekBar) {
////                int progress = seekBar.getProgress() < 10 ? 10 : seekBar.getProgress();
//                JNILib.transformStarCount(seekBar.getProgress() /100f);
//            }
//        });
        seekBarWidth.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvWaveWidth.setText("波长:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
//                float progress=0.2f+seekBar.getProgress()/ 100f<0.8?(0.2f+seekBar.getProgress()/ 100f):0.8f;
                JNILib.transformWaveWidth(seekBar.getProgress()/100f);
            }
        });
        seekBarStrength.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvStrenth.setText("强度:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                JNILib.transformStrength(progress / 100f);
            }
        });
        seekBarSmoothness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvSmoothness.setText("切换快慢:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                JNILib.transformSmoothness(progress / 100f);
            }
        });
        seekBarDistance.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvDistance.setText("振幅:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                JNILib.transformDistance(progress / 1000f);
            }
        });seekBarType.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tvType.setText("预设效果:"+i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                int progress = seekBar.getProgress();
                JNILib.transformType(progress);
            }
        });
//每隔25毫秒调用一次渲染

       Observable
                .interval(25, TimeUnit.MILLISECONDS)
                .subscribeOn(AndroidSchedulers.mainThread())
                .subscribe(new Observer<Long>() {
                    @Override
                    public void onSubscribe(Disposable d) {
                        mDisposable=d;
                    }

                    @Override
                    public void onNext(Long aLong) {
                        mView.requestRender();
                    }

                    @Override
                    public void onError(Throwable e) {

                    }

                    @Override
                    public void onComplete() {

                    }
                });

    }

    void showSeekBar(String path) {
        if (path.equals("soft_light")) {
            findViewById(R.id.llStrength).setVisibility(View.VISIBLE);
        }if (path.equals("lr_close") || path.equals("lr_open") || path.equals("impact") || path.equals("RGB_to_gray")|| path.equals("gray_to_RGB") || path.equals("color_insert")||path.equals("water_drop")||path.equals("dissolve")||path.equals("up_down_close")||path.equals("up_down_open")||path.equals("up_down_hold")||path.equals("rotate")||path.equals("arrow_switch")||path.equals("dispersion_switch")||path.equals("mosaic")||path.equals("color_stripe")||path.equals("cut_horizontal")||path.equals("cut_vertical")||path.equals("cut_zoom")||path.equals("snow")||path.equals("blur_line")||path.equals("cut")||path.equals("lr_blur")) {
            findViewById(R.id.llTime).setVisibility(View.VISIBLE);
        }if (path.equals("water_drop")) {
            findViewById(R.id.llWidth).setVisibility(View.VISIBLE);
        }if (path.equals("tilt_shift_lens")){
          //  findViewById(R.id.llDimWidth).setVisibility(View.VISIBLE);
        }if (path.equals("star_mirror")){
            findViewById(R.id.llTransformStarCount).setVisibility(View.VISIBLE);
        }if (path.equals("final")){
            findViewById(R.id.llTransformFRadius).setVisibility(View.VISIBLE);
            findViewById(R.id.llTransformHoldTime).setVisibility(View.VISIBLE);
        }if (path.equals("impact")){
            findViewById(R.id.llTransformZoomIn).setVisibility(View.VISIBLE);
        }if (path.equals("arrow_switch")) {
            findViewById(R.id.llTransformArrowCount).setVisibility(View.VISIBLE);
        }if (path.equals("dispersion_switch")) {
            findViewById(R.id.llTransformDistance).setVisibility(View.VISIBLE);
            findViewById(R.id.llTransformSmoothness).setVisibility(View.VISIBLE);
        }if (path.equals("color_stripe")) {
            findViewById(R.id.llTransformStripeNum).setVisibility(View.VISIBLE);
        }if (path.equals("cut_horizontal")||path.equals("cut_vertical")) {
            findViewById(R.id.llTransformBlockNum).setVisibility(View.VISIBLE);
        }if (path.equals("mosaic")) {
            findViewById(R.id.llTransformBlockWidth).setVisibility(View.VISIBLE);
        }if (path.equals("snow")) {
            findViewById(R.id.llTransformSizeScale).setVisibility(View.VISIBLE);
        }if (path.equals("blur_line")) {
            findViewById(R.id.llTransformBlurRadius).setVisibility(View.VISIBLE);
            findViewById(R.id.llTransformJitterY).setVisibility(View.VISIBLE);
        }if (path.equals("cut")) {
            findViewById(R.id.llTransformType).setVisibility(View.VISIBLE);
        }if (path.equals("lr_blur")) {
            findViewById(R.id.llTransformTime2).setVisibility(View.VISIBLE);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        JNILib.shutDown();
        if(mDisposable!=null&&!mDisposable.isDisposed()){
            mDisposable.dispose();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
        if(mDisposable!=null&&!mDisposable.isDisposed()){
            mDisposable.dispose();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    @Override
    public void onCallBack(long cosTime) {
        Log.e(TAG, "onCallBack: "+cosTime);
        tvCosTime.setText("耗时："+cosTime+"毫秒");
    }
}
