package com.puremilk.arenginecameredemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.util.Size;
import android.view.Surface;
import android.view.Window;
import android.view.WindowManager;

import com.puremilk.nativelib.Vector2Int;
import com.unity3d.player.UnityPlayer;
import com.puremilk.nativelib.NativeLib;

public class MainActivity extends AppCompatActivity {
    private final String TAG="MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NativeLib nativeLib=new NativeLib();
        Vector2Int bestSize =   nativeLib.GetBestPreviewSize(new Vector2Int(1100,720));
        Log.d(TAG, "onCreate: TargetSize"+bestSize.x+" "+bestSize.y);
//        CameraManager cameraManager =   (CameraManager)UnityPlayer.currentActivity.getSystemService(Context.CAMERA_SERVICE);
//        try{
//            String[] cameraIdList =  cameraManager.getCameraIdList();
//            for (int i=0;i<cameraIdList.length;i++){
//                Log.i(TAG, "onCreate: Camera ID:"+cameraIdList[i]);
//                CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(cameraIdList[i]);
//                StreamConfigurationMap sMap = cameraCharacteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
//                Size[] sizes =  sMap.getOutputSizes(SurfaceTexture.class);
//                Size targetSize =   ChoseSize(sizes,new Size(1100,720));
//
//                Log.d(TAG, "onCreate: TargetSize"+targetSize);
//
//            }
//        }catch (Exception e){
//            Log.e(TAG, "onCreate: "+e.getMessage());
//        }

    }

    private Size ChoseSize(Size[] sizes,Size target)
    {
        long curDelta=Long.MAX_VALUE;
        float curRatio=Float.MAX_VALUE;
        int index=0;
        float targetRatio=target.getHeight()/target.getWidth();
       for (int i=0;i<sizes.length;i++){
           Log.i(TAG, "ChoseSize: "+sizes[i].toString());
           long delta =  (sizes[i].getWidth()-target.getWidth())*(sizes[i].getHeight()-target.getHeight());
           if(delta==0){
               if(curDelta==0){
                   float ratio=sizes[i].getHeight()/sizes[i].getWidth();
                   float deltaRotio=ratio-targetRatio;
                   deltaRotio=deltaRotio<0?-deltaRotio:deltaRotio;
                   if(deltaRotio<curRatio){
                       index=i;
                       curRatio=deltaRotio;
                       continue;

                   }

               }

           }else if(delta<0)
           {
               delta=-delta;
           }

           if(delta<curDelta){
               curDelta=delta;
               index=i;

           }
       }
       return sizes[index];
    }
}