# avrodemo
avro library (https://avro.apache.org/) demo app
based on official examples

# build & run demo app
./build.sh

# Q&A

- Is data strongly typed? If so how to work with different data types
  
  yes if data is generated by generator tool
  no if data is encoded/decoded using schema. Then all types matcihng schema can be encoded/decoded between each other

- Is there code generator tool like in protobufs to create C++ code from schema, or can it all be done in hand-written code?

  yes, and definatelly should be used when having complex data type (e.g. to avoid having manually implement codec_traits)
  It generates header with type(s) defined in schema and codec_traits for those types to be able to elegantly encode/decode types

- How to handle changes/versioning in protocol if we need to change format or add fields
  
  there is no versionning support.
  The only thing which might be usefull (though it is not versionig) is if type A is subset of type B
  then resolving decoded (https://avro.apache.org/docs/1.11.1/api/cpp/html/index.html#ReadingDifferentSchema)
  could be used to encode/decode between types.
  
  Any versionning must be implemented by application layer protocol.
  
