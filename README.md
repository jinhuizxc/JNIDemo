# JNIDemo

* 部分参考:
- [JNI相关配置javah,ndk-build和指令集以及.mk文件详细讲解(亲测可用)](https://blog.csdn.net/liuxu841911548/article/details/53931490)
- [android studio javah 配置](https://blog.csdn.net/qq_22703355/article/details/79907232)
```
name:javah$JDKPath$\bin\javah.exe
program:
parameters:-classpath . -jni -d $ModuleFileDir$/src/main/jni $FileClass$
working directory:$ModuleFileDir$\src\main\java
```

### 系列文章
- [NDK开发文章汇总](https://www.jianshu.com/p/b18426df68f8)
- [NDK学习demo](https://github.com/103style/NDKDoc)