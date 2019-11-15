package com.example.testapp;

// 创建JniArrayOperation类，编写对应的测试代码：
public class JniArrayOperation {
    static {
        System.loadLibrary("array_operation");
    }
    public native int[] getIntArray(int length);

    public native void sortIntArray(int[] arr);

    public void test() {
        //获取随机的20个数
        int[] array = getIntArray(20);
        for (int i : array) {
            System.out.print(i + ", ");
        }
        System.out.println();
        //对数组进行排序
        sortIntArray(array);
        System.out.println("After sort:");
        for (int i : array) {
            System.out.print(i + ", ");
        }
        System.out.println();

        // 打印结果:
        // System.out: 18, 87, 91, 23, 17, 65, 14, 97, 19, 66, 92, 54, 8, 54, 50, 56, 68, 19, 61, 39,
        // System.out: After sort:
        // System.out: 8, 14, 17, 18, 19, 19, 23, 39, 50, 54, 54, 56, 61, 65, 66, 68, 87, 91, 92, 97,
    }
}

