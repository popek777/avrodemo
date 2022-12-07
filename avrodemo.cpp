#include <iostream>

extern void test_encode_decode_generic_datatype_with_traits();
extern void test_decode_generic_datatype_with_schema();

int main(int argc, char **argv) {

  test_encode_decode_generic_datatype_with_traits();
  test_decode_generic_datatype_with_schema();

  return 0;
}
