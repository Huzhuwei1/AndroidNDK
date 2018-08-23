cmake_minimum_required(VERSION 3.4.1)

add_library(
             jni

             SHARED
             src/main/jni/Jni.cpp)



target_link_libraries( # Specifies the target library.
                       jni

                       android
                       log
                        )