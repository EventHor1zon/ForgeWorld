
#include <Unity.h>
#include "CircularBuffer.h"
#include <stdint.h>

#define TEST_BUFFER_SIZE_BYTES 512

uint8_t buffer[TEST_BUFFER_SIZE_BYTES]= {0};

CBuffer_init_t init = {
  .size = TEST_BUFFER_SIZE_BYTES, 
  .allow_overwrite = 0, 
  .buffer = buffer, 
  .sem = NULL
};

CBuffer_Handle_t cbuff;
CBuff handle = &cbuff;

void test_cbuffer_create_null_handle(void)
{
    TEST_ASSERT_NULL(cbuffer_create(NULL, &init));
}

void test_cbuffer_create_null_args(void) {
    TEST_ASSERT_NULL(cbuffer_create(handle, NULL));
}

void test_cbuffer_create_zero_length(void) 
{
    CBuffer_init_t init_zero = init;
    init_zero.size = 0;
    TEST_ASSERT_NULL(cbuffer_create(handle, &init_zero));
}

void test_cbuffer_create_valid(void)
{
    TEST_ASSERT_NOT_NULL(cbuffer_create(handle, &init));
    TEST_ASSERT_EQUAL(cbuffer_available_space(handle), init.size));
    TEST_ASSERT_EQUAL(handle->buffer_start, init.buffer);
}







