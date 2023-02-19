//
// Created by zhouxuhua on 2023/2/17.
//

#ifndef CAMERA_HELPER_202302171709_H
#define CAMERA_HELPER_202302171709_H
#if __cplusplus
extern "C"{
#endif
__declspec(dllexport)  typedef struct Vector2Int{
    public:
        int x;
        int y;
    } Vector2Int;

__declspec(dllexport) void CameraHelper_GetBestPreviewSize(const Vector2Int *targetSize,Vector2Int *outSize);
#if __cplusplus
}
#endif
#endif //CAMERA_HELPER_202302171709_H
