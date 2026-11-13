set(srcs
    "CBuffer.c"
)

set(includes "inc/")

add_library(cbuffer STATIC ${srcs})
target_include_directories(cbuffer PUBLIC ${includes})
target_link_libraries(cbuffer PRIVATE ptypes)

add_subdirectory(test)
