package com.example.testapp;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;

import com.blankj.utilcode.util.ToastUtils;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.content.ContextCompat;

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

        // todo JNI操作Java数组
        new JniArrayOperation().test();

        /**
         * todo JNI实现文件加解密
         编写测试代码
         实现创建文件逻辑
         实现JNI加密逻辑
         实现JNI解密逻辑
         执行测试代码

         执行程序会在 手机根目录 生成以下三个文件：
         testJni.txt：原文件
         encryption_testJni.txt：加密之后的文件
         decryption_testJni.txt：解密之后的文件

         确实在手机存储的位置发现3个文件，ok;
         */
        testEncryptor();

        /**
         * JNI实现文件拆分和合并
         编写测试代码
         实现创建文件逻辑
         实现JNI文件拆分逻辑
         实现JNI文件合并逻辑
         执行测试代码
         */
        testFileOperation();
    }

    private void testFileOperation() {
        if (hasFilePermission()) {
            new JniFileOperation().test();
            ToastUtils.showShort("任务完成，测试文件路径:" + Config.getBaseUrl());
        }
    }

    /**
     * 申请权限
     */
    private boolean hasFilePermission() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0x1024);
                return false;
            }
        }
        return true;
    }

    private void testEncryptor() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0x1024);
                return;
            }
        }
        new Encryptor().test();
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
