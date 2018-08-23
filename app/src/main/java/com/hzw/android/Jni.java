package com.hzw.android;

import android.content.Context;

/**
 * Created by huzw on 2018/8/22.
 */

public class Jni {

    static {
        System.loadLibrary("jni");
    }

    public native  String getKey(Context context);
}
