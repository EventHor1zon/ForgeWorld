cmake_minimum_required(VERSION 3.20)

project(forgeworld LANGUAGES C ASM)

enable_testing()

# add_subdirectory(device_registry)
# add_subdirectory(api)
# add_subdirectory(drivers)
add_subdirectory(buffers/CBuffer)
add_subdirectory(port)
# add_subdirectory(communications)
# add_subdirectory(utilities)


add_library(unity 
  STATIC 
    thirdparty/Unity/src/unity.c
  )

target_include_directories(unity PUBLIC thirdparty/Unity/src)

