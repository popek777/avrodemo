#include <iostream>
#include <sstream>

#include "avro/Decoder.hh"
#include "avro/Encoder.hh"
#include "avro/Specific.hh"
#include "avro/Compiler.hh"
#include "avro/Generic.hh"

namespace {
struct SomeType {
  int idx{0};
  std::string name;
  double value{0.};
};

std::ostream &operator<<(std::ostream &os, const SomeType &obj) {
  os << '(' << obj.idx << ", " << obj.name << ", " << obj.value << ')';
  return os;
}
} // namespace

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
         "implemented in encoder/decoder (like in cereal library)\n"
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

void test_decode_generic_datatype_with_schema()
{
  std::cout
      << "====================================================================\\n"
         "=== encode generic datatype manually and decode with matching schema\n"
         "====================================================================\\n"
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

    constexpr const char* schemaText = 
R"({
    "type": "record",
    "name": "some_name_for_some_type",
    "fields" : [
        {"name": "some_id", "type": "int"},
        {"name": "some_name", "type" : "string"}
        {"name": "some_value", "type" : "double"}
    ]
})";
    std::istringstream iss(schemaText);
    avro::ValidSchema schema;
    avro::compileJsonSchema(iss, schema);
    avro::GenericDatum datum(schema);
    
    avro::decode(*d, datum);

    std::cout << "Type: " << datum.type() << std::endl;
    if (datum.type() != avro::AVRO_RECORD) {
      throw std::runtime_error{"should be record!"};
    }

    const avro::GenericRecord &record = datum.value<avro::GenericRecord>();
    std::cout << "Field-count: " << record.fieldCount() << std::endl;

    {
      const avro::GenericDatum &field0 = record.fieldAt(0);
      std::cout << "field0 type: " << field0.type()
                << ", value: " << field0.value<int>() << std::endl;
      dest.idx = field0.value<int>();
    }

    {
      const avro::GenericDatum &field1 = record.fieldAt(1);
      std::cout << "field1 type: " << field1.type()
                << ", value: " << field1.value<std::string>() << std::endl;
      dest.name = field1.value<std::string>();
    }

    {
      const avro::GenericDatum &field2 = record.fieldAt(2);
      std::cout << "field2 type: " << field2.type()
                << ", value: " << field2.value<double>() << std::endl;
      dest.value = field2.value<double>();
    }

    std::cout << "dest: " << dest << std::endl;
}
