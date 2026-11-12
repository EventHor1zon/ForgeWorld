cmake_minimum_required(VERSION 3.20)

project(forgeworld)

add_subdirectory(device_registry)
add_subdirectory(api)
add_subdirectory(drivers)
add_subdirectory(buffers)
add_subdirectory(port)
add_subdirectory(communications)
add_subdirectory(utilities)

add_subdirectory(thirdparty/Unity)


