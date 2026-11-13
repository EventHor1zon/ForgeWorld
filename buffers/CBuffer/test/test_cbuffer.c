// Unity test of cbuffer module
//
//
//

#include <CBuffer.h>
#include <unity.h>
#include <stdint.h>


void setUp() {} //Nothing to do yet
void tearDown() {} //Nothing to do yet

void testCbuffCreateValid(void) 
{
  TEST_ASSERT_TRUE(1); 
}

int main(void) {

  UNITY_BEGIN();
  RUN_TEST(testCbuffCreateValid);
  return UNITY_END();
}
