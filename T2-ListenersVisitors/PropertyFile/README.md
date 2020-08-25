# PropertyFile

A translation of the PropertyFile visitor and listener applications from T2-ListenersVisitors.pptx to C++ and the assignment format.

Authors: Braedy Kuzma (braedy@ualberta.ca), Deric Cheung (dacheung@ualberta.ca)

# Usage
## Building
### Linux
  1. Install git, java (only the runtime is necessary), and cmake (>= v3.0).
     - Until now, cmake has found the dependencies without issues. If you
       encounter an issue, let Braedy know and we can fix it.
  1. Make a directory that you intend to build the project in and change into
     that directory.
  1. Run `cmake <path-to-project>`.
  1. Run `make`.
  1. Done.

## Running

After building, use the following command to run the example.
```
./bin/pfile t.properties
```

