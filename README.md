# running

`make run` will launch the JIT example

## test rig

Need an automated test rig to determine if assembled code is being properly generated from JIT.
1) test generation
2) test result

to start this, need a compiler and script that will generate assembly for a function for output by inspection.
(so do this)

./dump.js dumps the test() function in main
./run.js runs the code in main in qemu (then kills it, dumps output)