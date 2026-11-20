

option(RTOS_TYPE "RTOS_TYPE" "")

if(RTOS_TYPE STREQUAL "FRERTOS")
  add_library(
    ptypes 
      STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/rtos_primitives/FreeRTOS_port.c
  )

  target_link_libraries(ptypes PRIVATE freertos)
else()
  add_library(
    ptypes
      STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/rtos_primitives/port_rtos.c
  )
endif()

target_include_directories(
  ptypes 
    INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/rtos_primitives/include/
)


