package com.example.testapp;

import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import java.util.Date;
import java.util.Random;

/**
 * JNI访问Java成员变量
 * JNI访问Java静态变量
 * JNI访问Java非静态方法
 * JNI访问Java静态方法
 * JNI访问Java构造方法
 *
 * JNI获取类的成员变量的ID调用GetFieldID获取，通过Set[类型]Field修改变量值。
 * JNI获取类的成员变量的ID调用GetStaticFieldID获取，通过SetStatic[类型]Field修改变量值。
 * JNI获取类的方法的ID调用GetMethodID获取，通过Call[类型]Method调用方法。
 * JNI获取类的静态方法的ID调用GetStaticMethodID获取，通过CallStatic[类型]Method调用方法。
 * JNI获取类的构造方法的ID调用GetMethodID获取，通过NewObject构造，构造函数名为"<init>"。
 *
 *
 */
public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("hello-ndk");
    }

    // 首先定义变量showText
    public String showText = "Hello World";
    private static String staticString = "static string";

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //添加下面两行代码
        TextView show = findViewById(R.id.tv_test);
        show.setText(helloNDK());

        // TODO JNI访问Java成员变量
        // 调用验证结果：
        TextView accessFiledShow = findViewById(R.id.tv_access_filed_show);
        String res = "before: " + showText;
        //通过ndk 修改成员变量
        accessField();
        res += ", after:" + showText;
        accessFiledShow.setText(res);

        // TODO JNI访问Java静态变量
        // 同上添加静态属性和 native方法:

        TextView accessStaticFiledShow = findViewById(R.id.tv_static_access_filed_show);
        res = "before: " + staticString;
        //通过ndk 修改静态变量
        accessStaticField();
        res += ", after:" + staticString;
        accessStaticFiledShow.setText(res);

        // todo JNI访问Java非静态方法
        TextView tvName = findViewById(R.id.tv_auth_name);
        res = "authName = " + accessMethod();
        tvName.setText(res);

        // todo JNI访问Java静态方法
        TextView staticMethodShow = findViewById(R.id.tv_static_method_show);
        res = "accessStaticMethod(100) = " + accessStaticMethod(100);
        staticMethodShow.setText(res);

        // todo JNI访问Java构造方法
        TextView staticConstShow = findViewById(R.id.tv_const_show);
        res = accessConstructor().toString();
        staticConstShow.setText(res);

    }

    public native Date accessConstructor();


    public native String helloNDK();

    // 添加native方法accessField()：
    public native void accessField();

    public native void accessStaticField();

    public String getAuthName(String name) {
        Log.e(TAG, "name = " + name);
        return name;
    }

    public native String accessMethod();

    private static int getRandomValue(int max) {
        return new Random().nextInt(max);
    }

    public native int accessStaticMethod(int max);

}
