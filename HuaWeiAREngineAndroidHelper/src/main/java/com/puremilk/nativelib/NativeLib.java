package com.puremilk.nativelib;

public class NativeLib {

    // Used to load the 'nativelib' library on application startup.
    static {
        System.loadLibrary("HuaWeiAREngineAndroidHelper");
    }

    public native Vector2Int GetBestPreviewSize(Vector2Int targetSize);
}