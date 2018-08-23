package com.hzw.android;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Jni jni = new Jni();
        TextView textView = findViewById(R.id.tv);
        textView.setText(jni.getKey(this));
    }
}
