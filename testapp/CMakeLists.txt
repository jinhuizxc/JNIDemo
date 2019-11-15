cmake_minimum_required(VERSION 3.4.1)

add_library( hello-ndk
             SHARED
             src/main/cpp/hello-ndk.cpp)


find_library( log-lib # 库路径的变量名
              log ) # 对应的库名

#将预构建库关联到您自己的原生库
target_link_libraries( hello-ndk
                       ${log-lib} )

add_library( array_operation
        SHARED
        src/main/cpp/array_operation.cpp)
target_link_libraries( hello-ndk array_operation
        ${log-lib} )

add_library(encryptor
        SHARED
        src/main/cpp/encryptor.cpp)
target_link_libraries(
        encryptor
        ${log-lib})

add_library(
        file_operation
        SHARED
        src/main/cpp/file_operation.cpp)
target_link_libraries(
        file_operation
        ${log-lib})




