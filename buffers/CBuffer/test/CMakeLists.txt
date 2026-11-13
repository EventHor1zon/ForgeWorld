

add_executable(test_cbuffer 
  test_cbuffer.c
)

target_link_libraries(
  test_cbuffer 
    PUBLIC 
  cbuffer 
  unity
  ptypes
)

add_test(
  NAME 
    test_cbuffers
  COMMAND
    test_cbuffer
)


