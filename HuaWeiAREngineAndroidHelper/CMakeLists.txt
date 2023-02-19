

cmake_minimum_required(VERSION 3.18.1)

project("HuaWeiAREngineAndroidHelper")

add_library(HuaWeiAREngineAndroidHelper SHARED
        src/main/cpp/sources/nativelib.cpp
        )
add_library(HuaWeiAREngineAndroidHelper_ndk SHARED
        src/main/cpp/sources/CameraHelper.cpp
        )

target_include_directories(HuaWeiAREngineAndroidHelper PRIVATE
                           src/main/cpp/includes)
target_include_directories(HuaWeiAREngineAndroidHelper_ndk PRIVATE
        src/main/cpp/includes)

target_link_libraries(HuaWeiAREngineAndroidHelper
        log
        android
        HuaWeiAREngineAndroidHelper_ndk
        )
target_link_libraries(HuaWeiAREngineAndroidHelper_ndk
        log
        android
        camera2ndk
        mediandk
        )