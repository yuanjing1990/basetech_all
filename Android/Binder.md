# Binder理解

## 简述
- Binder 通信采用 C/S 架构，从组件视角来说，包含 Client、 Server、 ServiceManager 以及 Binder 驱动，其中 ServiceManager 用于管理系统中的各种服务。
- Binder 在 framework 层进行了封装，通过 JNI 技术调用 Native（C/C++）层的 Binder 架构。
- Binder 在 Native 层以 ioctl 的方式与 Binder 驱动通讯。
--------------------- 
![基本结构][binder_layer_graph]

代码位置

- kernel层
```
/kernel/drivers/android/binder.c
/kernel/include/uapi/linux/android/binder.h
```
- Native层
```
/frameworks/native/libs/binder/*
```
- JNI层
```
/frameworks/base/core/jni/android_util_Binder.h
/frameworks/base/core/jni/android_util_Binder.cpp
```
- Framework层
```
/frameworks/base/core/java/android/os/Binder.java
```

[binder_layer_graph]: https://img-blog.csdn.net/20170411180827946?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZnJlZWtpdGV5dQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast