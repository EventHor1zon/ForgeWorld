// Unity test of cbuffer module
//
//
//

#include <CBuffer.h>
#include <unity.h>
#include <stdint.h>
#include <string.h>

#define TEST_CBUFF_SIZE_BYTES 512UL
uint8_t buffer[TEST_CBUFF_SIZE_BYTES];

static CBuffer_Handle_t handle;


CBuffer_init_t valid_init = {
  .size = TEST_CBUFF_SIZE_BYTES, 
  .buffer = buffer, 
  .allow_ovr = false, 
  .sem = NULL
};


void setUp() {
  memset(buffer, 0, TEST_CBUFF_SIZE_BYTES);
}

void tearDown() {} //Nothing to do yet

void testCbuffCreateValid(void) 
{
  CBuff buff = cbuffer_create(&handle, &valid_init);
  
  TEST_ASSERT_NOT_NULL(buff);
  TEST_ASSERT_EQUAL_UINT32(buff->buffer_len, TEST_CBUFF_SIZE_BYTES);
  TEST_ASSERT_EQUAL_UINT8(buff->allow_overwrite, valid_init.allow_ovr);
}

void testCbufferPointersValidAtStart(void)
{
  CBuff buff = cbuffer_create(&handle, &valid_init);

  TEST_ASSERT_EQUAL_PTR(buff->read_ptr, buff->write_ptr);
  TEST_ASSERT_EQUAL_PTR(buff->read_ptr, buff->buffer_start);
  TEST_ASSERT_EQUAL_PTR(buff->write_ptr, buff->buffer_start);
}

void testCbufferCreateInvalidSize(void)
{
  CBuffer_init_t invalid_sz = {
    .size = 0,
    .buffer = buffer, 
    .allow_ovr = false, 
    .sem = NULL 
  };

  CBuff buff = cbuffer_create(&handle, &invalid_sz);

  TEST_ASSERT_NULL(buff);
}

void testCbufferCreateInvalidBuffer(void)
{

  CBuffer_init_t invalid_buff = {
    .size = TEST_CBUFF_SIZE_BYTES,
    .buffer = NULL, 
    .allow_ovr = false, 
    .sem = NULL 
  };

  CBuff buff = cbuffer_create(&handle, &invalid_buff);

  TEST_ASSERT_NULL(buff);
}

void testCbufferWriteOneByte(void)
{
  CBuff buff = cbuffer_create(&handle, &valid_init);
  uint8_t onebyte = 0x0A;
  uint32_t write_len = 1;
  cbuffer_write(buff, &onebyte, &write_len);
  TEST_ASSERT_EQUAL_UINT32(write_len, 1);
  TEST_ASSERT_EQUAL_UINT8(buffer[0], onebyte);
  TEST_ASSERT_EQUAL_PTR(buff->write_ptr, (void *)&buffer[1]);
}

void testCBufferWriteReadOneByte(void)
{
  CBuff buff = cbuffer_create(&handle, &valid_init);
  uint8_t onebyte = 0x1D;
  uint8_t anotherbyte = 0;
  uint32_t write_len = 1;
  uint32_t read_len = 1;
  cbuffer_write(buff, &onebyte, &write_len);
  cbuffer_read(buff, &anotherbyte, &read_len);

  TEST_ASSERT_EQUAL_UINT32(read_len, 1);
  TEST_ASSERT_EQUAL_UINT8(onebyte, anotherbyte);
  TEST_ASSERT_EQUAL_PTR(buff->read_ptr, buff->write_ptr);
}

void testCbufferWriteFullBuffer(void) 
{
  CBuff buff = cbuffer_create(&handle, &valid_init);

  uint32_t fourbytes = 0xAABBCCDD;
  uint32_t write_len = 4;
  for(uint32_t i=0; i < (TEST_CBUFF_SIZE_BYTES / 4); i++) {
    cbuffer_write(buff, &fourbytes, &write_len);
  }
  /** assert we have wrapped around and are back at the start **/
  TEST_ASSERT_EQUAL_UINT32(write_len, 4);
  TEST_ASSERT_EQUAL_PTR(buff->write_ptr, buff->buffer_start);
  TEST_ASSERT_EQUAL_UINT32(*(uint32_t *)&buffer[TEST_CBUFF_SIZE_BYTES-4], fourbytes);
}

void testCbufferWriteFullBufferPlusOneAllowed(void)
{
  valid_init.allow_ovr = true;
  CBuff buff = cbuffer_create(&handle, &valid_init);
  uint32_t fourbytes = 0xAABBCCDD;
  uint32_t write_len = 4;

  for(uint32_t i=0; i < (TEST_CBUFF_SIZE_BYTES / 4); i++) {
    cbuffer_write(buff, &fourbytes, &write_len);
  }
  TEST_ASSERT_EQUAL_UINT32(write_len, 4);
  fourbytes = 0xCAFEBABE;
  
  cbuffer_write(buff, &fourbytes, &write_len);
  TEST_ASSERT_EQUAL_UINT32(*(uint32_t *)&buffer[0], fourbytes);
}

void testCbufferOverwriteFailsWhenNotAllowed(void)
{
  CBuff buff = cbuffer_create(&handle, &valid_init);
  uint32_t fourbytes = 0xAABBCCDD;
  uint32_t write_len = 4;

  for(uint32_t i=0; i < (TEST_CBUFF_SIZE_BYTES / 4); i++) {
    cbuffer_write(buff, &fourbytes, &write_len);
  }
  TEST_ASSERT_EQUAL_UINT32(write_len, 4);
  fourbytes = 0xDEADBEEF;
  cbuffer_write(buff, &fourbytes, &write_len);
  TEST_ASSERT_EQUAL_UINT32(write_len, 0);
  TEST_ASSERT_EQUAL_UINT32(*(uint32_t *)&buffer[0], 0xAABBCCDD);
}

int main(void) {

  UNITY_BEGIN();
  RUN_TEST(testCbuffCreateValid);
  RUN_TEST(testCbufferPointersValidAtStart);
  RUN_TEST(testCbufferCreateInvalidSize);
  RUN_TEST(testCbufferWriteOneByte);
  RUN_TEST(testCBufferWriteReadOneByte);
  RUN_TEST(testCbufferWriteFullBuffer);
  RUN_TEST(testCbufferWriteFullBufferPlusOneAllowed);
  RUN_TEST(testCbufferOverwriteFailsWhenNotAllowed);
  return UNITY_END();
}
