//
// Created by zhouxuhua on 2023/2/17.
//
#include <string>
#include <camera/NdkCameraManager.h>
#include <android/log.h>
#include <camera/NdkCameraMetadataTags.h>
#include <camera/NdkCameraError.h>
#include <media/NdkImage.h>
#include "CameraHelper.h"
#include <vector>

void CameraHelper_GetBestPreviewSize(const Vector2Int *targetSize,Vector2Int *outSize) {
    if(targetSize->x<=0||targetSize->y<=0){
        throw "=CameraHelper_GetBestPreviewSize:width or height is less than 0!";
    }
    ACameraManager *aCameraManager = ACameraManager_create();
    ACameraIdList *aCameraIdList{};
    camera_status_t cameraStatus =  ACameraManager_getCameraIdList(aCameraManager, &aCameraIdList);
    if(cameraStatus==camera_status_t::ACAMERA_OK)
    {
        int camNums = aCameraIdList->numCameras;
        const char **cameraIds = aCameraIdList->cameraIds;
        for (int i = 0; i < camNums; i++) {
            const char *camId = cameraIds[i];
            ACameraMetadata *cameraMetadata{};
            ACameraManager_getCameraCharacteristics(aCameraManager,camId,&cameraMetadata);
            ACameraMetadata_const_entry streamConfig{};
            ACameraMetadata_getConstEntry(cameraMetadata,acamera_metadata_tag::ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS,&streamConfig);

            long curRect=LONG_MAX;
            float curRatioDelta=MAXFLOAT;
            float  targetRatio=static_cast<float>(targetSize->y) / static_cast<float>(targetSize->x);
            for (int j=0;j<streamConfig.count;j+=4){
                if(streamConfig.data.i32[j]==AIMAGE_FORMAT_JPEG){
                    __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "zxh","streamconfig ---- config%d :[%d,%d,%d,%d]",j,streamConfig.data.i32[j],streamConfig.data.i32[1+j],streamConfig.data.i32[2+j],streamConfig.data.i32[3+j]);
                    int width= streamConfig.data.i32[1+j];
                    int height=streamConfig.data.i32[2+j];
                    long  rect=( width- targetSize->x)*(height- targetSize->y);
                    if(rect<0){
                        rect=-rect;
                    }else if(rect==0){
                        float  ratio=static_cast<float>(height)/static_cast<float>(width);
                        float ratioDelta = abs(ratio-targetRatio);
                        __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "zxh","ratioDelta:%f,curDelta:%f",ratioDelta,curRatioDelta);
                        if(ratioDelta<curRatioDelta){
                          outSize->x=width;
                          outSize->y=height;
                          curRect=rect;
                          curRatioDelta=ratioDelta;
                          __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "zxh","ratioDelta");
                          continue;

                        }
                    }
                    if(rect<curRect){
                        outSize->x=width;
                        outSize->y=height;
                        curRect=rect;
                        __android_log_print(android_LogPriority::ANDROID_LOG_DEBUG, "zxh","Rect");
                    }
                }
            }
        }
        ACameraManager_deleteCameraIdList(aCameraIdList);
        ACameraManager_delete(aCameraManager);
    };


}