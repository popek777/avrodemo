# avrodemo
avro library (https://avro.apache.org/) demo app


# notes
1. For some reason steps from here https://docs.conan.io/en/latest/developing_packages/package_dev_flow.html (to soruce/install/build) failed:

   as a solution slightly changed flow commands were used:

   conan source --source-folder tmp/source .
   
   conan install --install-folder tmp/install --output-folder tmp .
   
   conan build --source-folder tmp/source --install-folder tmp/install --build-folder tmp .
   
   
