package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // 应用的MainActivity 会使用System.loadLibrary()加载原生库
    static {
        System.loadLibrary("native-lib");
    }

    // 首先定义变量showText
    public String showText = "Hello World";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }

    /**
     * MainActivity.onCreate() 调用 stringFromJNI()，
     * 后者返回“来Hello from C++”，并使用它来更新 TextView。
     */
    public native String stringFromJNI();

    /**
     *  添加native方法accessField()：
     */
    public native void accessField();

}
