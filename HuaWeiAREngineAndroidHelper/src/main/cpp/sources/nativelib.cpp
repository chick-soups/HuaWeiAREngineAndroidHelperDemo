#include <jni.h>
#include <string>
#include <android/log.h>
#include "CameraHelper.h"
#if __cplusplus
extern "C"{
#endif

JNIEXPORT jobject JNICALL
Java_com_puremilk_nativelib_NativeLib_GetBestPreviewSize(JNIEnv *env, jobject thiz,
                                                         jobject target_size) {
    jclass Vector2IntJClass = env->FindClass("com/puremilk/nativelib/Vector2Int");
    jfieldID xField = env->GetFieldID(Vector2IntJClass,"x","I");
    jfieldID yField = env->GetFieldID(Vector2IntJClass,"y","I");

    Vector2Int targetSize{env->GetIntField(target_size,xField),env->GetIntField(target_size,yField)},outSize{};
    CameraHelper_GetBestPreviewSize(&targetSize,&outSize);
    jobject vector2IntJObject = env->AllocObject(Vector2IntJClass);
    env->SetIntField(vector2IntJObject,xField,outSize.x);
    env->SetIntField(vector2IntJObject,yField,outSize.y);
    return  vector2IntJObject;
}
#if __cplusplus
}
#endif