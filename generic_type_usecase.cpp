#include <iostream>

#include "avro/Decoder.hh"
#include "avro/Encoder.hh"
#include "avro/Specific.hh"

struct SomeType {
  int idx{0};
  std::string name;
  double value{0.};
};

std::ostream &operator<<(std::ostream &os, const SomeType &obj) {
  os << '(' << obj.idx << ", " << obj.name << ", " << obj.value << ')';
  return os;
}

// trait to implemente encode/decode 'strategy' for custom type
namespace avro {
template <> struct codec_traits<SomeType> {
  static void encode(Encoder &e, const SomeType &obj) {
    avro::encode(e, obj.idx);
    avro::encode(e, obj.name);
    avro::encode(e, obj.value);
  }

  static void decode(Decoder &d, SomeType &obj) {
    avro::decode(d, obj.idx);
    avro::decode(d, obj.name);
    avro::decode(d, obj.value);
  }
};
} // namespace avro

void test_encode_decode_generic_datatype_with_traits() {

  std::cout
      << "==============================================================\n"
         "=== encode/decode generic datatype with using codec_traits ===\n"
         "==============================================================\n"
         "disadvantage:\n"
         "lot of boilerplate and must remember order of members "
         "encoding decoding\n"
         "Would be nicer to have singe func with & operator which would be "
         "then "
         "implemented in encoder/decoder (like in cereal library)"
      << std::endl;

  SomeType src{34, "lorem ipsum", 45.234};
  std::cout << "src: " << src << std::endl;

  std::unique_ptr<avro::OutputStream> out = avro::memoryOutputStream();
  avro::EncoderPtr e = avro::binaryEncoder();
  e->init(*out);

  avro::encode(*e, src);

  std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(*out);
  avro::DecoderPtr d = avro::binaryDecoder();
  d->init(*in);

  SomeType dest;
  avro::decode(*d, dest);

  std::cout << "dest: " << src << std::endl;
}

